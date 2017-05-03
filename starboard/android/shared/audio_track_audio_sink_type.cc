// Copyright 2017 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "starboard/android/shared/audio_track_audio_sink_type.h"

#include <algorithm>
#include <deque>

#include "starboard/android/shared/jni_env_ext.h"
#include "starboard/android/shared/jni_utils.h"
#include "starboard/common/scoped_ptr.h"
#include "starboard/mutex.h"
#include "starboard/thread.h"

namespace starboard {
namespace android {
namespace shared {
namespace {

// Helper function to compute the size of the two valid starboard audio sample
// types.
size_t GetSampleSize(SbMediaAudioSampleType sample_type) {
  switch (sample_type) {
    case kSbMediaAudioSampleTypeFloat32:
      return sizeof(float);
    case kSbMediaAudioSampleTypeInt16:
      return sizeof(int16_t);
  }
  SB_NOTREACHED();
  return 0u;
}

int GetAudioFormatSampleType(SbMediaAudioSampleType sample_type) {
  switch (sample_type) {
    case kSbMediaAudioSampleTypeFloat32:
      // Android AudioFormat.ENCODING_PCM_FLOAT.
      return 4;
    case kSbMediaAudioSampleTypeInt16:
      // Android AudioFormat.ENCODING_PCM_16BIT.
      return 2;
  }
  SB_NOTREACHED();
  return 0u;
}

void* IncrementPointerByBytes(void* pointer, size_t offset) {
  return static_cast<uint8_t*>(pointer) + offset;
}

jbyteArray ByteArrayFromRaw(const void* data, int size) {
  return JniEnvExt::Get()->NewByteArrayFromRaw(static_cast<const jbyte*>(data),
                                               size);
}

jfloatArray FloatArrayFromRaw(const void* data, int size) {
  return JniEnvExt::Get()->NewFloatArrayFromRaw(
      static_cast<const jfloat*>(data), size);
}

class AudioTrackAudioSink : public SbAudioSinkPrivate {
 public:
  AudioTrackAudioSink(
      Type* type,
      int channels,
      int sampling_frequency_hz,
      SbMediaAudioSampleType sample_type,
      SbAudioSinkFrameBuffers frame_buffers,
      int frames_per_channel,
      SbAudioSinkUpdateSourceStatusFunc update_source_status_func,
      SbAudioSinkConsumeFramesFunc consume_frame_func,
      void* context);
  ~AudioTrackAudioSink() SB_OVERRIDE;

  bool IsType(Type* type) SB_OVERRIDE { return type_ == type; }
  void SetPlaybackRate(double playback_rate) SB_OVERRIDE {
    SB_DCHECK(playback_rate >= 0.0);
    if (playback_rate != 0.0 && playback_rate != 1.0) {
      SB_NOTIMPLEMENTED() << "TODO: Only playback rates of 0.0 and 1.0 are "
                             "currently supported.";
      playback_rate = (playback_rate > 0.0) ? 1.0 : 0.0;
    }
    ScopedLock lock(mutex_);
    playback_rate_ = playback_rate;
  }

 private:
  static void* ThreadEntryPoint(void* context);
  void AudioThreadFunc();

  Type* type_;
  int channels_;
  int sampling_frequency_hz_;
  SbMediaAudioSampleType sample_type_;
  void* frame_buffer_;
  int frames_per_channel_;
  SbAudioSinkUpdateSourceStatusFunc update_source_status_func_;
  SbAudioSinkConsumeFramesFunc consume_frame_func_;
  void* context_;
  int last_playback_head_position_;
  jobject j_audio_track_bridge_;

  volatile bool quit_;
  SbThread audio_out_thread_;

  starboard::Mutex mutex_;
  double playback_rate_;

