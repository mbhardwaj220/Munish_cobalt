// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_I18N_RTL_H_
#define BASE_I18N_RTL_H_
#pragma once

#include "base/string16.h"
#include "build/build_config.h"

class FilePath;

namespace base {
namespace i18n {

const char16 kRightToLeftMark = 0x200F;
const char16 kLeftToRightMark = 0x200E;
const char16 kLeftToRightEmbeddingMark = 0x202A;
const char16 kRightToLeftEmbeddingMark = 0x202B;
const char16 kPopDirectionalFormatting = 0x202C;
const char16 kLeftToRightOverride = 0x202D;
const char16 kRightToLeftOverride = 0x202E;

enum TextDirection {
  UNKNOWN_DIRECTION,
  RIGHT_TO_LEFT,
  LEFT_TO_RIGHT,
};

// Get language and region from the OS.
void GetLanguageAndRegionFromOS(std::string* lang, std::string* region);

// Sets the default locale of ICU.
// Once the application locale of Chrome in GetApplicationLocale is determined,
// the default locale of ICU need to be changed to match the application locale
// so that ICU functions work correctly in a locale-dependent manner.
// This is handy in that we don't have to call GetApplicationLocale()
// everytime we call locale-dependent ICU APIs as long as we make sure
// that this is called before any locale-dependent API is called.
void SetICUDefaultLocale(const std::string& locale_string);

// Returns true if the application text direction is right-to-left.
bool IsRTL();

// Returns whether the text direction for the default ICU locale is RTL.  This
// assumes that SetICUDefaultLocale has been called to set the default locale to
// the UI locale of Chrome.
// NOTE: Generally, you should call IsRTL() instead of this.
bool ICUIsRTL();

// Returns the text direction for |locale_name|.
TextDirection GetTextDirectionForLocale(const char* locale_name);

// Given the string in |text|, returns the directionality of the first
// character with strong directionality in the string. If no character in the
// text has strong directionality, LEFT_TO_RIGHT is returned. The Bidi
// character types L, LRE, LRO, R, AL, RLE, and RLO are considered as strong
// directionality characters. Please refer to http://unicode.org/reports/tr9/
// for more information.
TextDirection GetFirstStrongCharacterDirection(const string16& text);
#if defined(WCHAR_T_IS_UTF32)
TextDirection GetFirstStrongCharacterDirection(const std::wstring& text);
#endif

// Given the string in |text|, this function creates a copy of the string with
// the appropriate Unicode formatting marks that mark the string direction
// (either left-to-right or right-to-left). The new string is returned in
// |localized_text|. The function checks both the current locale and the
// contents of the string in order to determine the direction of the returned
// string. The function returns true if the string in |text| was properly
// adjusted.
//
// Certain LTR strings are not rendered correctly when the context is RTL. For
// example, the string "Foo!" will appear as "!Foo" if it is rendered as is in
// an RTL context. Calling this function will make sure the returned localized
// string is always treated as a right-to-left string. This is done by
// inserting certain Unicode formatting marks into the returned string.
//
// TODO(brettw) bug 47194: This funciton is confusing. If it does no adjustment
// becuase the current locale is not RTL, it will do nothing and return false.
// This means you have to check the return value in many cases which doesn't
// make sense. This should be cleaned up and probably just take a single
// argument that's a pointer to a string that it modifies as necessary. In the
// meantime, the recommended usage is to use the same arg as input & output,
// which will work without extra checks:
//   AdjustStringForLocaleDirection(text, &text);
//
// TODO(idana) bug# 1206120: this function adjusts the string in question only
// if the current locale is right-to-left. The function does not take care of
// the opposite case (an RTL string displayed in an LTR context) since
// adjusting the string involves inserting Unicode formatting characters that
// Windows does not handle well unless right-to-left language support is
// installed. Since the English version of Windows doesn't have right-to-left
// language support installed by default, inserting the direction Unicode mark
// results in Windows displaying squares.
bool AdjustStringForLocaleDirection(const string16& text,
                                    string16* localized_text);
#if defined(WCHAR_T_IS_UTF32)
bool AdjustStringForLocaleDirection(const std::wstring& text,
                                    std::wstring* localized_text);
#endif

// Returns true if the string contains at least one character with strong right
// to left directionality; that is, a character with either R or AL Unicode
// BiDi character type.
bool StringContainsStrongRTLChars(const string16& text);
#if defined(WCHAR_T_IS_UTF32)
bool StringContainsStrongRTLChars(const std::wstring& text);
#endif

// Wraps a string with an LRE-PDF pair which essentialy marks the string as a
// Left-To-Right string. Doing this is useful in order to make sure LTR
// strings are rendered properly in an RTL context.
void WrapStringWithLTRFormatting(string16* text);
#if defined(WCHAR_T_IS_UTF32)
void WrapStringWithLTRFormatting(std::wstring* text);
#endif

// Wraps a string with an RLE-PDF pair which essentialy marks the string as a
// Right-To-Left string. Doing this is useful in order to make sure RTL
// strings are rendered properly in an LTR context.
void WrapStringWithRTLFormatting(string16* text);
#if defined(WCHAR_T_IS_UTF32)
void WrapStringWithRTLFormatting(std::wstring* text);
#endif

// Wraps file path to get it to display correctly in RTL UI. All filepaths
// should be passed through this function before display in UI for RTL locales.
void WrapPathWithLTRFormatting(const FilePath& path,
                               string16* rtl_safe_path);

// Given the string in |text|, this function returns the adjusted string having
// LTR directionality for display purpose. Which means that in RTL locale the
// string is wrapped with LRE (Left-To-Right Embedding) and PDF (Pop
// Directional Formatting) marks and returned. In LTR locale, the string itself
// is returned.
std::wstring GetDisplayStringInLTRDirectionality(std::wstring* text);

// Strip the beginning (U+202A..U+202B, U+202D..U+202E) and/or ending (U+202C)
// explicit bidi control characters from |text|, if there are any. Otherwise,
// return the text itself. Explicit bidi control characters display and have
// semantic effect. They can be deleted so they might not always appear in a
// pair.
const string16 StripWrappingBidiControlCharacters(const string16& text);

}  // namespace i18n
}  // namespace base

#endif  // BASE_I18N_RTL_H_
