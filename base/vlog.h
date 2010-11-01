// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_VLOG_H_
#define BASE_VLOG_H_
#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/string_piece.h"

namespace logging {

// A helper class containing all the settings for vlogging.
class VlogInfo {
 public:
  // |v_switch| gives the default maximal active V-logging level; 0 is
  // the default.  Normally positive values are used for V-logging
  // levels.
  //
  // |vmodule_switch| gives the per-module maximal V-logging levels to
  // override the value given by |v_switch|.
  // E.g. "my_module=2,foo*=3" would change the logging level for all
  // code in source files "my_module.*" and "foo*.*" ("-inl" suffixes
  // are also disregarded for this matching).
  //
  // Any pattern containing a forward or backward slash will be tested
  // against the whole pathname and not just the module.  E.g.,
  // "*/foo/bar/*=2" would change the logging level for all code in
  // source files under a "foo/bar" directory.
  VlogInfo(const std::string& v_switch,
           const std::string& vmodule_switch);
  ~VlogInfo();

  // Returns the vlog level for a given file (usually taken from
  // __FILE__).
  int GetVlogLevel(const base::StringPiece& file);

  static const int kDefaultVlogLevel;

 private:
  // VmodulePattern holds all the information for each pattern parsed
  // from |vmodule_switch|.
  struct VmodulePattern {
    enum MatchTarget { MATCH_MODULE, MATCH_FILE };

    explicit VmodulePattern(const std::string& pattern);

    VmodulePattern();

    std::string pattern;
    int vlog_level;
    MatchTarget match_target;
  };

  int max_vlog_level_;
  std::vector<VmodulePattern> vmodule_levels_;

  DISALLOW_COPY_AND_ASSIGN(VlogInfo);
};

// Returns true if the string passed in matches the vlog pattern.  The
// vlog pattern string can contain wildcards like * and ?.  ? matches
// exactly one character while * matches 0 or more characters.  Also,
// as a special case, a / or \ character matches either / or \.
//
// Examples:
//   "kh?n" matches "khan" but not "khn" or "khaan"
//   "kh*n" matches "khn", "khan", or even "khaaaaan"
//   "/foo\bar" matches "/foo/bar", "\foo\bar", or "/foo\bar"
//     (disregarding C escaping rules)
bool MatchVlogPattern(const base::StringPiece& string,
                      const base::StringPiece& vlog_pattern);

}  // namespace logging

#endif  // BASE_VLOG_H_
