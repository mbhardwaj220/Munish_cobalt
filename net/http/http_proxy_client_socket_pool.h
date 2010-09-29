// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_HTTP_HTTP_PROXY_CLIENT_SOCKET_POOL_H_
#define NET_HTTP_HTTP_PROXY_CLIENT_SOCKET_POOL_H_
#pragma once

#include <string>

#include "base/basictypes.h"
#include "base/ref_counted.h"
#include "base/scoped_ptr.h"
#include "base/time.h"
#include "net/base/host_port_pair.h"
#include "net/http/http_auth.h"
#include "net/socket/client_socket_pool_base.h"
#include "net/socket/client_socket_pool_histograms.h"
#include "net/socket/client_socket_pool.h"

namespace net {

class HostResolver;
class HttpAuthCache;
class HttpAuthHandlerFactory;
class SSLClientSocketPool;
class SSLSocketParams;
class TCPClientSocketPool;
class TCPSocketParams;

// HttpProxySocketParams only needs the socket params for one of the proxy
// types.  The other param must be NULL.  When using an HTTP Proxy,
// |tcp_params| must be set.  When using an HTTPS Proxy, |ssl_params|
// must be set.
class HttpProxySocketParams : public base::RefCounted<HttpProxySocketParams> {
 public:
  HttpProxySocketParams(const scoped_refptr<TCPSocketParams>& tcp_params,
                        const scoped_refptr<SSLSocketParams>& ssl_params,
                        const GURL& request_url,
                        const std::string& user_agent,
                        HostPortPair endpoint,
                        HttpAuthCache* http_auth_cache,
                        HttpAuthHandlerFactory* http_auth_handler_factory,
                        bool tunnel);

  const scoped_refptr<TCPSocketParams>& tcp_params() const {
    return tcp_params_;
  }
  const scoped_refptr<SSLSocketParams>& ssl_params() const {
    return ssl_params_;
  }
  const GURL& request_url() const { return request_url_; }
  const std::string& user_agent() const { return user_agent_; }
  const HostPortPair& endpoint() const { return endpoint_; }
  HttpAuthCache* http_auth_cache() const { return http_auth_cache_; }
  HttpAuthHandlerFactory* http_auth_handler_factory() const {
    return http_auth_handler_factory_;
  }
  const HostResolver::RequestInfo& destination() const;
  bool tunnel() const { return tunnel_; }

 private:
  friend class base::RefCounted<HttpProxySocketParams>;
  ~HttpProxySocketParams();

  const scoped_refptr<TCPSocketParams> tcp_params_;
  const scoped_refptr<SSLSocketParams> ssl_params_;
  const GURL request_url_;
  const std::string user_agent_;
  const HostPortPair endpoint_;
  HttpAuthCache* const http_auth_cache_;
  HttpAuthHandlerFactory* const http_auth_handler_factory_;
  const bool tunnel_;

  DISALLOW_COPY_AND_ASSIGN(HttpProxySocketParams);
};

// HttpProxyConnectJob optionally establishes a tunnel through the proxy
// server after connecting the underlying transport socket.
class HttpProxyConnectJob : public ConnectJob {
 public:
  HttpProxyConnectJob(const std::string& group_name,
                      const scoped_refptr<HttpProxySocketParams>& params,
                      const base::TimeDelta& timeout_duration,
                      TCPClientSocketPool* tcp_pool,
                      SSLClientSocketPool* ssl_pool,
                      const scoped_refptr<HostResolver> &host_resolver,
                      Delegate* delegate,
                      NetLog* net_log);
  virtual ~HttpProxyConnectJob();

  // ConnectJob methods.
  virtual LoadState GetLoadState() const;

 private:
  enum State {
    STATE_TCP_CONNECT,
    STATE_TCP_CONNECT_COMPLETE,
    STATE_SSL_CONNECT,
    STATE_SSL_CONNECT_COMPLETE,
    STATE_HTTP_PROXY_CONNECT,
    STATE_HTTP_PROXY_CONNECT_COMPLETE,
    STATE_NONE,
  };

  // Begins the tcp connection and the optional Http proxy tunnel.  If the
  // request is not immediately servicable (likely), the request will return
  // ERR_IO_PENDING. An OK return from this function or the callback means
  // that the connection is established; ERR_PROXY_AUTH_REQUESTED means
  // that the tunnel needs authentication credentials, the socket will be
  // returned in this case, and must be release back to the pool; or
  // a standard net error code will be returned.
  virtual int ConnectInternal();

