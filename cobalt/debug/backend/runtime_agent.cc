// Copyright 2016 The Cobalt Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "cobalt/debug/backend/runtime_agent.h"

#include "base/bind.h"

namespace cobalt {
namespace debug {
namespace backend {

namespace {
// Definitions from the set specified here:
// https://chromedevtools.github.io/devtools-protocol/1-3/Runtime
constexpr char kInspectorDomain[] = "Runtime";

// File to load JavaScript runtime implementation from.
constexpr char kScriptFile[] = "runtime.js";
}  // namespace

RuntimeAgent::RuntimeAgent(DebugDispatcher* dispatcher)
    : dispatcher_(dispatcher),
      ALLOW_THIS_IN_INITIALIZER_LIST(commands_(this, kInspectorDomain)) {
  DCHECK(dispatcher_);
  if (!dispatcher_->RunScriptFile(kScriptFile)) {
    DLOG(WARNING) << "Cannot execute Runtime initialization script.";
  }

  commands_["enable"] = &RuntimeAgent::Enable;
  commands_["disable"] = &RuntimeAgent::Disable;
  commands_["compileScript"] = &RuntimeAgent::CompileScript;

  dispatcher_->AddDomain(kInspectorDomain, commands_.Bind());
}

RuntimeAgent::~RuntimeAgent() { dispatcher_->RemoveDomain(kInspectorDomain); }

void RuntimeAgent::CompileScript(const Command& command) {
  // TODO: Parse the JS without eval-ing it... This is to support:
  // a) Multi-line input from the devtools console
  // b) https://developers.google.com/web/tools/chrome-devtools/snippets
  command.SendResponse();
}

void RuntimeAgent::Disable(const Command& command) { command.SendResponse(); }

void RuntimeAgent::Enable(const Command& command) {
  dispatcher_->SendScriptEvent(
      std::string(kInspectorDomain) + ".executionContextCreated",
      "runtime.executionContextCreatedEvent");
  command.SendResponse();
}

}  // namespace backend
}  // namespace debug
}  // namespace cobalt
