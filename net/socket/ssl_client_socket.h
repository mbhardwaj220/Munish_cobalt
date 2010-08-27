// Copyright (c) 2006-2009 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SOCKET_SSL_CLIENT_SOCKET_H_
#define NET_SOCKET_SSL_CLIENT_SOCKET_H_
#pragma once

#include <string>

#include "net/base/load_flags.h"
#include "net/base/net_errors.h"
#include "net/socket/client_socket.h"

namespace net {

class SSLCertRequestInfo;
class SSLInfo;

// A client socket that uses SSL as the transport layer.
//
// NOTE: The SSL handshake occurs within the Connect method after a TCP
// connection is established.  If a SSL error occurs during the handshake,
// Connect will fail.
//
class SSLClientSocket : public ClientSocket {
 public:
  SSLClientSocket() : was_npn_negotiated_(false), was_spdy_negotiated_(false) {
  }
  // Next Protocol Negotiation (NPN) allows a TLS client and server to come to
  // an agreement about the application level protocol to speak over a
  // connection.
  enum NextProtoStatus {
    kNextProtoUnsupported = 0,  // The server doesn't support NPN.
    kNextProtoNegotiated = 1,   // We agreed on a protocol.
    kNextProtoNoOverlap = 2,    // No protocols in common. We requested
                                // the first protocol in our list.
  };

  // Next Protocol Negotiation (NPN), if successful, results in agreement on an
  // application-level string that specifies the application level protocol to
  // use over the TLS connection. NextProto enumerates the application level
  // protocols that we recognise.
  enum NextProto {
    kProtoUnknown = 0,
    kProtoHTTP11 = 1,
    kProtoSPDY1 = 2,
    kProtoSPDY2 = 3,
  };

  // Gets the SSL connection information of the socket.
  virtual void GetSSLInfo(SSLInfo* ssl_info) = 0;

  // Gets the SSL CertificateRequest info of the socket after Connect failed
  // with ERR_SSL_CLIENT_AUTH_CERT_NEEDED.
  virtual void GetSSLCertRequestInfo(
      SSLCertRequestInfo* cert_request_info) = 0;

  // Get the application level protocol that we negotiated with the server.
  // *proto is set to the resulting protocol (n.b. that the string may have
  // embedded NULs).
  //   kNextProtoUnsupported: *proto is cleared.
  //   kNextProtoNegotiated:  *proto is set to the negotiated protocol.
  //   kNextProtoNoOverlap:   *proto is set to the first protocol in the
  //                          supported list.
  virtual NextProtoStatus GetNextProto(std::string* proto) = 0;

  static NextProto NextProtoFromString(const std::string& proto_string) {
    if (proto_string == "http1.1" || proto_string == "http/1.1") {
      return kProtoHTTP11;
    } else if (proto_string == "spdy/1") {
      return kProtoSPDY1;
    } else if (proto_string == "spdy/2") {
      return kProtoSPDY2;
    } else {
      return kProtoUnknown;
    }
  }

  static bool IgnoreCertError(int error, int load_flags) {
    if (error == OK || load_flags & LOAD_IGNORE_ALL_CERT_ERRORS)
      return true;

    if (error == ERR_CERT_COMMON_NAME_INVALID &&
        (load_flags & LOAD_IGNORE_CERT_COMMON_NAME_INVALID))
      return true;
    if(error == ERR_CERT_DATE_INVALID &&
            (load_flags & LOAD_IGNORE_CERT_DATE_INVALID))
      return true;
    if(error == ERR_CERT_AUTHORITY_INVALID &&
            (load_flags & LOAD_IGNORE_CERT_AUTHORITY_INVALID))
      return true;

    return false;
  }

  virtual bool was_npn_negotiated() const {
    return was_npn_negotiated_;
  }

  virtual bool set_was_npn_negotiated(bool negotiated) {
    return was_npn_negotiated_ = negotiated;
  }

  virtual bool was_spdy_negotiated() const {
    return was_spdy_negotiated_;
  }

  virtual bool set_was_spdy_negotiated(bool negotiated) {
    return was_spdy_negotiated_ = negotiated;
  }

 private:
  // True if NPN was responded to, independent of selecting SPDY or HTTP.
  bool was_npn_negotiated_;
  // True if NPN successfully negotiated SPDY.
  bool was_spdy_negotiated_;
};

}  // namespace net

#endif  // NET_SOCKET_SSL_CLIENT_SOCKET_H_
