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

#ifndef DOM_HTML_ELEMENT_H_
#define DOM_HTML_ELEMENT_H_

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/string_piece.h"
#include "cobalt/base/source_location.h"
#include "cobalt/cssom/css_style_declaration.h"
#include "cobalt/cssom/css_style_rule.h"
#include "cobalt/cssom/css_transition_set.h"
#include "cobalt/cssom/mutation_observer.h"
#include "cobalt/cssom/style_sheet_list.h"
#include "cobalt/dom/element.h"

namespace cobalt {
namespace dom {

class HTMLBodyElement;
class HTMLDivElement;
class HTMLElementContext;
class HTMLHeadElement;
class HTMLHtmlElement;
class HTMLLinkElement;
class HTMLMediaElement;
class HTMLScriptElement;
class HTMLSpanElement;
class HTMLStyleElement;

// The basic interface, from which all the HTML elements' interfaces inherit,
// and which must be used by elements that have no additional requirements.
//   http://www.w3.org/TR/html5/dom.html#htmlelement
class HTMLElement : public Element, public cssom::MutationObserver {
 public:
  // Web API: ElementCSSInlineStyle (implements)
  //   http://www.w3.org/TR/2013/WD-cssom-20131205/#elementcssinlinestyle
  const scoped_refptr<cssom::CSSStyleDeclaration>& style() { return style_; }

  // Custom, not in any spec: Node.
  scoped_refptr<Node> Duplicate() const OVERRIDE;

  // Custom, not in any spec: Element.
  scoped_refptr<HTMLElement> AsHTMLElement() OVERRIDE { return this; }

  // Custom, not in any spec.
  //
  // From cssom::CSSStyleDeclaration::MutationObserver.
  void OnCSSMutation() OVERRIDE;

  // Safe type conversion methods that will downcast to the required type if
  // possible or return NULL otherwise.
  virtual scoped_refptr<HTMLBodyElement> AsHTMLBodyElement();
  virtual scoped_refptr<HTMLDivElement> AsHTMLDivElement();
  virtual scoped_refptr<HTMLHeadElement> AsHTMLHeadElement();
  virtual scoped_refptr<HTMLHtmlElement> AsHTMLHtmlElement();
  virtual scoped_refptr<HTMLLinkElement> AsHTMLLinkElement();
  virtual scoped_refptr<HTMLMediaElement> AsHTMLMediaElement();
  virtual scoped_refptr<HTMLScriptElement> AsHTMLScriptElement();
  virtual scoped_refptr<HTMLSpanElement> AsHTMLSpanElement();
  virtual scoped_refptr<HTMLStyleElement> AsHTMLStyleElement();

  // Points to ">" of opening tag.
  virtual void SetOpeningTagLocation(
      const base::SourceLocation& /*opening_tag_location*/) {}

  // Used by layout engine to cache the computed values.
  // See http://www.w3.org/TR/css-cascade-3/#computed for the definition of
  // computed value.
  scoped_refptr<const cssom::CSSStyleDeclarationData> computed_style() const {
    return computed_style_;
  }

  // Used by layout engine to cache the rule matching results.
  cssom::RulesWithCascadePriority* matching_rules() {
    return matching_rules_.get();
  }

  cssom::TransitionSet* transitions() { return &transitions_; }

  // Updates the cached computed style of one HTML element.
  //   http://www.w3.org/TR/css-cascade-3/#value-stages
  void UpdateComputedStyle(
      const scoped_refptr<const cssom::CSSStyleDeclarationData>&
          parent_computed_style,
      const base::Time& style_change_event_time);
  // Calls UpdateComputedStyle() on itself and all descendants.
  void UpdateComputedStyleRecursively(
      const scoped_refptr<const cssom::CSSStyleDeclarationData>&
          parent_computed_style,
      const base::Time& style_change_event_time, bool ancestors_were_valid);

  // Updates the cached set of CSS rules that match with this HTML element.
  void UpdateMatchingRules(
      const scoped_refptr<cssom::CSSStyleSheet>& user_agent_style_sheet,
      const scoped_refptr<cssom::StyleSheetList>& author_style_sheets);
  // Calls UpdateMatchingRules() on itself and all descendants.
  void UpdateMatchingRulesRecursively(
      const scoped_refptr<cssom::CSSStyleSheet>& user_agent_style_sheet,
      const scoped_refptr<cssom::StyleSheetList>& author_style_sheets);

  DEFINE_WRAPPABLE_TYPE(HTMLElement);

 protected:
  HTMLElement(Document* document, HTMLElementContext* html_element_context);
  ~HTMLElement() OVERRIDE;

 private:
  void UpdateTransitions(const cssom::CSSStyleDeclarationData* source,
                         const cssom::CSSStyleDeclarationData* destination);

  scoped_refptr<cssom::CSSStyleDeclaration> style_;
  scoped_refptr<cssom::CSSStyleDeclarationData> computed_style_;
  scoped_ptr<cssom::RulesWithCascadePriority> matching_rules_;
  cssom::TransitionSet transitions_;

  // Keeps track of whether the HTML element's current computed style is out
  // of date or not.
  bool computed_style_valid_;
};

}  // namespace dom
}  // namespace cobalt

#endif  // DOM_HTML_ELEMENT_H_
