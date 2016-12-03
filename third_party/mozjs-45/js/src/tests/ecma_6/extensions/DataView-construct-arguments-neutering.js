// |reftest| skip-if(!xulRuntime.shell) -- needs neuter()
/*
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/licenses/publicdomain/
 */

var gTestfile = "DataView-construct-arguments-neutering.js";
//-----------------------------------------------------------------------------
var BUGNUMBER = 991981;
var summary =
  "new DataView(...) shouldn't misbehave horribly if index-argument " +
  "conversion neuters the ArrayBuffer to be viewed";

print(BUGNUMBER + ": " + summary);

/**************
 * BEGIN TEST *
 **************/

function testByteOffset(dataType)
{
  var ab = new ArrayBuffer(0x1000);

  var start =
    {
      valueOf: function()
      {
        neuter(ab, dataType);
        gc();
        return 0x800;
      }
    };

  var ok = false;
  try
  {
    new DataView(ab, start);
  }
  catch (e)
  {
    ok = true;
  }
  assertEq(ok, true, "byteOffset weirdness should have thrown");
  assertEq(ab.byteLength, 0, "neutering should work for byteOffset weirdness");
}
testByteOffset("change-data");
testByteOffset("same-data");

function testByteLength(dataType)
{
  var ab = new ArrayBuffer(0x1000);

  var len =
    {
      valueOf: function()
      {
        neuter(ab, dataType);
        gc();
        return 0x800;
      }
    };

  var ok = false;
  try
  {
    new DataView(ab, 0x800, len);
  }
  catch (e)
  {
    ok = true;
  }
  assertEq(ok, true, "byteLength weirdness should have thrown");
  assertEq(ab.byteLength, 0, "neutering should work for byteLength weirdness");
}
testByteLength("change-data");
testByteLength("same-data");

/******************************************************************************/

if (typeof reportCompare === "function")
  reportCompare(true, true);

print("Tests complete");
