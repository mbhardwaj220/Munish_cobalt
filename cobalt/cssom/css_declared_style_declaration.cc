/*
 * Copyright 2016 Google Inc. All Rights Reserved.
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

#include "cobalt/cssom/css_declared_style_declaration.h"

#include "base/lazy_instance.h"
#include "cobalt/cssom/css_parser.h"
#include "cobalt/cssom/css_style_declaration_data.h"
#include "cobalt/cssom/mutation_observer.h"

namespace cobalt {
namespace cssom {

namespace {

struct NonTrivialStaticFields {
  NonTrivialStaticFields()
      : location(base::SourceLocation(
            CSSStyleDeclaration::GetSourceLocationName(), 1, 1)) {}

  const base::SourceLocation location;

 private:
  DISALLOW_COPY_AND_ASSIGN(NonTrivialStaticFields);
};

// |non_trivial_static_fields| will be lazily created on the first time it's
// accessed.
base::LazyInstance<NonTrivialStaticFields> non_trivial_static_fields =
    LAZY_INSTANCE_INITIALIZER;

}  // namespace

CSSDeclaredStyleDeclaration::CSSDeclaredStyleDeclaration(CSSParser* css_parser)
    : data_(new CSSStyleDeclarationData),
      css_parser_(css_parser),
      mutation_observer_(NULL) {}

CSSDeclaredStyleDeclaration::CSSDeclaredStyleDeclaration(
    const scoped_refptr<CSSStyleDeclarationData>& style, CSSParser* css_parser)
    : data_(style), css_parser_(css_parser), mutation_observer_(NULL) {
  DCHECK(data_.get());
}

// This returns the result of serializing a CSS declaration block.
// The current implementation does not handle shorthands.
//   https://www.w3.org/TR/cssom/#serialize-a-css-declaration-block
std::string CSSDeclaredStyleDeclaration::css_text(
    script::ExceptionState* /*exception_state*/) const {
  return data_->SerializeCSSDeclarationBlock();
}

void CSSDeclaredStyleDeclaration::set_css_text(
    const std::string& css_text, script::ExceptionState* /*exception_state*/) {
  DCHECK(css_parser_);
  scoped_refptr<CSSStyleDeclarationData> declaration =
      css_parser_->ParseStyleDeclarationList(
          css_text, non_trivial_static_fields.Get().location);

  bool changed = true;

  if (declaration) {
    if (*data_ == *declaration) {
      changed = false;
    }
    data_ = declaration;
  } else {
    data_ = new CSSStyleDeclarationData();
  }

  if (changed) {
    RecordMutation();
  }
}

// The length attribute must return the number of CSS declarations in the
// declarations.
//   https://www.w3.org/TR/cssom/#dom-cssstyledeclaration-length
unsigned int CSSDeclaredStyleDeclaration::length() const {
  return data_->length();
}

// The item(index) method must return the property name of the CSS declaration
// at position index.
//   https://www.w3.org/TR/cssom/#dom-cssstyledeclaration-item
base::optional<std::string> CSSDeclaredStyleDeclaration::Item(
    unsigned int index) const {
  const char* item = data_->Item(index);
  return item ? base::optional<std::string>(item) : base::nullopt;
}

std::string CSSDeclaredStyleDeclaration::GetDeclaredPropertyValueStringByKey(
    const PropertyKey key) const {
  return data_->GetDeclaredPropertyValueString(key);
}

void CSSDeclaredStyleDeclaration::SetPropertyValue(
    const std::string& property_name, const std::string& property_value,
    script::ExceptionState* /*exception_state*/) {
  DCHECK(css_parser_);
  css_parser_->ParsePropertyIntoDeclarationData(
      property_name, property_value, non_trivial_static_fields.Get().location,
      data_.get());

  RecordMutation();
}

void CSSDeclaredStyleDeclaration::RecordMutation() {
  if (mutation_observer_) {
    // Trigger layout update.
    mutation_observer_->OnCSSMutation();
  }
}

}  // namespace cssom
}  // namespace cobalt
