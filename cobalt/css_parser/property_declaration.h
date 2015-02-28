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

#ifndef CSS_PARSER_PROPERTY_DECLARATION_H_
#define CSS_PARSER_PROPERTY_DECLARATION_H_

#include "base/memory/scoped_ptr.h"
#include "cobalt/css_parser/trivial_string_piece.h"
#include "cobalt/cssom/property_value.h"

namespace cobalt {
namespace css_parser {

// A helper used in YYSTYPE to hold together the name, value, and importance
// of the property.
struct PropertyDeclaration {
  PropertyDeclaration(const std::string& name,
                      const scoped_refptr<cssom::PropertyValue>& value,
                      bool important)
      : name(name), value(value), important(important) {}

  std::string name;
  scoped_refptr<cssom::PropertyValue> value;
  bool important;
};

}  // namespace css_parser
}  // namespace cobalt

#endif  // CSS_PARSER_PROPERTY_DECLARATION_H_
