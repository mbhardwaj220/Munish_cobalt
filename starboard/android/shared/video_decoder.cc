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

#include "starboard/android/shared/video_decoder.h"

#include <cmath>

#include "starboard/android/shared/application_android.h"
#include "starboard/android/shared/decode_target_internal.h"
#include "starboard/android/shared/jni_env_ext.h"
#include "starboard/android/shared/media_common.h"
#include "starboard/android/shared/video_window.h"
#include "starboard/android/shared/window_internal.h"
#include "starboard/decode_target.h"
#include "starboard/drm.h"
#include "starboard/memory.h"
#include "starboard/string.h"
#include "starboard/thread.h"

namespace starboard {
namespace android {
namespace shared {

namespace {

const jlong kDequeueTimeout = 0;
const SbMediaTime kOutputBufferWorkFailure = -1;
const SbTime kSbTimeNone = -1;

// Map an |SbMediaVideoCodec| into its corresponding mime type string.
const char* GetMimeTypeFromCodecType(const SbMediaVideoCodec type) {
  switch (type) {
    case kSbMediaVideoCodecNone:
      return NULL;
    case kSbMediaVideoCodecH264:
      return "video/avc";
    case kSbMediaVideoCodecH265:
      return "video/hevc";
    case kSbMediaVideoCodecMpeg2:
      return NULL;
    case kSbMediaVideoCodecTheora:
      return NULL;
    case kSbMediaVideoCodecVc1:
      return NULL;
    case kSbMediaVideoCodecVp10:
      return NULL;
    case kSbMediaVideoCodecVp8:
      return "video/x-vnd.on2.vp8";
    case kSbMediaVideoCodecVp9:
      return "video/x-vnd.on2.vp9";
  }
  return NULL;
}

}  // namespace

VideoDecoder::VideoDecoder(SbMediaVideoCodec video_codec,
                           SbPlayerOutputMode output_mode,
                           SbDecodeTargetProvider* decode_target_provider)
    : video_codec_(video_codec),
      host_(NULL),
      stream_ended_(false),
      error_occured_(false),
      decoder_thread_(kSbThreadInvalid),
      media_codec_bridge_(NULL),
      current_time_(kSbTimeNone),
      output_mode_(output_mode),
      decode_target_provider_(decode_target_provider),
      decode_target_(kSbDecodeTargetInvalid),
      frame_width_(0),
      frame_height_(0) {
  if (!InitializeCodec()) {
    SB_LOG(ERROR) << "Failed to initialize video decoder.";
    TeardownCodec();
  }
}

VideoDecoder::~VideoDecoder() {
  Reset();
  TeardownCodec();
  ClearVideoWindow();
}

void VideoDecoder::SetHost(Host* host) {
  SB_DCHECK(host != NULL);
  SB_DCHECK(host_ == NULL);
  host_ = host;
}

void VideoDecoder::WriteInputBuffer(const InputBuffer& input_buffer) {
  SB_DCHECK(event_queue_.Poll().type == kInvalid);
  SB_DCHECK(host_ != NULL);

  if (stream_ended_) {
    SB_LOG(ERROR) << "WriteInputFrame() was called after WriteEndOfStream().";
    return;
  }

  if (!SbThreadIsValid(decoder_thread_)) {
    decoder_thread_ =
        SbThreadCreate(0, kSbThreadPriorityHigh, kSbThreadNoAffinity, true,
                       "video_decoder", &VideoDecoder::ThreadEntryPoint, this);
    SB_DCHECK(SbThreadIsValid(decoder_thread_));
  }

  event_queue_.Put(Event(input_buffer));
}

void VideoDecoder::WriteEndOfStream() {
  SB_DCHECK(host_ != NULL);

  // We have to flush the decoder to decode the rest frames and to ensure that
  // Decode() is not called when the stream is ended.
  stream_ended_ = true;
  event_queue_.Put(Event(kWriteEndOfStream));
}

void VideoDecoder::Reset() {
  // Join the thread to ensure that all callbacks in process are finished.
  if (SbThreadIsValid(decoder_thread_)) {
    event_queue_.Put(Event(kReset));
    SbThreadJoin(decoder_thread_, NULL);
  }

  decoder_thread_ = kSbThreadInvalid;
  stream_ended_ = false;
}

bool VideoDecoder::InitializeCodec() {
  const char* mime = GetMimeTypeFromCodecType(video_codec_);
  if (!mime) {
    SB_LOG(ERROR) << "Mime type " << mime << " is not supported.";
  }

  // Setup the output surface object.  If we are in punch-out mode, target
  // the passed in Android video surface.  If we are in decode-to-texture
  // mode, create a surface from a new texture target and use that as the
  // output surface.
  jobject j_output_surface = NULL;
  switch (output_mode_) {
    case kSbPlayerOutputModePunchOut: {
      j_output_surface = GetVideoSurface();
      SB_DCHECK(j_output_surface);
    } break;
    case kSbPlayerOutputModeDecodeToTexture: {
      starboard::ScopedLock lock(decode_target_mutex_);
      // A width and height of (0, 0) is provided here because Android doesn't
      // actually allocate any memory into the texture at this time.  That is
      // done behind the scenes, the acquired texture is not actually backed
      // by texture data until updateTexImage() is called on it.
      decode_target_ = SbDecodeTargetAcquireFromProvider(
          decode_target_provider_, kSbDecodeTargetFormat1PlaneRGBA, 0, 0);
      if (!SbDecodeTargetIsValid(decode_target_)) {
        SB_LOG(ERROR) << "Could not acquire a decode target from provider.";
        return false;
      }
      j_output_surface = decode_target_->data->surface;
    } break;
    case kSbPlayerOutputModeInvalid: {
      SB_NOTREACHED();
    } break;
  }
  SB_DCHECK(j_output_surface);

  ANativeWindow* video_window = GetVideoWindow();
  SB_DCHECK(video_window);
  int width = ANativeWindow_getWidth(video_window);
  int height = ANativeWindow_getHeight(video_window);

  jobject j_media_crypto = NULL;
  media_codec_bridge_ = MediaCodecBridge::CreateVideoMediaCodecBridge(
      mime, width, height, j_output_surface, j_media_crypto);
  if (!media_codec_bridge_) {
    SB_LOG(ERROR) << "Failed to create video media codec bridge.";
    return false;
  }

  return true;
}

void VideoDecoder::TeardownCodec() {
  media_codec_bridge_.reset();

  starboard::ScopedLock lock(decode_target_mutex_);
  if (SbDecodeTargetIsValid(decode_target_)) {
    SbDecodeTargetReleaseToProvider(decode_target_provider_, decode_target_);
    decode_target_ = kSbDecodeTargetInvalid;
  }
}

// static
void* VideoDecoder::ThreadEntryPoint(void* context) {
  SB_DCHECK(context);
  VideoDecoder* decoder = static_cast<VideoDecoder*>(context);
  decoder->DecoderThreadFunc();
  return NULL;
}

void VideoDecoder::DecoderThreadFunc() {
  for (;;) {
    Event event = event_queue_.Get();
    if (event.type == kReset) {
      SB_LOG(INFO) << "Reset event occurred.";
      jint status = media_codec_bridge_->Flush();
      if (status != MEDIA_CODEC_OK) {
        SB_LOG(ERROR) << "Failed to flush video media codec.";
      }
      while (!pending_work_.empty()) {
        pending_work_.pop_front();
      }
      return;
    }
    if (error_occured_) {
      continue;
    }
    if (event.type == kWriteInputBuffer) {
      pending_work_.push_back(event.input_buffer);
      bool did_input = true;
      bool did_output = true;
      while (did_input || did_output) {
        did_input = ProcessOneInputBuffer();
        did_output = ProcessOneOutputBuffer();
      }
      host_->OnDecoderStatusUpdate(kNeedMoreInput, NULL);
    } else if (event.type == kWriteEndOfStream) {
      pending_work_.push_back(InputBufferOrEos(InputBufferOrEos::CreateEos()));
      host_->OnDecoderStatusUpdate(kBufferFull, VideoFrame::CreateEOSFrame());
    } else {
      SB_NOTREACHED();
    }
  }
}

bool VideoDecoder::ProcessOneInputBuffer() {
  if (pending_work_.empty()) {
    return false;
  }
  InputBufferOrEos input_buffer_or_eos = pending_work_.front();
  InputBuffer input_buffer = input_buffer_or_eos.input_buffer;
  bool is_eos = input_buffer_or_eos.is_eos;
  pending_work_.pop_front();
  SB_CHECK(media_codec_bridge_);

  DequeueInputResult dequeue_input_result =
      media_codec_bridge_->DequeueInputBuffer(kDequeueTimeout);
  if (dequeue_input_result.index < 0) {
    if (dequeue_input_result.status != MEDIA_CODEC_DEQUEUE_INPUT_AGAIN_LATER) {
      SB_LOG(ERROR) << "|dequeueInputBuffer| failed with status: "
                    << dequeue_input_result.status;
    }
    pending_work_.push_front(input_buffer_or_eos);
    return false;
  }
  ScopedJavaByteBuffer byte_buffer(
      media_codec_bridge_->GetInputBuffer(dequeue_input_result.index));
  if (!is_eos &&
      (byte_buffer.IsNull() || byte_buffer.capacity() < input_buffer.size())) {
    SB_LOG(ERROR) << "Unable to write to MediaCodec input buffer.";
    return false;
  }

  if (!is_eos) {
    byte_buffer.CopyInto(input_buffer.data(), input_buffer.size());
  }

  jint status = media_codec_bridge_->QueueInputBuffer(
      dequeue_input_result.index, /*offset=*/0,
      is_eos ? 0 : input_buffer.size(),
      ConvertSbMediaTimeToMicroseconds(input_buffer.pts()),
      is_eos ? BUFFER_FLAG_END_OF_STREAM : 0);
  if (status != MEDIA_CODEC_OK) {
    SB_LOG(ERROR) << "|queueInputBuffer| failed with status: " << status;
    return false;
  }
  if (is_eos) {
    status = media_codec_bridge_->Flush();
    if (status != MEDIA_CODEC_OK) {
      SB_LOG(ERROR) << "Failed to flush media codec.";
    }
    host_->OnDecoderStatusUpdate(kBufferFull, VideoFrame::CreateEOSFrame());
  }

  return true;
}

bool VideoDecoder::ProcessOneOutputBuffer() {
  SB_CHECK(media_codec_bridge_);
  DequeueOutputResult dequeue_output_result =
      media_codec_bridge_->DequeueOutputBuffer(kDequeueTimeout);
  if (dequeue_output_result.index < 0) {
    // Don't bother logging a try again later status, it will happen a lot.
    if (dequeue_output_result.status !=
        MEDIA_CODEC_DEQUEUE_OUTPUT_AGAIN_LATER) {
      SB_LOG(ERROR) << "|dequeueOutputBuffer| failed with status: "
                    << dequeue_output_result.status;
    }
    return false;
  }

  SbTime delay = (current_time_ == kSbTimeNone)
                     ? 0
                     : (dequeue_output_result.presentation_time_microseconds -
                        GetAdjustedCurrentTime());

  if (delay > 0) {
    SbThreadSleep(delay);
  }

  media_codec_bridge_->ReleaseOutputBuffer(dequeue_output_result.index, true);

  // Record the latest width/height of the decoded input.
  SurfaceDimensions output_dimensions =
      media_codec_bridge_->GetOutputDimensions();
  frame_width_ = output_dimensions.width;
  frame_height_ = output_dimensions.height;

  SbMediaTime out_pts = ConvertMicrosecondsToSbMediaTime(
      dequeue_output_result.presentation_time_microseconds);
  host_->OnDecoderStatusUpdate(kBufferFull,
                               VideoFrame::CreateEmptyFrame(out_pts));
  return true;
}

namespace {
void updateTexImage(jobject surface_texture) {
  JniEnvExt::Get()->CallVoidMethod(surface_texture, "updateTexImage", "()V");
}

void getTransformMatrix(jobject surface_texture, float* matrix4x4) {
  JniEnvExt* env = JniEnvExt::Get();

  jfloatArray java_array = env->NewFloatArray(16);
  SB_DCHECK(java_array);

  env->CallVoidMethod(surface_texture, "getTransformMatrix", "([F)V",
                      java_array);

  jfloat* array_values = env->GetFloatArrayElements(java_array, 0);
  SbMemoryCopy(matrix4x4, array_values, sizeof(float) * 16);

  env->DeleteLocalRef(java_array);
}

// Rounds the float to the nearest integer, and also does a DCHECK to make sure
// that the input float was already near an integer value.
int RoundToNearInteger(float x) {
  int rounded = static_cast<int>(x + 0.5f);
  SB_DCHECK(std::abs(static_cast<float>(x - rounded)) < 0.01f);
  return rounded;
}

// Converts a 4x4 matrix representing the texture coordinate transform into
// an equivalent rectangle representing the region within the texture where
// the pixel data is valid.  Note that the width and height of this region may
// be negative to indicate that that axis should be flipped.
void SetDecodeTargetContentRegionFromMatrix(
    SbDecodeTargetInfoContentRegion* content_region,
    int width,
    int height,
    const float* matrix4x4) {
  // Ensure that this matrix contains no rotations or shears.  In other words,
  // make sure that we can convert it to a decode target content region without
  // losing any information.
  SB_DCHECK(matrix4x4[1] == 0.0f);
  SB_DCHECK(matrix4x4[2] == 0.0f);
  SB_DCHECK(matrix4x4[3] == 0.0f);

  SB_DCHECK(matrix4x4[4] == 0.0f);
  SB_DCHECK(matrix4x4[6] == 0.0f);
  SB_DCHECK(matrix4x4[7] == 0.0f);

  SB_DCHECK(matrix4x4[8] == 0.0f);
  SB_DCHECK(matrix4x4[9] == 0.0f);
  SB_DCHECK(matrix4x4[10] == 1.0f);
  SB_DCHECK(matrix4x4[11] == 0.0f);

  SB_DCHECK(matrix4x4[14] == 0.0f);
  SB_DCHECK(matrix4x4[15] == 1.0f);

  float origin_x = matrix4x4[12];
  float origin_y = matrix4x4[13];

  float extent_x = matrix4x4[0] + matrix4x4[12];
  float extent_y = matrix4x4[5] + matrix4x4[13];

  SB_DCHECK(origin_y >= 0.0f);
  SB_DCHECK(origin_y <= 1.0f);
  SB_DCHECK(origin_x >= 0.0f);
  SB_DCHECK(origin_x <= 1.0f);
  SB_DCHECK(extent_x >= 0.0f);
  SB_DCHECK(extent_x <= 1.0f);
  SB_DCHECK(extent_y >= 0.0f);
  SB_DCHECK(extent_y <= 1.0f);

  // Flip the y-axis to match ContentRegion's coordinate system.
  origin_y = 1.0f - origin_y;
  extent_y = 1.0f - extent_y;

  content_region->left = RoundToNearInteger(origin_x * width);
  content_region->right = RoundToNearInteger(extent_x * width);

  // Note that in GL coordinates, the origin is the bottom and the extent
  // is the top.
  content_region->top = RoundToNearInteger(extent_y * height);
  content_region->bottom = RoundToNearInteger(origin_y * height);
}
}  // namespace

// When in decode-to-texture mode, this returns the current decoded video frame.
SbDecodeTarget VideoDecoder::GetCurrentDecodeTarget() {
  SB_DCHECK(output_mode_ == kSbPlayerOutputModeDecodeToTexture);
  // We must take a lock here since this function can be called from a
  // separate thread.
  starboard::ScopedLock lock(decode_target_mutex_);

  if (SbDecodeTargetIsValid(decode_target_)) {
    updateTexImage(decode_target_->data->surface_texture);

    float matrix4x4[16];
    getTransformMatrix(decode_target_->data->surface_texture, matrix4x4);
    SetDecodeTargetContentRegionFromMatrix(
        &decode_target_->data->info.planes[0].content_region, frame_width_,
        frame_height_, matrix4x4);

    // Take this opportunity to update the decode target's width and height.
    decode_target_->data->info.planes[0].width = frame_width_;
    decode_target_->data->info.planes[0].height = frame_height_;
    decode_target_->data->info.width = frame_width_;
    decode_target_->data->info.height = frame_height_;

    SbDecodeTarget out_decode_target = new SbDecodeTargetPrivate;
    out_decode_target->data = decode_target_->data;

    return out_decode_target;
  } else {
    return kSbDecodeTargetInvalid;
  }
}

}  // namespace shared
}  // namespace android
}  // namespace starboard

