/*
 * Copyright 2017 Google Inc. All Rights Reserved.
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

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/message_loop.h"
#include "cobalt/dom/element.h"
#include "cobalt/dom/mutation_observer_init.h"
#include "cobalt/dom/mutation_observer_task_manager.h"
#include "cobalt/dom/mutation_record.h"
#include "cobalt/dom/mutation_reporter.h"
#include "cobalt/dom/node_list.h"
#include "cobalt/script/sequence.h"
#include "cobalt/test/empty_document.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

using ::testing::_;
using ::testing::SaveArg;

namespace cobalt {
namespace dom {
// Helper struct for childList mutations.
struct ChildListMutationArguments {
  scoped_refptr<dom::Element> previous_sibling;
  scoped_refptr<dom::Element> next_sibling;
  scoped_refptr<dom::NodeList> added_nodes;
  scoped_refptr<dom::NodeList> removed_nodes;
};

class MutationCallbackMock {
 public:
  MOCK_METHOD2(NativeMutationCallback,
               void(const MutationObserver::MutationRecordSequence&,
                    const scoped_refptr<MutationObserver>&));
};

class MutationObserverTest : public ::testing::Test {
 protected:
  dom::Document* document() { return empty_document_.document(); }
  MutationObserverTaskManager* task_manager() { return &task_manager_; }
  MutationCallbackMock* callback_mock() { return &callback_mock_; }

  scoped_refptr<Element> CreateDiv() {
    scoped_refptr<Element> element = document()->CreateElement("div");
    document()->AppendChild(element);
    return element;
  }

  scoped_refptr<MutationObserver> CreateObserver() {
    return new MutationObserver(
        base::Bind(&MutationCallbackMock::NativeMutationCallback,
                   base::Unretained(&callback_mock_)),
        &task_manager_);
  }

  ChildListMutationArguments CreateChildListMutationArguments() {
    // These nodes are not actually related in the way they are named
    // (next_sibling, previous_sibling, etc) but that is not relevant for the
    // purpose of these tests.
    ChildListMutationArguments args;
    args.previous_sibling = CreateDiv();
    args.next_sibling = CreateDiv();
    args.added_nodes = new NodeList();
    args.added_nodes->AppendNode(CreateDiv());
    args.removed_nodes = new NodeList();
    args.removed_nodes->AppendNode(CreateDiv());
    return args;
  }

 private:
  MutationObserverTaskManager task_manager_;
  test::EmptyDocument empty_document_;
  MutationCallbackMock callback_mock_;
  MessageLoop message_loop_;
};

TEST_F(MutationObserverTest, CreateAttributeMutationRecord) {
  scoped_refptr<dom::Element> target = CreateDiv();
  scoped_refptr<MutationRecord> record =
      MutationRecord::CreateAttributeMutationRecord(target, "attribute_name",
                                                    "old_value");
  ASSERT_TRUE(record);

  // "type" and attribute-related attributes are set as expected
  EXPECT_STREQ("attribute", record->type().c_str());
  EXPECT_TRUE(record->attribute_name());
  EXPECT_STREQ("attribute_name", record->attribute_name()->c_str());
  EXPECT_TRUE(record->old_value());
  EXPECT_STREQ("old_value", record->old_value()->c_str());

  // "target" is set as expected.
  EXPECT_EQ(target, record->target());

  // Namespaces are not supported.
  EXPECT_FALSE(record->attribute_namespace());

  // Unrelated attributes are not set.
  EXPECT_FALSE(record->added_nodes());
  EXPECT_FALSE(record->removed_nodes());
  EXPECT_FALSE(record->previous_sibling());
  EXPECT_FALSE(record->next_sibling());
}

TEST_F(MutationObserverTest, CreateCharacterDataMutationRecord) {
  scoped_refptr<dom::Element> target = CreateDiv();
  scoped_refptr<MutationRecord> record =
      MutationRecord::CreateCharacterDataMutationRecord(target,
                                                        "old_character_data");
  ASSERT_TRUE(record);

  // "type" and attribute-related attributes are set as expected
  EXPECT_STREQ("characterData", record->type().c_str());
  EXPECT_TRUE(record->old_value());
  EXPECT_STREQ("old_character_data", record->old_value()->c_str());

  // "target" is set as expected.
  EXPECT_EQ(target, record->target());

  // Unrelated attributes are not set.
  EXPECT_FALSE(record->attribute_name());
  EXPECT_FALSE(record->attribute_namespace());
  EXPECT_FALSE(record->added_nodes());
  EXPECT_FALSE(record->removed_nodes());
  EXPECT_FALSE(record->previous_sibling());
  EXPECT_FALSE(record->next_sibling());
}

TEST_F(MutationObserverTest, CreateChildListMutationRecord) {
  scoped_refptr<dom::Element> target = CreateDiv();

  ChildListMutationArguments args = CreateChildListMutationArguments();
  scoped_refptr<MutationRecord> record =
      MutationRecord::CreateChildListMutationRecord(
          target, args.added_nodes, args.removed_nodes, args.previous_sibling,
          args.next_sibling);
  ASSERT_TRUE(record);

  // "type" and attribute-related attributes are set as expected
  EXPECT_STREQ("childList", record->type().c_str());
  EXPECT_EQ(args.added_nodes, record->added_nodes());
  EXPECT_EQ(args.removed_nodes, record->removed_nodes());
  EXPECT_EQ(args.previous_sibling, record->previous_sibling());
  EXPECT_EQ(args.next_sibling, record->next_sibling());

  // "target" is set as expected.
  EXPECT_EQ(target, record->target());

  // Unrelated attributes are not set.
  EXPECT_FALSE(record->attribute_name());
  EXPECT_FALSE(record->attribute_namespace());
  EXPECT_FALSE(record->old_value());
}

TEST_F(MutationObserverTest, MutationObserverInit) {
  MutationObserverInit init;
  // Default values are set according to spec.
  EXPECT_FALSE(init.child_list());
  EXPECT_FALSE(init.subtree());

  // Other values are not set.
  EXPECT_FALSE(init.has_attributes());
  EXPECT_FALSE(init.has_character_data());
  EXPECT_FALSE(init.has_attribute_old_value());
  EXPECT_FALSE(init.has_character_data_old_value());
  EXPECT_FALSE(init.has_attribute_filter());

  // Set other values.
  init.set_attributes(true);
  init.set_character_data(true);
  init.set_attribute_old_value(true);
  init.set_character_data_old_value(true);
  script::Sequence<std::string> attribute_filter;
  attribute_filter.push_back("a_filter");
  init.set_attribute_filter(attribute_filter);

  // Other values are now set.
  EXPECT_TRUE(init.has_attributes());
  EXPECT_TRUE(init.attributes());
  EXPECT_TRUE(init.has_character_data());
  EXPECT_TRUE(init.character_data());
  EXPECT_TRUE(init.has_attribute_old_value());
  EXPECT_TRUE(init.attribute_old_value());
  EXPECT_TRUE(init.has_character_data_old_value());
  EXPECT_TRUE(init.character_data_old_value());
  EXPECT_TRUE(init.has_attribute_filter());
  EXPECT_EQ(init.attribute_filter().size(), attribute_filter.size());
  EXPECT_EQ(init.attribute_filter().at(0), attribute_filter.at(0));
}

TEST_F(MutationObserverTest, TakeRecords) {
  scoped_refptr<dom::Element> target = CreateDiv();

  // Newly created observer shouldn't have records.
  scoped_refptr<MutationObserver> observer = CreateObserver();
  MutationObserver::MutationRecordSequence records;
  records = observer->TakeRecords();
  EXPECT_TRUE(records.empty());

  // Append a mutation records.
  scoped_refptr<MutationRecord> record =
      MutationRecord::CreateCharacterDataMutationRecord(target,
                                                        "old_character_data");
  observer->QueueMutationRecord(record);

  // The queued record can be taken once.
  records = observer->TakeRecords();
  ASSERT_EQ(1, records.size());
  ASSERT_EQ(records.at(0), record);
  records = observer->TakeRecords();
  EXPECT_TRUE(records.empty());
}

TEST_F(MutationObserverTest, Notify) {
  scoped_refptr<dom::Element> target = CreateDiv();

  // Create a new observer and queue a mutation record.
  scoped_refptr<MutationObserver> observer = CreateObserver();
  scoped_refptr<MutationRecord> record =
      MutationRecord::CreateCharacterDataMutationRecord(target,
                                                        "old_character_data");
  observer->QueueMutationRecord(record);

  // Callback should be fired with the first argument being a sequence of the
  // queued record, and the second argument being the observer.
  MutationObserver::MutationRecordSequence records;
  EXPECT_CALL(*callback_mock(), NativeMutationCallback(_, observer))
      .WillOnce(SaveArg<0>(&records));
  observer->Notify();
  ASSERT_EQ(1, records.size());
  EXPECT_EQ(record, records.at(0));

  // There should be no more records queued up after the callback has been
  // fired.
  records = observer->TakeRecords();
  EXPECT_TRUE(records.empty());
}

TEST_F(MutationObserverTest, ReportMutation) {
  scoped_refptr<dom::Element> target = CreateDiv();
  // Create a registered observer that cares about attribute and character data
  // mutations.
  scoped_refptr<MutationObserver> observer = CreateObserver();
  MutationObserverInit init;
  init.set_attributes(true);
  init.set_child_list(false);
  init.set_character_data(true);

  RegisteredObserver registered_observer(target.get(), observer, init);
  std::vector<const RegisteredObserver*> registered_observers;
  registered_observers.push_back(&registered_observer);

  // Create a MutationReporter for the list of registered observers.
  MutationReporter reporter(target.get(), registered_observers);

  // Report a few mutations.
  reporter.ReportAttributesMutation("attribute_name", "old_value");
  reporter.ReportCharacterDataMutation("old_character_data");
  ChildListMutationArguments args = CreateChildListMutationArguments();
  reporter.ReportChildListMutation(args.added_nodes, args.removed_nodes,
                                   args.previous_sibling, args.next_sibling);

  // Check that mutation records for the mutation types we care about have
  // been queued.
  MutationObserver::MutationRecordSequence records = observer->TakeRecords();
  ASSERT_EQ(2, records.size());
  EXPECT_EQ(records.at(0)->type(), "attribute");
  EXPECT_EQ(records.at(1)->type(), "characterData");
}

TEST_F(MutationObserverTest, AttributeFilter) {
  scoped_refptr<dom::Element> target = CreateDiv();
  // Create a registered observer that cares about attribute and character data
  // mutations.
  scoped_refptr<MutationObserver> observer = CreateObserver();
  MutationObserverInit init;
  script::Sequence<std::string> attribute_filter;
  attribute_filter.push_back("banana");
  attribute_filter.push_back("potato");
  init.set_attribute_filter(attribute_filter);
  init.set_attributes(true);

  RegisteredObserver registered_observer(target.get(), observer, init);
  std::vector<const RegisteredObserver*> registered_observers;
  registered_observers.push_back(&registered_observer);

  // Create a MutationReporter for the list of registered observers.
  MutationReporter reporter(target.get(), registered_observers);

  // Report a few attribute mutations.
  reporter.ReportAttributesMutation("banana", "rotten");
  reporter.ReportAttributesMutation("apple", "wormy");
  reporter.ReportAttributesMutation("potato", "mashed");

  // Check that mutation records for the filtered attrbiutes have been queued.
  MutationObserver::MutationRecordSequence records = observer->TakeRecords();
  ASSERT_EQ(2, records.size());
  EXPECT_STREQ(records.at(0)->attribute_name()->c_str(), "banana");
  EXPECT_STREQ(records.at(1)->attribute_name()->c_str(), "potato");
}

TEST_F(MutationObserverTest, RegisteredObserverList) {
  scoped_refptr<dom::Element> target = CreateDiv();
  scoped_refptr<MutationObserver> observer = CreateObserver();

  RegisteredObserverList observer_list(target.get());

  // Add an observer with options.
  MutationObserverInit options;
  options.set_attributes(true);
  EXPECT_TRUE(observer_list.AddMutationObserver(observer, options));
  EXPECT_EQ(1, observer_list.registered_observers().size());
  EXPECT_EQ(observer, observer_list.registered_observers()[0].observer());
  EXPECT_TRUE(observer_list.registered_observers()[0].options().attributes());
  EXPECT_FALSE(
      observer_list.registered_observers()[0].options().has_character_data());
  EXPECT_FALSE(observer_list.registered_observers()[0].options().child_list());

  // Adding the same observer updates the options.
  options = MutationObserverInit();
  options.set_child_list(true);
  EXPECT_TRUE(observer_list.AddMutationObserver(observer, options));
  EXPECT_EQ(1, observer_list.registered_observers().size());
  EXPECT_EQ(observer, observer_list.registered_observers()[0].observer());
  EXPECT_FALSE(
      observer_list.registered_observers()[0].options().has_attributes());
  EXPECT_FALSE(
      observer_list.registered_observers()[0].options().has_character_data());
  EXPECT_TRUE(observer_list.registered_observers()[0].options().child_list());

  // Remove the observer.
  observer_list.RemoveMutationObserver(observer);
  EXPECT_EQ(0, observer_list.registered_observers().size());
}

TEST_F(MutationObserverTest, LazilySetOptions) {
  scoped_refptr<dom::Element> target = CreateDiv();
  scoped_refptr<MutationObserver> observer = CreateObserver();

  RegisteredObserverList observer_list(target.get());

  // |attributes| gets set if an attribute-related option is set.
  MutationObserverInit options;
  options.set_attribute_old_value(true);
  EXPECT_TRUE(observer_list.AddMutationObserver(observer, options));
  EXPECT_EQ(1, observer_list.registered_observers().size());
  EXPECT_TRUE(observer_list.registered_observers()[0].options().attributes());

  // |character_data| gets set if an attribute-related option is set.
  options = MutationObserverInit();
  options.set_character_data_old_value(true);
  EXPECT_TRUE(observer_list.AddMutationObserver(observer, options));
  EXPECT_EQ(1, observer_list.registered_observers().size());
  EXPECT_TRUE(
      observer_list.registered_observers()[0].options().character_data());
}

TEST_F(MutationObserverTest, InvalidOptions) {
  scoped_refptr<dom::Element> target = CreateDiv();
  scoped_refptr<MutationObserver> observer = CreateObserver();

  RegisteredObserverList observer_list(target.get());

  // No type of mutation is set.
  MutationObserverInit options;
  EXPECT_FALSE(observer_list.AddMutationObserver(observer, options));
  EXPECT_EQ(0, observer_list.registered_observers().size());

  // |attributes| is set as false, but attribute old data is set.
  options.set_attributes(false);
  options.set_attribute_old_value(true);
  EXPECT_FALSE(observer_list.AddMutationObserver(observer, options));
  EXPECT_EQ(0, observer_list.registered_observers().size());

  // |character_data| is set as false, but attribute old data is set.
  options = MutationObserverInit();
  options.set_character_data(false);
  options.set_character_data_old_value(true);
  EXPECT_FALSE(observer_list.AddMutationObserver(observer, options));
  EXPECT_EQ(0, observer_list.registered_observers().size());
}

}  // namespace dom
}  // namespace cobalt
