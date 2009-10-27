// Copyright (c) 2008 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/basictypes.h"
#include "base/file_path.h"
#include "base/file_util.h"
#include "base/string_util.h"
#include "testing/gtest/include/gtest/gtest.h"
#include "testing/platform_test.h"

// This macro helps avoid wrapped lines in the test structs.
#define FPL(x) FILE_PATH_LITERAL(x)

struct UnaryTestData {
  const FilePath::CharType* input;
  const FilePath::CharType* expected;
};

struct UnaryBooleanTestData {
  const FilePath::CharType* input;
  bool expected;
};

struct BinaryTestData {
  const FilePath::CharType* inputs[2];
  const FilePath::CharType* expected;
};

struct BinaryBooleanTestData {
  const FilePath::CharType* inputs[2];
  bool expected;
};

struct BinaryIntTestData {
  const FilePath::CharType* inputs[2];
  int expected;
};

// file_util winds up using autoreleased objects on the Mac, so this needs
// to be a PlatformTest
class FilePathTest : public PlatformTest {
 protected:
  virtual void SetUp() {
    PlatformTest::SetUp();
  }
  virtual void TearDown() {
    PlatformTest::TearDown();
  }
};

TEST_F(FilePathTest, DirName) {
  const struct UnaryTestData cases[] = {
    { FPL(""),              FPL(".") },
    { FPL("aa"),            FPL(".") },
    { FPL("/aa/bb"),        FPL("/aa") },
    { FPL("/aa/bb/"),       FPL("/aa") },
    { FPL("/aa/bb//"),      FPL("/aa") },
    { FPL("/aa/bb/ccc"),    FPL("/aa/bb") },
    { FPL("/aa"),           FPL("/") },
    { FPL("/aa/"),          FPL("/") },
    { FPL("/"),             FPL("/") },
    { FPL("//"),            FPL("//") },
    { FPL("///"),           FPL("/") },
    { FPL("aa/"),           FPL(".") },
    { FPL("aa/bb"),         FPL("aa") },
    { FPL("aa/bb/"),        FPL("aa") },
    { FPL("aa/bb//"),       FPL("aa") },
    { FPL("aa//bb//"),      FPL("aa") },
    { FPL("aa//bb/"),       FPL("aa") },
    { FPL("aa//bb"),        FPL("aa") },
    { FPL("//aa/bb"),       FPL("//aa") },
    { FPL("//aa/"),         FPL("//") },
    { FPL("//aa"),          FPL("//") },
    { FPL("0:"),            FPL(".") },
    { FPL("@:"),            FPL(".") },
    { FPL("[:"),            FPL(".") },
    { FPL("`:"),            FPL(".") },
    { FPL("{:"),            FPL(".") },
    { FPL("\xB3:"),         FPL(".") },
    { FPL("\xC5:"),         FPL(".") },
#if defined(OS_WIN)
    { FPL("\x0143:"),       FPL(".") },
#endif  // OS_WIN
#if defined(FILE_PATH_USES_DRIVE_LETTERS)
    { FPL("c:"),            FPL("c:") },
    { FPL("C:"),            FPL("C:") },
    { FPL("A:"),            FPL("A:") },
    { FPL("Z:"),            FPL("Z:") },
    { FPL("a:"),            FPL("a:") },
    { FPL("z:"),            FPL("z:") },
    { FPL("c:aa"),          FPL("c:") },
    { FPL("c:/"),           FPL("c:/") },
    { FPL("c://"),          FPL("c://") },
    { FPL("c:///"),         FPL("c:/") },
    { FPL("c:/aa"),         FPL("c:/") },
    { FPL("c:/aa/"),        FPL("c:/") },
    { FPL("c:/aa/bb"),      FPL("c:/aa") },
    { FPL("c:aa/bb"),       FPL("c:aa") },
#endif  // FILE_PATH_USES_DRIVE_LETTERS
#if defined(FILE_PATH_USES_WIN_SEPARATORS)
    { FPL("\\aa\\bb"),      FPL("\\aa") },
    { FPL("\\aa\\bb\\"),    FPL("\\aa") },
    { FPL("\\aa\\bb\\\\"),  FPL("\\aa") },
    { FPL("\\aa\\bb\\ccc"), FPL("\\aa\\bb") },
    { FPL("\\aa"),          FPL("\\") },
    { FPL("\\aa\\"),        FPL("\\") },
    { FPL("\\"),            FPL("\\") },
    { FPL("\\\\"),          FPL("\\\\") },
    { FPL("\\\\\\"),        FPL("\\") },
    { FPL("aa\\"),          FPL(".") },
    { FPL("aa\\bb"),        FPL("aa") },
    { FPL("aa\\bb\\"),      FPL("aa") },
    { FPL("aa\\bb\\\\"),    FPL("aa") },
    { FPL("aa\\\\bb\\\\"),  FPL("aa") },
    { FPL("aa\\\\bb\\"),    FPL("aa") },
    { FPL("aa\\\\bb"),      FPL("aa") },
    { FPL("\\\\aa\\bb"),    FPL("\\\\aa") },
    { FPL("\\\\aa\\"),      FPL("\\\\") },
    { FPL("\\\\aa"),        FPL("\\\\") },
#if defined(FILE_PATH_USES_DRIVE_LETTERS)
    { FPL("c:\\"),          FPL("c:\\") },
    { FPL("c:\\\\"),        FPL("c:\\\\") },
    { FPL("c:\\\\\\"),      FPL("c:\\") },
    { FPL("c:\\aa"),        FPL("c:\\") },
    { FPL("c:\\aa\\"),      FPL("c:\\") },
    { FPL("c:\\aa\\bb"),    FPL("c:\\aa") },
    { FPL("c:aa\\bb"),      FPL("c:aa") },
#endif  // FILE_PATH_USES_DRIVE_LETTERS
#endif  // FILE_PATH_USES_WIN_SEPARATORS
  };

  for (size_t i = 0; i < arraysize(cases); ++i) {
    FilePath input(cases[i].input);
    FilePath observed = input.DirName();
    EXPECT_EQ(FilePath::StringType(cases[i].expected), observed.value()) <<
              "i: " << i << ", input: " << input.value();
  }
}

TEST_F(FilePathTest, BaseName) {
  const struct UnaryTestData cases[] = {
    { FPL(""),              FPL("") },
    { FPL("aa"),            FPL("aa") },
    { FPL("/aa/bb"),        FPL("bb") },
    { FPL("/aa/bb/"),       FPL("bb") },
    { FPL("/aa/bb//"),      FPL("bb") },
    { FPL("/aa/bb/ccc"),    FPL("ccc") },
    { FPL("/aa"),           FPL("aa") },
    { FPL("/"),             FPL("/") },
    { FPL("//"),            FPL("//") },
    { FPL("///"),           FPL("/") },
    { FPL("aa/"),           FPL("aa") },
    { FPL("aa/bb"),         FPL("bb") },
    { FPL("aa/bb/"),        FPL("bb") },
    { FPL("aa/bb//"),       FPL("bb") },
    { FPL("aa//bb//"),      FPL("bb") },
    { FPL("aa//bb/"),       FPL("bb") },
    { FPL("aa//bb"),        FPL("bb") },
    { FPL("//aa/bb"),       FPL("bb") },
    { FPL("//aa/"),         FPL("aa") },
    { FPL("//aa"),          FPL("aa") },
    { FPL("0:"),            FPL("0:") },
    { FPL("@:"),            FPL("@:") },
    { FPL("[:"),            FPL("[:") },
    { FPL("`:"),            FPL("`:") },
    { FPL("{:"),            FPL("{:") },
    { FPL("\xB3:"),         FPL("\xB3:") },
    { FPL("\xC5:"),         FPL("\xC5:") },
#if defined(OS_WIN)
    { FPL("\x0143:"),       FPL("\x0143:") },
#endif  // OS_WIN
#if defined(FILE_PATH_USES_DRIVE_LETTERS)
    { FPL("c:"),            FPL("") },
    { FPL("C:"),            FPL("") },
    { FPL("A:"),            FPL("") },
    { FPL("Z:"),            FPL("") },
    { FPL("a:"),            FPL("") },
    { FPL("z:"),            FPL("") },
    { FPL("c:aa"),          FPL("aa") },
    { FPL("c:/"),           FPL("/") },
    { FPL("c://"),          FPL("//") },
    { FPL("c:///"),         FPL("/") },
    { FPL("c:/aa"),         FPL("aa") },
    { FPL("c:/aa/"),        FPL("aa") },
    { FPL("c:/aa/bb"),      FPL("bb") },
    { FPL("c:aa/bb"),       FPL("bb") },
#endif  // FILE_PATH_USES_DRIVE_LETTERS
#if defined(FILE_PATH_USES_WIN_SEPARATORS)
    { FPL("\\aa\\bb"),      FPL("bb") },
    { FPL("\\aa\\bb\\"),    FPL("bb") },
    { FPL("\\aa\\bb\\\\"),  FPL("bb") },
    { FPL("\\aa\\bb\\ccc"), FPL("ccc") },
    { FPL("\\aa"),          FPL("aa") },
    { FPL("\\"),            FPL("\\") },
    { FPL("\\\\"),          FPL("\\\\") },
    { FPL("\\\\\\"),        FPL("\\") },
    { FPL("aa\\"),          FPL("aa") },
    { FPL("aa\\bb"),        FPL("bb") },
    { FPL("aa\\bb\\"),      FPL("bb") },
    { FPL("aa\\bb\\\\"),    FPL("bb") },
    { FPL("aa\\\\bb\\\\"),  FPL("bb") },
    { FPL("aa\\\\bb\\"),    FPL("bb") },
    { FPL("aa\\\\bb"),      FPL("bb") },
    { FPL("\\\\aa\\bb"),    FPL("bb") },
    { FPL("\\\\aa\\"),      FPL("aa") },
    { FPL("\\\\aa"),        FPL("aa") },
#if defined(FILE_PATH_USES_DRIVE_LETTERS)
    { FPL("c:\\"),          FPL("\\") },
    { FPL("c:\\\\"),        FPL("\\\\") },
    { FPL("c:\\\\\\"),      FPL("\\") },
    { FPL("c:\\aa"),        FPL("aa") },
    { FPL("c:\\aa\\"),      FPL("aa") },
    { FPL("c:\\aa\\bb"),    FPL("bb") },
    { FPL("c:aa\\bb"),      FPL("bb") },
#endif  // FILE_PATH_USES_DRIVE_LETTERS
#endif  // FILE_PATH_USES_WIN_SEPARATORS
  };

  for (size_t i = 0; i < arraysize(cases); ++i) {
    FilePath input(cases[i].input);
    FilePath observed = input.BaseName();
    EXPECT_EQ(FilePath::StringType(cases[i].expected), observed.value()) <<
              "i: " << i << ", input: " << input.value();
  }
}

