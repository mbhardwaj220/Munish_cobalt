/*
 * Copyright 2012 Google Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "shell_buffer_factory.h"

#include "base/logging.h"
#include "base/stringprintf.h"

namespace media {

ShellBufferFactory* ShellBufferFactory::instance_ = NULL;

// static
void ShellBufferFactory::Initialize() {
  // safe to call multiple times
  if (!instance_) {
    instance_ = new ShellBufferFactory();
  }
}

// static
scoped_refptr<DecoderBuffer> ShellBufferFactory::GetVideoDecoderBuffer() {
  DCHECK(instance_);
  base::AutoLock lock(instance_->lock_);
  scoped_refptr<DecoderBuffer> video_buffer;
  // check for available free buffer first
  if (instance_->free_video_buffers_list_.size()) {
    video_buffer = instance_->free_video_buffers_list_.front();
    instance_->free_video_buffers_list_.pop_front();
  } else {
    // allocate new buffer and set a handle
    video_buffer = new DecoderBuffer(ShellVideoDecoderBufferMaxSize);
    video_buffer->SetHandle(++instance_->buffer_handle_counter_);
    if (instance_->allocated_video_buffers_map_.size() >=
        ShellMaxVideoDecoderBufferCount) {
      DLOG(WARNING) << base::StringPrintf(
          "allocating excess video DecoderBuffer, total count now: %d",
          instance_->allocated_video_buffers_map_.size() + 1);
    }
  }
  DCHECK(video_buffer);
  // store buffer in allocated map
  instance_->allocated_video_buffers_map_[video_buffer->GetHandle()] =
      video_buffer;
  return video_buffer;
}

// static
void ShellBufferFactory::ReturnVideoDecoderBuffer(
    scoped_refptr<DecoderBuffer> video_buffer) {
  DCHECK(instance_);
  base::AutoLock lock(instance_->lock_);
  DecoderBufferMap::iterator it = instance_->allocated_video_buffers_map_.find(
      video_buffer->GetHandle());
  // must always find it
  DCHECK(it != instance_->allocated_video_buffers_map_.end());
  // remove from allocated map
  instance_->allocated_video_buffers_map_.erase(it);
  int total_video_buffers = instance_->free_video_buffers_list_.size() +
      instance_->allocated_video_buffers_map_.size();
  // add to free list if we aren't over-allocated
  if (total_video_buffers < ShellMaxVideoDecoderBufferCount) {
    instance_->free_video_buffers_list_.push_back(video_buffer);
  } else {
    DLOG(WARNING) << base::StringPrintf(
        "freeing excess video DecoderBuffer, total count now: %d",
        total_video_buffers);
  }
}

// static
scoped_refptr<DecoderBuffer> ShellBufferFactory::GetAudioDecoderBuffer() {
  DCHECK(instance_);
  base::AutoLock lock(instance_->lock_);
  scoped_refptr<DecoderBuffer> audio_buffer;
  // check for available free buffer first
  if (instance_->free_audio_buffers_list_.size()) {
    audio_buffer = instance_->free_audio_buffers_list_.front();
    instance_->free_audio_buffers_list_.pop_front();
  } else {
    // allocate new buffer and set a handle
    audio_buffer = new DecoderBuffer(ShellAudioDecoderBufferMaxSize);
    audio_buffer->SetHandle(++instance_->buffer_handle_counter_);
    if (instance_->allocated_audio_buffers_map_.size() >=
        ShellMaxAudioDecoderBufferCount) {
      DLOG(WARNING) << base::StringPrintf(
          "allocating excess audio DecoderBuffer, total count now: %d",
          instance_->allocated_audio_buffers_map_.size() + 1);
    }
  }
  DCHECK(audio_buffer);
  // store buffer in allocated map
  instance_->allocated_audio_buffers_map_[audio_buffer->GetHandle()] =
      audio_buffer;
  return audio_buffer;
}

// static
void ShellBufferFactory::ReturnAudioDecoderBuffer(
    scoped_refptr<DecoderBuffer> audio_buffer) {
  DCHECK(instance_);
  base::AutoLock lock(instance_->lock_);
  DecoderBufferMap::iterator it = instance_->allocated_audio_buffers_map_.find(
      audio_buffer->GetHandle());
  // must always find it
  DCHECK(it != instance_->allocated_audio_buffers_map_.end());
  // remove from allocated map
  instance_->allocated_audio_buffers_map_.erase(it);
  // add to free list if we aren't over-allocated
  int total_audio_buffers = instance_->free_audio_buffers_list_.size() +
      instance_->allocated_audio_buffers_map_.size();
  if (total_audio_buffers < ShellMaxAudioDecoderBufferCount) {
    instance_->free_audio_buffers_list_.push_back(audio_buffer);
  } else {
    DLOG(WARNING) << base::StringPrintf(
        "freeing excess audio DecoderBuffer, total count now: %d",
        total_audio_buffers);
  }
}

// static
bool ShellBufferFactory::IsNearDecoderBufferOverflow() {
  base::AutoLock lock(instance_->lock_);
  // return true if we are down to only one buffer in either audio
  // or video max buffer counts
  return (instance_->free_video_buffers_list_.size() +
          instance_->allocated_video_buffers_map_.size() >
          ShellMaxVideoDecoderBufferCount - 1) ||
         (instance_->free_audio_buffers_list_.size() +
          instance_->allocated_audio_buffers_map_.size() >
          ShellMaxAudioDecoderBufferCount - 1);

}

// static
void ShellBufferFactory::Terminate() {
  delete instance_;
  instance_ = NULL;
}

ShellBufferFactory::ShellBufferFactory() {
  // no-op
}

ShellBufferFactory::~ShellBufferFactory() {
  base::AutoLock lock(lock_);
  // should have already had all buffers returned
  DCHECK_EQ(allocated_audio_buffers_map_.size(), 0);
  DCHECK_EQ(allocated_video_buffers_map_.size(), 0);
  // explicitly wipe pointers, likely to happen on list dtor anyway but
  // just to be absolutely sure..
  free_audio_buffers_list_.clear();
  free_video_buffers_list_.clear();
}

}  // namespace media
