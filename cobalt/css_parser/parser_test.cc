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

#include "cobalt/css_parser/parser.h"

#include "base/bind.h"
#include "cobalt/base/polymorphic_downcast.h"
#include "cobalt/cssom/css_rule_list.h"
#include "cobalt/cssom/css_style_declaration.h"
#include "cobalt/cssom/css_style_rule.h"
#include "cobalt/cssom/css_style_sheet.h"
#include "cobalt/cssom/length_value.h"
#include "cobalt/cssom/property_value_visitor.h"
#include "cobalt/cssom/rgba_color_value.h"
#include "cobalt/cssom/string_value.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace cobalt {
namespace css_parser {

using ::testing::ByRef;
using ::testing::Eq;
using ::testing::Pointee;
using ::testing::_;

class MockParserObserver {
 public:
  MOCK_METHOD1(OnWarning, void(const std::string& message));
  MOCK_METHOD1(OnError, void(const std::string& message));
};

class MockPropertyValueVisitor : public cssom::PropertyValueVisitor {
 public:
  MOCK_METHOD1(VisitInherited, void(cssom::InheritedValue* inherited_value));
  MOCK_METHOD1(VisitInitial, void(cssom::InitialValue* initial_value));
  MOCK_METHOD1(VisitLength, void(cssom::LengthValue* length_value));
  MOCK_METHOD1(VisitRGBAColor, void(cssom::RGBAColorValue* color_value));
  MOCK_METHOD1(VisitString, void(cssom::StringValue* string_value));
};

class ParserTest : public ::testing::Test {
 public:
  void SetUp() OVERRIDE {
    parser_observer_ = make_scoped_ptr(new MockParserObserver());
    parser_ = make_scoped_ptr(
        new Parser(base::Bind(&MockParserObserver::OnWarning,
                              base::Unretained(parser_observer_.get())),
                   base::Bind(&MockParserObserver::OnError,
                              base::Unretained(parser_observer_.get()))));
  }

  void TearDown() OVERRIDE {
    parser_.reset();
    parser_observer_.reset();
  }

