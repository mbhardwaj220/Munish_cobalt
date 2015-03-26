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

#ifndef BROWSER_WEB_MODULE_H_
#define BROWSER_WEB_MODULE_H_

#include "base/threading/thread_checker.h"
#include "cobalt/css_parser/parser.h"
#include "cobalt/dom/window.h"
#include "cobalt/layout/layout_manager.h"
#include "cobalt/loader/fetcher_factory.h"
#include "cobalt/math/size.h"
#include "cobalt/media/media_module.h"
#include "cobalt/render_tree/resource_provider.h"
#include "cobalt/script/global_object_proxy.h"
#include "cobalt/script/javascript_engine.h"
#include "cobalt/script/script_runner.h"
#include "googleurl/src/gurl.h"

namespace cobalt {
namespace browser {

// WebModule hosts all components of Cobalt that deal with or implement the
// WebAPI.  This includes the ability to fetch resources given a URL, parse
// various web formats like HTML and CSS, host a DOM tree, manage a JavaScript
// engine, and lay out a web page.  Ultimately, interaction with WebModule is
// done through calls to InjectEvent() such as when dealing with external input
// (e.g. keyboards and gamepads), and handling render tree output from WebModule
// when it calls the on_render_tree_produced_ callback (provided upon
// construction).
// It is expected that all components internal to WebModule will operate on
// the same thread.
class WebModule {
 public:
  // All browser subcomponent options should have default constructors that
  // setup reasonable default options.
  struct Options {
    Options() : layout_trigger(layout::LayoutManager::kOnDocumentMutation) {}

    GURL url;
    layout::LayoutManager::LayoutTrigger layout_trigger;
  };

  WebModule(const layout::LayoutManager::OnRenderTreeProducedCallback&
                on_render_tree_produced,
            const math::Size& window_dimensions,
            render_tree::ResourceProvider* resource_provider,
            const Options& options);
  ~WebModule();

  // Call this to inject a key event into the web module which will ultimately
  // make its way to the DOM's Document object and handled appropriately.
  void InjectEvent(const scoped_refptr<dom::Event>& event);

  static std::string GetUserAgent();

 private:
  // Ensures that all calls to the WebModule are made from the same thread.
  base::ThreadChecker thread_checker_;

  scoped_ptr<css_parser::Parser> css_parser_;

  // JavaScript engine for the browser.
  scoped_ptr<script::JavaScriptEngine> javascript_engine_;

  // JavaScript Global Object for the browser. There should be one per window,
  // but since there is only one window, we can have one per browser.
  scoped_refptr<script::GlobalObjectProxy> global_object_proxy_;

  // Interface for the document to execute JavaScript code.
  scoped_ptr<script::ScriptRunner> script_runner_;

  // FetcherFactory that is used to create a fetcher according to URL.
  scoped_ptr<loader::FetcherFactory> fetcher_factory_;

  // The Window object wraps all DOM-related components.
  scoped_refptr<dom::Window> window_;

  // Triggers layout whenever the document changes.
  layout::LayoutManager layout_manager_;

  // Controls all media playback related objects/resources.
  scoped_ptr<media::MediaModule> media_module_;
};

}  // namespace browser
}  // namespace cobalt

#endif  // BROWSER_WEB_MODULE_H_
