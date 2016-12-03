/* -*- tab-width: 2; indent-tabs-mode: nil; js-indent-level: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


/**
   File Name:          11.7.2.js
   ECMA Section:       11.7.2  The signed right shift operator ( >> )
   Description:
   Performs a sign-filling bitwise right shift operation on the left argument
   by the amount specified by the right argument.

   The production ShiftExpression : ShiftExpression >> AdditiveExpression is
   evaluated as follows:

   1.  Evaluate ShiftExpression.
   2.  Call GetValue(Result(1)).
   3.  Evaluate AdditiveExpression.
   4.  Call GetValue(Result(3)).
   5.  Call ToInt32(Result(2)).
   6.  Call ToUint32(Result(4)).
   7.  Mask out all but the least significant 5 bits of Result(6), that is,
   compute Result(6) & 0x1F.
   8.  Perform sign-extending right shift of Result(5) by Result(7) bits. The
   most significant bit is propagated. The result is a signed 32 bit
   integer.
   9.  Return Result(8).

   Author:             christine@netscape.com
   Date:               12 november 1997
*/
var SECTION = "11.7.2";
var VERSION = "ECMA_1";
startTest();

writeHeaderToLog( SECTION + "  The signed right shift operator ( >> )");

var power = 0;
var addexp = 0;

for ( power = 0; power <= 32; power++ ) {
  shiftexp = Math.pow( 2, power );

  for ( addexp = 0; addexp <= 32; addexp++ ) {
    new TestCase( SECTION,
		  shiftexp + " >> " + addexp,
		  SignedRightShift( shiftexp, addexp ),
		  shiftexp >> addexp );
  }
}

for ( power = 0; power <= 32; power++ ) {
  shiftexp = -Math.pow( 2, power );

  for ( addexp = 0; addexp <= 32; addexp++ ) {
    new TestCase( SECTION,
		  shiftexp + " >> " + addexp,
		  SignedRightShift( shiftexp, addexp ),
		  shiftexp >> addexp );
  }
}

test();

function ToInteger( n ) {
  n = Number( n );
  var sign = ( n < 0 ) ? -1 : 1;

  if ( n != n ) {
    return 0;
  }
  if ( Math.abs( n ) == 0 || Math.abs( n ) == Number.POSITIVE_INFINITY ) {
    return n;
  }
  return ( sign * Math.floor(Math.abs(n)) );
}
function ToInt32( n ) {
  n = Number( n );
  var sign = ( n < 0 ) ? -1 : 1;

  if ( Math.abs( n ) == 0 || Math.abs( n ) == Number.POSITIVE_INFINITY) {
    return 0;
  }

  n = (sign * Math.floor( Math.abs(n) )) % Math.pow(2,32);
  n = ( n >= Math.pow(2,31) ) ? n - Math.pow(2,32) : n;

  return ( n );
}
function ToUint32( n ) {
  n = Number( n );
  var sign = ( n < 0 ) ? -1 : 1;

  if ( Math.abs( n ) == 0 || Math.abs( n ) == Number.POSITIVE_INFINITY) {
    return 0;
  }
  n = sign * Math.floor( Math.abs(n) )

    n = n % Math.pow(2,32);

  if ( n < 0 ){
    n += Math.pow(2,32);
  }

  return ( n );
}
function ToUint16( n ) {
  var sign = ( n < 0 ) ? -1 : 1;

  if ( Math.abs( n ) == 0 || Math.abs( n ) == Number.POSITIVE_INFINITY) {
    return 0;
  }

  n = ( sign * Math.floor( Math.abs(n) ) ) % Math.pow(2,16);

  if (n <0) {
    n += Math.pow(2,16);
  }

  return ( n );
}
function Mask( b, n ) {
  b = ToUint32BitString( b );
  b = b.substring( b.length - n );
  b = ToUint32Decimal( b );
  return ( b );
}
function ToUint32BitString( n ) {
  var b = "";
  for ( p = 31; p >=0; p-- ) {
    if ( n >= Math.pow(2,p) ) {
      b += "1";
      n -= Math.pow(2,p);
    } else {
      b += "0";
    }
  }
  return b;
}
function ToInt32BitString( n ) {
  var b = "";
  var sign = ( n < 0 ) ? -1 : 1;

  b += ( sign == 1 ) ? "0" : "1";

  for ( p = 30; p >=0; p-- ) {
    if ( (sign == 1 ) ? sign * n >= Math.pow(2,p) : sign * n > Math.pow(2,p) ) {
      b += ( sign == 1 ) ? "1" : "0";
      n -= sign * Math.pow( 2, p );
    } else {
      b += ( sign == 1 ) ? "0" : "1";
    }
  }

  return b;
}
function ToInt32Decimal( bin ) {
  var r = 0;
  var sign;

  if ( Number(bin.charAt(0)) == 0 ) {
    sign = 1;
    r = 0;
  } else {
    sign = -1;
    r = -(Math.pow(2,31));
  }

  for ( var j = 0; j < 31; j++ ) {
    r += Math.pow( 2, j ) * Number(bin.charAt(31-j));
  }

  return r;
}
function ToUint32Decimal( bin ) {
  var r = 0;

  for ( l = bin.length; l < 32; l++ ) {
    bin = "0" + bin;
  }

  for ( j = 0; j < 31; j++ ) {
    r += Math.pow( 2, j ) * Number(bin.charAt(31-j));
  }

  return r;
}
function SignedRightShift( s, a ) {
  s = ToInt32( s );
  a = ToUint32( a );
  a = Mask( a, 5 );
  return ( SignedRShift( s, a ) );
}
function SignedRShift( s, a ) {
  s = ToInt32BitString( s );

  var firstbit = s.substring(0,1);

  s = s.substring( 1, s.length );

  for ( var z = 0; z < a; z++ ) {
    s = firstbit + s;
  }

  s = s.substring( 0, s.length - a);

  s = firstbit +s;


  return ToInt32(ToInt32Decimal(s));
}
