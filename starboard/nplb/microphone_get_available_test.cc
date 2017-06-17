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

#include "starboard/microphone.h"
#include "starboard/nplb/microphone_helpers.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace starboard {
namespace nplb {

#if SB_HAS(MICROPHONE) && SB_API_VERSION >= 2

TEST(SbMicrophoneGetAvailableTest, SunnyDay) {
  SbMicrophoneInfo info_array[kMaxNumberOfMicrophone];
  int available_microphones =
      SbMicrophoneGetAvailable(info_array, kMaxNumberOfMicrophone);
  EXPECT_GE(available_microphones, 0);
}

TEST(SbMicrophoneGetAvailableTest, RainyDay0NumberOfMicrophone) {
  SbMicrophoneInfo info_array[kMaxNumberOfMicrophone];
  if (SbMicrophoneGetAvailable(info_array, kMaxNumberOfMicrophone) > 0) {
    int available_microphones = SbMicrophoneGetAvailable(info_array, 0);
    EXPECT_GT(available_microphones, 0);
  }
}

TEST(SbMicrophoneGetAvailableTest, RainyDayNegativeNumberOfMicrophone) {
  SbMicrophoneInfo info_array[kMaxNumberOfMicrophone];
  if (SbMicrophoneGetAvailable(info_array, kMaxNumberOfMicrophone) > 0) {
    int available_microphones = SbMicrophoneGetAvailable(info_array, -10);
    EXPECT_GT(available_microphones, 0);
  }
}

TEST(SbMicrophoneGetAvailableTest, RainyDayNULLInfoArray) {
  SbMicrophoneInfo info_array[kMaxNumberOfMicrophone];
  if (SbMicrophoneGetAvailable(info_array, kMaxNumberOfMicrophone) > 0) {
    int available_microphones =
        SbMicrophoneGetAvailable(NULL, kMaxNumberOfMicrophone);
    EXPECT_GT(available_microphones, 0);
  }
}

#endif  // SB_HAS(MICROPHONE) && SB_API_VERSION >= 2

}  // namespace nplb
}  // namespace starboard
