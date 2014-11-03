/*
 * Copyright (C) 2012 Google Inc. All rights reserved.
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
#include "bindings/core/v8/V8Blob.h"

#include "bindings/core/v8/ExceptionState.h"
#include "bindings/core/v8/custom/V8BlobCustomHelpers.h"

namespace blink {

void V8Blob::constructorCustom(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ConstructionContext, "Blob", info.Holder(), info.GetIsolate());
    if (!info.Length()) {
        Blob* blob = Blob::create();
        v8SetReturnValue(info, blob);
        return;
    }

    // FIXME: handle sequences based on ES6 @@iterator, see http://crbug.com/393866
    if (!info[0]->IsArray()) {
        exceptionState.throwTypeError(ExceptionMessages::argumentNullOrIncorrectType(1, "Array"));
        exceptionState.throwIfNeeded();
        return;
    }

    V8BlobCustomHelpers::ParsedProperties properties(false);
    if (info.Length() > 1) {
        if (!info[1]->IsObject()) {
            exceptionState.throwTypeError("The 2nd argument is not of type Object.");
            exceptionState.throwIfNeeded();
            return;
        }

        if (!properties.parseBlobPropertyBag(info.GetIsolate(), info[1], "Blob", exceptionState)) {
            exceptionState.throwIfNeeded();
            return;
        }
    }

    OwnPtr<BlobData> blobData = BlobData::create();
    blobData->setContentType(properties.contentType());
    if (!V8BlobCustomHelpers::processBlobParts(info.GetIsolate(), v8::Local<v8::Object>::Cast(info[0]), properties.normalizeLineEndingsToNative(), *blobData))
        return;

    long long blobSize = blobData->length();
    Blob* blob = Blob::create(BlobDataHandle::create(blobData.release(), blobSize));
    v8SetReturnValue(info, blob);
}

} // namespace blink