TEST_F(FilePathTest, Append) {
  const struct BinaryTestData cases[] = {
    { { FPL(""),           FPL("cc") }, FPL("cc") },
    { { FPL("."),          FPL("ff") }, FPL("ff") },
    { { FPL("/"),          FPL("cc") }, FPL("/cc") },
    { { FPL("/aa"),        FPL("") },   FPL("/aa") },
    { { FPL("/aa/"),       FPL("") },   FPL("/aa") },
    { { FPL("//aa"),       FPL("") },   FPL("//aa") },
    { { FPL("//aa/"),      FPL("") },   FPL("//aa") },
    { { FPL("//"),         FPL("aa") }, FPL("//aa") },
#if defined(FILE_PATH_USES_DRIVE_LETTERS)
    { { FPL("c:"),         FPL("a") },  FPL("c:a") },
    { { FPL("c:"),         FPL("") },   FPL("c:") },
    { { FPL("c:/"),        FPL("a") },  FPL("c:/a") },
    { { FPL("c://"),       FPL("a") },  FPL("c://a") },
    { { FPL("c:///"),      FPL("a") },  FPL("c:/a") },
#endif  // FILE_PATH_USES_DRIVE_LETTERS
#if defined(FILE_PATH_USES_WIN_SEPARATORS)
    // Append introduces the default separator character, so these test cases
    // need to be defined with different expected results on platforms that use
    // different default separator characters.
    { { FPL("\\"),         FPL("cc") }, FPL("\\cc") },
    { { FPL("\\aa"),       FPL("") },   FPL("\\aa") },
    { { FPL("\\aa\\"),     FPL("") },   FPL("\\aa") },
    { { FPL("\\\\aa"),     FPL("") },   FPL("\\\\aa") },
    { { FPL("\\\\aa\\"),   FPL("") },   FPL("\\\\aa") },
    { { FPL("\\\\"),       FPL("aa") }, FPL("\\\\aa") },
    { { FPL("/aa/bb"),     FPL("cc") }, FPL("/aa/bb\\cc") },
    { { FPL("/aa/bb/"),    FPL("cc") }, FPL("/aa/bb\\cc") },
    { { FPL("aa/bb/"),     FPL("cc") }, FPL("aa/bb\\cc") },
    { { FPL("aa/bb"),      FPL("cc") }, FPL("aa/bb\\cc") },
    { { FPL("a/b"),        FPL("c") },  FPL("a/b\\c") },
    { { FPL("a/b/"),       FPL("c") },  FPL("a/b\\c") },
    { { FPL("//aa"),       FPL("bb") }, FPL("//aa\\bb") },
    { { FPL("//aa/"),      FPL("bb") }, FPL("//aa\\bb") },
    { { FPL("\\aa\\bb"),   FPL("cc") }, FPL("\\aa\\bb\\cc") },
    { { FPL("\\aa\\bb\\"), FPL("cc") }, FPL("\\aa\\bb\\cc") },
    { { FPL("aa\\bb\\"),   FPL("cc") }, FPL("aa\\bb\\cc") },
    { { FPL("aa\\bb"),     FPL("cc") }, FPL("aa\\bb\\cc") },
    { { FPL("a\\b"),       FPL("c") },  FPL("a\\b\\c") },
    { { FPL("a\\b\\"),     FPL("c") },  FPL("a\\b\\c") },
    { { FPL("\\\\aa"),     FPL("bb") }, FPL("\\\\aa\\bb") },
    { { FPL("\\\\aa\\"),   FPL("bb") }, FPL("\\\\aa\\bb") },
#if defined(FILE_PATH_USES_DRIVE_LETTERS)
    { { FPL("c:\\"),       FPL("a") },  FPL("c:\\a") },
    { { FPL("c:\\\\"),     FPL("a") },  FPL("c:\\\\a") },
    { { FPL("c:\\\\\\"),   FPL("a") },  FPL("c:\\a") },
    { { FPL("c:\\"),       FPL("") },   FPL("c:\\") },
    { { FPL("c:\\a"),      FPL("b") },  FPL("c:\\a\\b") },
    { { FPL("c:\\a\\"),    FPL("b") },  FPL("c:\\a\\b") },
#endif  // FILE_PATH_USES_DRIVE_LETTERS
#else  // FILE_PATH_USES_WIN_SEPARATORS
    { { FPL("/aa/bb"),     FPL("cc") }, FPL("/aa/bb/cc") },
    { { FPL("/aa/bb/"),    FPL("cc") }, FPL("/aa/bb/cc") },
    { { FPL("aa/bb/"),     FPL("cc") }, FPL("aa/bb/cc") },
    { { FPL("aa/bb"),      FPL("cc") }, FPL("aa/bb/cc") },
    { { FPL("a/b"),        FPL("c") },  FPL("a/b/c") },
    { { FPL("a/b/"),       FPL("c") },  FPL("a/b/c") },
    { { FPL("//aa"),       FPL("bb") }, FPL("//aa/bb") },
    { { FPL("//aa/"),      FPL("bb") }, FPL("//aa/bb") },
#if defined(FILE_PATH_USES_DRIVE_LETTERS)
    { { FPL("c:/"),        FPL("a") },  FPL("c:/a") },
    { { FPL("c:/"),        FPL("") },   FPL("c:/") },
    { { FPL("c:/a"),       FPL("b") },  FPL("c:/a/b") },
    { { FPL("c:/a/"),      FPL("b") },  FPL("c:/a/b") },
#endif  // FILE_PATH_USES_DRIVE_LETTERS
#endif  // FILE_PATH_USES_WIN_SEPARATORS
  };

  for (size_t i = 0; i < arraysize(cases); ++i) {
    FilePath root(cases[i].inputs[0]);
    FilePath::StringType leaf(cases[i].inputs[1]);
    FilePath observed_str = root.Append(leaf);
    EXPECT_EQ(FilePath::StringType(cases[i].expected), observed_str.value()) <<
              "i: " << i << ", root: " << root.value() << ", leaf: " << leaf;
    FilePath observed_path = root.Append(FilePath(leaf));
    EXPECT_EQ(FilePath::StringType(cases[i].expected), observed_path.value()) <<
              "i: " << i << ", root: " << root.value() << ", leaf: " << leaf;

    // TODO(erikkay): It would be nice to have a unicode test append value to
    // handle the case when AppendASCII is passed UTF8
#if defined(OS_WIN)
    std::string ascii = WideToASCII(leaf);
#elif defined(OS_POSIX)
    std::string ascii = leaf;
#endif
    observed_str = root.AppendASCII(ascii);
    EXPECT_EQ(FilePath::StringType(cases[i].expected), observed_str.value()) <<
              "i: " << i << ", root: " << root.value() << ", leaf: " << leaf;
  }
}

