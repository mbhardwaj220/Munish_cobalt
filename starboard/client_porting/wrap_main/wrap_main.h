/*
 * Copyright 2016 Google Inc. All Rights Reserved.
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

// This header defines two macros, COBALT_WRAP_SIMPLE_MAIN() and
// COBALT_WRAP_BASE_MAIN(). Simple main is for programs that are
// run-and-terminate, like unit tests. Base main is for programs that need a
// main message loop, and will terminate when the quit_closure is called.

#ifndef STARBOARD_CLIENT_PORTING_WRAP_MAIN_WRAP_MAIN_H_
#define STARBOARD_CLIENT_PORTING_WRAP_MAIN_WRAP_MAIN_H_

#if defined(_WIN32)
#include <windows.h>
#endif

namespace {
void DisableWindowsCrtDialog() {
#if defined(_WIN32)
  if (!IsDebuggerPresent()) {
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
  }
#endif
}
}  // namespace

#if defined(STARBOARD)
#include "starboard/event.h"
#include "starboard/system.h"

namespace starboard {
namespace client_porting {
namespace wrap_main {
// A main-style function.
typedef int (*MainFunction)(int argc, char** argv);

template <MainFunction main_function>
void SimpleEventHandler(const SbEvent* event) {
  switch (event->type) {
    case kSbEventTypeStart: {
      SbEventStartData* data = static_cast<SbEventStartData*>(event->data);
      SbSystemRequestStop(
          main_function(data->argument_count, data->argument_values));
      break;
    }
    default:
      break;
  }
}

}  // namespace wrap_main
}  // namespace client_porting
}  // namespace starboard

#define STARBOARD_WRAP_SIMPLE_MAIN(main_function)                \
  void SbEventHandle(const SbEvent* event) {                     \
    DisableWindowsCrtDialog();                                   \
    ::starboard::client_porting::wrap_main::SimpleEventHandler<  \
        main_function>(event);                                   \
  }

#else
#define STARBOARD_WRAP_SIMPLE_MAIN(main_function) \
  int main(int argc, char** argv) {               \
    DisableWindowsCrtDialog();                    \
    return main_function(argc, argv);             \
  }

#endif  // STARBOARD
#endif  // STARBOARD_CLIENT_PORTING_WRAP_MAIN_WRAP_MAIN_H_
