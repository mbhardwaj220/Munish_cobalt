/*
 * Copyright 2015 Google Inc. All Rights Reserved.
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

#include "cobalt/dom/media_source.h"

#include <algorithm>
#include <limits>
#include <vector>

#include "base/hash_tables.h"
#include "base/lazy_instance.h"
#include "base/logging.h"
#include "base/string_split.h"
#include "base/string_util.h"
#include "cobalt/dom/event.h"

namespace cobalt {
namespace dom {

using ::media::WebMediaPlayer;

namespace {

typedef base::hash_map<std::string, scoped_refptr<MediaSource> >
    MediaSourceRegistry;

base::LazyInstance<MediaSourceRegistry> s_media_source_registry =
    LAZY_INSTANCE_INITIALIZER;

// Parse mime and codecs from content type. It will return "video/mp4" and
// ("avc1.42E01E", "mp4a.40.2") for "video/mp4; codecs="avc1.42E01E, mp4a.40.2".
// Note that this function does minimum validation as the media stack will check
// the mime type and codecs strictly.
bool ParseContentType(const std::string& content_type, std::string* mime,
                      std::vector<std::string>* codecs) {
  DCHECK(mime);
  DCHECK(codecs);
  static const char kCodecs[] = "codecs=";

  std::vector<std::string> tokens;
  // SplitString will also trim the results.
  ::base::SplitString(content_type, ';', &tokens);
  // The first one has to be mime type with delimiter '/' like 'video/mp4'.
  if (tokens.size() < 2 || tokens[0].find('/') == tokens[0].npos) {
    return false;
  }
  *mime = tokens[0];
  for (size_t i = 1; i < tokens.size(); ++i) {
    if (strncasecmp(tokens[i].c_str(), kCodecs, strlen(kCodecs))) {
      continue;
    }
    std::string codec_string = tokens[i].substr(strlen("codecs="));
    TrimString(codec_string, " \"", &codec_string);
    // SplitString will also trim the results.
    ::base::SplitString(codec_string, ',', codecs);
    break;
  }
  return !codecs->empty();
}

}  // namespace

// static
void MediaSource::Registry::Register(
    const std::string& blob_url,
    const scoped_refptr<MediaSource>& media_source) {
  DCHECK(media_source);
  MediaSourceRegistry& registry = s_media_source_registry.Get();
  DCHECK(registry.find(blob_url) == registry.end());
  registry.insert(std::make_pair(blob_url, media_source));
}

// static
scoped_refptr<MediaSource> MediaSource::Registry::Retrieve(
    const std::string& blob_url) {
  MediaSourceRegistry& registry = s_media_source_registry.Get();
  MediaSourceRegistry::iterator iter = registry.find(blob_url);
  if (iter == registry.end()) {
    DLOG(WARNING) << "Cannot find MediaSource object for blob url " << blob_url;
    return NULL;
  }

  return iter->second;
}

// static
void MediaSource::Registry::Unregister(const std::string& blob_url) {
  MediaSourceRegistry& registry = s_media_source_registry.Get();
  MediaSourceRegistry::iterator iter = registry.find(blob_url);
  if (iter == registry.end()) {
    DLOG(WARNING) << "Cannot find MediaSource object for blob url " << blob_url;
    return;
  }

  registry.erase(iter);
}

MediaSource::MediaSource()
    : ready_state_(kReadyStateClosed),
      player_(NULL),
      event_queue_(this),
      source_buffers_(new SourceBufferList(&event_queue_)) {}

scoped_refptr<SourceBufferList> MediaSource::source_buffers() const {
  return source_buffers_;
}

scoped_refptr<SourceBufferList> MediaSource::active_source_buffers() const {
  // All source buffers are 'active' as we don't support buffer selection.
  return source_buffers_;
}

double MediaSource::duration() const {
  if (ready_state_ == kReadyStateClosed) {
    return std::numeric_limits<float>::quiet_NaN();
  }

  DCHECK(player_);
  return player_->SourceGetDuration();
}

void MediaSource::set_duration(double duration) {
  if (duration < 0.0 || isnan(duration)) {
    // TODO(***REMOVED***): raise INVALID_ACCESS_ERR.
    NOTREACHED();
    return;
  }
  if (ready_state_ != kReadyStateOpen) {
    // TODO(***REMOVED***): raise INVALID_ACCESS_ERR.
    NOTREACHED();
    return;
  }
  DCHECK(player_);
  player_->SourceSetDuration(duration);
}

scoped_refptr<SourceBuffer> MediaSource::AddSourceBuffer(
    const std::string& type) {
  DLOG(INFO) << "add SourceBuffer with type " << type;

  if (type.empty()) {
    // TODO(***REMOVED***): raise INVALID_ACCESS_ERR.
    NOTREACHED();
    return NULL;
  }

  std::string mime;
  std::vector<std::string> codecs;

  if (!ParseContentType(type, &mime, &codecs)) {
    // TODO(***REMOVED***): raise NOT_SUPPORTED_ERR.
    NOTREACHED();
    return NULL;
  }

  if (!player_ || ready_state_ != kReadyStateOpen) {
    // TODO(***REMOVED***): raise INVALID_STATE_ERR.
    NOTREACHED();
    return NULL;
  }

  // 5. Create a new SourceBuffer object and associated resources.
  std::string id = source_buffers_->GenerateUniqueId();
  DCHECK(!id.empty());

  scoped_refptr<SourceBuffer> source_buffer = new SourceBuffer(this, id);

  switch (player_->SourceAddId(source_buffer->id(), mime, codecs)) {
    case WebMediaPlayer::kAddIdStatusOk:
      source_buffers_->Add(source_buffer);
      return source_buffer;
    case WebMediaPlayer::kAddIdStatusNotSupported:
      // TODO(***REMOVED***): raise NOT_SUPPORTED_ERR.
      NOTREACHED();
      return NULL;
    case WebMediaPlayer::kAddIdStatusReachedIdLimit:
      // TODO(***REMOVED***): raise QUOTA_EXCEEDED_ERR.
      NOTREACHED();
      return NULL;
  }

  NOTREACHED();
  return NULL;
}

void MediaSource::RemoveSourceBuffer(
    const scoped_refptr<SourceBuffer>& source_buffer) {
  if (source_buffer == NULL) {
    // TODO(***REMOVED***): raise INVALID_ACCESS_ERR.
    NOTREACHED();
    return;
  }

  if (!player_ || source_buffers_->length() == 0) {
    // TODO(***REMOVED***): raise INVALID_STATE_ERR.
    NOTREACHED();
    return;
  }

  if (!source_buffers_->Remove(source_buffer)) {
    // TODO(***REMOVED***): raise NOT_FOUND_ERR.
    NOTREACHED();
    return;
  }

  player_->SourceRemoveId(source_buffer->id());
}

std::string MediaSource::ready_state() const {
  switch (ready_state_) {
    case kReadyStateClosed:
      return "closed";
    case kReadyStateOpen:
      return "open";
    case kReadyStateEnded:
      return "ended";
  }
  NOTREACHED() << "ready_state_ (" << ready_state_ << ") is invalid";
  return "";
}

void MediaSource::EndOfStream() {
  // If there is no error string provided, treat it as empty.
  EndOfStream("");
}

void MediaSource::EndOfStream(const std::string& error) {
  if (!player_ || ready_state_ != kReadyStateOpen) {
    // TODO(***REMOVED***): raise INVALID_STATE_ERR.
    NOTREACHED();
    return;
  }

  WebMediaPlayer::EndOfStreamStatus eos_status =
      WebMediaPlayer::kEndOfStreamStatusNoError;

  if (error.empty() || error == "null") {
    eos_status = WebMediaPlayer::kEndOfStreamStatusNoError;
  } else if (error == "network") {
    eos_status = WebMediaPlayer::kEndOfStreamStatusNetworkError;
  } else if (error == "decode") {
    eos_status = WebMediaPlayer::kEndOfStreamStatusDecodeError;
  } else {
    // TODO(***REMOVED***): raise INVALID_ACCESS_ERR.
    NOTREACHED();
    return;
  }

  SetReadyState(kReadyStateEnded);
  player_->SourceEndOfStream(eos_status);
}

void MediaSource::SetPlayer(WebMediaPlayer* player) {
  // It is possible to reuse a MediaSource object but unlikely. DCHECK it until
  // it is used in this way.
  DCHECK(!player_);
  player_ = player;
}

void MediaSource::ScheduleEvent(const std::string& event_name) {
  event_queue_.Enqueue(new Event(event_name));
}

scoped_refptr<TimeRanges> MediaSource::GetBuffered(
    const SourceBuffer* source_buffer) {
  if (!player_ || ready_state_ != kReadyStateOpen) {
    // TODO(***REMOVED***): raise INVALID_STATE_ERR.
    NOTREACHED();
    return NULL;
  }

  ::media::Ranges<base::TimeDelta> media_time_ranges =
      player_->SourceBuffered(source_buffer->id());
  scoped_refptr<TimeRanges> dom_time_ranges = new TimeRanges;
  for (size_t index = 0; index < media_time_ranges.size(); ++index) {
    dom_time_ranges->Add(media_time_ranges.start(index).InSecondsF(),
                         media_time_ranges.end(index).InSecondsF());
  }
  return dom_time_ranges;
}

bool MediaSource::SetTimestampOffset(const SourceBuffer* source_buffer,
                                     double timestamp_offset) {
  if (!player_ || ready_state_ != kReadyStateOpen) {
    // TODO(***REMOVED***): raise INVALID_STATE_ERR.
    NOTREACHED();
    return false;
  }
  if (!player_->SourceSetTimestampOffset(source_buffer->id(),
                                         timestamp_offset)) {
    // TODO(***REMOVED***): raise INVALID_STATE_ERR.
    NOTREACHED();
    return false;
  }
  return true;
}

void MediaSource::Append(const SourceBuffer* source_buffer, const uint8* buffer,
                         int size) {
  if (!buffer) {
    // TODO(***REMOVED***): raise INVALID_ACCESS_ERR.
    NOTREACHED();
    return;
  }

  if (!player_ || ready_state_ == kReadyStateClosed) {
    // TODO(***REMOVED***): raise INVALID_STATE_ERR.
    NOTREACHED();
    return;
  }

  if (ready_state_ == kReadyStateEnded) {
    SetReadyState(kReadyStateOpen);
  }

  // If size is greater than kMaxAppendSize, we will append the data in multiple
  // small chunks with size less than or equal to kMaxAppendSize.  This can
  // avoid memory allocation spike as ChunkDemuxer may try to allocator memory
  // in size around 'append_size * 2'.
  const int kMaxAppendSize = 128 * 1024;
  int offset = 0;
  while (offset < size) {
    int chunk_size = std::min(size - offset, kMaxAppendSize);
    if (!player_->SourceAppend(source_buffer->id(), buffer + offset,
                               chunk_size)) {
      // TODO(***REMOVED***): raise SYNTAX_ERR.
      NOTREACHED();
      return;
    }
    offset += chunk_size;
  }
}

void MediaSource::Abort(const SourceBuffer* source_buffer) {
  if (!player_ || ready_state_ != kReadyStateOpen) {
    // TODO(***REMOVED***): raise INVALID_STATE_ERR.
    NOTREACHED();
    return;
  }

  bool aborted = player_->SourceAbort(source_buffer->id());
  DCHECK(aborted);
}

MediaSource::ReadyState MediaSource::GetReadyState() const {
  return ready_state_;
}

void MediaSource::SetReadyState(ReadyState ready_state) {
  if (ready_state_ == ready_state) {
    return;
  }

  ReadyState old_state = ready_state_;
  ready_state_ = ready_state;

  if (ready_state_ == kReadyStateClosed) {
    source_buffers_->Clear();
    player_ = NULL;
    ScheduleEvent("closed");
    return;
  }

  if (old_state == kReadyStateOpen && ready_state_ == kReadyStateEnded) {
    ScheduleEvent("ended");
    return;
  }

  if (ready_state_ == kReadyStateOpen) {
    ScheduleEvent("open");
  }
}

}  // namespace dom
}  // namespace cobalt
