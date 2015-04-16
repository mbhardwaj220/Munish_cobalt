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

#ifndef MEDIA_MEDIA_MODULE_H_
#define MEDIA_MEDIA_MODULE_H_

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"

namespace cobalt {
namespace media {

// TODO(***REMOVED***) : Collapse MediaModule into ShellMediaPlatform.
class MediaModule {
 public:
  virtual ~MediaModule() {}

  // This function should be defined on individual platform to create the
  // platform specific MediaModule.
  static scoped_ptr<MediaModule> Create();

 protected:
  MediaModule() {}

 private:
  DISALLOW_COPY_AND_ASSIGN(MediaModule);
};

}  // namespace media
}  // namespace cobalt

#endif  // MEDIA_MEDIA_MODULE_H_
