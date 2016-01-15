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

#ifndef COBALT_DOM_FONT_LIST_H_
#define COBALT_DOM_FONT_LIST_H_

#include <map>
#include <string>
#include <vector>

#include "base/containers/small_map.h"
#include "base/hash_tables.h"
#include "base/memory/ref_counted.h"
#include "cobalt/math/rect_f.h"
#include "cobalt/render_tree/font.h"

namespace cobalt {
namespace dom {

class FontCache;

// A font run specifies a run of contiguous text that will be displayed in a
// single font. While the text itself is external to the font run, the font
// run contains a reference to its font along with the offset and length
// information needed to determine the specific text contained within the run.
struct FontRun {
  FontRun(size_t run_start_position, size_t run_length,
          const scoped_refptr<render_tree::Font>& run_font)
      : start_position(run_start_position),
        length(run_length),
        font(run_font) {}

  size_t start_position;
  size_t length;
  scoped_refptr<render_tree::Font> font;
};

typedef std::vector<FontRun> FontRunList;

// A specific font family within a font list. It has an internal state, which
// lets the font list know whether or not the font has already been requested,
// and if so, whether or not it was available. |font_| and |character_map_|
// will only be non-NULL in the case where |state_| is set to |kLoadedState|.
class FontListFont {
 public:
  typedef std::map<int32, render_tree::GlyphIndex> CharacterGlyphMap;

  enum State {
    kUnrequestedState,
    kLoadingWithTimerActiveState,
    kLoadingWithTimerExpiredState,
    kLoadedState,
    kUnavailableState,
    kDuplicateState,
  };

  explicit FontListFont(const std::string& family_name);

  const std::string& family_name() const { return family_name_; }

  State state() const { return state_; }
  void set_state(State state) { state_ = state; }

  const scoped_refptr<render_tree::Font>& font() const { return font_; }
  void set_font(const scoped_refptr<render_tree::Font> font) { font_ = font; }

  void set_character_glyph_map(CharacterGlyphMap* character_glyph_map) {
    character_glyph_map_ = character_glyph_map;
  }

  // Whether or not the font has the specified UTF-32 character. If the map does
  // not already contain the character, the underlying font is checked for
  // having the character and the map is updated with the return value, ensuring
  // that the underlying font will only ever need to be queried once for a
  // character.
  bool HasGlyphForCharacter(int32 utf32_character);

 private:
  std::string family_name_;
  State state_;

  // The render_tree::Font obtained via the font cache using |family_name_| in
  // font list font, along with |style_| and |size_| from the containing font
  // list. It is only non-NULL in the case where |state_| is set to
  // |kLoadedState|.
  scoped_refptr<render_tree::Font> font_;

  // A mapping of all characters for this font that have previously been
  // queried to whether or not the font supports the character. A single
  // character map is used to represent a typeface, and all fonts containing
  // the same underlying typeface will share the same character map, which
  // is owned by the font cache. A character not appearing in the map merely
  // means that it has not been queried yet, and not that the character is not
  // supported. It is only non-NULL in the case where |state_| is set to
  // |kLoadedState|.
  CharacterGlyphMap* character_glyph_map_;
};

// The key used for maps with a |FontList| value. It is also used for
// initializing the member variables of a |FontList| object.
struct FontListKey {
  FontListKey() : size(0) {}

  bool operator<(const FontListKey& rhs) const {
    if (size < rhs.size) {
      return true;
    } else if (rhs.size < size) {
      return false;
    } else if (style.weight < rhs.style.weight) {
      return true;
    } else if (rhs.style.weight < style.weight) {
      return false;
    } else if (style.slant < rhs.style.slant) {
      return true;
    } else if (rhs.style.slant < style.slant) {
      return false;
    } else {
      return family_names < rhs.family_names;
    }
  }

  std::vector<std::string> family_names;
  render_tree::FontStyle style;
  float size;
};

// |FontList| represents a unique font-style, font-weight, font-size, and
// font-family property combination within a document and is shared by all
// layout objects with matching font properties. It tracks a list of fonts,
// which it lazily requests from the font cache as required. It uses these to
// determine the font metrics for the font properties, as well as the specific
// fonts that should be used to render passed in text.
class FontList : public base::RefCounted<FontList> {
 public:
  typedef base::SmallMap<
      std::map<render_tree::TypefaceId, scoped_refptr<render_tree::Font> >, 4>
      FallbackTypefaceToFontMap;
  typedef std::vector<FontListFont> FontListFonts;

