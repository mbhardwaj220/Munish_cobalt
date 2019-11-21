//
// Copyright 2015 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// DebugAnnotator9.h: D3D9 helpers for adding trace annotations.
//

#include "libANGLE/renderer/d3d/d3d9/DebugAnnotator9.h"

#include "common/platform.h"

namespace rx
{

void DebugAnnotator9::beginEvent(const char *eventName, const char *eventMessage)
{
    angle::LoggingAnnotator::beginEvent(eventName, eventMessage);
    std::mbstate_t state = std::mbstate_t();
    std::mbsrtowcs(mWCharMessage, &eventMessage, kMaxMessageLength, &state);
    D3DPERF_BeginEvent(0, mWCharMessage);
}

void DebugAnnotator9::endEvent(const char *eventName)
{
    angle::LoggingAnnotator::endEvent(eventName);
    D3DPERF_EndEvent();
}

void DebugAnnotator9::setMarker(const char *markerName)
{
    angle::LoggingAnnotator::setMarker(markerName);
    std::mbstate_t state = std::mbstate_t();
    std::mbsrtowcs(mWCharMessage, &markerName, kMaxMessageLength, &state);
    D3DPERF_SetMarker(0, mWCharMessage);
}

bool DebugAnnotator9::getStatus()
{
    return !!D3DPERF_GetStatus();
}

}  // namespace rx
