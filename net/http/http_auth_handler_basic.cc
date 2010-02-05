// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "net/http/http_auth_handler_basic.h"

#include <string>

#include "base/base64.h"
#include "base/string_util.h"
#include "net/base/net_errors.h"
#include "net/http/http_auth.h"

namespace net {

// Note that if a realm was not specified, we will default it to "";
// so specifying 'Basic realm=""' is equivalent to 'Basic'.
//
// This is more generous than RFC 2617, which is pretty clear in the
// production of challenge that realm is required.
//
// We allow it to be compatibility with certain embedded webservers that don't
// include a realm (see http://crbug.com/20984.)
bool HttpAuthHandlerBasic::Init(std::string::const_iterator challenge_begin,
                                std::string::const_iterator challenge_end) {
  scheme_ = "basic";
  score_ = 1;
  properties_ = 0;

  // Verify the challenge's auth-scheme.
  HttpAuth::ChallengeTokenizer challenge_tok(challenge_begin, challenge_end);
  if (!challenge_tok.valid() ||
      !LowerCaseEqualsASCII(challenge_tok.scheme(), "basic"))
    return false;

  // Extract the realm (may be missing).
  while (challenge_tok.GetNext()) {
    if (LowerCaseEqualsASCII(challenge_tok.name(), "realm"))
      realm_ = challenge_tok.unquoted_value();
  }

  return challenge_tok.valid();
}

int HttpAuthHandlerBasic::GenerateAuthToken(
    const std::wstring& username,
    const std::wstring& password,
    const HttpRequestInfo*,
    const ProxyInfo*,
    std::string* auth_token) {
  // TODO(eroman): is this the right encoding of username/password?
  std::string base64_username_password;
  if (!base::Base64Encode(WideToUTF8(username) + ":" + WideToUTF8(password),
                          &base64_username_password)) {
    LOG(ERROR) << "Unexpected problem Base64 encoding.";
    return ERR_UNEXPECTED;
  }
  *auth_token = "Basic " + base64_username_password;
  return OK;
}

int HttpAuthHandlerBasic::GenerateDefaultAuthToken(
    const HttpRequestInfo* request,
    const ProxyInfo* proxy,
    std::string* auth_token) {
  NOTREACHED();
  LOG(ERROR) << ErrorToString(ERR_NOT_IMPLEMENTED);
  return ERR_NOT_IMPLEMENTED;
}


}  // namespace net