  int written_frames_;
};

AudioTrackAudioSink::AudioTrackAudioSink(
    Type* type,
    int channels,
    int sampling_frequency_hz,
    SbMediaAudioSampleType sample_type,
    SbAudioSinkFrameBuffers frame_buffers,
    int frames_per_channel,
    SbAudioSinkUpdateSourceStatusFunc update_source_status_func,
    SbAudioSinkConsumeFramesFunc consume_frame_func,
    void* context)
    : type_(type),
      channels_(channels),
      sampling_frequency_hz_(sampling_frequency_hz),
      sample_type_(sample_type),
      frame_buffer_(frame_buffers[0]),
      frames_per_channel_(frames_per_channel),
      update_source_status_func_(update_source_status_func),
      consume_frame_func_(consume_frame_func),
      context_(context),
      last_playback_head_position_(0),
      j_audio_track_bridge_(NULL),
      quit_(false),
      audio_out_thread_(kSbThreadInvalid),
      playback_rate_(1.0f),
      written_frames_(0) {
  SB_DCHECK(update_source_status_func_);
  SB_DCHECK(consume_frame_func_);
  SB_DCHECK(frame_buffer_);
  SB_DCHECK(SbAudioSinkIsAudioSampleTypeSupported(sample_type));

  JniEnvExt* env = JniEnvExt::Get();
  jobject j_audio_track_bridge = env->CallStaticObjectMethodOrAbort(
      "foo/cobalt/media/AudioTrackBridge", "create",
      "(III)Lfoo/cobalt/media/AudioTrackBridge;",
      GetAudioFormatSampleType(sample_type_), sampling_frequency_hz_,
      channels_);
  j_audio_track_bridge_ = env->ConvertLocalRefToGlobalRef(j_audio_track_bridge);

  audio_out_thread_ = SbThreadCreate(
      0, kSbThreadPriorityRealTime, kSbThreadNoAffinity, true,
      "audio_track_audio_out", &AudioTrackAudioSink::ThreadEntryPoint, this);
  SB_DCHECK(SbThreadIsValid(audio_out_thread_));
}

AudioTrackAudioSink::~AudioTrackAudioSink() {
  quit_ = true;

  if (SbThreadIsValid(audio_out_thread_)) {
    SbThreadJoin(audio_out_thread_, NULL);
  }

  JniEnvExt* env = JniEnvExt::Get();
  if (j_audio_track_bridge_) {
    env->CallVoidMethodOrAbort(j_audio_track_bridge_, "release", "()V");
    env->DeleteGlobalRef(j_audio_track_bridge_);
    j_audio_track_bridge_ = NULL;
  }
}

// static
void* AudioTrackAudioSink::ThreadEntryPoint(void* context) {
  SB_DCHECK(context);
  AudioTrackAudioSink* sink = reinterpret_cast<AudioTrackAudioSink*>(context);
  sink->AudioThreadFunc();

  return NULL;
}

void AudioTrackAudioSink::AudioThreadFunc() {
  JniEnvExt* env = JniEnvExt::Get();
  env->CallVoidMethodOrAbort(j_audio_track_bridge_, "play", "()V");

  while (!quit_) {
    int playback_head_position = env->CallIntMethodOrAbort(
        j_audio_track_bridge_, "getPlaybackHeadPosition", "()I");
    int frames_consumed = playback_head_position - last_playback_head_position_;
    last_playback_head_position_ = playback_head_position;
    if (frames_consumed != 0) {
      consume_frame_func_(frames_consumed, context_);
      written_frames_ -= frames_consumed;
    }

    int frames_in_buffer;
    int offset_in_frames;
    bool is_playing;
    bool is_eos_reached;
    update_source_status_func_(&frames_in_buffer, &offset_in_frames,
                               &is_playing, &is_eos_reached, context_);

    bool is_playback_rate_zero = false;
    {
      ScopedLock lock(mutex_);
      is_playback_rate_zero = playback_rate_ == 0.0;
    }

    if (!is_playing || frames_in_buffer == 0 || is_playback_rate_zero) {
      continue;
    }

    int start_position =
        (offset_in_frames + written_frames_) % frames_per_channel_;
    int expected_written_frames = 0;
    if (frames_per_channel_ > offset_in_frames + written_frames_) {
      expected_written_frames =
          std::min(frames_per_channel_ - (offset_in_frames + written_frames_),
                   frames_in_buffer - written_frames_);
    } else {
      expected_written_frames = frames_in_buffer - written_frames_;
    }

    if (expected_written_frames == 0) {
      // It is possible that all the frames in buffer are written to the
      // soundcard, but those are not being consumed.
      continue;
    }
    SB_DCHECK(expected_written_frames > 0);

    if (sample_type_ == kSbMediaAudioSampleTypeFloat32) {
      int expected_written_size = expected_written_frames * channels_;
      ScopedLocalJavaRef<jfloatArray> j_buf(FloatArrayFromRaw(
          IncrementPointerByBytes(
              frame_buffer_,
              start_position * channels_ * GetSampleSize(sample_type_)),
          expected_written_size));
      jint written = env->CallIntMethodOrAbort(j_audio_track_bridge_, "write",
                                               "([F)I", j_buf.Get());
      SB_DCHECK(written >= 0);
      SB_DCHECK(written % channels_ == 0);
      written_frames_ += written / channels_;
    } else {
      SB_DCHECK(sample_type_ == kSbMediaAudioSampleTypeInt16);
      int expected_written_size =
          expected_written_frames * channels_ * GetSampleSize(sample_type_);
      ScopedLocalJavaRef<jbyteArray> j_buf(ByteArrayFromRaw(
          IncrementPointerByBytes(
              frame_buffer_,
              start_position * channels_ * GetSampleSize(sample_type_)),
          expected_written_size));
      jint written = env->CallIntMethodOrAbort(j_audio_track_bridge_, "write",
                                               "([B)I", j_buf.Get());
      SB_DCHECK(written >= 0);
      SB_DCHECK(written % (channels_ * GetSampleSize(sample_type_)) == 0);
      written_frames_ += written / (channels_ * GetSampleSize(sample_type_));
    }
  }
}

}  // namespace

SbAudioSink AudioTrackAudioSinkType::Create(
    int channels,
    int sampling_frequency_hz,
    SbMediaAudioSampleType audio_sample_type,
    SbMediaAudioFrameStorageType audio_frame_storage_type,
    SbAudioSinkFrameBuffers frame_buffers,
    int frames_per_channel,
    SbAudioSinkUpdateSourceStatusFunc update_source_status_func,
    SbAudioSinkConsumeFramesFunc consume_frames_func,
    void* context) {
  return new AudioTrackAudioSink(this, channels, sampling_frequency_hz,
                                 audio_sample_type, frame_buffers,
                                 frames_per_channel, update_source_status_func,
                                 consume_frames_func, context);
}

}  // namespace shared
}  // namespace android
}  // namespace starboard

namespace {
SbAudioSinkPrivate::Type* audio_track_audio_sink_type_;
}  // namespace

// static
void SbAudioSinkPrivate::PlatformInitialize() {
  SB_DCHECK(!audio_track_audio_sink_type_);
  audio_track_audio_sink_type_ =
      new starboard::android::shared::AudioTrackAudioSinkType;
  SetPrimaryType(audio_track_audio_sink_type_);
  EnableFallbackToStub();
}

// static
void SbAudioSinkPrivate::PlatformTearDown() {
  SB_DCHECK(audio_track_audio_sink_type_ == GetPrimaryType());
  SetPrimaryType(NULL);
  delete audio_track_audio_sink_type_;
  audio_track_audio_sink_type_ = NULL;
}
