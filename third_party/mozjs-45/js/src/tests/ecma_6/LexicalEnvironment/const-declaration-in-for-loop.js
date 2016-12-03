/*
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/licenses/publicdomain/
 */

var gTestfile = "const-declaration-in-for-loop.js";
//-----------------------------------------------------------------------------
var BUGNUMBER = 1146644;
var summary =
  "Don't crash compiling a non-body-level for-loop whose loop declaration is " +
  "a const";

print(BUGNUMBER + ": " + summary);

/**************
 * BEGIN TEST *
 **************/

// Don't attempt execution as a script if we can't properly emulate it.  We
// could perhaps use eval, but eval, while also doing global execution, is its
// own can of messiness.  Ongoing work on for-loop scoping for lexical
// declarations will likely make these tests redundant with other tests to be
// added, anyway, in the very short term.
var executeGlobalScript = typeof evaluate === "function"
                        ? evaluate
                        : function(s) {};

for (const a1 = 3; false; )
  continue;

Function(`for (const a2 = 3; false; )
            continue;
         `)();

if (true)
{
  for (const a3 = 3; false; )
    continue;
}

Function(`if (true)
          {
            for (const a4 = 3; false; )
              continue;
          }`)();

// We don't support for (const ... in ...) or for (const ... of ...) yet.  When
// we do, these all should start passing without throwing a syntax error, and
// we can remove the try/catch here, and the ultimate throw-canary forcing this
// test to be updated.
try
{

executeGlobalScript(`for (const a5 of [])
                       continue;`);

Function(`for (const a6 of [])
            continue;`)();

executeGlobalScript(`if (true)
                     {
                       for (const a7 of [])
                         continue;
                     }`);

Function(`if (true)
          {
            for (const a8 of [])
              continue;
          }`)();

executeGlobalScript(`for (const a9 in {})
                       continue;`);

Function(`for (const a10 in {})
            continue;`)();

executeGlobalScript(`if (true)
                     {
                       for (const a11 in {})
                         continue;
                     }`);

Function(`if (true)
          {
            for (const a12 in {})
              continue;
          }`)();

throw new Error("Congratulations on making for (const … in/of …) work!  " +
                "Please remove the try/catch and this throw.");
}
catch (e)
{
  assertEq(e instanceof SyntaxError, true,
           "unexpected error: expected SyntaxError, got " + e);
}

/******************************************************************************/

if (typeof reportCompare === "function")
  reportCompare(true, true);

print("Tests complete");
