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

#include <directfb.h>

#include "starboard/blitter.h"
#include "starboard/log.h"
#include "starboard/shared/directfb/blitter_internal.h"

bool SbBlitterFillRect(SbBlitterContext context, SbBlitterRect rect) {
  if (!SbBlitterIsContextValid(context)) {
    SB_DLOG(ERROR) << __FUNCTION__ << ": Invalid context.";
    return false;
  }
  if (rect.width < 0 || rect.height < 0) {
    SB_DLOG(ERROR) << __FUNCTION__ << ": Width and height must both be "
                   << "greater than or equal to 0.";
    return false;
  }

  if (!context->current_render_target) {
    SB_DLOG(ERROR) << __FUNCTION__ << ": Render target must be previously "
                   << "specified on a context before issuing draw calls.";
    return false;
  }

  IDirectFBSurface* surface = context->current_render_target->surface;

  if (!SetupDFBSurfaceDrawStateFromBlitterContextState(context, surface)) {
    SB_DLOG(ERROR) << __FUNCTION__ << ": Error setting DFB Surface state.";
    return false;
  }
  // Issued the DirectFB draw call to fill a rectangle with a color.
  if (surface->FillRectangle(surface, rect.x, rect.y, rect.width,
                             rect.height) != DFB_OK) {
    SB_DLOG(ERROR) << __FUNCTION__ << ": Error calling FillRectangle().";
    return false;
  }

  return true;
}
