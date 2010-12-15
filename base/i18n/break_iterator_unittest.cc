// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/i18n/break_iterator.h"

#include "base/string_piece.h"
#include "base/string_util.h"
#include "base/utf_string_conversions.h"
#include "testing/gtest/include/gtest/gtest.h"

TEST(BreakIteratorTest, BreakWord) {
  string16 space(UTF8ToUTF16(" "));

  string16 str(UTF8ToUTF16(" foo bar! \npouet boom"));
  base::BreakIterator iter(&str, base::BreakIterator::BREAK_WORD);
  ASSERT_TRUE(iter.Init());
  EXPECT_TRUE(iter.Advance());
  EXPECT_FALSE(iter.IsWord());
  EXPECT_EQ(space, iter.GetString());
  EXPECT_TRUE(iter.Advance());
  EXPECT_TRUE(iter.IsWord());
  EXPECT_EQ(UTF8ToUTF16("foo"), iter.GetString());
  EXPECT_TRUE(iter.Advance());
  EXPECT_FALSE(iter.IsWord());
  EXPECT_EQ(space, iter.GetString());
  EXPECT_TRUE(iter.Advance());
  EXPECT_TRUE(iter.IsWord());
  EXPECT_EQ(UTF8ToUTF16("bar"), iter.GetString());
  EXPECT_TRUE(iter.Advance());
  EXPECT_FALSE(iter.IsWord());
  EXPECT_EQ(UTF8ToUTF16("!"), iter.GetString());
  EXPECT_TRUE(iter.Advance());
  EXPECT_FALSE(iter.IsWord());
  EXPECT_EQ(space, iter.GetString());
  EXPECT_TRUE(iter.Advance());
  EXPECT_FALSE(iter.IsWord());
  EXPECT_EQ(UTF8ToUTF16("\n"), iter.GetString());
  EXPECT_TRUE(iter.Advance());
  EXPECT_TRUE(iter.IsWord());
  EXPECT_EQ(UTF8ToUTF16("pouet"), iter.GetString());
  EXPECT_TRUE(iter.Advance());
  EXPECT_FALSE(iter.IsWord());
  EXPECT_EQ(space, iter.GetString());
  EXPECT_TRUE(iter.Advance());
  EXPECT_TRUE(iter.IsWord());
  EXPECT_EQ(UTF8ToUTF16("boom"), iter.GetString());
  EXPECT_FALSE(iter.Advance());
  EXPECT_FALSE(iter.IsWord());
}

TEST(BreakIteratorTest, BreakSpace) {
  string16 str(UTF8ToUTF16(" foo bar! \npouet boom"));
  base::BreakIterator iter(&str, base::BreakIterator::BREAK_SPACE);
  ASSERT_TRUE(iter.Init());
  EXPECT_TRUE(iter.Advance());
  EXPECT_FALSE(iter.IsWord());
  EXPECT_EQ(UTF8ToUTF16(" "), iter.GetString());
  EXPECT_TRUE(iter.Advance());
  EXPECT_FALSE(iter.IsWord());
  EXPECT_EQ(UTF8ToUTF16("foo "), iter.GetString());
  EXPECT_TRUE(iter.Advance());
  EXPECT_FALSE(iter.IsWord());
  EXPECT_EQ(UTF8ToUTF16("bar! \n"), iter.GetString());
  EXPECT_TRUE(iter.Advance());
  EXPECT_FALSE(iter.IsWord());
  EXPECT_EQ(UTF8ToUTF16("pouet "), iter.GetString());
  EXPECT_TRUE(iter.Advance());
  EXPECT_FALSE(iter.IsWord());
  EXPECT_EQ(UTF8ToUTF16("boom"), iter.GetString());
  EXPECT_FALSE(iter.Advance());
  EXPECT_FALSE(iter.IsWord());
}

TEST(BreakIteratorTest, BreakWide16) {
  //  "Παγκόσμιος Ιστός"
  const string16 str(WideToUTF16(
      L"\x03a0\x03b1\x03b3\x03ba\x03cc\x03c3\x03bc\x03b9"
      L"\x03bf\x03c2\x0020\x0399\x03c3\x03c4\x03cc\x03c2"));
  const string16 word1(str.substr(0, 10));
  const string16 word2(str.substr(11, 5));
  base::BreakIterator iter(&str, base::BreakIterator::BREAK_WORD);
  ASSERT_TRUE(iter.Init());
  EXPECT_TRUE(iter.Advance());
  EXPECT_TRUE(iter.IsWord());
  EXPECT_EQ(word1, iter.GetString());
  EXPECT_TRUE(iter.Advance());
  EXPECT_FALSE(iter.IsWord());
  EXPECT_EQ(UTF8ToUTF16(" "), iter.GetString());
  EXPECT_TRUE(iter.Advance());
  EXPECT_TRUE(iter.IsWord());
  EXPECT_EQ(word2, iter.GetString());
  EXPECT_FALSE(iter.Advance());
  EXPECT_FALSE(iter.IsWord());
}

TEST(BreakIteratorTest, BreakWide32) {
  // U+1D49C MATHEMATICAL SCRIPT CAPITAL A
  const char* very_wide_char = "\xF0\x9D\x92\x9C";
  const string16 str(
      UTF8ToUTF16(StringPrintf("%s a", very_wide_char)));
  const string16 very_wide_word(str.substr(0, 2));

  base::BreakIterator iter(&str, base::BreakIterator::BREAK_WORD);
  ASSERT_TRUE(iter.Init());
  EXPECT_TRUE(iter.Advance());
  EXPECT_TRUE(iter.IsWord());
  EXPECT_EQ(very_wide_word, iter.GetString());
  EXPECT_TRUE(iter.Advance());
  EXPECT_FALSE(iter.IsWord());
  EXPECT_EQ(UTF8ToUTF16(" "), iter.GetString());
  EXPECT_TRUE(iter.Advance());
  EXPECT_TRUE(iter.IsWord());
  EXPECT_EQ(UTF8ToUTF16("a"), iter.GetString());
  EXPECT_FALSE(iter.Advance());
  EXPECT_FALSE(iter.IsWord());
}
