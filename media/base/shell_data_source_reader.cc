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

#include "media/base/shell_data_source_reader.h"

#include <limits.h>  // for ULLONG_MAX

namespace media {

const int ShellDataSourceReader::kReadError = DataSource::kReadError;

ShellDataSourceReader::ShellDataSourceReader()
    : blocking_read_event_(false, false)
    , file_size_(-1)
    , read_has_failed_(false)
    , last_bytes_read_(0) {
  blocking_read_cb_ = base::Bind(&ShellDataSourceReader::BlockingReadCompleted,
                                 this);
}

ShellDataSourceReader::~ShellDataSourceReader() {
  AbortPendingReadIfAny();
}

void ShellDataSourceReader::SetDataSource(
    scoped_refptr<DataSource> data_source) {
  data_source_ = data_source;
}

void ShellDataSourceReader::SetErrorCallback(base::Closure read_error_closure) {
  read_error_closure_ = read_error_closure;
}

// currently only single-threaded reads supported
int ShellDataSourceReader::BlockingRead(int64 position, int size, uint8 *data) {
  // read failures are unrecoverable, all subsequent reads will also fail
  if (read_has_failed_) {
    return -1;
  }

  // check bounds of read at or past EOF
  if (file_size_ >= 0 && position >= file_size_) {
    return 0;
  }

  data_source_->Read(position,
                     size,
                     data,
                     blocking_read_cb_);

  // wait for callback on read completion
  blocking_read_event_.Wait();

  if (last_bytes_read_ == DataSource::kReadError) {
    // make all future reads fail
    read_has_failed_ = true;
    // run canned callback error Closure
    if (!read_error_closure_.is_null()) {
      read_error_closure_.Run();
    }
    return kReadError;
  }

  return last_bytes_read_;
}

void ShellDataSourceReader::BlockingReadCompleted(int bytes_read) {
  last_bytes_read_ = bytes_read;
  // wake up blocked thread
  blocking_read_event_.Signal();
}

void ShellDataSourceReader::AbortPendingReadIfAny() {
  last_bytes_read_ = 0;
  // treat all subsequent reads as errors
  read_has_failed_ = true;
  blocking_read_event_.Signal();
}

int64 ShellDataSourceReader::FileSize() {
  if (file_size_ == -1) {
    if (!data_source_->GetSize(&file_size_)) {
      file_size_ = -1;
    }
  }
  return file_size_;
}

}  // namespace media
