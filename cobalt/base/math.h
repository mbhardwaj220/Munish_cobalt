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

#ifndef BASE_MATH_H_
#define BASE_MATH_H_

#include <cmath>

#include "build/build_config.h"

// The MSVC compiler doesn't have roundf().
#if defined(COMPILER_MSVC)
float roundf(float x);
#endif  // defined(COMPILER_MSVC)

#endif  // BASE_MATH_H_