TEST_F(FilePathTest, StripTrailingSeparators) {
  const struct UnaryTestData cases[] = {
    { FPL(""),              FPL("") },
    { FPL("/"),             FPL("/") },
    { FPL("//"),            FPL("//") },
    { FPL("///"),           FPL("/") },
    { FPL("////"),          FPL("/") },
    { FPL("a/"),            FPL("a") },
    { FPL("a//"),           FPL("a") },
    { FPL("a///"),          FPL("a") },
    { FPL("a////"),         FPL("a") },
    { FPL("/a"),            FPL("/a") },
    { FPL("/a/"),           FPL("/a") },
    { FPL("/a//"),          FPL("/a") },
    { FPL("/a///"),         FPL("/a") },
    { FPL("/a////"),        FPL("/a") },
#if defined(FILE_PATH_USES_DRIVE_LETTERS)
    { FPL("c:"),            FPL("c:") },
    { FPL("c:/"),           FPL("c:/") },
    { FPL("c://"),          FPL("c://") },
    { FPL("c:///"),         FPL("c:/") },
    { FPL("c:////"),        FPL("c:/") },
    { FPL("c:/a"),          FPL("c:/a") },
    { FPL("c:/a/"),         FPL("c:/a") },
    { FPL("c:/a//"),        FPL("c:/a") },
    { FPL("c:/a///"),       FPL("c:/a") },
    { FPL("c:/a////"),      FPL("c:/a") },
#endif  // FILE_PATH_USES_DRIVE_LETTERS
#if defined(FILE_PATH_USES_WIN_SEPARATORS)
    { FPL("\\"),            FPL("\\") },
    { FPL("\\\\"),          FPL("\\\\") },
    { FPL("\\\\\\"),        FPL("\\") },
    { FPL("\\\\\\\\"),      FPL("\\") },
    { FPL("a\\"),           FPL("a") },
    { FPL("a\\\\"),         FPL("a") },
    { FPL("a\\\\\\"),       FPL("a") },
    { FPL("a\\\\\\\\"),     FPL("a") },
    { FPL("\\a"),           FPL("\\a") },
    { FPL("\\a\\"),         FPL("\\a") },
    { FPL("\\a\\\\"),       FPL("\\a") },
    { FPL("\\a\\\\\\"),     FPL("\\a") },
    { FPL("\\a\\\\\\\\"),   FPL("\\a") },
#if defined(FILE_PATH_USES_DRIVE_LETTERS)
    { FPL("c:\\"),          FPL("c:\\") },
    { FPL("c:\\\\"),        FPL("c:\\\\") },
    { FPL("c:\\\\\\"),      FPL("c:\\") },
    { FPL("c:\\\\\\\\"),    FPL("c:\\") },
    { FPL("c:\\a"),         FPL("c:\\a") },
    { FPL("c:\\a\\"),       FPL("c:\\a") },
    { FPL("c:\\a\\\\"),     FPL("c:\\a") },
    { FPL("c:\\a\\\\\\"),   FPL("c:\\a") },
    { FPL("c:\\a\\\\\\\\"), FPL("c:\\a") },
#endif  // FILE_PATH_USES_DRIVE_LETTERS
#endif  // FILE_PATH_USES_WIN_SEPARATORS
  };

  for (size_t i = 0; i < arraysize(cases); ++i) {
    FilePath input(cases[i].input);
    FilePath observed = input.StripTrailingSeparators();
    EXPECT_EQ(FilePath::StringType(cases[i].expected), observed.value()) <<
              "i: " << i << ", input: " << input.value();
  }
}

TEST_F(FilePathTest, IsAbsolute) {
  const struct UnaryBooleanTestData cases[] = {
    { FPL(""),       false },
    { FPL("a"),      false },
    { FPL("c:"),     false },
    { FPL("c:a"),    false },
    { FPL("a/b"),    false },
    { FPL("//"),     true },
    { FPL("//a"),    true },
    { FPL("c:a/b"),  false },
    { FPL("?:/a"),   false },
#if defined(FILE_PATH_USES_DRIVE_LETTERS)
    { FPL("/"),      false },
    { FPL("/a"),     false },
    { FPL("/."),     false },
    { FPL("/.."),    false },
    { FPL("c:/"),    true },
    { FPL("c:/a"),   true },
    { FPL("c:/."),   true },
    { FPL("c:/.."),  true },
    { FPL("C:/a"),   true },
    { FPL("d:/a"),   true },
#else  // FILE_PATH_USES_DRIVE_LETTERS
    { FPL("/"),      true },
    { FPL("/a"),     true },
    { FPL("/."),     true },
    { FPL("/.."),    true },
    { FPL("c:/"),    false },
#endif  // FILE_PATH_USES_DRIVE_LETTERS
#if defined(FILE_PATH_USES_WIN_SEPARATORS)
    { FPL("a\\b"),   false },
    { FPL("\\\\"),   true },
    { FPL("\\\\a"),  true },
    { FPL("a\\b"),   false },
    { FPL("\\\\"),   true },
    { FPL("//a"),    true },
    { FPL("c:a\\b"), false },
    { FPL("?:\\a"),  false },
#if defined(FILE_PATH_USES_DRIVE_LETTERS)
    { FPL("\\"),     false },
    { FPL("\\a"),    false },
    { FPL("\\."),    false },
    { FPL("\\.."),   false },
    { FPL("c:\\"),   true },
    { FPL("c:\\"),   true },
    { FPL("c:\\a"),  true },
    { FPL("c:\\."),  true },
    { FPL("c:\\.."), true },
    { FPL("C:\\a"),  true },
    { FPL("d:\\a"),  true },
#else  // FILE_PATH_USES_DRIVE_LETTERS
    { FPL("\\"),     true },
    { FPL("\\a"),    true },
    { FPL("\\."),    true },
    { FPL("\\.."),   true },
    { FPL("c:\\"),   false },
#endif  // FILE_PATH_USES_DRIVE_LETTERS
#endif  // FILE_PATH_USES_WIN_SEPARATORS
  };

  for (size_t i = 0; i < arraysize(cases); ++i) {
    FilePath input(cases[i].input);
    bool observed = input.IsAbsolute();
    EXPECT_EQ(cases[i].expected, observed) <<
              "i: " << i << ", input: " << input.value();
  }
}

