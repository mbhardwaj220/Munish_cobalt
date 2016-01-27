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

#include "cobalt/render_tree/node_visitor.h"

#include <string>

#include "cobalt/math/size.h"
#include "cobalt/render_tree/composition_node.h"
#include "cobalt/render_tree/filter_node.h"
#include "cobalt/render_tree/font.h"
#include "cobalt/render_tree/image_node.h"
#include "cobalt/render_tree/rect_node.h"
#include "cobalt/render_tree/rect_shadow_node.h"
#include "cobalt/render_tree/text_node.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

using cobalt::render_tree::Brush;
using cobalt::render_tree::BrushVisitor;
using cobalt::render_tree::ColorRGBA;
using cobalt::render_tree::CompositionNode;
using cobalt::render_tree::FilterNode;
using cobalt::render_tree::Font;
using cobalt::render_tree::FontMetrics;
using cobalt::render_tree::Image;
using cobalt::render_tree::ImageNode;
using cobalt::render_tree::NodeVisitor;
using cobalt::render_tree::OpacityFilter;
using cobalt::render_tree::RectNode;
using cobalt::render_tree::RectShadowNode;
using cobalt::render_tree::TextNode;

class MockNodeVisitor : public NodeVisitor {
 public:
  MOCK_METHOD1(Visit, void(CompositionNode* composition));
  MOCK_METHOD1(Visit, void(FilterNode* image));
  MOCK_METHOD1(Visit, void(ImageNode* image));
  MOCK_METHOD1(Visit, void(RectNode* rect));
  MOCK_METHOD1(Visit, void(RectShadowNode* rect_shadow));
  MOCK_METHOD1(Visit, void(TextNode* text));
};

TEST(NodeVisitorTest, VisitsComposition) {
  scoped_refptr<CompositionNode> composition(
      new CompositionNode(CompositionNode::Builder()));
  MockNodeVisitor mock_visitor;
  EXPECT_CALL(mock_visitor, Visit(composition.get()));
  composition->Accept(&mock_visitor);
}

TEST(NodeVisitorTest, VisitsFilter) {
  scoped_refptr<FilterNode> filter(new FilterNode(OpacityFilter(0.5f), NULL));
  MockNodeVisitor mock_visitor;
  EXPECT_CALL(mock_visitor, Visit(filter.get()));
  filter->Accept(&mock_visitor);
}

namespace {

class DummyImage : public Image {
  const cobalt::math::Size& GetSize() const OVERRIDE { return size_; }

 private:
  cobalt::math::Size size_;
};

class DummyBrush : public Brush {
  void Accept(BrushVisitor* visitor) const OVERRIDE {
    UNREFERENCED_PARAMETER(visitor);
  }
};

}  // namespace

TEST(NodeVisitorTest, VisitsImage) {
  scoped_refptr<DummyImage> image = make_scoped_refptr(new DummyImage());
  scoped_refptr<ImageNode> image_node(new ImageNode(image));
  MockNodeVisitor mock_visitor;
  EXPECT_CALL(mock_visitor, Visit(image_node.get()));
  image_node->Accept(&mock_visitor);
}

TEST(NodeVisitorTest, VisitsRect) {
  scoped_refptr<RectNode> rect(
      new RectNode(cobalt::math::SizeF(), scoped_ptr<Brush>(new DummyBrush())));
  MockNodeVisitor mock_visitor;
  EXPECT_CALL(mock_visitor, Visit(rect.get()));
  rect->Accept(&mock_visitor);
}

TEST(NodeVisitorTest, VisitsRectShadow) {
  scoped_refptr<RectShadowNode> rect_shadow(new RectShadowNode(
      cobalt::math::SizeF(),
      cobalt::render_tree::Shadow(
          cobalt::math::Vector2dF(1.0f, 1.0f), 1.0f,
          ColorRGBA(0, 0, 0, 1.0f))));
  MockNodeVisitor mock_visitor;
  EXPECT_CALL(mock_visitor, Visit(rect_shadow.get()));
  rect_shadow->Accept(&mock_visitor);
}

namespace {

class DummyFont : public Font {
 public:
  cobalt::render_tree::TypefaceId GetTypefaceId() const OVERRIDE { return 0; }

  cobalt::math::RectF GetBounds(const std::string& text) const OVERRIDE {
    UNREFERENCED_PARAMETER(text);
    return cobalt::math::RectF();
  }

  FontMetrics GetFontMetrics() const OVERRIDE {
    return FontMetrics(0, 0, 0, 0);
  }

  uint32 GetEstimatedSizeInBytes() const OVERRIDE { return 0; }

  scoped_refptr<Font> CloneWithSize(float font_size) const OVERRIDE {
    UNREFERENCED_PARAMETER(font_size);
    return NULL;
  }

  cobalt::render_tree::GlyphIndex GetGlyphForCharacter(
      int32 utf32_character) const OVERRIDE {
    UNREFERENCED_PARAMETER(utf32_character);
    return cobalt::render_tree::GlyphIndex(1);
  }
};

}  // namespace

TEST(NodeVisitorTest, VisitsText) {
  scoped_refptr<TextNode> text(new TextNode("foobar",
                                            make_scoped_refptr(new DummyFont()),
                                            ColorRGBA(0.0f, 0.0f, 0.0f)));
  MockNodeVisitor mock_visitor;
  EXPECT_CALL(mock_visitor, Visit(text.get()));
  text->Accept(&mock_visitor);
}
