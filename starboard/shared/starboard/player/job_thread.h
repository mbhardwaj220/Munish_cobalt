// Copyright 2018 The Cobalt Authors. All Rights Reserved.
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

#ifndef STARBOARD_SHARED_STARBOARD_PLAYER_JOB_THREAD_H_
#define STARBOARD_SHARED_STARBOARD_PLAYER_JOB_THREAD_H_

#include "starboard/common/scoped_ptr.h"
#include "starboard/shared/internal_only.h"
#include "starboard/shared/starboard/player/job_queue.h"
#include "starboard/thread.h"

#ifndef __cplusplus
#error "Only C++ files can include this header."
#endif

namespace starboard {
namespace shared {
namespace starboard {
namespace player {

// This class implements a thread that holds a JobQueue.
class JobThread {
 public:
  explicit JobThread(const char* thread_name);
  ~JobThread();

  JobQueue* job_queue() { return job_queue_.get(); }

 private:
  static void* ThreadEntryPoint(void* context);
  void RunLoop();

  SbThread thread_;
  scoped_ptr<JobQueue> job_queue_;
};

}  // namespace player
}  // namespace starboard
}  // namespace shared
}  // namespace starboard

#endif  // STARBOARD_SHARED_STARBOARD_PLAYER_JOB_THREAD_H_
