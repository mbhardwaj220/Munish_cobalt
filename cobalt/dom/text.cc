/*
 * Copyright 2014 Google Inc. All Rights Reserved.
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

#include "cobalt/dom/text.h"

namespace cobalt {
namespace dom {

// static
scoped_refptr<Text> Text::Create(const base::StringPiece& text) {
  return make_scoped_refptr(new Text(text));
}

Text::Text(const base::StringPiece& text) : text_(text.begin(), text.end()) {}

const std::string& Text::node_name() const {
  static const std::string kTextName("#text");
  return kTextName;
}

bool Text::CheckAcceptAsChild(const scoped_refptr<Node>& child) const {
  // Can't attach children nodes to a text node.
  return false;
}

void Text::Accept(NodeVisitor* visitor) { visitor->Visit(this); }

void Text::Accept(ConstNodeVisitor* visitor) const { visitor->Visit(this); }

}  // namespace dom
}  // namespace cobalt
