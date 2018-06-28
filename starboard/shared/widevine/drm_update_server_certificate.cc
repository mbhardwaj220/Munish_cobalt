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

#include "starboard/drm.h"

#include "starboard/log.h"

#if SB_API_VERSION >= SB_DRM_REFINEMENT_API_VERSION

void SbDrmUpdateServerCertificate(SbDrmSystem drm_system,
                                  int ticket,
                                  const void* certificate,
                                  int certificate_size) {
  SB_UNREFERENCED_PARAMETER(drm_system);
  SB_UNREFERENCED_PARAMETER(ticket);
  SB_UNREFERENCED_PARAMETER(certificate);
  SB_UNREFERENCED_PARAMETER(certificate_size);

  SB_NOTREACHED();
}

#endif  // SB_API_VERSION >= SB_DRM_REFINEMENT_API_VERSION
