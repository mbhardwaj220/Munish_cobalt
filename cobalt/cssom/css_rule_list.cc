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

#include "cobalt/cssom/css_rule_list.h"

#include <limits>

#include "base/logging.h"
#include "cobalt/cssom/css_font_face_rule.h"
#include "cobalt/cssom/css_media_rule.h"
#include "cobalt/cssom/css_parser.h"
#include "cobalt/cssom/css_rule_visitor.h"
#include "cobalt/cssom/css_style_rule.h"
#include "cobalt/cssom/css_style_sheet.h"

namespace cobalt {
namespace cssom {

CSSRuleList::CSSRuleList() : parent_style_sheet_(NULL) {}

scoped_refptr<CSSRule> CSSRuleList::Item(unsigned int index) const {
  return index < css_rules_.size() ? css_rules_[index] : NULL;
}

unsigned int CSSRuleList::length() const {
  CHECK_LE(css_rules_.size(), std::numeric_limits<unsigned int>::max());
  return static_cast<unsigned int>(css_rules_.size());
}

unsigned int CSSRuleList::InsertRule(const std::string& rule,
                                     unsigned int index) {
  DCHECK(parent_style_sheet_);
  scoped_refptr<CSSStyleRule> css_rule =
      parent_style_sheet_->css_parser()->ParseStyleRule(
          rule, base::SourceLocation("[object CSSStyleSheet]", 1, 1));

  if (!css_rule) {
    return 0;
  }

  if (index > css_rules_.size()) {
    // TODO(***REMOVED***): Throw JS IndexSizeError.
    LOG(ERROR) << "IndexSizeError";
    return 0;
  }

  // TODO(***REMOVED***): Currently we only support appending rule to the end of the
  // rule list, which is the use case in performance spike and ***REMOVED***. Properly
  // implement insertion if necessary.
  if (index != css_rules_.size()) {
    LOG(WARNING) << "InsertRule will always append the rule to the end of the "
                    "rule list.";
  }

  AppendCSSStyleRule(css_rule);
  return index;
}

void CSSRuleList::AttachToCSSStyleSheet(CSSStyleSheet* style_sheet) {
  DCHECK(style_sheet);
  parent_style_sheet_ = style_sheet;
  for (CSSRules::iterator it = css_rules_.begin(); it != css_rules_.end();
       ++it) {
    DCHECK(*it);
    (*it)->AttachToCSSStyleSheet(style_sheet);
  }
}

void CSSRuleList::AppendCSSStyleRule(
    const scoped_refptr<CSSStyleRule>& css_style_rule) {
  if (parent_style_sheet_) {
    css_style_rule->AttachToCSSStyleSheet(parent_style_sheet_);
    parent_style_sheet_->OnCSSMutation();
  }
  css_rules_.push_back(css_style_rule);
}

// Appends a CSSFontFaceRule to the current style sheet.
void CSSRuleList::AppendCSSFontFaceRule(
    const scoped_refptr<CSSFontFaceRule>& css_font_face_rule) {
  css_rules_.push_back(css_font_face_rule);
}

// Appends a CSSMediaRule to the current style sheet.
void CSSRuleList::AppendCSSMediaRule(
    const scoped_refptr<CSSMediaRule>& css_media_rule) {
  if (parent_style_sheet_) {
    css_media_rule->AttachToCSSStyleSheet(parent_style_sheet_);
    parent_style_sheet_->OnCSSMutation();
  }
  css_rules_.push_back(css_media_rule);
}

void CSSRuleList::Accept(CSSRuleVisitor* visitor) {
  for (CSSRules::const_iterator it = css_rules_.begin(); it != css_rules_.end();
       ++it) {
    (*it)->Accept(visitor);
  }
}

CSSRuleList::~CSSRuleList() {}

}  // namespace cssom
}  // namespace cobalt
