// Copyright 2019 The Cobalt Authors. All Rights Reserved.
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

// This file was initially generated by starboard/tools/create_derived_build.py,
// though it may have been modified since its creation.

#ifndef STARBOARD_LINUX_X64X11_BLITTERGLES_SBVERSION_11_CONFIGURATION_PUBLIC_H_
#define STARBOARD_LINUX_X64X11_BLITTERGLES_SBVERSION_11_CONFIGURATION_PUBLIC_H_

#undef SB_API_VERSION
#define SB_API_VERSION 11

// --- Architecture Configuration --------------------------------------------

// Whether the current platform is big endian. SB_IS_LITTLE_ENDIAN will be
// automatically set based on this.
#define SB_IS_BIG_ENDIAN 0

// Whether the current platform is an ARM architecture.
#define SB_IS_ARCH_ARM 0

// Whether the current platform is a MIPS architecture.
#define SB_IS_ARCH_MIPS 0

// Whether the current platform is a PPC architecture.
#define SB_IS_ARCH_PPC 0

// Whether the current platform is an x86 architecture.
#define SB_IS_ARCH_X86 1

// Whether the current platform is a 32-bit architecture.
#define SB_IS_32_BIT 0

// Whether the current platform is a 64-bit architecture.
#define SB_IS_64_BIT 1

// Whether the current platform's pointers are 32-bit.
// Whether the current platform's longs are 32-bit.
#define SB_HAS_32_BIT_POINTERS 0
#define SB_HAS_32_BIT_LONG 0

// Whether the current platform's pointers are 64-bit.
// Whether the current platform's longs are 64-bit.
#define SB_HAS_64_BIT_POINTERS 1
#define SB_HAS_64_BIT_LONG 1

// Configuration parameters that allow the application to make some general
// compile-time decisions with respect to the the number of cores likely to be
// available on this platform. For a definitive measure, the application should
// still call SbSystemGetNumberOfProcessors at runtime.

// Whether the current platform's thread scheduler will automatically balance
// threads between cores, as opposed to systems where threads will only ever run
// on the specifically pinned core.
#define SB_HAS_CROSS_CORE_SCHEDULER 1

// --- Graphics Configuration ------------------------------------------------

// Indicates whether or not the given platform supports rendering of NV12
// textures. These textures typically originate from video decoders.
#define SB_HAS_NV12_TEXTURE_SUPPORT 1

// --- Shared Configuration and Overrides ------------------------------------

// Include the Linux configuration that's common between all Desktop Linuxes.
#include "starboard/linux/shared/configuration_public.h"

// Include the Blitter - GLES configuration that's common between all Blitter -
// GLES configurations.
#include "starboard/linux/x64x11/blittergles/shared/configuration_public.h"

// Starboard API versions 11 and earlier must define this variable, and have
// microphone supported.
#define SB_HAS_MICROPHONE 1

// Whether the current platform has speech synthesis.
#undef SB_HAS_SPEECH_SYNTHESIS
#define SB_HAS_SPEECH_SYNTHESIS 0

// Whether the current platform implements the on screen keyboard interface.
#define SB_HAS_ON_SCREEN_KEYBOARD 0

#endif  // STARBOARD_LINUX_X64X11_BLITTERGLES_SBVERSION_11_CONFIGURATION_PUBLIC_H_