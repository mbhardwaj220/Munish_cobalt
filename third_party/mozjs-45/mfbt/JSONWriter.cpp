/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "mozilla/JSONWriter.h"

namespace mozilla {
namespace detail {

// The chars with non-'___' entries in this table are those that can be
// represented with a two-char escape sequence. The value is the second char in
// the sequence, that which follows the initial backslash.
#define ___ 0
const char gTwoCharEscapes[256] = {
/*          0    1    2    3    4    5    6    7    8    9 */
/*   0+ */ ___, ___, ___, ___, ___, ___, ___, ___, 'b', 't',
/*  10+ */ 'n', ___, 'f', 'r', ___, ___, ___, ___, ___, ___,
/*  20+ */ ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
/*  30+ */ ___, ___, ___, ___, '"', ___, ___, ___, ___, ___,
/*  40+ */ ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
/*  50+ */ ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
/*  60+ */ ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
/*  70+ */ ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
/*  80+ */ ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
/*  90+ */ ___, ___,'\\', ___, ___, ___, ___, ___, ___, ___,
/* 100+ */ ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
/* 110+ */ ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
/* 120+ */ ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
/* 130+ */ ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
/* 140+ */ ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
/* 150+ */ ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
/* 160+ */ ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
/* 170+ */ ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
/* 180+ */ ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
/* 190+ */ ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
/* 200+ */ ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
/* 210+ */ ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
/* 220+ */ ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
/* 230+ */ ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
/* 240+ */ ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
/* 250+ */ ___, ___, ___, ___, ___, ___
};
#undef ___

} // namespace detail
} // namespace mozilla

