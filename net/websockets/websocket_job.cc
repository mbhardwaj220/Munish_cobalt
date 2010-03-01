// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "net/websockets/websocket_job.h"

#include "googleurl/src/gurl.h"
#include "net/base/net_errors.h"
#include "net/base/cookie_policy.h"
#include "net/base/cookie_store.h"
#include "net/http/http_util.h"
#include "net/url_request/url_request_context.h"

namespace net {

// lower-case header names.
static const char* const kCookieHeaders[] = {
  "cookie", "cookie2"
};
static const char* const kSetCookieHeaders[] = {
  "set-cookie", "set-cookie2"
};

static SocketStreamJob* WebSocketJobFactory(
    const GURL& url, SocketStream::Delegate* delegate) {
  WebSocketJob* job = new WebSocketJob(delegate);
  job->InitSocketStream(new SocketStream(url, job));
  return job;
}

class WebSocketJobInitSingleton {
 private:
  friend struct DefaultSingletonTraits<WebSocketJobInitSingleton>;
  WebSocketJobInitSingleton() {
    SocketStreamJob::RegisterProtocolFactory("ws", WebSocketJobFactory);
    SocketStreamJob::RegisterProtocolFactory("wss", WebSocketJobFactory);
  }
};

static void ParseHandshakeMessage(
    const char* handshake_message, int len,
    std::string* status_line,
    std::string* header) {
  size_t i = base::StringPiece(handshake_message, len).find_first_of("\r\n");
  if (i == base::StringPiece::npos) {
    *status_line = std::string(handshake_message, len);
    *header = "";
    return;
  }
  *status_line = std::string(handshake_message, i + 2);
  *header = std::string(handshake_message + i + 2, len - i - 2);
}

static void FetchResponseCookies(
    const char* handshake_message, int len,
    std::vector<std::string>* response_cookies) {
  std::string handshake_response(handshake_message, len);
  HttpUtil::HeadersIterator iter(handshake_response.begin(),
                                 handshake_response.end(), "\r\n");
  while (iter.GetNext()) {
    for (size_t i = 0; i < arraysize(kSetCookieHeaders); i++) {
      if (LowerCaseEqualsASCII(iter.name_begin(), iter.name_end(),
                               kSetCookieHeaders[i])) {
        response_cookies->push_back(iter.values());
      }
    }
  }
}

// static
void WebSocketJob::EnsureInit() {
  Singleton<WebSocketJobInitSingleton>::get();
}

WebSocketJob::WebSocketJob(SocketStream::Delegate* delegate)
    : delegate_(delegate),
      state_(INITIALIZED),
      handshake_request_sent_(0),
      handshake_response_header_length_(0),
      response_cookies_save_index_(0),
      ALLOW_THIS_IN_INITIALIZER_LIST(can_get_cookies_callback_(
          this, &WebSocketJob::OnCanGetCookiesCompleted)),
      ALLOW_THIS_IN_INITIALIZER_LIST(can_set_cookie_callback_(
          this, &WebSocketJob::OnCanSetCookieCompleted)) {
}

WebSocketJob::~WebSocketJob() {
  DCHECK_EQ(CLOSED, state_);
  DCHECK(!delegate_);
  DCHECK(!socket_.get());
}

void WebSocketJob::Connect() {
  DCHECK(socket_.get());
  DCHECK_EQ(state_, INITIALIZED);
  state_ = CONNECTING;
  socket_->Connect();
}

bool WebSocketJob::SendData(const char* data, int len) {
  switch (state_) {
    case INITIALIZED:
      return false;

    case CONNECTING:
      return SendHandshakeRequest(data, len);

    case OPEN:
      return socket_->SendData(data, len);

    case CLOSED:
      return false;
  }
  return false;
}

void WebSocketJob::Close() {
  state_ = CLOSED;
  socket_->Close();
}

void WebSocketJob::RestartWithAuth(
    const std::wstring& username,
    const std::wstring& password) {
  state_ = CONNECTING;
  socket_->RestartWithAuth(username, password);
}

void WebSocketJob::DetachDelegate() {
  state_ = CLOSED;
  delegate_ = NULL;
  if (socket_)
    socket_->DetachDelegate();
  socket_ = NULL;
}

void WebSocketJob::OnConnected(
    SocketStream* socket, int max_pending_send_allowed) {
  if (delegate_)
    delegate_->OnConnected(socket, max_pending_send_allowed);
}

void WebSocketJob::OnSentData(SocketStream* socket, int amount_sent) {
  if (state_ == CONNECTING) {
    OnSentHandshakeRequest(socket, amount_sent);
    return;
  }
  if (delegate_)
    delegate_->OnSentData(socket, amount_sent);
}

void WebSocketJob::OnReceivedData(
    SocketStream* socket, const char* data, int len) {
  if (state_ == CONNECTING) {
    OnReceivedHandshakeResponse(socket, data, len);
    return;
  }
  if (delegate_)
    delegate_->OnReceivedData(socket, data, len);
}

void WebSocketJob::OnClose(SocketStream* socket) {
  state_ = CLOSED;
  SocketStream::Delegate* delegate = delegate_;
  delegate_ = NULL;
  socket_ = NULL;
  if (delegate)
    delegate->OnClose(socket);
}

void WebSocketJob::OnAuthRequired(
    SocketStream* socket, AuthChallengeInfo* auth_info) {
  if (delegate_)
    delegate_->OnAuthRequired(socket, auth_info);
}

void WebSocketJob::OnError(const SocketStream* socket, int error) {
  if (delegate_)
    delegate_->OnError(socket, error);
}

bool WebSocketJob::SendHandshakeRequest(const char* data, int len) {
  DCHECK_EQ(state_, CONNECTING);
  if (!handshake_request_.empty()) {
    // if we're already sending handshake message, don't send any more data
    // until handshake is completed.
    return false;
  }
  original_handshake_request_.append(data, len);
  original_handshake_request_header_length_ =
      HttpUtil::LocateEndOfHeaders(original_handshake_request_.data(),
                                   original_handshake_request_.size(), 0);
  if (original_handshake_request_header_length_ > 0) {
    // handshake message is completed.
    AddCookieHeaderAndSend();
  }
  // Just buffered in original_handshake_request_.
  return true;
}

void WebSocketJob::AddCookieHeaderAndSend() {
  AddRef();  // Balanced in OnCanGetCookiesCompleted

  int policy = OK;
  if (socket_->context()->cookie_policy()) {
    GURL url_for_cookies = GetURLForCookies();
    policy = socket_->context()->cookie_policy()->CanGetCookies(
        url_for_cookies,
        url_for_cookies,
        &can_get_cookies_callback_);
    if (policy == ERR_IO_PENDING)
      return;  // Wait for completion callback
  }
  OnCanGetCookiesCompleted(policy);
}

void WebSocketJob::OnCanGetCookiesCompleted(int policy) {
  if (socket_ && delegate_ && state_ == CONNECTING) {
    std::string handshake_request_status_line;
    std::string handshake_request_header;
    ParseHandshakeMessage(original_handshake_request_.data(),
                          original_handshake_request_header_length_,
                          &handshake_request_status_line,
                          &handshake_request_header);

    // Remove cookie headers.
    handshake_request_header = HttpUtil::StripHeaders(
        handshake_request_header,
        kCookieHeaders, arraysize(kCookieHeaders));

    if (policy == OK) {
      // Add cookies, including HttpOnly cookies.
      if (socket_->context()->cookie_store()) {
        CookieOptions cookie_options;
        cookie_options.set_include_httponly();
        std::string cookie =
            socket_->context()->cookie_store()->GetCookiesWithOptions(
                GetURLForCookies(), cookie_options);
        if (!cookie.empty()) {
          HttpUtil::AppendHeaderIfMissing("Cookie", cookie,
                                          &handshake_request_header);
        }
      }
    }

    // Simply ignore rest data in original request header after
    // original_handshake_request_header_length_, because websocket protocol
    // doesn't allow sending message before handshake is completed.
    // TODO(ukai): report as error?
    handshake_request_ =
          handshake_request_status_line + handshake_request_header + "\r\n";

    handshake_request_sent_ = 0;
    socket_->SendData(handshake_request_.data(),
                      handshake_request_.size());
  }
  Release();  // Balance AddRef taken in AddCookieHeaderAndSend
}

void WebSocketJob::OnSentHandshakeRequest(
    SocketStream* socket, int amount_sent) {
  DCHECK_EQ(state_, CONNECTING);
  handshake_request_sent_ += amount_sent;
  if (handshake_request_sent_ >= handshake_request_.size()) {
    // handshake request has been sent.
    // notify original size of handshake request to delegate.
    if (delegate_)
      delegate_->OnSentData(socket, original_handshake_request_.size());
  }
}

void WebSocketJob::OnReceivedHandshakeResponse(
    SocketStream* socket, const char* data, int len) {
  DCHECK_EQ(state_, CONNECTING);
  handshake_response_.append(data, len);
  handshake_response_header_length_ = HttpUtil::LocateEndOfHeaders(
      handshake_response_.data(),
      handshake_response_.size(), 0);
  if (handshake_response_header_length_ > 0) {
    // handshake message is completed.
    SaveCookiesAndNotifyHeaderComplete();
  }
}

void WebSocketJob::SaveCookiesAndNotifyHeaderComplete() {
  // handshake message is completed.
  DCHECK(handshake_response_.data());
  DCHECK_GT(handshake_response_header_length_, 0);

  response_cookies_.clear();
  response_cookies_save_index_ = 0;

  FetchResponseCookies(handshake_response_.data(),
                       handshake_response_header_length_,
                       &response_cookies_);

  // Now, loop over the response cookies, and attempt to persist each.
  SaveNextCookie();
}

void WebSocketJob::SaveNextCookie() {
  if (response_cookies_save_index_ == response_cookies_.size()) {
    response_cookies_.clear();
    response_cookies_save_index_ = 0;

    std::string handshake_response_status_line;
    std::string handshake_response_header;
    ParseHandshakeMessage(handshake_response_.data(),
                          handshake_response_header_length_,
                          &handshake_response_status_line,
                          &handshake_response_header);
    // Remove cookie headers.
    std::string filtered_handshake_response_header =
        HttpUtil::StripHeaders(
            handshake_response_header,
            kSetCookieHeaders, arraysize(kSetCookieHeaders));
    std::string remaining_data =
        std::string(handshake_response_.data() +
                    handshake_response_header_length_,
                    handshake_response_.size() -
                    handshake_response_header_length_);
    std::string received_data =
        handshake_response_status_line +
        filtered_handshake_response_header +
        "\r\n" +
        remaining_data;
    state_ = OPEN;
    if (delegate_)
      delegate_->OnReceivedData(socket_,
                                received_data.data(), received_data.size());
    return;
  }

  AddRef();  // Balanced in OnCanSetCookieCompleted

  int policy = OK;
  if (socket_->context()->cookie_policy()) {
    GURL url_for_cookies = GetURLForCookies();
    policy = socket_->context()->cookie_policy()->CanSetCookie(
        url_for_cookies,
        url_for_cookies,
        response_cookies_[response_cookies_save_index_],
        &can_set_cookie_callback_);
    if (policy == ERR_IO_PENDING)
      return;  // Wait for completion callback
  }

  OnCanSetCookieCompleted(policy);
}

void WebSocketJob::OnCanSetCookieCompleted(int policy) {
  if (socket_ && delegate_ && state_ == CONNECTING) {
    if ((policy == OK || policy == OK_FOR_SESSION_ONLY) &&
        socket_->context()->cookie_store()) {
      CookieOptions options;
      options.set_include_httponly();
      if (policy == OK_FOR_SESSION_ONLY)
        options.set_force_session();
      GURL url_for_cookies = GetURLForCookies();
      socket_->context()->cookie_store()->SetCookieWithOptions(
          url_for_cookies, response_cookies_[response_cookies_save_index_],
          options);
    }
    response_cookies_save_index_++;
    SaveNextCookie();
  }
  Release();  // Balance AddRef taken in SaveNextCookie
}

GURL WebSocketJob::GetURLForCookies() const {
  GURL url = socket_->url();
  std::string scheme = socket_->is_secure() ? "https" : "http";
  url_canon::Replacements<char> replacements;
  replacements.SetScheme(scheme.c_str(),
                         url_parse::Component(0, scheme.length()));
  return url.ReplaceComponents(replacements);
}

}  // namespace net