TEST_F(FilePathTest, PathComponentsTest) {
  const struct UnaryTestData cases[] = {
    { FPL("//foo/bar/baz/"),          FPL("|//|foo|bar|baz")},
    { FPL("///"),                     FPL("|/")},
    { FPL("/foo//bar//baz/"),         FPL("|/|foo|bar|baz")},
    { FPL("/foo/bar/baz/"),           FPL("|/|foo|bar|baz")},
    { FPL("/foo/bar/baz//"),          FPL("|/|foo|bar|baz")},
    { FPL("/foo/bar/baz///"),         FPL("|/|foo|bar|baz")},
    { FPL("/foo/bar/baz"),            FPL("|/|foo|bar|baz")},
    { FPL("/foo/bar.bot/baz.txt"),    FPL("|/|foo|bar.bot|baz.txt")},
    { FPL("//foo//bar/baz"),          FPL("|//|foo|bar|baz")},
    { FPL("/"),                       FPL("|/")},
    { FPL("foo"),                     FPL("|foo")},
    { FPL(""),                        FPL("")},
#if defined(FILE_PATH_USES_DRIVE_LETTERS)
    { FPL("e:/foo"),                  FPL("|e:|/|foo")},
    { FPL("e:/"),                     FPL("|e:|/")},
    { FPL("e:"),                      FPL("|e:")},
#endif  // FILE_PATH_USES_DRIVE_LETTERS
#if defined(FILE_PATH_USES_WIN_SEPARATORS)
    { FPL("../foo"),                  FPL("|..|foo")},
    { FPL("./foo"),                   FPL("|foo")},
    { FPL("../foo/bar/"),             FPL("|..|foo|bar") },
    { FPL("\\\\foo\\bar\\baz\\"),     FPL("|\\\\|foo|bar|baz")},
    { FPL("\\\\\\"),                  FPL("|\\")},
    { FPL("\\foo\\\\bar\\\\baz\\"),   FPL("|\\|foo|bar|baz")},
    { FPL("\\foo\\bar\\baz\\"),       FPL("|\\|foo|bar|baz")},
    { FPL("\\foo\\bar\\baz\\\\"),     FPL("|\\|foo|bar|baz")},
    { FPL("\\foo\\bar\\baz\\\\\\"),   FPL("|\\|foo|bar|baz")},
    { FPL("\\foo\\bar\\baz"),         FPL("|\\|foo|bar|baz")},
    { FPL("\\foo\\bar/baz\\\\\\"),    FPL("|\\|foo|bar|baz")},
    { FPL("/foo\\bar\\baz"),          FPL("|/|foo|bar|baz")},
    { FPL("\\foo\\bar.bot\\baz.txt"), FPL("|\\|foo|bar.bot|baz.txt")},
    { FPL("\\\\foo\\\\bar\\baz"),     FPL("|\\\\|foo|bar|baz")},
    { FPL("\\"),                      FPL("|\\")},
#endif  // FILE_PATH_USES_WIN_SEPARATORS
  };

  for (size_t i = 0; i < arraysize(cases); ++i) {
    FilePath input(cases[i].input);
    std::vector<FilePath::StringType> comps;
    input.GetComponents(&comps);

    FilePath::StringType observed;
    for (size_t j = 0; j < comps.size(); ++j) {
      observed.append(FILE_PATH_LITERAL("|"), 1);
      observed.append(comps[j]);
    }
    EXPECT_EQ(FilePath::StringType(cases[i].expected), observed) <<
              "i: " << i << ", input: " << input.value();
  }
}

TEST_F(FilePathTest, AppendAndResolveRelativeTest) {
  const struct BinaryTestData cases[] = {
#if defined(FILE_PATH_USES_DRIVE_LETTERS)
    { { FPL("c:/"),              FPL("foo") },        FPL("c:/foo") },
    { { FPL("f:/foo/bar"),       FPL("..") },         FPL("f:/foo") },
    { { FPL("f:/foo.bar"),       FPL("..") },         FPL("f:/") },
    { { FPL("F:/foo/.."),        FPL("./bar/.") },    FPL("F:/bar") },
    { { FPL("E:/Foo/bar"),       FPL("../..") },      FPL("E:/") },
    { { FPL("E:/Foo/bar/."),     FPL("../..") },      FPL("E:/") },
    { { FPL("e:/foo/.."),        FPL("bar/..") },     FPL("e:/") },
    { { FPL("c:/foo/./bar/.."),  FPL("../baz") },     FPL("c:/baz") },
    { { FPL("E:/./foo/bar/.."),  FPL("../baz/..") },  FPL("E:/") },
    { { FPL("x:/foo/../bar/.."), FPL("baz/../boo") }, FPL("x:/boo") },
    { { FPL("E:/foo.bar/.."),    FPL("../baz/..") },  FPL("") },
    { { FPL("Z:/foo"),           FPL("../..") },      FPL("") },
    { { FPL("y:/"),              FPL("..") },         FPL("") },
    { { FPL("B:/.."),            FPL("bar/.") },      FPL("") },
    { { FPL("a:/foo/.."),        FPL("..") },         FPL("") },
    { { FPL("r:/.."),            FPL("..") },         FPL("") },
    { { FPL("F:/foo/.."),        FPL("../..") },      FPL("") },
    { { FPL("O:/foo/bar/.."),    FPL("../..") },      FPL("") },
#endif  // FILE_PATH_USES_DRIVE_LETTERS
#if defined(FILE_PATH_USES_WIN_SEPARATORS)
    { { FPL("\\\\"),                FPL("foo") },         FPL("\\\\foo") },
    { { FPL("\\\\foo"),             FPL("bar") },         FPL("\\\\foo\\bar") },
    { { FPL("\\\\foo\\bar"),        FPL("..") },          FPL("\\\\foo") },
    { { FPL("\\\\foo.bar"),         FPL("..") },          FPL("\\\\") },
    { { FPL("\\\\Foo\\bar"),        FPL("..\\..") },      FPL("\\\\") },
    { { FPL("\\\\Foo\\bar\\."),     FPL("..\\..") },      FPL("\\\\") },
    { { FPL("\\\\foo\\bar"), FPL("foo\\..\\baz") }, FPL("\\\\foo\\bar\\baz") },
    { { FPL("\\\\foo\\.\\bar"),     FPL("..\\baz\\.") },  FPL("\\\\foo\\baz") },
    { { FPL("\\\\.\\foo\\.."),      FPL("bar") },         FPL("\\\\bar") },
    { { FPL("\\\\foo\\.."),         FPL(".\\bar\\..") },  FPL("\\\\") },
    { { FPL("\\\\foo\\bar\\.."),    FPL("..\\baz") },     FPL("\\\\baz") },
    { { FPL("\\\\foo\\bar\\.."),    FPL("..\\baz\\..") }, FPL("\\\\") },
    { { FPL("\\\\foo\\..\\bar\\.."), FPL("baz\\..\\boo") }, FPL("\\\\boo"), },
    { { FPL("\\\\foo.bar\\.."),     FPL("..\\baz\\..") }, FPL("") },
    { { FPL("\\\\foo"),             FPL("..\\..") },      FPL("") },
    { { FPL("\\\\"),                FPL("..") },          FPL("") },
    { { FPL("\\\\.."),              FPL("bar\\.") },      FPL("") },
    { { FPL("\\\\foo\\.."),         FPL("..") },          FPL("") },
    { { FPL("\\\\.."),              FPL("..") },          FPL("") },
    { { FPL("\\\\foo\\.."),         FPL("..\\..") },      FPL("") },
    { { FPL("\\\\foo\\bar\\.."),    FPL("..\\..") },      FPL("") },
#if defined(FILE_PATH_USES_DRIVE_LETTERS)
    { { FPL("E:/foo"),           FPL("bar") },        FPL("E:/foo\\bar") },
    { { FPL("C:/foo/bar"),       FPL("foo/../baz") }, FPL("C:/foo\\bar\\baz") },
    { { FPL("e:/foo/bar"),       FPL("../baz") },     FPL("e:/foo\\baz") },
#endif
#else  // FILE_PATH_USES_WIN_SEPARAORS
    { { FPL("/"),              FPL("foo") },        FPL("/foo") },
    { { FPL("/foo"),           FPL("bar") },        FPL("/foo/bar") },
    { { FPL("/foo/bar/"),      FPL("..") },         FPL("/foo") },
    { { FPL("/foo.bar"),       FPL("..") },         FPL("/") },
    { { FPL("//foo"),          FPL("..") },         FPL("//") },
    { { FPL("/foo/./bar"),     FPL("../..") },      FPL("/") },
    { { FPL("/foo/bar/."),     FPL("foo/../baz") }, FPL("/foo/bar/baz") },
    { { FPL("/./foo/bar"),     FPL("../baz/.") },   FPL("/foo/baz") },
    { { FPL("/foo/.."),        FPL("./bar") },      FPL("/bar") },
    { { FPL("/foo/.."),        FPL("bar/..") },     FPL("/") },
    { { FPL("//foo/bar/.."),   FPL("../baz") },     FPL("//baz") },
    { { FPL("/foo/bar/.."),    FPL("../baz/..") },  FPL("/") },
    { { FPL("/foo/../bar/.."), FPL("baz/../boo") }, FPL("/boo") },
    { { FPL("//foo.bar/.."),   FPL("../baz") },     FPL("") },
    { { FPL("/foo"),           FPL("../..") },      FPL("") },
    { { FPL("//"),             FPL("..") },         FPL("") },
    { { FPL("/.."),            FPL("./bar") },      FPL("") },
    { { FPL("/foo/.."),        FPL("..") },         FPL("") },
    { { FPL("/.."),            FPL("..") },         FPL("") },
    { { FPL("/foo/.."),        FPL("../..") },      FPL("") },
    { { FPL("/foo/bar/.."),    FPL("../..") },      FPL("") },
#if defined(FILE_PATH_USES_DRIVE_LETTERS)
    { { FPL("E:/foo"),           FPL("bar") },        FPL("E:/foo/bar") },
    { { FPL("C:/foo/bar"),       FPL("foo/../baz") }, FPL("C:/foo/bar/baz") },
    { { FPL("e:/foo/bar"),       FPL("../baz") },     FPL("e:/foo/baz") },
#endif
#endif  // FILE_PATH_USES_WIN_SEPARAORS
  };

  for (size_t i = 0; i < arraysize(cases); ++i) {
    FilePath parent(cases[i].inputs[0]);
    FilePath child(cases[i].inputs[1]);

    FilePath result;
    EXPECT_EQ(cases[i].expected[0] != '\0',
              parent.AppendAndResolveRelative(child, &result)) <<
        "i: " << i << ", parent: " << parent.value() << ", child: " <<
        child.value();
    EXPECT_STREQ(cases[i].expected, result.value().c_str());
  }
}

