// Copyright 2008, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//    * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//    * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "net/http/http_network_layer.h"

#include "base/notimplemented.h"
#include "net/base/client_socket_factory.h"
#include "net/http/http_network_session.h"
#include "net/http/http_network_transaction.h"
#include "net/proxy/proxy_resolver_fixed.h"
#if defined(OS_WIN)
#include "net/http/http_transaction_winhttp.h"
#include "net/proxy/proxy_resolver_winhttp.h"
#endif

namespace net {

//-----------------------------------------------------------------------------

#if defined(OS_WIN)
// static
bool HttpNetworkLayer::use_winhttp_ = true;
#endif

// static
HttpTransactionFactory* HttpNetworkLayer::CreateFactory(
    const ProxyInfo* pi) {
#if defined(OS_WIN)
  if (use_winhttp_)
    return new HttpTransactionWinHttp::Factory(pi);
#endif

  return new HttpNetworkLayer(pi);
}

#if defined(OS_WIN)
// static
void HttpNetworkLayer::UseWinHttp(bool value) {
  use_winhttp_ = value;
}
#endif

//-----------------------------------------------------------------------------

HttpNetworkLayer::HttpNetworkLayer(const ProxyInfo* pi)
    : suspended_(false) {
  ProxyResolver* proxy_resolver;
  if (pi) {
    proxy_resolver = new ProxyResolverFixed(*pi);
  } else {
#if defined(OS_WIN)
    proxy_resolver = new ProxyResolverWinHttp();
#else
    NOTIMPLEMENTED();
    proxy_resolver = NULL;
#endif
  }
  session_ = new HttpNetworkSession(proxy_resolver);
}

HttpNetworkLayer::~HttpNetworkLayer() {
}

HttpTransaction* HttpNetworkLayer::CreateTransaction() {
  if (suspended_)
    return NULL;

  return new HttpNetworkTransaction(
      session_, ClientSocketFactory::GetDefaultFactory());
}

HttpCache* HttpNetworkLayer::GetCache() {
  return NULL;
}

AuthCache* HttpNetworkLayer::GetAuthCache() {
  return session_->auth_cache();
}

void HttpNetworkLayer::Suspend(bool suspend) {
  suspended_ = suspend;

  if (suspend)
    session_->connection_pool()->CloseIdleSockets();
}

}  // namespace net
