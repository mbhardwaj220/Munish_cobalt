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

#if defined(ENABLE_TEST_RUNNER)

#include "cobalt/dom/test_runner.h"

namespace cobalt {
namespace dom {

TestRunner::TestRunner() : should_wait_(false) {}

void TestRunner::NotifyDone() {
  DCHECK(should_wait_);
  notify_done_callback_.Run();
}

void TestRunner::WaitUntilDone() { should_wait_ = true; }

}  // namespace dom
}  // namespace cobalt

#endif  // ENABLE_TEST_RUNNER
