// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * Type(x) and Type(y) are Object-s.
 * Return true, if x and y are references to the same Object; otherwise, return false
 *
 * @path ch11/11.9/11.9.1/S11.9.1_A7.1.js
 * @description Checking Boolean object, Number object, String object, Object object
 */

//CHECK#1
if ((new Boolean(true) == new Boolean(true)) !== false) {
  $ERROR('#1: (new Boolean(true) == new Boolean(true)) === false');
}

//CHECK#2
if ((new Number(1) == new Number(1)) !== false) {
  $ERROR('#2: (new Number(1) == new Number(1)) === false');
}

//CHECK#3
if ((new String("x") == new String("x")) !== false) {
  $ERROR('#3: (new String("x") == new String("x")) === false');
}

//CHECK#4
if ((new Object() == new Object()) !== false) {
  $ERROR('#4: (new Object() == new Object()) === false');
}

//CHECK#5
x = {}; 
y = x;
if ((x == y) !== true) {
  $ERROR('#5: x = {}; y = x; (x == y) === true');
}

//CHECK#6
if ((new Boolean(true) == new Number(1)) !== false) {
  $ERROR('#6 (new Boolean(true) == new Number(1)) === false');
}

//CHECK#7
if ((new Number(1) == new String("1")) !== false) {
  $ERROR('#7: (new Number(1) == new String("1")) === false');
}

//CHECK#8
if ((new String("1") == new Boolean(true)) !== false) {
  $ERROR('#8: (new String("x") == new Boolean(true)) === false');
}

