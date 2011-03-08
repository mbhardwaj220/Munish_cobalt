// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "net/base/network_delegate.h"

#include "base/logging.h"

namespace net {

bool NetworkDelegate::NotifyBeforeURLRequest(URLRequest* request,
                                             CompletionCallback* callback) {
  DCHECK(CalledOnValidThread());
  DCHECK(request);
  DCHECK(callback);
  return OnBeforeURLRequest(request, callback);
}

void NetworkDelegate::NotifySendHttpRequest(HttpRequestHeaders* headers) {
  DCHECK(CalledOnValidThread());
  DCHECK(headers);
  OnSendHttpRequest(headers);
}

void NetworkDelegate::NotifyResponseStarted(URLRequest* request) {
  DCHECK(CalledOnValidThread());
  DCHECK(request);
  OnResponseStarted(request);
}

void NetworkDelegate::NotifyReadCompleted(URLRequest* request, int bytes_read) {
  DCHECK(CalledOnValidThread());
  DCHECK(request);
  OnReadCompleted(request, bytes_read);
}

}  // namespace net
