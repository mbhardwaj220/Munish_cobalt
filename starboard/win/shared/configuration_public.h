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

// Other source files should never include this header directly, but should
// include the generic "starboard/configuration.h" instead.

#ifndef STARBOARD_WIN_SHARED_CONFIGURATION_PUBLIC_H_
#define STARBOARD_WIN_SHARED_CONFIGURATION_PUBLIC_H_

#if SB_API_VERSION != SB_EXPERIMENTAL_API_VERSION
#error \
    "This platform's sabi.json file is expected to track the experimental " \
"Starboard API version."
#endif  // SB_API_VERSION != SB_EXPERIMENTAL_API_VERSION

// --- Architecture Configuration --------------------------------------------

// Some platforms will not align variables on the stack with an alignment
// greater than 16 bytes. Platforms where this is the case should define the
// following quirk.
#undef SB_HAS_QUIRK_DOES_NOT_STACK_ALIGN_OVER_16_BYTES

// --- System Header Configuration -------------------------------------------

// Any system headers listed here that are not provided by the platform will be
// emulated in starboard/types.h.

// Whether the current platform provides the standard header sys/types.h.
#define SB_HAS_SYS_TYPES_H 0

// Whether the current platform provides ssize_t.
#define SB_HAS_SSIZE_T 0

#if !defined(__WCHAR_MAX__)
#include <wchar.h>
#define __WCHAR_MAX__ WCHAR_MAX
#endif

// Type detection for wchar_t.
#if defined(__WCHAR_MAX__) && \
    (__WCHAR_MAX__ == 0x7fffffff || __WCHAR_MAX__ == 0xffffffff)
#define SB_IS_WCHAR_T_UTF32 1
#elif defined(__WCHAR_MAX__) && \
    (__WCHAR_MAX__ == 0x7fff || __WCHAR_MAX__ == 0xffff)
#define SB_IS_WCHAR_T_UTF16 1
#endif

// Chrome only defines this for ARMEL.
#if defined(__ARMEL__)
// Chrome has an exclusion for iOS here, we should too when we support iOS.
#define SB_IS_WCHAR_T_UNSIGNED 1
#endif

// --- Compiler Configuration ------------------------------------------------

// The platform's annotation for forcing a C function to be inlined.
//   https://msdn.microsoft.com/en-us/library/bw1hbe6y.aspx#Anchor_1
#define SB_C_FORCE_INLINE __forceinline

// The platform's annotation for marking a C function as suggested to be
// inlined.
#define SB_C_INLINE inline

// The platform's annotation for marking a C function as forcibly not
// inlined.
#define SB_C_NOINLINE __declspec(noinline)

// The platform's annotation for marking a symbol as exported outside of the
// current shared library.
#define SB_EXPORT_PLATFORM __declspec(dllexport)

// The platform's annotation for marking a symbol as imported from outside of
// the current linking unit.
#define SB_IMPORT_PLATFORM

// --- Extensions Configuration ----------------------------------------------

// Please use <unordered_map> and <unordered_set> for the hash table types.
#define SB_HAS_STD_UNORDERED_HASH 1

// GCC/Clang doesn't define a long long hash function, except for Android and
// Game consoles.
#define SB_HAS_LONG_LONG_HASH 1

// GCC/Clang doesn't define a string hash function, except for Game Consoles.
#define SB_HAS_STRING_HASH 1

// Desktop Linux needs a using statement for the hash functions.
#define SB_HAS_HASH_USING 1

// Set this to 1 if hash functions for custom types can be defined as a
// hash_value() function. Otherwise, they need to be placed inside a
// partially-specified hash struct template with an operator().
#define SB_HAS_HASH_VALUE 1

// Set this to 1 if use of hash_map or hash_set causes a deprecation warning
// (which then breaks the build).
#define SB_HAS_HASH_WARNING 1
#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS

// The location to include hash_map on this platform.
#define SB_HASH_MAP_INCLUDE <hash_map>

// C++'s hash_map and hash_set are often found in different namespaces depending
// on the compiler.
#define SB_HASH_NAMESPACE stdext

// The location to include hash_set on this platform.
#define SB_HASH_SET_INCLUDE <hash_set>

// --- Filesystem Configuration ----------------------------------------------

// On some platforms the file system stores access times at a coarser
// granularity than other times. When this quirk is defined, we assume the
// access time is of 1 day precision.
#undef SB_HAS_QUIRK_FILESYSTEM_COARSE_ACCESS_TIME

// --- Graphics Configuration ------------------------------------------------

// Specifies whether this platform supports a performant accelerated blitter
// API. The basic requirement is a scaled, clipped, alpha-blended blit.
#define SB_HAS_BLITTER 0

// Indicates whether or not the given platform supports bilinear filtering.
// This can be checked to enable/disable renderer tests that verify that this is
// working properly.
#define SB_HAS_BILINEAR_FILTERING_SUPPORT 1

// Indicates whether or not the given platform supports rendering of NV12
// textures. These textures typically originate from video decoders.
#define SB_HAS_NV12_TEXTURE_SUPPORT 0

#define SB_HAS_VIRTUAL_REALITY 0

// --- I/O Configuration -----------------------------------------------------

// Whether the current platform supports on screen keyboard.
#define SB_HAS_ON_SCREEN_KEYBOARD 0

// Whether the current platform has speech synthesis.
#define SB_HAS_SPEECH_SYNTHESIS 0

// Whether the current platform has speech recognizer.
#define SB_HAS_SPEECH_RECOGNIZER 0

// --- Media Configuration ---------------------------------------------------

// Whether the current platform supports captions. Implementation is required
// after Starboard version 11.
#if SB_API_VERSION < 12
#define SB_HAS_CAPTIONS 0
#endif  // SB_API_VERSION < 12

// dlmalloc will use the ffs intrinsic if available.  Platforms on which this is
// not available should define the following quirk.
#undef SB_HAS_QUIRK_NO_FFS

// --- Memory Configuration --------------------------------------------------

// Whether this platform has and should use an MMAP function to map physical
// memory to the virtual address space.
#if SB_API_VERSION < 12
SB_HAS_MMAP 1
#endif

// Whether this platform can map executable memory. Implies SB_HAS_MMAP. This is
// required for platforms that want to JIT.
#define SB_CAN_MAP_EXECUTABLE_MEMORY 1

// --- Network Configuration -------------------------------------------------

// Specifies whether this platform supports IPV6.
#define SB_HAS_IPV6 1

// Specifies whether this platform supports pipe.
#define SB_HAS_PIPE 1

// --- Thread Configuration --------------------------------------------------

// --- Timing API ------------------------------------------------------------

// Whether this platform has an API to retrieve how long the current thread
// has spent in the executing state.
#define SB_HAS_TIME_THREAD_NOW 0

// --- Tuneable Parameters ---------------------------------------------------

// --- User Configuration ----------------------------------------------------

// --- Platform Specific Audits ----------------------------------------------

// Whether or not the platform supports socket connection reset.
#define SB_HAS_SOCKET_ERROR_CONNECTION_RESET_SUPPORT 1

#endif  // STARBOARD_WIN_SHARED_CONFIGURATION_PUBLIC_H_