TEST_F(FilePathTest, IsParentTest) {
  const struct BinaryBooleanTestData cases[] = {
    { { FPL("/"),             FPL("/foo/bar/baz") },      true},
    { { FPL("/foo/bar"),      FPL("/foo/bar/baz") },      true},
    { { FPL("/foo/bar/"),     FPL("/foo/bar/baz") },      true},
    { { FPL("//foo/bar/"),    FPL("//foo/bar/baz") },     true},
    { { FPL("/foo/bar"),      FPL("/foo2/bar/baz") },     false},
    { { FPL("/foo/bar.txt"),  FPL("/foo/bar/baz") },      false},
    { { FPL("/foo/bar"),      FPL("/foo/bar2/baz") },     false},
    { { FPL("/foo/bar"),      FPL("/foo/bar") },          false},
    { { FPL("/foo/bar/baz"),  FPL("/foo/bar") },          false},
    { { FPL("foo/bar"),       FPL("foo/bar/baz") },       true},
    { { FPL("foo/bar"),       FPL("foo2/bar/baz") },      false},
    { { FPL("foo/bar"),       FPL("foo/bar2/baz") },      false},
    { { FPL(""),              FPL("foo") },               false},
#if defined(FILE_PATH_USES_DRIVE_LETTERS)
    { { FPL("c:/foo/bar"),    FPL("c:/foo/bar/baz") },    true},
    { { FPL("E:/foo/bar"),    FPL("e:/foo/bar/baz") },    true},
    { { FPL("f:/foo/bar"),    FPL("F:/foo/bar/baz") },    true},
    { { FPL("E:/Foo/bar"),    FPL("e:/foo/bar/baz") },    false},
    { { FPL("f:/foo/bar"),    FPL("F:/foo/Bar/baz") },    false},
    { { FPL("c:/"),           FPL("c:/foo/bar/baz") },    true},
    { { FPL("c:"),            FPL("c:/foo/bar/baz") },    true},
    { { FPL("c:/foo/bar"),    FPL("d:/foo/bar/baz") },    false},
    { { FPL("c:/foo/bar"),    FPL("D:/foo/bar/baz") },    false},
    { { FPL("C:/foo/bar"),    FPL("d:/foo/bar/baz") },    false},
    { { FPL("c:/foo/bar"),    FPL("c:/foo2/bar/baz") },   false},
    { { FPL("e:/foo/bar"),    FPL("E:/foo2/bar/baz") },   false},
    { { FPL("F:/foo/bar"),    FPL("f:/foo2/bar/baz") },   false},
    { { FPL("c:/foo/bar"),    FPL("c:/foo/bar2/baz") },   false},
#endif  // FILE_PATH_USES_DRIVE_LETTERS
#if defined(FILE_PATH_USES_WIN_SEPARATORS)
    { { FPL("\\foo\\bar"),    FPL("\\foo\\bar\\baz") },   true},
    { { FPL("\\foo/bar"),     FPL("\\foo\\bar\\baz") },   true},
    { { FPL("\\foo/bar"),     FPL("\\foo/bar/baz") },     true},
    { { FPL("\\"),            FPL("\\foo\\bar\\baz") },   true},
    { { FPL(""),              FPL("\\foo\\bar\\baz") },   false},
    { { FPL("\\foo\\bar"),    FPL("\\foo2\\bar\\baz") },  false},
    { { FPL("\\foo\\bar"),    FPL("\\foo\\bar2\\baz") },  false},
#endif  // FILE_PATH_USES_WIN_SEPARATORS
  };

  for (size_t i = 0; i < arraysize(cases); ++i) {
    FilePath parent(cases[i].inputs[0]);
    FilePath child(cases[i].inputs[1]);

    EXPECT_EQ(parent.IsParent(child), cases[i].expected) <<
        "i: " << i << ", parent: " << parent.value() << ", child: " <<
        child.value();
  }
}

TEST_F(FilePathTest, AppendRelativePathTest) {
  const struct BinaryTestData cases[] = {
#if defined(FILE_PATH_USES_WIN_SEPARATORS)
    { { FPL("/"),             FPL("/foo/bar/baz") },      FPL("foo\\bar\\baz")},
#else  // FILE_PATH_USES_WIN_SEPARATORS
    { { FPL("/"),             FPL("/foo/bar/baz") },      FPL("foo/bar/baz")},
#endif  // FILE_PATH_USES_WIN_SEPARATORS
    { { FPL("/foo/bar"),      FPL("/foo/bar/baz") },      FPL("baz")},
    { { FPL("/foo/bar/"),     FPL("/foo/bar/baz") },      FPL("baz")},
    { { FPL("//foo/bar/"),    FPL("//foo/bar/baz") },     FPL("baz")},
    { { FPL("/foo/bar"),      FPL("/foo2/bar/baz") },     FPL("")},
    { { FPL("/foo/bar.txt"),  FPL("/foo/bar/baz") },      FPL("")},
    { { FPL("/foo/bar"),      FPL("/foo/bar2/baz") },     FPL("")},
    { { FPL("/foo/bar"),      FPL("/foo/bar") },          FPL("")},
    { { FPL("/foo/bar/baz"),  FPL("/foo/bar") },          FPL("")},
    { { FPL("foo/bar"),       FPL("foo/bar/baz") },       FPL("baz")},
    { { FPL("foo/bar"),       FPL("foo2/bar/baz") },      FPL("")},
    { { FPL("foo/bar"),       FPL("foo/bar2/baz") },      FPL("")},
    { { FPL(""),              FPL("foo") },               FPL("")},
#if defined(FILE_PATH_USES_DRIVE_LETTERS)
    { { FPL("c:/foo/bar"),    FPL("c:/foo/bar/baz") },    FPL("baz")},
    { { FPL("E:/foo/bar"),    FPL("e:/foo/bar/baz") },    FPL("baz")},
    { { FPL("f:/foo/bar"),    FPL("F:/foo/bar/baz") },    FPL("baz")},
    { { FPL("E:/Foo/bar"),    FPL("e:/foo/bar/baz") },    FPL("")},
    { { FPL("f:/foo/bar"),    FPL("F:/foo/Bar/baz") },    FPL("")},
#if defined(FILE_PATH_USES_WIN_SEPARATORS)
    { { FPL("c:/"),           FPL("c:/foo/bar/baz") },    FPL("foo\\bar\\baz")},
    // TODO(akalin): Figure out how to handle the corner case in the
    // commented-out test case below.  Appending to an empty path gives
    // /foo\bar\baz but appending to a nonempty path "blah" gives
    // blah\foo\bar\baz.
    // { { FPL("c:"),            FPL("c:/foo/bar/baz") }, FPL("foo\\bar\\baz")},
#endif  // FILE_PATH_USES_WIN_SEPARATORS
    { { FPL("c:/foo/bar"),    FPL("d:/foo/bar/baz") },    FPL("")},
    { { FPL("c:/foo/bar"),    FPL("D:/foo/bar/baz") },    FPL("")},
    { { FPL("C:/foo/bar"),    FPL("d:/foo/bar/baz") },    FPL("")},
    { { FPL("c:/foo/bar"),    FPL("c:/foo2/bar/baz") },   FPL("")},
    { { FPL("e:/foo/bar"),    FPL("E:/foo2/bar/baz") },   FPL("")},
    { { FPL("F:/foo/bar"),    FPL("f:/foo2/bar/baz") },   FPL("")},
    { { FPL("c:/foo/bar"),    FPL("c:/foo/bar2/baz") },   FPL("")},
#endif  // FILE_PATH_USES_DRIVE_LETTERS
#if defined(FILE_PATH_USES_WIN_SEPARATORS)
    { { FPL("\\foo\\bar"),    FPL("\\foo\\bar\\baz") },   FPL("baz")},
    { { FPL("\\foo/bar"),     FPL("\\foo\\bar\\baz") },   FPL("baz")},
    { { FPL("\\foo/bar"),     FPL("\\foo/bar/baz") },     FPL("baz")},
    { { FPL("\\"),            FPL("\\foo\\bar\\baz") },   FPL("foo\\bar\\baz")},
    { { FPL(""),              FPL("\\foo\\bar\\baz") },   FPL("")},
    { { FPL("\\foo\\bar"),    FPL("\\foo2\\bar\\baz") },  FPL("")},
    { { FPL("\\foo\\bar"),    FPL("\\foo\\bar2\\baz") },  FPL("")},
#endif  // FILE_PATH_USES_WIN_SEPARATORS
  };

  const FilePath base(FPL("blah"));

  for (size_t i = 0; i < arraysize(cases); ++i) {
    FilePath parent(cases[i].inputs[0]);
    FilePath child(cases[i].inputs[1]);
    {
      FilePath result;
      bool success = parent.AppendRelativePath(child, &result);
      EXPECT_EQ(cases[i].expected[0] != '\0', success) <<
        "i: " << i << ", parent: " << parent.value() << ", child: " <<
        child.value();
      EXPECT_STREQ(cases[i].expected, result.value().c_str()) <<
        "i: " << i << ", parent: " << parent.value() << ", child: " <<
        child.value();
    }
    {
      FilePath result(base);
      bool success = parent.AppendRelativePath(child, &result);
      EXPECT_EQ(cases[i].expected[0] != '\0', success) <<
        "i: " << i << ", parent: " << parent.value() << ", child: " <<
        child.value();
      EXPECT_EQ(base.Append(cases[i].expected).value(), result.value()) <<
        "i: " << i << ", parent: " << parent.value() << ", child: " <<
        child.value();
    }
  }
}