  FontList(FontCache* font_cache, const FontListKey& font_list_key);

  bool IsVisible() const;

  // Reset loading fonts sets all font list fonts with a state of
  // |kLoadingState| back to |kUnrequestedState|, which will cause them to be
  // re-requested then next time they are needed.
  // If a font is encountered with a state of |kLoadingState| prior to the
  // first loaded font, then the primary font and its associated values are
  // reset, as they may change if the loading font is now available.
  void ResetLoadingFonts();

  // Given a string of text, this determines the font to use for each character
  // in the string and populates a passed in font run list with the information.
  void GenerateFontRunList(const std::string& text, FontRunList* list);

  // Given a string of text, return its bounding rectangle.
  // This is accomplished by generating the font runs for the text and then
  // calculating the bounds by combining the rectangles of each of the runs.
  math::RectF GetBounds(const std::string& text);

  const render_tree::FontMetrics& GetFontMetrics();
  float GetSpaceWidth();

  // Returns the UTF-8 string that signifies an ellipsis code point.
  std::string GetEllipsisString() const;
  // Returns the first font in the font-list that supports the ellipsis code
  // point. In the case where the ellipsis font has not already been calculated,
  // it lazily generates it.
  const scoped_refptr<render_tree::Font>& GetEllipsisFont();
  // Returns the width of the ellipsis in the ellipsis font. In the case where
  // the width has not already been calculated, it lazily generates it.
  float GetEllipsisWidth();

  render_tree::FontStyle style() const { return style_; }
  float size() const { return size_; }

 private:
  // Request a font from the font cache and update its state depending on the
  // results of the request. If the font is successfully set, then both its
  // |font_| and |character_map_| are non-NULL after this call.
  void RequestFont(size_t index);

  // The primary font is the first successfully loaded font among the font list
  // fonts. A loading font will potentially later become the primary font if it
  // successfully loads, but until then, a subsequent font will be used as the
  // primary one.
  // |GetPrimaryFont()| causes |RequestFont()| to be called on each font with a
  // state of |kUnrequestedState| in the list, until a font is encountered with
  // a state of |kLoadedState|.
  const scoped_refptr<render_tree::Font>& GetPrimaryFont();

  // Returns the first font in the font list that supports the specified
  // UTF-32 character or a fallback font provided by the font cache if none of
  // them do.
  // |GetPrimaryFont()| causes |RequestFont()| to be called on each font with a
  // state of |kUnrequestedState| in the list, until a font is encountered with
  // that has the specified character or all fonts in the list have been
  // requested.
  const scoped_refptr<render_tree::Font>& GetCharacterFont(
      int32 utf32_character);

  // Lazily generates the ellipsis ellipsis font and ellipsis width. If the info
  // is already generated, it is immediately returned.
  void GenerateEllipsisInfo();

  // The font cache, which provides both font family fonts and character
  // fallback fonts to the font list.
  FontCache* const font_cache_;

  FontListFonts fonts_;
  render_tree::FontStyle style_;
  float size_;

  // The first loaded font in the font list. Lazily generated the first time it
  // is requested. Used with font metrics and for generating the size of the
  // space character.
  scoped_refptr<render_tree::Font> primary_font_;

  // Font metrics are lazily generated the first time they are requested.
  bool is_font_metrics_set_;
  render_tree::FontMetrics font_metrics_;

  // Space width is lazily generated the first time it is requested.
  bool is_space_width_set_;
  float space_width_;

  // The ellipsis info is lazily generated the first time it is requested.
  bool is_ellipsis_info_set_;
  scoped_refptr<render_tree::Font> ellipsis_font_;
  float ellipsis_width_;

  // This is a mapping of a unique typeface id to a specific font for use with
  // character fallback. This allows the font list to request the typeface id
  // that supports a character from the font cache, rather than the font itself,
  // allowing the font cache to avoid creating a font on each request.
  FallbackTypefaceToFontMap fallback_typeface_to_font_map_;
};

}  // namespace dom
}  // namespace cobalt

#endif  // COBALT_DOM_FONT_LIST_H_
