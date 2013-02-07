/*
 * Copyright 2012 Google Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SRC_DIAL_SERVICE_H_
#define SRC_DIAL_SERVICE_H_

#include <string>

#include "base/threading/thread.h"
#include "net/dial/dial_udp_server.h"
#include "net/dial/dial_http_server.h"

class LBWebViewHost;

namespace net {

class DialService : public base::RefCountedThreadSafe<DialService> {
 public:
  DialService(LBWebViewHost* host);
  virtual ~DialService();

  void StartService();
  void StopService();

  bool is_running() const { return is_running_; }

 private:
  void SpinUpServices();
  void SpinDownServices();

  bool CurrentThreadIsValid() const {
    return MessageLoop::current() == thread_->message_loop();
  }

  scoped_ptr<base::Thread> thread_;
  scoped_ptr<net::DialHttpServer> http_server_;
  scoped_ptr<net::DialUdpServer> udp_server_;
  bool is_running_;

  LBWebViewHost* host_; // not owned.
};

} // namespace net

#endif // SRC_DIAL_SERVICE_H_