  void OnIOComplete(int result);

  // Runs the state transition loop.
  int DoLoop(int result);

  // Connecting to HTTP Proxy
  int DoTCPConnect();
  int DoTCPConnectComplete(int result);
  // Connecting to HTTPS Proxy
  int DoSSLConnect();
  int DoSSLConnectComplete(int result);

  int DoHttpProxyConnect();
  int DoHttpProxyConnectComplete(int result);

  scoped_refptr<HttpProxySocketParams> params_;
  TCPClientSocketPool* const tcp_pool_;
  SSLClientSocketPool* const ssl_pool_;
  const scoped_refptr<HostResolver> resolver_;

  State next_state_;
  CompletionCallbackImpl<HttpProxyConnectJob> callback_;
  scoped_ptr<ClientSocketHandle> transport_socket_handle_;
  scoped_ptr<ClientSocket> transport_socket_;
  bool using_spdy_;

  DISALLOW_COPY_AND_ASSIGN(HttpProxyConnectJob);
};

class HttpProxyClientSocketPool : public ClientSocketPool {
 public:
  HttpProxyClientSocketPool(
      int max_sockets,
      int max_sockets_per_group,
      ClientSocketPoolHistograms* histograms,
      const scoped_refptr<HostResolver>& host_resolver,
      TCPClientSocketPool* tcp_pool,
      SSLClientSocketPool* ssl_pool,
      NetLog* net_log);

  virtual ~HttpProxyClientSocketPool();

  // ClientSocketPool methods:
  virtual int RequestSocket(const std::string& group_name,
                            const void* connect_params,
                            RequestPriority priority,
                            ClientSocketHandle* handle,
                            CompletionCallback* callback,
                            const BoundNetLog& net_log);

  virtual void CancelRequest(const std::string& group_name,
                             ClientSocketHandle* handle);

  virtual void ReleaseSocket(const std::string& group_name,
                             ClientSocket* socket,
                             int id);

  virtual void Flush();

  virtual void CloseIdleSockets();

  virtual int IdleSocketCount() const {
    return base_.idle_socket_count();
  }

  virtual int IdleSocketCountInGroup(const std::string& group_name) const;

  virtual LoadState GetLoadState(const std::string& group_name,
                                 const ClientSocketHandle* handle) const;

  virtual DictionaryValue* GetInfoAsValue(const std::string& name,
                                          const std::string& type,
                                          bool include_nested_pools) const;

  virtual base::TimeDelta ConnectionTimeout() const {
    return base_.ConnectionTimeout();
  }

  virtual ClientSocketPoolHistograms* histograms() const {
    return base_.histograms();
  };

 private:
  typedef ClientSocketPoolBase<HttpProxySocketParams> PoolBase;

  class HttpProxyConnectJobFactory : public PoolBase::ConnectJobFactory {
   public:
    HttpProxyConnectJobFactory(
        TCPClientSocketPool* tcp_pool,
        SSLClientSocketPool* ssl_pool,
        HostResolver* host_resolver,
        NetLog* net_log);

    // ClientSocketPoolBase::ConnectJobFactory methods.
    virtual ConnectJob* NewConnectJob(const std::string& group_name,
                                      const PoolBase::Request& request,
                                      ConnectJob::Delegate* delegate) const;

    virtual base::TimeDelta ConnectionTimeout() const { return timeout_; }

   private:
    TCPClientSocketPool* const tcp_pool_;
    SSLClientSocketPool* const ssl_pool_;
    const scoped_refptr<HostResolver> host_resolver_;
    NetLog* net_log_;
    base::TimeDelta timeout_;

    DISALLOW_COPY_AND_ASSIGN(HttpProxyConnectJobFactory);
  };

  TCPClientSocketPool* const tcp_pool_;
  SSLClientSocketPool* const ssl_pool_;
  PoolBase base_;

  DISALLOW_COPY_AND_ASSIGN(HttpProxyClientSocketPool);
};

REGISTER_SOCKET_PARAMS_FOR_POOL(HttpProxyClientSocketPool,
                                HttpProxySocketParams);

}  // namespace net

#endif  // NET_HTTP_HTTP_PROXY_CLIENT_SOCKET_POOL_H_
