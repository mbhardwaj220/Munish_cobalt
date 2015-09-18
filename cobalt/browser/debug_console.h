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

#ifndef BROWSER_DEBUG_CONSOLE_H_
#define BROWSER_DEBUG_CONSOLE_H_

#include <string>

#include "cobalt/browser/web_module.h"

namespace cobalt {
namespace browser {

// DebugConsole wraps the web module used to implement the debug console.
class DebugConsole {
 public:
  enum DebugConsoleMode {
    kDebugConsoleOff,
    kDebugConsoleOn,
    kDebugConsoleHide,
    kDebugConsoleOnly
  };

  DebugConsole(const GURL& url, const WebModule::OnRenderTreeProducedCallback&
                                    render_tree_produced_callback,
               const base::Callback<void(const std::string&)>& error_callback,
               media::MediaModule* media_module,
               network::NetworkModule* network_module,
               const math::Size& window_dimensions,
               render_tree::ResourceProvider* resource_provider,
               float layout_refresh_rate, const WebModule::Options& options);
  ~DebugConsole();

  // Gets the user-specified debug console mode from the command-line.
  static DebugConsoleMode GetDebugConsoleModeFromCommandLine();

 private:
  // Sets up everything to do with the management of the web page that
  // implements the debug console.
  // This web module will produce a second render tree to combine with the main
  // one.
  WebModule web_module_;
};

}  // namespace browser
}  // namespace cobalt

#endif  // BROWSER_DEBUG_CONSOLE_H_
