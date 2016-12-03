/* -*- indent-tabs-mode: nil; js-indent-level: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

//-----------------------------------------------------------------------------
var BUGNUMBER = 341499;
var summary = 'Iterators: do not assert from close handler when ' +
  'allocating GC things';
var actual = 'No Crash';
var expect = 'No Crash';

printBugNumber(BUGNUMBER);
printStatus (summary);

var someGlobal;

function generator()
{
  try {
    yield 0;
  } finally {
    someGlobal = [];
  }
}

var iter = generator();
iter.next();
iter = null;

gc();

reportCompare(expect, actual, summary);
