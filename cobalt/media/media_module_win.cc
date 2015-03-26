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

#include "cobalt/media/media_module.h"

namespace cobalt {
namespace media {

// There is no media stack on Windows and the XB1 media stack cannot be used
// directly on Windows. So MediaModule on windows does nothing.
scoped_ptr<MediaModule> MediaModule::Create() {
  return make_scoped_ptr(new MediaModule);
}

}  // namespace media
}  // namespace cobalt
