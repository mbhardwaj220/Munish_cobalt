/*
 * Copyright 2015 Google Inc. All Rights Reserved.
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

#include "cobalt/network/network_module.h"

#include "base/logging.h"
#include "base/stringprintf.h"
#include "base/synchronization/waitable_event.h"
#include "base/threading/thread.h"
#include "cobalt/network/network_system.h"

namespace cobalt {
namespace network {

namespace {
// Do-nothing callback, intended to release these resources
// on the IO thread. Called during NetworkModule destruction.
void OnDestroy(scoped_ptr<URLRequestContext> /* url_request_context */,
               scoped_ptr<NetworkDelegate> /* network_delegate */) {}
}  // namespace

NetworkModule::NetworkModule()
    : storage_manager_(NULL), preferred_language_("en-US") {
  Initialize(NULL /* event_dispatcher */);
}

NetworkModule::NetworkModule(storage::StorageManager* storage_manager,
                             base::EventDispatcher* event_dispatcher,
                             const std::string& preferred_language)
    : storage_manager_(storage_manager),
      preferred_language_(preferred_language) {
  Initialize(event_dispatcher);
}

NetworkModule::~NetworkModule() {
  // Order of destruction is important here.
  // URLRequestContext and NetworkDelegate must be destroyed on the IO thread.
  // The ObjectWatchMultiplexer must be destroyed last.  (The sockets owned
  // by URLRequestContext will destroy their ObjectWatchers, which need the
  // multiplexer.)
  url_request_context_getter_ = NULL;
  message_loop_proxy()->PostTask(
      FROM_HERE, base::Bind(&OnDestroy, base::Passed(&url_request_context_),
                            base::Passed(&network_delegate_)));
  // This will run the above task, and then stop the thread.
  thread_.reset(NULL);
  object_watch_multiplexer_.reset(NULL);
  network_system_.reset(NULL);
}

void NetworkModule::Initialize(base::EventDispatcher* event_dispatcher) {
  thread_.reset(new base::Thread("NetworkModule"));
  object_watch_multiplexer_.reset(new base::ObjectWatchMultiplexer());
  user_agent_.reset(new UserAgent(preferred_language_));

  network_system_ = NetworkSystem::Create(event_dispatcher);

  // Launch the IO thread.
  base::Thread::Options thread_options;
  thread_options.message_loop_type = MessageLoop::TYPE_IO;
  thread_options.stack_size = 256 * 1024;
  thread_->StartWithOptions(thread_options);

  base::WaitableEvent creation_event(true, false);
  // Run Network module startup on IO thread,
  // so the network delegate and URL request context are
  // constructed on that thread.
  message_loop_proxy()->PostTask(
      FROM_HERE, base::Bind(&NetworkModule::OnCreate, base::Unretained(this),
                            &creation_event));
  // Wait for OnCreate() to run, so we can be sure our members
  // have been constructed.
  creation_event.Wait();
  DCHECK(url_request_context_);
  url_request_context_getter_ = new network::URLRequestContextGetter(
      url_request_context_.get(), thread_.get());
}

void NetworkModule::OnCreate(base::WaitableEvent* creation_event) {
  DCHECK(message_loop_proxy()->BelongsToCurrentThread());

  url_request_context_.reset(new URLRequestContext(storage_manager_));
  NetworkDelegate::Options net_options;
  // TODO(***REMOVED***): Specify any override to the cookie settings
  // in net_options.
  network_delegate_.reset(new NetworkDelegate(net_options));
  url_request_context_->set_http_user_agent_settings(user_agent_.get());
  url_request_context_->set_network_delegate(network_delegate_.get());
  creation_event->Signal();
}

}  // namespace network
}  // namespace cobalt
