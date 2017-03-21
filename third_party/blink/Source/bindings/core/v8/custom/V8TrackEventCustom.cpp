/*
 * Copyright (C) 2011 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "bindings/core/v8/V8TrackEvent.h"

#include "bindings/core/v8/V8AudioTrack.h"
#include "bindings/core/v8/V8TextTrack.h"
#include "bindings/core/v8/V8VideoTrack.h"
#include "core/html/track/TrackBase.h"
#include "core/html/track/TrackEvent.h"

namespace blink {

void V8TrackEvent::trackAttributeGetterCustom(const v8::PropertyCallbackInfo<v8::Value>& info)
{
    TrackEvent* trackEvent = V8TrackEvent::toImpl(info.Holder());
    TrackBase* track = trackEvent->track();

    if (!track) {
        v8SetReturnValueNull(info);
        return;
    }

    switch (track->type()) {
    case TrackBase::TextTrack:
        v8SetReturnValueFast(info, toTextTrack(track), trackEvent);
        return;

    case TrackBase::AudioTrack:
        v8SetReturnValueFast(info, toAudioTrack(track), trackEvent);
        return;

    case TrackBase::VideoTrack:
        v8SetReturnValueFast(info, toVideoTrack(track), trackEvent);
        return;
    }

    v8SetReturnValueNull(info);
}

} // namespace blink
