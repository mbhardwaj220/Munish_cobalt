// Copyright 2016 Google Inc. All Rights Reserved.
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

#ifndef STARBOARD_SHARED_STARBOARD_PLAYER_FILTER_VIDEO_RENDERER_INTERNAL_H_
#define STARBOARD_SHARED_STARBOARD_PLAYER_FILTER_VIDEO_RENDERER_INTERNAL_H_

#include <list>

#include "starboard/atomic.h"
#include "starboard/common/ref_counted.h"
#include "starboard/common/scoped_ptr.h"
#include "starboard/log.h"
#include "starboard/media.h"
#include "starboard/mutex.h"
#include "starboard/shared/internal_only.h"
#include "starboard/shared/starboard/player/filter/media_time_provider.h"
#include "starboard/shared/starboard/player/filter/video_decoder_internal.h"
#include "starboard/shared/starboard/player/filter/video_frame_internal.h"
#include "starboard/shared/starboard/player/filter/video_render_algorithm.h"
#include "starboard/shared/starboard/player/filter/video_renderer_internal.h"
#include "starboard/shared/starboard/player/filter/video_renderer_sink.h"
#include "starboard/shared/starboard/player/input_buffer_internal.h"
#include "starboard/shared/starboard/player/job_queue.h"
#include "starboard/time.h"

namespace starboard {
namespace shared {
namespace starboard {
namespace player {
namespace filter {

// A class that sits in between the video decoder, the video sink and the
// pipeline to coordinate data transfer between these parties.
class VideoRenderer : JobQueue::JobOwner {
 public:
  typedef VideoDecoder::ErrorCB ErrorCB;
  typedef std::function<void()> PrerolledCB;
  typedef std::function<void()> EndedCB;

  // All of the functions are called on the PlayerWorker thread unless marked
  // otherwise.
  VideoRenderer(scoped_ptr<VideoDecoder> decoder,
                MediaTimeProvider* media_time_provider,
                scoped_ptr<VideoRenderAlgorithm> algorithm,
                scoped_refptr<VideoRendererSink> sink);
  ~VideoRenderer();

  void Initialize(const ErrorCB& error_cb,
                  const PrerolledCB& prerolled_cb,
                  const EndedCB& ended_cb);
  int GetDroppedFrames() const { return algorithm_->GetDroppedFrames(); }

  void WriteSample(const scoped_refptr<InputBuffer>& input_buffer);
  void WriteEndOfStream();

  void Seek(SbTime seek_to_time);

  bool IsEndOfStreamWritten() const { return end_of_stream_written_.load(); }
  bool CanAcceptMoreData() const;

  // Both of the following two functions can be called on any threads.
  void SetBounds(int z_index, int x, int y, int width, int height);
  SbDecodeTarget GetCurrentDecodeTarget();

 private:
  typedef std::list<scoped_refptr<VideoFrame>> Frames;

  // Both of the following two functions can be called on any threads.
  void OnDecoderStatus(VideoDecoder::Status status,
                       const scoped_refptr<VideoFrame>& frame);
  void Render(VideoRendererSink::DrawFrameCB draw_frame_cb);
  void OnSeekTimeout();

  MediaTimeProvider* const media_time_provider_;
  scoped_ptr<VideoRenderAlgorithm> algorithm_;
  scoped_refptr<VideoRendererSink> sink_;
  scoped_ptr<VideoDecoder> decoder_;

  PrerolledCB prerolled_cb_;
  EndedCB ended_cb_;

  SbTimeMonotonic absolute_time_of_first_input_ = 0;
  // Our owner will attempt to seek to time 0 when playback begins.  In
  // general, seeking could require a full reset of the underlying decoder on
  // some platforms, so we make an effort to improve playback startup
  // performance by keeping track of whether we already have a fresh decoder,
  // and can thus avoid doing a full reset.
  bool first_input_written_ = false;
  atomic_bool end_of_stream_written_;
  atomic_bool ended_cb_called_;

  atomic_bool need_more_input_;
  atomic_bool seeking_;
  SbTime seeking_to_time_ = 0;

  atomic_int32_t number_of_frames_;
  Mutex frames_mutex_;
  Frames frames_;
};

}  // namespace filter
}  // namespace player
}  // namespace starboard
}  // namespace shared
}  // namespace starboard

#endif  // STARBOARD_SHARED_STARBOARD_PLAYER_FILTER_VIDEO_RENDERER_INTERNAL_H_