TEST_F(FilePathTest, EqualityTest) {
  const struct BinaryBooleanTestData cases[] = {
    { { FPL("/foo/bar/baz"),  FPL("/foo/bar/baz") },      true},
    { { FPL("/foo/bar"),      FPL("/foo/bar/baz") },      false},
    { { FPL("/foo/bar/baz"),  FPL("/foo/bar") },          false},
    { { FPL("//foo/bar/"),    FPL("//foo/bar/") },        true},
    { { FPL("/foo/bar"),      FPL("/foo2/bar") },         false},
    { { FPL("/foo/bar.txt"),  FPL("/foo/bar") },          false},
    { { FPL("foo/bar"),       FPL("foo/bar") },           true},
    { { FPL("foo/bar"),       FPL("foo/bar/baz") },       false},
    { { FPL(""),              FPL("foo") },               false},
#if defined(FILE_PATH_USES_DRIVE_LETTERS)
    { { FPL("c:/foo/bar"),    FPL("c:/foo/bar") },        true},
    { { FPL("E:/foo/bar"),    FPL("e:/foo/bar") },        true},
    { { FPL("f:/foo/bar"),    FPL("F:/foo/bar") },        true},
    { { FPL("E:/Foo/bar"),    FPL("e:/foo/bar") },        false},
    { { FPL("f:/foo/bar"),    FPL("F:/foo/Bar") },        false},
    { { FPL("c:/"),           FPL("c:/") },               true},
    { { FPL("c:"),            FPL("c:") },                true},
    { { FPL("c:/foo/bar"),    FPL("d:/foo/bar") },        false},
    { { FPL("c:/foo/bar"),    FPL("D:/foo/bar") },        false},
    { { FPL("C:/foo/bar"),    FPL("d:/foo/bar") },        false},
    { { FPL("c:/foo/bar"),    FPL("c:/foo2/bar") },       false},
#endif  // FILE_PATH_USES_DRIVE_LETTERS
#if defined(FILE_PATH_USES_WIN_SEPARATORS)
    { { FPL("\\foo\\bar"),    FPL("\\foo\\bar") },        true},
    { { FPL("\\foo/bar"),     FPL("\\foo/bar") },         true},
    { { FPL("\\foo/bar"),     FPL("\\foo\bar") },         false},
    { { FPL("\\"),            FPL("\\") },                true},
    { { FPL("\\"),            FPL("/") },                 false},
    { { FPL(""),              FPL("\\") },                false},
    { { FPL("\\foo\\bar"),    FPL("\\foo2\\bar") },       false},
    { { FPL("\\foo\\bar"),    FPL("\\foo\\bar2") },       false},
#if defined(FILE_PATH_USES_DRIVE_LETTERS)
    { { FPL("c:\\foo\\bar"),    FPL("c:\\foo\\bar") },    true},
    { { FPL("E:\\foo\\bar"),    FPL("e:\\foo\\bar") },    true},
    { { FPL("f:\\foo\\bar"),    FPL("F:\\foo/bar") },     false},
#endif  // FILE_PATH_USES_DRIVE_LETTERS
#endif  // FILE_PATH_USES_WIN_SEPARATORS
  };

  for (size_t i = 0; i < arraysize(cases); ++i) {
    FilePath a(cases[i].inputs[0]);
    FilePath b(cases[i].inputs[1]);

    EXPECT_EQ(a == b, cases[i].expected) <<
      "equality i: " << i << ", a: " << a.value() << ", b: " <<
      b.value();
  }

  for (size_t i = 0; i < arraysize(cases); ++i) {
    FilePath a(cases[i].inputs[0]);
    FilePath b(cases[i].inputs[1]);

    EXPECT_EQ(a != b, !cases[i].expected) <<
      "inequality i: " << i << ", a: " << a.value() << ", b: " <<
      b.value();
  }
}

TEST_F(FilePathTest, Extension) {
  FilePath base_dir(FILE_PATH_LITERAL("base_dir"));

  FilePath jpg = base_dir.Append(FILE_PATH_LITERAL("foo.jpg"));
  EXPECT_EQ(jpg.Extension(), FILE_PATH_LITERAL(".jpg"));

  FilePath base = jpg.BaseName().RemoveExtension();
  EXPECT_EQ(base.value(), FILE_PATH_LITERAL("foo"));

  FilePath path_no_ext = base_dir.Append(base);
  EXPECT_EQ(jpg.RemoveExtension().value(), path_no_ext.value());

  EXPECT_EQ(path_no_ext.value(), path_no_ext.RemoveExtension().value());
  EXPECT_EQ(path_no_ext.Extension(), FILE_PATH_LITERAL(""));
}

TEST_F(FilePathTest, Extension2) {
  const struct UnaryTestData cases[] = {
#if defined(FILE_PATH_USES_WIN_SEPARATORS)
    { FPL("C:\\a\\b\\c.ext"),        FPL(".ext") },
    { FPL("C:\\a\\b\\c."),           FPL(".") },
    { FPL("C:\\a\\b\\c"),            FPL("") },
    { FPL("C:\\a\\b\\"),             FPL("") },
    { FPL("C:\\a\\b.\\"),            FPL(".") },
    { FPL("C:\\a\\b\\c.ext1.ext2"),  FPL(".ext2") },
    { FPL("C:\\foo.bar\\\\\\"),      FPL(".bar") },
    { FPL("C:\\foo.bar\\.."),        FPL("") },
    { FPL("C:\\foo.bar\\..\\\\"),    FPL("") },
#endif
    { FPL("/foo/bar/baz.ext"),       FPL(".ext") },
    { FPL("/foo/bar/baz."),          FPL(".") },
    { FPL("/foo/bar/baz.."),         FPL(".") },
    { FPL("/foo/bar/baz"),           FPL("") },
    { FPL("/foo/bar/"),              FPL("") },
    { FPL("/foo/bar./"),             FPL(".") },
    { FPL("/foo/bar/baz.ext1.ext2"), FPL(".ext2") },
    { FPL("."),                      FPL("") },
    { FPL(".."),                     FPL("") },
    { FPL("./foo"),                  FPL("") },
    { FPL("./foo.ext"),              FPL(".ext") },
    { FPL("/foo.ext1/bar.ext2"),     FPL(".ext2") },
    { FPL("/foo.bar////"),           FPL(".bar") },
    { FPL("/foo.bar/.."),            FPL("") },
    { FPL("/foo.bar/..////"),        FPL("") },
  };
  for (unsigned int i = 0; i < arraysize(cases); ++i) {
    FilePath path(cases[i].input);
    FilePath::StringType extension = path.Extension();
    EXPECT_STREQ(cases[i].expected, extension.c_str()) << "i: " << i <<
        ", path: " << path.value();
  }
}