namespace starboard {
namespace shared {
namespace starboard {
namespace player {
namespace filter {

// static
VideoDecoder* VideoDecoder::Create(const Parameters& parameters) {
  ::starboard::android::shared::VideoDecoder* decoder =
      new ::starboard::android::shared::VideoDecoder(
          parameters.video_codec
#if SB_API_VERSION >= SB_PLAYER_DECODE_TO_TEXTURE_API_VERSION
          ,
          parameters.output_mode, parameters.decode_target_provider
#endif        // SB_API_VERSION >= SB_PLAYER_DECODE_TO_TEXTURE_API_VERSION
          );  // NOLINT(whitespace/parens)
  if (!decoder->is_valid()) {
    delete decoder;
    return NULL;
  }
  return decoder;
}

// static
bool VideoDecoder::OutputModeSupported(SbPlayerOutputMode output_mode,
                                       SbMediaVideoCodec codec,
                                       SbDrmSystem drm_system) {
  if (output_mode == kSbPlayerOutputModePunchOut) {
    return true;
  }

  if (output_mode == kSbPlayerOutputModeDecodeToTexture) {
    return !SbDrmSystemIsValid(drm_system);
  }

  return false;
}

}  // namespace filter
}  // namespace player
}  // namespace starboard
}  // namespace shared
}  // namespace starboard
