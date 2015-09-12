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

#ifndef CSSOM_CSS_GROUPING_RULE_H_
#define CSSOM_CSS_GROUPING_RULE_H_

#include <string>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "cobalt/cssom/css_rule.h"
#include "cobalt/script/wrappable.h"

namespace cobalt {
namespace cssom {

class CSSRuleList;
class CSSRuleVisitor;

// The CSSGroupingRule interface represents an at-rule that contains other rules
//  nested inside itself.
//   http://www.w3.org/TR/cssom/#cssgroupingrule
//   http://www.w3.org/TR/css3-conditional/#cssgroupingrule
class CSSGroupingRule : public CSSRule {
 public:
  CSSGroupingRule();
  explicit CSSGroupingRule(const scoped_refptr<CSSRuleList>& css_rule_list);

  // Set the css rules for the style sheet.
  void set_css_rules(const scoped_refptr<CSSRuleList>& css_rule_list);

  // Returns a read-only, live object representing the CSS rules.
  scoped_refptr<CSSRuleList> css_rules();

  // Inserts a new rule into the css rule list of the group. This Web API takes
  // a string as input and parses it into a rule.
  unsigned int InsertRule(const std::string& rule, unsigned int index);

  // Custom, not in any spec.
  //

  // From CSSRule.
  void Accept(CSSRuleVisitor* visitor) OVERRIDE {
    UNREFERENCED_PARAMETER(visitor);
    NOTREACHED();
  }

  DEFINE_WRAPPABLE_TYPE(CSSGroupingRule);

 protected:
  virtual ~CSSGroupingRule() OVERRIDE;

 private:
  scoped_refptr<CSSRuleList> css_rule_list_;

  DISALLOW_COPY_AND_ASSIGN(CSSGroupingRule);
};

}  // namespace cssom
}  // namespace cobalt

#endif  // CSSOM_CSS_GROUPING_RULE_H_