TEST_F(FilePathTest, InsertBeforeExtension) {
  const struct BinaryTestData cases[] = {
    { { FPL(""),                FPL("") },        FPL("") },
    { { FPL(""),                FPL("txt") },     FPL("") },
    { { FPL("."),               FPL("txt") },     FPL("") },
    { { FPL(".."),              FPL("txt") },     FPL("") },
    { { FPL("foo.dll"),         FPL("txt") },     FPL("footxt.dll") },
    { { FPL("."),               FPL("") },        FPL(".") },
    { { FPL("foo.dll"),         FPL(".txt") },    FPL("foo.txt.dll") },
    { { FPL("foo"),             FPL("txt") },     FPL("footxt") },
    { { FPL("foo"),             FPL(".txt") },    FPL("foo.txt") },
    { { FPL("foo.baz.dll"),     FPL("txt") },     FPL("foo.baztxt.dll") },
    { { FPL("foo.baz.dll"),     FPL(".txt") },    FPL("foo.baz.txt.dll") },
    { { FPL("foo.dll"),         FPL("") },        FPL("foo.dll") },
    { { FPL("foo.dll"),         FPL(".") },       FPL("foo..dll") },
    { { FPL("foo"),             FPL("") },        FPL("foo") },
    { { FPL("foo"),             FPL(".") },       FPL("foo.") },
    { { FPL("foo.baz.dll"),     FPL("") },        FPL("foo.baz.dll") },
    { { FPL("foo.baz.dll"),     FPL(".") },       FPL("foo.baz..dll") },
#if defined(FILE_PATH_USES_WIN_SEPARATORS)
    { { FPL("\\"),              FPL("") },        FPL("\\") },
    { { FPL("\\"),              FPL("txt") },     FPL("\\txt") },
    { { FPL("\\."),             FPL("txt") },     FPL("") },
    { { FPL("\\.."),            FPL("txt") },     FPL("") },
    { { FPL("\\."),             FPL("") },        FPL("\\.") },
    { { FPL("C:\\bar\\foo.dll"), FPL("txt") },
        FPL("C:\\bar\\footxt.dll") },
    { { FPL("C:\\bar.baz\\foodll"), FPL("txt") },
        FPL("C:\\bar.baz\\foodlltxt") },
    { { FPL("C:\\bar.baz\\foo.dll"), FPL("txt") },
        FPL("C:\\bar.baz\\footxt.dll") },
    { { FPL("C:\\bar.baz\\foo.dll.exe"), FPL("txt") },
        FPL("C:\\bar.baz\\foo.dlltxt.exe") },
    { { FPL("C:\\bar.baz\\foo"), FPL("") },
        FPL("C:\\bar.baz\\foo") },
    { { FPL("C:\\bar.baz\\foo.exe"), FPL("") },
        FPL("C:\\bar.baz\\foo.exe") },
    { { FPL("C:\\bar.baz\\foo.dll.exe"), FPL("") },
        FPL("C:\\bar.baz\\foo.dll.exe") },
    { { FPL("C:\\bar\\baz\\foo.exe"), FPL(" (1)") },
        FPL("C:\\bar\\baz\\foo (1).exe") },
    { { FPL("C:\\foo.baz\\\\"), FPL(" (1)") },    FPL("C:\\foo (1).baz") },
    { { FPL("C:\\foo.baz\\..\\"), FPL(" (1)") },  FPL("") },
#endif
    { { FPL("/"),               FPL("") },        FPL("/") },
    { { FPL("/"),               FPL("txt") },     FPL("/txt") },
    { { FPL("/."),              FPL("txt") },     FPL("") },
    { { FPL("/.."),             FPL("txt") },     FPL("") },
    { { FPL("/."),              FPL("") },        FPL("/.") },
    { { FPL("/bar/foo.dll"),    FPL("txt") },     FPL("/bar/footxt.dll") },
    { { FPL("/bar.baz/foodll"), FPL("txt") },     FPL("/bar.baz/foodlltxt") },
    { { FPL("/bar.baz/foo.dll"), FPL("txt") },    FPL("/bar.baz/footxt.dll") },
    { { FPL("/bar.baz/foo.dll.exe"), FPL("txt") },
        FPL("/bar.baz/foo.dlltxt.exe") },
    { { FPL("/bar.baz/foo"),    FPL("") },        FPL("/bar.baz/foo") },
    { { FPL("/bar.baz/foo.exe"), FPL("") },       FPL("/bar.baz/foo.exe") },
    { { FPL("/bar.baz/foo.dll.exe"), FPL("") },   FPL("/bar.baz/foo.dll.exe") },
    { { FPL("/bar/baz/foo.exe"), FPL(" (1)") },   FPL("/bar/baz/foo (1).exe") },
    { { FPL("/bar/baz/..////"), FPL(" (1)") },    FPL("") },
  };
  for (unsigned int i = 0; i < arraysize(cases); ++i) {
    FilePath path(cases[i].inputs[0]);
    FilePath result = path.InsertBeforeExtension(cases[i].inputs[1]);
    EXPECT_EQ(cases[i].expected, result.value()) << "i: " << i <<
        ", path: " << path.value() << ", insert: " << cases[i].inputs[1];
  }
}

TEST_F(FilePathTest, ReplaceExtension) {
  const struct BinaryTestData cases[] = {
    { { FPL(""),              FPL("") },      FPL("") },
    { { FPL(""),              FPL("txt") },   FPL("") },
    { { FPL("."),             FPL("txt") },   FPL("") },
    { { FPL(".."),            FPL("txt") },   FPL("") },
    { { FPL("."),             FPL("") },      FPL("") },
    { { FPL("foo.dll"),       FPL("txt") },   FPL("foo.txt") },
    { { FPL("foo..dll"),      FPL("txt") },   FPL("foo..txt") },
    { { FPL("foo.dll"),       FPL(".txt") },  FPL("foo.txt") },
    { { FPL("foo"),           FPL("txt") },   FPL("foo.txt") },
    { { FPL("foo."),          FPL("txt") },   FPL("foo.txt") },
    { { FPL("foo.."),         FPL("txt") },   FPL("foo..txt") },
    { { FPL("foo"),           FPL(".txt") },  FPL("foo.txt") },
    { { FPL("foo.baz.dll"),   FPL("txt") },   FPL("foo.baz.txt") },
    { { FPL("foo.baz.dll"),   FPL(".txt") },  FPL("foo.baz.txt") },
    { { FPL("foo.dll"),       FPL("") },      FPL("foo") },
    { { FPL("foo.dll"),       FPL(".") },     FPL("foo") },
    { { FPL("foo"),           FPL("") },      FPL("foo") },
    { { FPL("foo"),           FPL(".") },     FPL("foo") },
    { { FPL("foo.baz.dll"),   FPL("") },      FPL("foo.baz") },
    { { FPL("foo.baz.dll"),   FPL(".") },     FPL("foo.baz") },
#if defined(FILE_PATH_USES_WIN_SEPARATORS)
    { { FPL("C:\\foo.bar\\foo"),    FPL("baz") }, FPL("C:\\foo.bar\\foo.baz") },
    { { FPL("C:\\foo.bar\\..\\\\"), FPL("baz") }, FPL("") },
#endif
    { { FPL("/foo.bar/foo"),        FPL("baz") }, FPL("/foo.bar/foo.baz") },
    { { FPL("/foo.bar/..////"),     FPL("baz") }, FPL("") },
  };
  for (unsigned int i = 0; i < arraysize(cases); ++i) {
    FilePath path(cases[i].inputs[0]);
    FilePath replaced = path.ReplaceExtension(cases[i].inputs[1]);
    EXPECT_EQ(cases[i].expected, replaced.value()) << "i: " << i <<
        ", path: " << path.value() << ", replace: " << cases[i].inputs[1];
  }
}

