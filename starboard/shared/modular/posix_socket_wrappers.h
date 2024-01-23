// Copyright 2023 The Cobalt Authors. All Rights Reserved.
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

#ifndef STARBOARD_SHARED_MODULAR_POSIX_SOCKET_WRAPPERS_H_
#define STARBOARD_SHARED_MODULAR_POSIX_SOCKET_WRAPPERS_H_

#include <stdint.h>

#include "starboard/configuration.h"
#include "starboard/export.h"

#ifdef __cplusplus
extern "C" {
#endif

// A representation of any possible supported address type.
typedef struct SocketAddress {
  // The storage for the address. For IPv4, only the first 4 bytes make up the
  // address. For IPv6, the entire buffer of 16 bytes is meaningful. An address
  // of all zeros means that the address is unspecified.
  uint8_t address[16];

  // The type of address this represents (IPv4 vs IPv6).
  int address_type;

  // The port component of this socket address. If not specified, it will be
  // zero, which is officially undefined.
  int port;
} SocketAddress;

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // STARBOARD_SHARED_MODULAR_POSIX_SOCKET_WRAPPERS_H_
