/* -*- indent-tabs-mode: nil; js-indent-level: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

//-----------------------------------------------------------------------------
var BUGNUMBER = 349851;
var summary = 'decompilation of yield \\n, 3';
var actual = '';
var expect = 'SyntaxError';


//-----------------------------------------------------------------------------
test();
//-----------------------------------------------------------------------------

function test()
{
  enterFunc ('test');
  printBugNumber(BUGNUMBER);
  printStatus (summary);
 
  // note the newline after yield is required for this test
  try
  {
    var f = eval('function(){ yield \n,3 }');
  }
  catch(ex)
  {
    actual = ex.name;
  }

  reportCompare(expect, actual, summary);

  exitFunc ('test');
}
