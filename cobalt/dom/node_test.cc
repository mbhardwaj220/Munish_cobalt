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

#include "cobalt/dom/node.h"

#include "cobalt/dom/comment.h"
#include "cobalt/dom/element.h"
#include "cobalt/dom/html_collection.h"
#include "cobalt/dom/node_list.h"
#include "cobalt/dom/stats.h"
#include "cobalt/dom/testing/fake_node.h"
#include "cobalt/dom/testing/gtest_workarounds.h"
#include "cobalt/dom/text.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace cobalt {
namespace dom {
namespace {

const scoped_refptr<Node> kNullNode;
const scoped_refptr<HTMLCollection> kNullCollection;

}  // namespace

//////////////////////////////////////////////////////////////////////////
// NodeTest
//////////////////////////////////////////////////////////////////////////

class NodeTest : public ::testing::Test {
 protected:
  NodeTest();
  ~NodeTest() OVERRIDE;
};

NodeTest::NodeTest() { EXPECT_TRUE(Stats::GetInstance()->CheckNoLeaks()); }

NodeTest::~NodeTest() { EXPECT_TRUE(Stats::GetInstance()->CheckNoLeaks()); }

//////////////////////////////////////////////////////////////////////////
// Test cases
//////////////////////////////////////////////////////////////////////////

TEST_F(NodeTest, CreateNode) {
  scoped_refptr<Node> node = new FakeNode();
  ASSERT_NE(NULL, node);
}

TEST_F(NodeTest, AppendChild) {
  scoped_refptr<Node> root = new FakeNode();

  scoped_refptr<Node> child1 = root->AppendChild(new FakeNode());
  ASSERT_NE(NULL, child1);
  scoped_refptr<Node> child2 = root->AppendChild(new FakeNode());
  ASSERT_NE(NULL, child2);

  // Properly handle NULL input.
  EXPECT_EQ(NULL, root->AppendChild(NULL));

  scoped_refptr<Node> children[] = {child1, child2};
  ExpectNodeChildrenEq(children, root);
}

TEST_F(NodeTest, AppendChildTwice) {
  scoped_refptr<Node> root = new FakeNode();

  scoped_refptr<Node> child1 = root->AppendChild(new FakeNode());
  scoped_refptr<Node> child2 = root->AppendChild(new FakeNode());

  // Append child1 for the second time.
  root->AppendChild(child1);

  scoped_refptr<Node> children[] = {child2, child1};
  ExpectNodeChildrenEq(children, root);
}

TEST_F(NodeTest, Contains) {
  scoped_refptr<Node> root = new FakeNode();
  scoped_refptr<Node> node = new FakeNode();

  scoped_refptr<Node> child1 = root->AppendChild(new FakeNode());
  scoped_refptr<Node> child2 = root->AppendChild(new FakeNode());

  EXPECT_TRUE(root->Contains(child1));
  EXPECT_TRUE(root->Contains(child2));

  EXPECT_FALSE(root->Contains(root));
  EXPECT_FALSE(root->Contains(node));
}

TEST_F(NodeTest, AppendChildWithParent) {
  scoped_refptr<Node> root1 = new FakeNode();
  scoped_refptr<Node> root2 = new FakeNode();

  scoped_refptr<Node> child = new FakeNode();
  root1->AppendChild(child);
  root2->AppendChild(child);

  EXPECT_FALSE(root1->Contains(child));
  EXPECT_TRUE(root2->Contains(child));

  EXPECT_EQ(root2, child->parent_node());
}

TEST_F(NodeTest, InsertBefore) {
  scoped_refptr<Node> root = new FakeNode();

  scoped_refptr<Node> child1 = root->InsertBefore(new FakeNode(), NULL);
  ASSERT_NE(NULL, child1);
  scoped_refptr<Node> child3 = root->InsertBefore(new FakeNode(), NULL);
  ASSERT_NE(NULL, child3);
  scoped_refptr<Node> child2 = root->InsertBefore(new FakeNode(), child3);
  ASSERT_NE(NULL, child2);

  // Properly handle NULL input.
  EXPECT_EQ(NULL, root->InsertBefore(NULL, NULL));
  // Properly handle a reference node that is not a child of root.
  EXPECT_EQ(NULL, root->InsertBefore(new FakeNode(), new FakeNode()));

  scoped_refptr<Node> children[] = {child1, child2, child3};
  ExpectNodeChildrenEq(children, root);
}

TEST_F(NodeTest, InsertBeforeTwice) {
  scoped_refptr<Node> root = new FakeNode();

  scoped_refptr<Node> child1 = root->InsertBefore(new FakeNode(), NULL);
  scoped_refptr<Node> child2 = root->InsertBefore(new FakeNode(), NULL);

  EXPECT_NE(NULL, root->InsertBefore(child2, child1));

  scoped_refptr<Node> children[] = {child2, child1};
  ExpectNodeChildrenEq(children, root);
}

TEST_F(NodeTest, InsertBeforeSelf) {
  scoped_refptr<Node> root = new FakeNode();

  scoped_refptr<Node> child1 = root->InsertBefore(new FakeNode(), NULL);
  scoped_refptr<Node> child2 = root->InsertBefore(new FakeNode(), NULL);

  EXPECT_NE(NULL, root->InsertBefore(child2, child2));

  scoped_refptr<Node> children[] = {child1, child2};
  ExpectNodeChildrenEq(children, root);
}

TEST_F(NodeTest, RemoveChild) {
  scoped_refptr<Node> root = new FakeNode();

  scoped_refptr<Node> child1 = root->AppendChild(new FakeNode());
  scoped_refptr<Node> child2 = root->AppendChild(new FakeNode());
  scoped_refptr<Node> child3 = root->AppendChild(new FakeNode());

  EXPECT_NE(NULL, root->RemoveChild(child1));
  EXPECT_NE(NULL, root->RemoveChild(child3));

  // Properly handle NULL input.
  EXPECT_EQ(NULL, root->RemoveChild(NULL));
  // Properly handle a node that is not a child of root.
  EXPECT_EQ(NULL, root->RemoveChild(child1));

  scoped_refptr<Node> children[] = {child2};
  ExpectNodeChildrenEq(children, root);
}

TEST_F(NodeTest, ChildNodes) {
  scoped_refptr<Node> root = new FakeNode();
  EXPECT_FALSE(root->HasChildNodes());
  EXPECT_EQ(0, root->child_nodes()->length());
  EXPECT_EQ(kNullNode, root->child_nodes()->Item(0));

  scoped_refptr<Node> child = new FakeNode();
  root->AppendChild(child);
  EXPECT_TRUE(root->HasChildNodes());
  EXPECT_EQ(1, root->child_nodes()->length());
  EXPECT_EQ(child, root->child_nodes()->Item(0));
  EXPECT_EQ(kNullNode, root->child_nodes()->Item(1));

  root->RemoveChild(child);
  EXPECT_FALSE(root->HasChildNodes());
  EXPECT_EQ(0, root->child_nodes()->length());
  EXPECT_EQ(kNullNode, root->child_nodes()->Item(0));
}

TEST_F(NodeTest, ParentElement) {
  scoped_refptr<Node> node = new FakeNode();
  EXPECT_EQ(NULL, node->parent_element());

  scoped_refptr<Node> root = new FakeNode();
  root->AppendChild(node);
  EXPECT_EQ(NULL, node->parent_element());

  root->RemoveChild(node);
  scoped_refptr<Element> parent_element = new Element();
  parent_element->AppendChild(node);
  EXPECT_EQ(parent_element, node->parent_element());
}

TEST_F(NodeTest, ParentNode) {
  scoped_refptr<Node> node = new FakeNode();
  node->AppendChild(new Text("first"));
  scoped_refptr<Element> child1 = node->AppendChild(new Element())->AsElement();
  node->AppendChild(new Text("middle"));
  scoped_refptr<Element> child2 = node->AppendChild(new Element())->AsElement();
  node->AppendChild(new Text("last"));
  child1->SetAttribute("id", "1");
  child2->SetAttribute("id", "2");
  scoped_refptr<HTMLCollection> children = node->children();

  // Check the result of the methods on ParentNode.
  EXPECT_EQ(2, node->child_element_count());
  EXPECT_EQ(child1, node->first_element_child());
  EXPECT_EQ(child2, node->last_element_child());
  ASSERT_NE(kNullCollection, children);
  EXPECT_EQ(2, children->length());
  EXPECT_EQ(child1, children->Item(0));
  EXPECT_EQ(child2, children->Item(1));
  EXPECT_EQ(kNullNode, children->Item(2));
  EXPECT_EQ(child1, children->NamedItem("1"));
  EXPECT_EQ(child2, children->NamedItem("2"));
  EXPECT_EQ(kNullNode, children->NamedItem("3"));

  // Remove a child and make sure that the children collection was updated
  // accordingly.
  node->RemoveChild(child2);
  EXPECT_EQ(1, children->length());
  EXPECT_EQ(child1, children->Item(0));
  EXPECT_EQ(kNullNode, children->Item(1));
  EXPECT_EQ(child1, children->NamedItem("1"));
  EXPECT_EQ(kNullNode, children->NamedItem("2"));
}

TEST_F(NodeTest, NonDocumentTypeChildNode) {
  scoped_refptr<Node> node = new FakeNode();
  node->AppendChild(new Text("first"));
  scoped_refptr<Element> child1 = node->AppendChild(new Element())->AsElement();
  node->AppendChild(new Text("middle"));
  scoped_refptr<Element> child2 = node->AppendChild(new Element())->AsElement();
  scoped_refptr<Element> child3 = node->AppendChild(new Element())->AsElement();
  node->AppendChild(new Text("last"));
  scoped_refptr<HTMLCollection> children = node->children();

  EXPECT_EQ(kNullNode, child1->previous_element_sibling());
  EXPECT_EQ(child1, child2->previous_element_sibling());
  EXPECT_EQ(child2, child3->previous_element_sibling());
  EXPECT_EQ(child2, child1->next_element_sibling());
  EXPECT_EQ(child3, child2->next_element_sibling());
  EXPECT_EQ(kNullNode, child3->next_element_sibling());
}

}  // namespace dom
}  // namespace cobalt
