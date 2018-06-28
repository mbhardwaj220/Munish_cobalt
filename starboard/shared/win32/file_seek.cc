// Copyright 2017 The Cobalt Authors. All Rights Reserved.
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

#include "starboard/file.h"

#include <windows.h>

#include "starboard/shared/win32/file_internal.h"

int64_t SbFileSeek(SbFile file, SbFileWhence whence, int64_t offset) {
  if (!starboard::shared::win32::HasValidHandle(file)) {
    return -1;
  }

  LARGE_INTEGER new_file_pointer = {0};
  LARGE_INTEGER offset_argument = {0};
  offset_argument.QuadPart = offset;
  BOOL success =
      SetFilePointerEx(file->file_handle, offset_argument, &new_file_pointer,
                       static_cast<DWORD>(whence));

  if (!success) {
    return -1;
  }

  return new_file_pointer.QuadPart;
}