 protected:
  scoped_ptr<MockParserObserver> parser_observer_;
  scoped_ptr<Parser> parser_;
};

// TODO(***REMOVED***): Test every reduction that has semantic action.

TEST_F(ParserTest, ParsesEmptyInput) {
  EXPECT_CALL(*parser_observer_, OnWarning(_)).Times(0);
  EXPECT_CALL(*parser_observer_, OnError(_)).Times(0);

  scoped_refptr<cssom::CSSStyleSheet> style_sheet =
      parser_->ParseStyleSheet("parser_test.css", "");
  ASSERT_NE(scoped_refptr<cssom::CSSStyleSheet>(), style_sheet);
  ASSERT_EQ(0, style_sheet->css_rules()->length());
}

TEST_F(ParserTest, HandlesUnrecoverableSyntaxError) {
  EXPECT_CALL(*parser_observer_, OnWarning(_)).Times(0);
  EXPECT_CALL(
      *parser_observer_,
      OnError("parser_test.css:1:15: error: unrecoverable syntax error"));

  scoped_refptr<cssom::CSSStyleSheet> style_sheet =
      parser_->ParseStyleSheet("parser_test.css", "@casino-royale");
  ASSERT_NE(scoped_refptr<cssom::CSSStyleSheet>(), style_sheet);
  ASSERT_EQ(0, style_sheet->css_rules()->length());
}

TEST_F(ParserTest, ParsesStylesheet) {
  EXPECT_CALL(
      *parser_observer_,
      OnWarning("parser_test.css:1:2: warning: @charset is not supported"));
  EXPECT_CALL(
      *parser_observer_,
      OnWarning(
          "parser_test.css:1:36: warning: property margin is not supported"));
  EXPECT_CALL(*parser_observer_, OnError(_)).Times(0);

  scoped_refptr<cssom::CSSStyleSheet> style_sheet = parser_->ParseStyleSheet(
      "parser_test.css", " @charset 'utf-8'; <!-- --> body { margin: 0; }");
  ASSERT_NE(scoped_refptr<cssom::CSSStyleSheet>(), style_sheet);
  ASSERT_EQ(1, style_sheet->css_rules()->length());
}

TEST_F(ParserTest, RecoversFromInvalidAtToken) {
  EXPECT_CALL(
      *parser_observer_,
      OnWarning("parser_test.css:1:9: warning: invalid token @cobalt-magic"));
  EXPECT_CALL(*parser_observer_, OnError(_)).Times(0);

  scoped_refptr<cssom::CSSStyleSheet> style_sheet = parser_->ParseStyleSheet(
      "parser_test.css", "body {} @cobalt-magic; div {}");
  ASSERT_NE(scoped_refptr<cssom::CSSStyleSheet>(), style_sheet);
  ASSERT_EQ(2, style_sheet->css_rules()->length());
}

TEST_F(ParserTest, RecoversFromInvalidRule) {
  EXPECT_CALL(*parser_observer_,
              OnWarning("parser_test.css:1:9: warning: invalid rule"));
  EXPECT_CALL(*parser_observer_, OnError(_)).Times(0);

  scoped_refptr<cssom::CSSStyleSheet> style_sheet = parser_->ParseStyleSheet(
      "parser_test.css", "body {} !important {} div {}");
  ASSERT_NE(scoped_refptr<cssom::CSSStyleSheet>(), style_sheet);
  ASSERT_EQ(2, style_sheet->css_rules()->length());
}

TEST_F(ParserTest, WarnsAboutUnsupportedCharset) {
  EXPECT_CALL(
      *parser_observer_,
      OnWarning("parser_test.css:1:1: warning: @charset is not supported"));
  EXPECT_CALL(*parser_observer_, OnError(_)).Times(0);

  scoped_refptr<cssom::CSSStyleSheet> style_sheet =
      parser_->ParseStyleSheet("parser_test.css", "@charset 'utf-8'; body {}");
  ASSERT_NE(scoped_refptr<cssom::CSSStyleSheet>(), style_sheet);
  ASSERT_EQ(1, style_sheet->css_rules()->length());
}

TEST_F(ParserTest, WarnsAboutUnsupportedInvalidCharsetFollowedByBlock) {
  EXPECT_CALL(
      *parser_observer_,
      OnWarning("parser_test.css:1:1: warning: @charset is not supported"));
  EXPECT_CALL(*parser_observer_, OnError(_)).Times(0);

  scoped_refptr<cssom::CSSStyleSheet> style_sheet = parser_->ParseStyleSheet(
      "parser_test.css", "@charset utf-3.14 {} body {}");
  ASSERT_NE(scoped_refptr<cssom::CSSStyleSheet>(), style_sheet);
  ASSERT_EQ(1, style_sheet->css_rules()->length());
}

TEST_F(ParserTest, WarnsAboutUnsupportedInvalidCharsetFollowedBySemicolon) {
  EXPECT_CALL(
      *parser_observer_,
      OnWarning("parser_test.css:1:1: warning: @charset is not supported"));
  EXPECT_CALL(*parser_observer_, OnError(_)).Times(0);

  scoped_refptr<cssom::CSSStyleSheet> style_sheet =
      parser_->ParseStyleSheet("parser_test.css", "@charset pony; body {}");
  ASSERT_NE(scoped_refptr<cssom::CSSStyleSheet>(), style_sheet);
  ASSERT_EQ(1, style_sheet->css_rules()->length());
}

TEST_F(ParserTest, ParsesNonTrivialInput) {
  EXPECT_CALL(
      *parser_observer_,
      OnWarning(
          "parser_test.css:2:3: warning: property padding is not supported"));
  EXPECT_CALL(*parser_observer_, OnWarning(
                                     "parser_test.css:3:3: warning: property "
                                     "line-height is not supported"));
  EXPECT_CALL(*parser_observer_, OnWarning(
                                     "parser_test.css:4:3: warning: property "
                                     "-moz-transition is not supported"));
  EXPECT_CALL(*parser_observer_, OnWarning(
                                     "parser_test.css:5:3: warning: property "
                                     "-webkit-transition is not supported"));
  EXPECT_CALL(*parser_observer_, OnWarning(
                                     "parser_test.css:6:3: warning: property "
                                     "transition is not supported"));
  EXPECT_CALL(*parser_observer_, OnWarning(
                                     "parser_test.css:7:3: warning: property "
                                     "transition-delay is not supported"));
  EXPECT_CALL(*parser_observer_,
              OnWarning(
                  "parser_test.css:8:3: warning: property "
                  "transition-timing-function is not supported"));
  EXPECT_CALL(*parser_observer_, OnError(_)).Times(0);

  scoped_refptr<cssom::CSSStyleSheet> style_sheet =
      parser_->ParseStyleSheet("parser_test.css",
                               ".lozenge {\n"
                               "  padding: 1.3em 0 0 1.5em;\n"
                               "  line-height: 3em;\n"
                               "  -moz-transition: opacity 100ms;\n"
                               "  -webkit-transition: opacity 100ms;\n"
                               "  transition: opacity 100ms;\n"
                               "  transition-delay: 100ms;\n"
                               "  transition-timing-function:\n"
                               "      cubic-bezier(0.4, 0.0, 0.2, 1.0);\n"
                               "}");
  ASSERT_NE(scoped_refptr<cssom::CSSStyleSheet>(), style_sheet);
  ASSERT_EQ(1, style_sheet->css_rules()->length());
}

TEST_F(ParserTest, ParsesOxideProperties) {
  EXPECT_CALL(*parser_observer_, OnWarning(_)).Times(0);
  EXPECT_CALL(*parser_observer_, OnError(_)).Times(0);

  scoped_refptr<cssom::CSSStyleSheet> style_sheet =
      parser_->ParseStyleSheet("cobalt-oxide.css",
                               "body {\n"
                               "  background-color: #ffffff;\n"
                               "  color: #0047ab;  /* Cobalt blue */\n"
                               "  font-family: \"Droid Sans\";\n"
                               "  font-size: 100px;\n"
                               "}\n");
  ASSERT_NE(scoped_refptr<cssom::CSSStyleSheet>(), style_sheet);

  scoped_refptr<cssom::CSSRuleList> css_rules = style_sheet->css_rules();
  ASSERT_EQ(1, css_rules->length());

  scoped_refptr<cssom::CSSStyleRule> style_rule =
      base::polymorphic_downcast<cssom::CSSStyleRule*>(
          css_rules->Item(0).get());

  scoped_refptr<cssom::CSSStyleDeclaration> style = style_rule->style();
  ASSERT_NE(scoped_refptr<cssom::CSSStyleDeclaration>(), style);

  MockPropertyValueVisitor mock_visitor;

  scoped_refptr<cssom::RGBAColorValue> background_color =
      new cssom::RGBAColorValue(0xffffffff);
  EXPECT_CALL(mock_visitor,
              VisitRGBAColor(Pointee(Eq(ByRef(*background_color)))));
  ASSERT_NE(static_cast<cssom::PropertyValue*>(NULL),
            style->background_color());
  style->background_color()->Accept(&mock_visitor);

  scoped_refptr<cssom::RGBAColorValue> color =
      new cssom::RGBAColorValue(0x0047abff);
  EXPECT_CALL(mock_visitor, VisitRGBAColor(Pointee(Eq(ByRef(*color)))));
  ASSERT_NE(static_cast<cssom::PropertyValue*>(NULL), style->color());
  style->color()->Accept(&mock_visitor);

  scoped_refptr<cssom::StringValue> font_family =
      new cssom::StringValue("Droid Sans");
  EXPECT_CALL(mock_visitor, VisitString(Pointee(Eq(ByRef(*font_family)))));
  ASSERT_NE(static_cast<cssom::PropertyValue*>(NULL), style->font_family());
  style->font_family()->Accept(&mock_visitor);

  scoped_refptr<cssom::LengthValue> font_size =
      new cssom::LengthValue(100, cssom::kPixelsUnit);
  EXPECT_CALL(mock_visitor, VisitLength(Pointee(Eq(ByRef(*font_size)))));
  ASSERT_NE(static_cast<cssom::PropertyValue*>(NULL), style->font_size());
  style->font_size()->Accept(&mock_visitor);
}

}  // namespace css_parser
}  // namespace cobalt
