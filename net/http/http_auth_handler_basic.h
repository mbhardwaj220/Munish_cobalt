// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_HTTP_HTTP_AUTH_HANDLER_BASIC_H_
#define NET_HTTP_HTTP_AUTH_HANDLER_BASIC_H_

#include <string>

#include "net/base/net_export.h"
#include "net/http/http_auth_handler.h"
#include "net/http/http_auth_handler_factory.h"

namespace net {

// Code for handling http basic authentication.
class NET_EXPORT_PRIVATE HttpAuthHandlerBasic : public HttpAuthHandler {
 public:
  class NET_EXPORT_PRIVATE Factory : public HttpAuthHandlerFactory {
   public:
    Factory();
    virtual ~Factory();

    virtual int CreateAuthHandler(
        HttpAuth::ChallengeTokenizer* challenge,
        HttpAuth::Target target,
        const GURL& origin,
        CreateReason reason,
        int digest_nonce_count,
        const BoundNetLog& net_log,
        scoped_ptr<HttpAuthHandler>* handler) override;
  };

  virtual HttpAuth::AuthorizationResult HandleAnotherChallenge(
      HttpAuth::ChallengeTokenizer* challenge) override;

 protected:
  virtual bool Init(HttpAuth::ChallengeTokenizer* challenge) override;

  virtual int GenerateAuthTokenImpl(const AuthCredentials* credentials,
                                    const HttpRequestInfo* request,
                                    const CompletionCallback& callback,
                                    std::string* auth_token) override;

 private:
  virtual ~HttpAuthHandlerBasic() {}

  bool ParseChallenge(HttpAuth::ChallengeTokenizer* challenge);
};

}  // namespace net

#endif  // NET_HTTP_HTTP_AUTH_HANDLER_BASIC_H_
