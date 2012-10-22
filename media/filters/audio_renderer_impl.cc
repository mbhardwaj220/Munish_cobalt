// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "media/filters/audio_renderer_impl.h"

#include <math.h>

#include <algorithm>

#include "base/bind.h"
#include "base/callback.h"
#include "base/callback_helpers.h"
#include "base/command_line.h"
#include "base/logging.h"
#include "media/audio/audio_util.h"
#include "media/base/demuxer_stream.h"
#include "media/base/media_switches.h"

namespace media {

AudioRendererImpl::AudioRendererImpl(media::AudioRendererSink* sink)
    : state_(kUninitialized),
      pending_read_(false),
      received_end_of_stream_(false),
      rendered_end_of_stream_(false),
      audio_time_buffered_(kNoTimestamp()),
      current_time_(kNoTimestamp()),
      bytes_per_frame_(0),
      stopped_(false),
      sink_(sink),
      underflow_disabled_(false),
      preroll_aborted_(false) {
}

void AudioRendererImpl::Play(const base::Closure& callback) {
  {
    base::AutoLock auto_lock(lock_);
    DCHECK_EQ(kPaused, state_);
    state_ = kPlaying;
    callback.Run();
  }

  if (stopped_)
    return;

  if (GetPlaybackRate() != 0.0f) {
    DoPlay();
  } else {
    DoPause();
  }
}

void AudioRendererImpl::DoPlay() {
  earliest_end_time_ = base::Time::Now();
  sink_->Play();
}

void AudioRendererImpl::Pause(const base::Closure& callback) {
  {
    base::AutoLock auto_lock(lock_);
    DCHECK(state_ == kPlaying || state_ == kUnderflow ||
           state_ == kRebuffering);
    pause_cb_ = callback;
    state_ = kPaused;

    // Pause only when we've completed our pending read.
    if (!pending_read_)
      base::ResetAndReturn(&pause_cb_).Run();
  }

  if (stopped_)
    return;

  DoPause();
}

void AudioRendererImpl::DoPause() {
  sink_->Pause(false);
}

void AudioRendererImpl::Flush(const base::Closure& callback) {
  decoder_->Reset(callback);
}

void AudioRendererImpl::Stop(const base::Closure& callback) {
  DCHECK(!callback.is_null());

  if (!stopped_) {
    sink_->Stop();
    stopped_ = true;
  }
  {
    base::AutoLock auto_lock(lock_);
    state_ = kStopped;
    algorithm_.reset(NULL);
    init_cb_.Reset();
    underflow_cb_.Reset();
    time_cb_.Reset();
  }

  callback.Run();
}

void AudioRendererImpl::Preroll(base::TimeDelta time,
                                const PipelineStatusCB& cb) {
  base::AutoLock auto_lock(lock_);
  DCHECK_EQ(kPaused, state_);
  DCHECK(!pending_read_) << "Pending read must complete before seeking";
  DCHECK(pause_cb_.is_null());
  DCHECK(preroll_cb_.is_null());
  state_ = kPrerolling;
  preroll_cb_ = cb;
  preroll_timestamp_ = time;

  // Throw away everything and schedule our reads.
  audio_time_buffered_ = kNoTimestamp();
  current_time_ = kNoTimestamp();
  received_end_of_stream_ = false;
  rendered_end_of_stream_ = false;
  preroll_aborted_ = false;

  // |algorithm_| will request more reads.
  algorithm_->FlushBuffers();

  if (stopped_)
    return;

  // Pause and flush the stream when we preroll to a new location.
  earliest_end_time_ = base::Time::Now();
  sink_->Pause(true);
}

void AudioRendererImpl::Initialize(const scoped_refptr<DemuxerStream>& stream,
                                   const AudioDecoderList& decoders,
                                   const PipelineStatusCB& init_cb,
                                   const StatisticsCB& statistics_cb,
                                   const base::Closure& underflow_cb,
                                   const TimeCB& time_cb,
                                   const base::Closure& ended_cb,
                                   const base::Closure& disabled_cb,
                                   const PipelineStatusCB& error_cb) {
  base::AutoLock auto_lock(lock_);
  DCHECK(stream);
  DCHECK(!decoders.empty());
  DCHECK_EQ(stream->type(), DemuxerStream::AUDIO);
  DCHECK(!init_cb.is_null());
  DCHECK(!statistics_cb.is_null());
  DCHECK(!underflow_cb.is_null());
  DCHECK(!time_cb.is_null());
  DCHECK(!ended_cb.is_null());
  DCHECK(!disabled_cb.is_null());
  DCHECK(!error_cb.is_null());
  DCHECK_EQ(kUninitialized, state_);

  init_cb_ = init_cb;
  statistics_cb_ = statistics_cb;
  underflow_cb_ = underflow_cb;
  time_cb_ = time_cb;
  ended_cb_ = ended_cb;
  disabled_cb_ = disabled_cb;
  error_cb_ = error_cb;

  scoped_ptr<AudioDecoderList> decoder_list(new AudioDecoderList(decoders));
  InitializeNextDecoder(stream, decoder_list.Pass());
}

void AudioRendererImpl::InitializeNextDecoder(
    const scoped_refptr<DemuxerStream>& demuxer_stream,
    scoped_ptr<AudioDecoderList> decoders) {
  lock_.AssertAcquired();
  DCHECK(!decoders->empty());

  scoped_refptr<AudioDecoder> decoder = decoders->front();
  decoders->pop_front();

  DCHECK(decoder);
  decoder_ = decoder;

  base::AutoUnlock auto_unlock(lock_);
  decoder->Initialize(
      demuxer_stream,
      base::Bind(&AudioRendererImpl::OnDecoderInitDone, this,
                 demuxer_stream,
                 base::Passed(&decoders)),
      statistics_cb_);
}

void AudioRendererImpl::OnDecoderInitDone(
    const scoped_refptr<DemuxerStream>& demuxer_stream,
    scoped_ptr<AudioDecoderList> decoders,
    PipelineStatus status) {
  base::AutoLock auto_lock(lock_);

  if (state_ == kStopped) {
    DCHECK(stopped_);
    return;
  }

  if (!decoders->empty() && status == DECODER_ERROR_NOT_SUPPORTED) {
    InitializeNextDecoder(demuxer_stream, decoders.Pass());
    return;
  }

  if (status != PIPELINE_OK) {
    base::ResetAndReturn(&init_cb_).Run(status);
    return;
  }

  // We're all good! Continue initializing the rest of the audio renderer based
  // on the decoder format.

  ChannelLayout channel_layout = decoder_->channel_layout();
  int channels = ChannelLayoutToChannelCount(channel_layout);
  int bits_per_channel = decoder_->bits_per_channel();
  int sample_rate = decoder_->samples_per_second();
  // TODO(vrk): Add method to AudioDecoder to compute bytes per frame.
  bytes_per_frame_ = channels * bits_per_channel / 8;

  algorithm_.reset(new AudioRendererAlgorithm());
  if (!algorithm_->ValidateConfig(channels, sample_rate, bits_per_channel)) {
    base::ResetAndReturn(&init_cb_).Run(PIPELINE_ERROR_INITIALIZATION_FAILED);
    return;
  }

  algorithm_->Initialize(
      channels, sample_rate, bits_per_channel, 0.0f,
      base::Bind(&AudioRendererImpl::ScheduleRead_Locked, this));

  int buffer_size = GetHighLatencyOutputBufferSize(sample_rate);
  AudioParameters::Format format = AudioParameters::AUDIO_PCM_LINEAR;

  // On Windows and Mac we can use the low latency pipeline because they provide
  // accurate and smooth delay information.  On other platforms like Linux there
  // are jitter issues.
  // TODO(dalecurtis): Fix bugs: http://crbug.com/138098 http://crbug.com/32757
#if defined(OS_WIN) || defined(OS_MAC)
  const CommandLine* cmd_line = CommandLine::ForCurrentProcess();
  // Either AudioOutputResampler or renderer side mixing must be enabled to use
  // the low latency pipeline.
  if (!cmd_line->HasSwitch(switches::kDisableRendererSideMixing) ||
      !cmd_line->HasSwitch(switches::kDisableAudioOutputResampler)) {
    // There are two cases here:
    //
    // 1. Renderer side mixing is enabled and the buffer size is actually
    //    controlled by the size of the AudioBus provided to Render().  In this
    //    case the buffer size below is ignored.
    //
    // 2. Renderer side mixing is disabled and AudioOutputResampler on the
    //    browser side is rebuffering to the hardware size on the fly.
    //
    // In the second case we need to choose a a buffer size small enough that
    // the decoder can fulfill the high frequency low latency audio callbacks,
    // but not so small that it's less than the hardware buffer size (or we'll
    // run into issues since the shared memory sync is non-blocking).
    //
    // The buffer size below is arbitrarily the same size used by Pepper Flash
    // for consistency.  Since renderer side mixing is only disabled for debug
    // purposes it's okay that this buffer size might lead to jitter since it's
    // not a multiple of the hardware buffer size.
    format = AudioParameters::AUDIO_PCM_LOW_LATENCY;
    buffer_size = 2048;
  }
#endif

  audio_parameters_ = AudioParameters(
      format, channel_layout, sample_rate, bits_per_channel, buffer_size);

  sink_->Initialize(audio_parameters_, this);
  sink_->Start();

  state_ = kPaused;
  base::ResetAndReturn(&init_cb_).Run(PIPELINE_OK);
}

void AudioRendererImpl::ResumeAfterUnderflow(bool buffer_more_audio) {
  base::AutoLock auto_lock(lock_);
  if (state_ == kUnderflow) {
    // The "&& preroll_aborted_" is a hack. If preroll is aborted, then we
    // shouldn't even reach the kUnderflow state to begin with. But for now
    // we're just making sure that the audio buffer capacity (i.e. the
    // number of bytes that need to be buffered for preroll to complete)
    // does not increase due to an aborted preroll.
    // TODO(vrk): Fix this bug correctly! (crbug.com/151352)
    if (buffer_more_audio && !preroll_aborted_)
      algorithm_->IncreaseQueueCapacity();

    state_ = kRebuffering;
  }
}

void AudioRendererImpl::SetVolume(float volume) {
  if (stopped_)
    return;
  sink_->SetVolume(volume);
}

AudioRendererImpl::~AudioRendererImpl() {
  // Stop() should have been called and |algorithm_| should have been destroyed.
  DCHECK(state_ == kUninitialized || state_ == kStopped);
  DCHECK(!algorithm_.get());
}

void AudioRendererImpl::DecodedAudioReady(AudioDecoder::Status status,
                                          const scoped_refptr<Buffer>& buffer) {
  base::AutoLock auto_lock(lock_);
  DCHECK(state_ == kPaused || state_ == kPrerolling || state_ == kPlaying ||
         state_ == kUnderflow || state_ == kRebuffering || state_ == kStopped);

  CHECK(pending_read_);
  pending_read_ = false;

  if (status == AudioDecoder::kAborted) {
    HandleAbortedReadOrDecodeError(false);
    return;
  }

  if (status == AudioDecoder::kDecodeError) {
    HandleAbortedReadOrDecodeError(true);
    return;
  }

  DCHECK_EQ(status, AudioDecoder::kOk);
  DCHECK(buffer);

  if (buffer->IsEndOfStream()) {
    received_end_of_stream_ = true;

    // Transition to kPlaying if we are currently handling an underflow since
    // no more data will be arriving.
    if (state_ == kUnderflow || state_ == kRebuffering)
      state_ = kPlaying;
  }

  switch (state_) {
    case kUninitialized:
      NOTREACHED();
      return;
    case kPaused:
      if (!buffer->IsEndOfStream())
        algorithm_->EnqueueBuffer(buffer);
      DCHECK(!pending_read_);
      base::ResetAndReturn(&pause_cb_).Run();
      return;
    case kPrerolling:
      if (IsBeforePrerollTime(buffer)) {
        ScheduleRead_Locked();
        return;
      }
      if (!buffer->IsEndOfStream()) {
        algorithm_->EnqueueBuffer(buffer);
        if (!algorithm_->IsQueueFull())
          return;
      }
      state_ = kPaused;
      base::ResetAndReturn(&preroll_cb_).Run(PIPELINE_OK);
      return;
    case kPlaying:
    case kUnderflow:
    case kRebuffering:
      if (!buffer->IsEndOfStream())
        algorithm_->EnqueueBuffer(buffer);
      return;
    case kStopped:
      return;
  }
}

void AudioRendererImpl::ScheduleRead_Locked() {
  lock_.AssertAcquired();
  if (pending_read_ || state_ == kPaused)
    return;
  pending_read_ = true;
  decoder_->Read(base::Bind(&AudioRendererImpl::DecodedAudioReady, this));
}

void AudioRendererImpl::SetPlaybackRate(float playback_rate) {
  DCHECK_LE(0.0f, playback_rate);

  if (!stopped_) {
    // We have two cases here:
    // Play: GetPlaybackRate() == 0.0 && playback_rate != 0.0
    // Pause: GetPlaybackRate() != 0.0 && playback_rate == 0.0
    if (GetPlaybackRate() == 0.0f && playback_rate != 0.0f) {
      DoPlay();
    } else if (GetPlaybackRate() != 0.0f && playback_rate == 0.0f) {
      // Pause is easy, we can always pause.
      DoPause();
    }
  }

  base::AutoLock auto_lock(lock_);
  algorithm_->SetPlaybackRate(playback_rate);
}

float AudioRendererImpl::GetPlaybackRate() {
  base::AutoLock auto_lock(lock_);
  return algorithm_->playback_rate();
}

bool AudioRendererImpl::IsBeforePrerollTime(
    const scoped_refptr<Buffer>& buffer) {
  return (state_ == kPrerolling) && buffer && !buffer->IsEndOfStream() &&
      (buffer->GetTimestamp() + buffer->GetDuration()) < preroll_timestamp_;
}

int AudioRendererImpl::Render(AudioBus* audio_bus,
                              int audio_delay_milliseconds) {
  if (stopped_ || GetPlaybackRate() == 0.0f) {
    // Output silence if stopped.
    audio_bus->Zero();
    return 0;
  }

  // Adjust the playback delay.
  base::TimeDelta request_delay =
      base::TimeDelta::FromMilliseconds(audio_delay_milliseconds);

  // Finally we need to adjust the delay according to playback rate.
  if (GetPlaybackRate() != 1.0f) {
    request_delay = base::TimeDelta::FromMicroseconds(
        static_cast<int64>(ceil(request_delay.InMicroseconds() *
                                GetPlaybackRate())));
  }

  int bytes_per_frame = audio_parameters_.GetBytesPerFrame();

  const int buf_size = audio_bus->frames() * bytes_per_frame;
  scoped_array<uint8> buf(new uint8[buf_size]);

  int frames_filled = FillBuffer(buf.get(), audio_bus->frames(), request_delay);
  int bytes_filled = frames_filled * bytes_per_frame;
  DCHECK_LE(bytes_filled, buf_size);
  UpdateEarliestEndTime(bytes_filled, request_delay, base::Time::Now());

  // Deinterleave audio data into the output bus.
  audio_bus->FromInterleaved(
      buf.get(), frames_filled, audio_parameters_.bits_per_sample() / 8);

  return frames_filled;
}

uint32 AudioRendererImpl::FillBuffer(uint8* dest,
                                     uint32 requested_frames,
                                     const base::TimeDelta& playback_delay) {
  base::TimeDelta current_time = kNoTimestamp();
  base::TimeDelta max_time = kNoTimestamp();

  size_t frames_written = 0;
  base::Closure underflow_cb;
  {
    base::AutoLock auto_lock(lock_);

    if (state_ == kRebuffering && algorithm_->IsQueueFull())
      state_ = kPlaying;

    // Mute audio by returning 0 when not playing.
    if (state_ != kPlaying) {
      // TODO(scherkus): To keep the audio hardware busy we write at most 8k of
      // zeros.  This gets around the tricky situation of pausing and resuming
      // the audio IPC layer in Chrome.  Ideally, we should return zero and then
      // the subclass can restart the conversation.
      //
      // This should get handled by the subclass http://crbug.com/106600
      const uint32 kZeroLength = 8192;
      size_t zeros_to_write =
          std::min(kZeroLength, requested_frames * bytes_per_frame_);
      memset(dest, 0, zeros_to_write);
      return zeros_to_write / bytes_per_frame_;
    }

    // We use the following conditions to determine end of playback:
    //   1) Algorithm can not fill the audio callback buffer
    //   2) We received an end of stream buffer
    //   3) We haven't already signalled that we've ended
    //   4) Our estimated earliest end time has expired
    //
    // TODO(enal): we should replace (4) with a check that the browser has no
    // more audio data or at least use a delayed callback.
    //
    // We use the following conditions to determine underflow:
    //   1) Algorithm can not fill the audio callback buffer
    //   2) We have NOT received an end of stream buffer
    //   3) We are in the kPlaying state
    //
    // Otherwise fill the buffer with whatever data we can send to the device.
    if (!algorithm_->CanFillBuffer() && received_end_of_stream_ &&
        !rendered_end_of_stream_ && base::Time::Now() >= earliest_end_time_) {
      rendered_end_of_stream_ = true;
      ended_cb_.Run();
    } else if (!algorithm_->CanFillBuffer() && !received_end_of_stream_ &&
               state_ == kPlaying && !underflow_disabled_) {
      state_ = kUnderflow;
      underflow_cb = underflow_cb_;
    } else if (algorithm_->CanFillBuffer()) {
      frames_written = algorithm_->FillBuffer(dest, requested_frames);
      DCHECK_GT(frames_written, 0u);
    } else {
      // We can't write any data this cycle. For example, we may have
      // sent all available data to the audio device while not reaching
      // |earliest_end_time_|.
    }

    // The |audio_time_buffered_| is the ending timestamp of the last frame
    // buffered at the audio device. |playback_delay| is the amount of time
    // buffered at the audio device. The current time can be computed by their
    // difference.
    if (audio_time_buffered_ != kNoTimestamp()) {
      base::TimeDelta previous_time = current_time_;
      current_time_ = audio_time_buffered_ - playback_delay;

      // Time can change in one of two ways:
      //   1) The time of the audio data at the audio device changed, or
      //   2) The playback delay value has changed
      //
      // We only want to set |current_time| (and thus execute |time_cb_|) if
      // time has progressed and we haven't signaled end of stream yet.
      //
      // Why? The current latency of the system results in getting the last call
      // to FillBuffer() later than we'd like, which delays firing the 'ended'
      // event, which delays the looping/trigging performance of short sound
      // effects.
      //
      // TODO(scherkus): revisit this and switch back to relying on playback
      // delay after we've revamped our audio IPC subsystem.
      if (current_time_ > previous_time && !rendered_end_of_stream_) {
        current_time = current_time_;
      }
    }

    // The call to FillBuffer() on |algorithm_| has increased the amount of
    // buffered audio data. Update the new amount of time buffered.
    max_time = algorithm_->GetTime();
    audio_time_buffered_ = max_time;
  }

  if (current_time != kNoTimestamp() && max_time != kNoTimestamp()) {
    time_cb_.Run(current_time, max_time);
  }

  if (!underflow_cb.is_null())
    underflow_cb.Run();

  return frames_written;
}

void AudioRendererImpl::UpdateEarliestEndTime(int bytes_filled,
                                              base::TimeDelta request_delay,
                                              base::Time time_now) {
  if (bytes_filled != 0) {
    base::TimeDelta predicted_play_time = ConvertToDuration(bytes_filled);
    float playback_rate = GetPlaybackRate();
    if (playback_rate != 1.0f) {
      predicted_play_time = base::TimeDelta::FromMicroseconds(
          static_cast<int64>(ceil(predicted_play_time.InMicroseconds() *
                                  playback_rate)));
    }
    earliest_end_time_ =
        std::max(earliest_end_time_,
                 time_now + request_delay + predicted_play_time);
  }
}

base::TimeDelta AudioRendererImpl::ConvertToDuration(int bytes) {
  int bytes_per_second = audio_parameters_.GetBytesPerSecond();
  CHECK(bytes_per_second);
  return base::TimeDelta::FromMicroseconds(
      base::Time::kMicrosecondsPerSecond * bytes / bytes_per_second);
}

void AudioRendererImpl::OnRenderError() {
  disabled_cb_.Run();
}

void AudioRendererImpl::DisableUnderflowForTesting() {
  underflow_disabled_ = true;
}

void AudioRendererImpl::HandleAbortedReadOrDecodeError(bool is_decode_error) {
  PipelineStatus status = is_decode_error ? PIPELINE_ERROR_DECODE : PIPELINE_OK;
  switch (state_) {
    case kUninitialized:
      NOTREACHED();
      return;
    case kPaused:
      if (status != PIPELINE_OK)
        error_cb_.Run(status);
      base::ResetAndReturn(&pause_cb_).Run();
      return;
    case kPrerolling:
      // This is a signal for abort if it's not an error.
      preroll_aborted_ = !is_decode_error;
      state_ = kPaused;
      base::ResetAndReturn(&preroll_cb_).Run(status);
      return;
    case kPlaying:
    case kUnderflow:
    case kRebuffering:
    case kStopped:
      if (status != PIPELINE_OK)
        error_cb_.Run(status);
      return;
  }
}

}  // namespace media