TEST_F(FilePathTest, MatchesExtension) {
  const struct BinaryBooleanTestData cases[] = {
    { { FPL("foo"),                     FPL("") },                    true},
    { { FPL("foo"),                     FPL(".") },                   false},
    { { FPL("foo."),                    FPL("") },                    false},
    { { FPL("foo."),                    FPL(".") },                   true},
    { { FPL("foo.txt"),                 FPL(".dll") },                false},
    { { FPL("foo.txt"),                 FPL(".txt") },                true},
    { { FPL("foo.txt.dll"),             FPL(".txt") },                false},
    { { FPL("foo.txt.dll"),             FPL(".dll") },                true},
    { { FPL("foo.TXT"),                 FPL(".txt") },                true},
    { { FPL("foo.txt"),                 FPL(".TXT") },                true},
    { { FPL("foo.tXt"),                 FPL(".txt") },                true},
    { { FPL("foo.txt"),                 FPL(".tXt") },                true},
    { { FPL("foo.tXt"),                 FPL(".TXT") },                true},
    { { FPL("foo.tXt"),                 FPL(".tXt") },                true},
#if defined(FILE_PATH_USES_DRIVE_LETTERS)
    { { FPL("c:/foo.txt.dll"),          FPL(".txt") },                false},
    { { FPL("c:/foo.txt"),              FPL(".txt") },                true},
#endif  // FILE_PATH_USES_DRIVE_LETTERS
#if defined(FILE_PATH_USES_WIN_SEPARATORS)
    { { FPL("c:\\bar\\foo.txt.dll"),    FPL(".txt") },                false},
    { { FPL("c:\\bar\\foo.txt"),        FPL(".txt") },                true},
#endif  // FILE_PATH_USES_DRIVE_LETTERS
    { { FPL("/bar/foo.txt.dll"),        FPL(".txt") },                false},
    { { FPL("/bar/foo.txt"),            FPL(".txt") },                true},
#if defined(OS_WIN) || defined(OS_MACOSX)
    // Umlauts A, O, U: direct comparison, and upper case vs. lower case
    { { FPL("foo.\u00E4\u00F6\u00FC"),  FPL(".\u00E4\u00F6\u00FC") }, true},
    { { FPL("foo.\u00C4\u00D6\u00DC"),  FPL(".\u00E4\u00F6\u00FC") }, true},
    // C with circumflex: direct comparison, and upper case vs. lower case
    { { FPL("foo.\u0109"),              FPL(".\u0109") },             true},
    { { FPL("foo.\u0108"),              FPL(".\u0109") },             true},
#endif
  };

  for (size_t i = 0; i < arraysize(cases); ++i) {
    FilePath path(cases[i].inputs[0]);
    FilePath::StringType ext(cases[i].inputs[1]);

    EXPECT_EQ(cases[i].expected, path.MatchesExtension(ext)) <<
        "i: " << i << ", path: " << path.value() << ", ext: " << ext;
  }
}

TEST_F(FilePathTest, CompareIgnoreCase) {
  const struct BinaryIntTestData cases[] = {
    { { FPL("foo"),                          FPL("foo") },                  0},
    { { FPL("FOO"),                          FPL("foo") },                  0},
    { { FPL("foo.ext"),                      FPL("foo.ext") },              0},
    { { FPL("FOO.EXT"),                      FPL("foo.ext") },              0},
    { { FPL("Foo.Ext"),                      FPL("foo.ext") },              0},
    { { FPL("foO"),                          FPL("foo") },                  0},
    { { FPL("foo"),                          FPL("foO") },                  0},
    { { FPL("fOo"),                          FPL("foo") },                  0},
    { { FPL("foo"),                          FPL("fOo") },                  0},
    { { FPL("bar"),                          FPL("foo") },                 -1},
    { { FPL("foo"),                          FPL("bar") },                  1},
    { { FPL("BAR"),                          FPL("foo") },                 -1},
    { { FPL("FOO"),                          FPL("bar") },                  1},
    { { FPL("bar"),                          FPL("FOO") },                 -1},
    { { FPL("foo"),                          FPL("BAR") },                  1},
    { { FPL("BAR"),                          FPL("FOO") },                 -1},
    { { FPL("FOO"),                          FPL("BAR") },                  1},
    // German "Eszett" (lower case and the new-fangled upper case)
    // Note that uc(<lowercase eszett>) => "SS", NOT <uppercase eszett>!
    // However, neither Windows nor Mac OSX converts these.
    // (or even have glyphs for <uppercase eszett>)
    { { FPL("\u00DF"),                       FPL("\u00DF") },               0},
    { { FPL("\u1E9E"),                       FPL("\u1E9E") },               0},
    { { FPL("\u00DF"),                       FPL("\u1E9E") },              -1},
    { { FPL("SS"),                           FPL("\u00DF") },              -1},
    { { FPL("SS"),                           FPL("\u1E9E") },              -1},
#if defined(OS_WIN) || defined(OS_MACOSX)
    // Umlauts A, O, U: direct comparison, and upper case vs. lower case
    { { FPL("\u00E4\u00F6\u00FC"),           FPL("\u00E4\u00F6\u00FC") },   0},
    { { FPL("\u00C4\u00D6\u00DC"),           FPL("\u00E4\u00F6\u00FC") },   0},
    // C with circumflex: direct comparison, and upper case vs. lower case
    { { FPL("\u0109"),                       FPL("\u0109") },               0},
    { { FPL("\u0108"),                       FPL("\u0109") },               0},
    // Cyrillic letter SHA: direct comparison, and upper case vs. lower case
    { { FPL("\u0428"),                       FPL("\u0428") },               0},
    { { FPL("\u0428"),                       FPL("\u0448") },               0},
    // Greek letter DELTA: direct comparison, and upper case vs. lower case
    { { FPL("\u0394"),                       FPL("\u0394") },               0},
    { { FPL("\u0394"),                       FPL("\u03B4") },               0},
    // Japanese full-width A: direct comparison, and upper case vs. lower case
    // Note that full-width and standard characters are considered different.
    { { FPL("\uFF21"),                       FPL("\uFF21") },               0},
    { { FPL("\uFF21"),                       FPL("\uFF41") },               0},
    { { FPL("A"),                            FPL("\uFF21") },              -1},
    { { FPL("A"),                            FPL("\uFF41") },              -1},
    { { FPL("a"),                            FPL("\uFF21") },              -1},
    { { FPL("a"),                            FPL("\uFF41") },              -1},
#endif
#if defined(OS_MACOSX)
    // Codepoints > 0x1000
    // Georgian letter DON: direct comparison, and upper case vs. lower case
    { { FPL("\u10A3"),                       FPL("\u10A3") },               0},
    { { FPL("\u10A3"),                       FPL("\u10D3") },               0},
    // Combining characters vs. pre-composed characters, upper and lower case
    { { FPL("k\u0301u\u032Do\u0304\u0301n"), FPL("\u1E31\u1E77\u1E53n") },  0},
    { { FPL("k\u0301u\u032Do\u0304\u0301n"), FPL("kuon") },                 1},
    { { FPL("kuon"), FPL("k\u0301u\u032Do\u0304\u0301n") },                -1},
    { { FPL("K\u0301U\u032DO\u0304\u0301N"), FPL("KUON") },                 1},
    { { FPL("KUON"), FPL("K\u0301U\u032DO\u0304\u0301N") },                -1},
    { { FPL("k\u0301u\u032Do\u0304\u0301n"), FPL("KUON") },                 1},
    { { FPL("K\u0301U\u032DO\u0304\u0301N"), FPL("\u1E31\u1E77\u1E53n") },  0},
    { { FPL("k\u0301u\u032Do\u0304\u0301n"), FPL("\u1E30\u1E76\u1E52n") },  0},
    { { FPL("k\u0301u\u032Do\u0304\u0302n"), FPL("\u1E30\u1E76\u1E52n") },  1},
#endif
  };

  for (size_t i = 0; i < arraysize(cases); ++i) {
    FilePath::StringType s1(cases[i].inputs[0]);
    FilePath::StringType s2(cases[i].inputs[1]);
    int result = FilePath::CompareIgnoreCase(s1, s2);
    EXPECT_EQ(cases[i].expected, result) <<
        "i: " << i << ", s1: " << s1 << ", s2: " << s2;
  }
}

TEST_F(FilePathTest, ReferencesParent) {
  const struct UnaryBooleanTestData cases[] = {
    { FPL("."),        false },
    { FPL(".."),       true },
    { FPL("a.."),      false },
    { FPL("..a"),      false },
    { FPL("../"),      true },
    { FPL("/.."),      true },
    { FPL("/../"),     true },
    { FPL("/a../"),    false },
    { FPL("/..a/"),    false },
    { FPL("//.."),     true },
    { FPL("..//"),     true },
    { FPL("//..//"),   true },
    { FPL("a//..//c"), true },
    { FPL("../b/c"),   true },
    { FPL("/../b/c"),  true },
    { FPL("a/b/.."),   true },
    { FPL("a/b/../"),  true },
    { FPL("a/../c"),   true },
    { FPL("a/b/c"),    false },
  };

  for (size_t i = 0; i < arraysize(cases); ++i) {
    FilePath input(cases[i].input);
    bool observed = input.ReferencesParent();
    EXPECT_EQ(cases[i].expected, observed) <<
              "i: " << i << ", input: " << input.value();
  }
}

