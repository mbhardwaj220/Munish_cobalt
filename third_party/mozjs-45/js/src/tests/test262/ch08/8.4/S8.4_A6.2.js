// Copyright 2009 the Sputnik authors.  All rights reserved.
// This code is governed by the BSD license found in the LICENSE file.

/**
 * Large string 8192 bytes
 *
 * @path ch08/8.4/S8.4_A6.2.js
 * @description Assign variable by large string
 */

////////////////////////////////////////////////////
// Check#2
var largeStr='Standard ECMA-2623r d Edition - December 1999S t a n d a r d i z i n g Informat i o n and Commu n i c a t i o n SystemsPhone: +41 22 849.60.00 - Fax: +41 22 849.60.01 - URL: ht tp: / /www.ecma.ch - Internet: helpdesk@ecma.chECMAScript LanguageSpecificationStandard ECMA-2623r d Edition - December 1999S t a n d a r d i z i n g Informat i o n and Commu n i c a t i o n SystemsPhone: +41 22 849.60.00 - Fax: +41 22 849.60.01 - URL: ht tp: / /www.ecma.ch - Internet: helpdesk@ecma.chMB Ecma-262.doc 08-04-02 16,53ECMAScript LanguageSpecificationBrief HistoryThis ECMA Standard is based on several originating technologies, the most well known being JavaScript (Netscape)and JScript (Microsoft). The language was invented by Brendan Eich at Netscape and first appeared in thatcompans Navigator 2.0 browser. It has appeared in all subsequent browsers from Netscape and in all browsers fromMicrosoft starting with Internet Explorer 3.0.The development of this Standard started in November 1996. The first edition of this ECMA Standard was adopted bythe ECMA General Assembly of June 1997.That ECMA Standard was submitted to ISO/IEC JTC 1 for adoption under the fast-track procedure, and approved asinternational standard ISO/IEC 16262, in April 1998. The ECMA General Assembly of June 1998 approved thesecond edition of ECMA-262 to keep it fully aligned with ISO/IEC 16262. Changes between the first and the secondedition are editorial in nature.The current document defines the third edition of the Standard and includes powerful regular expressions, betterstring handling, new control statements, try/catch exception handling, tighter definition of errors, formatting fornumeric output and minor changes in anticipation of forthcoming internationalisation facilities and future languagegrowth.Work on the language is not complete. The technical committee is working on significant enhancements, includingmechanisms for scripts to be created and used across the Internet, and tighter coordination with other standards bodiessuch as groups within the World Wide Web Consortium and the Wireless Application Protocol Forum.This Standard has been adopted as 3rd Edition of ECMA-262 by the ECMA General Assembly in December, 1999.- i -Table of contents1 Scope 12 Conformance 13 References 14 Overview 1 4.1 Web Scripting 2 4.2 Language Overview 2 4.2.1 Objects 3 4.3 Definitions 4 4.3.1 Type 4 4.3.2 Primitive Value 4 4.3.3 Object 4 4.3.4 Constructor 4 4.3.5 Prototype 4 4.3.6 Native Object 4 4.3.7 Built-in Object 4 4.3.8 Host Object 4 4.3.9 Undefined Value 4 4.3.10 Undefined Type 4 4.3.11 Null Value 4 4.3.12 Null Type 4 4.3.13 Boolean Value 4 4.3.14 Boolean Type 4 4.3.15 Boolean Object 5 4.3.16 String Value 5 4.3.17 String Type 5 4.3.18 String Object 5 4.3.19 Number Value 5 4.3.20 Number Type 5 4.3.21 Number Object 5 4.3.22 Infinity 5 4.3.23 NaN 5 5 Notational Conventions 6 5.1 Syntactic and Lexical Grammars 6 5.1.1 Context-Free Grammars 6 5.1.2 The Lexical and RegExp Grammars 6 5.1.3 The Numeric String Grammar 6 5.1.4 The Syntactic Grammar 6 5.1.5 Grammar Notation 7 5.2 Algorithm Conventions 9 6. Source Text 10 7 Lexical Conventions 11 7.1 Unicode Format-Control Characters 11 7.2 White Space 11 7.3 Line Terminators 12 7.4 Comments 12 - ii - 7.5 Tokens 13 7.5.1 Reserved Words 13 7.5.2 Keywords 13 7.5.3 Future Reserved Words 14 7.6 Identifiers 14 7.7 Punctuators 15 7.8 Literals 16 7.8.1 Null Literals 16 7.8.2 Boolean Literals 16 7.8.3 Numeric Literals 16 7.8.4 String Literals 18 7.8.5 Regular Expression Literals 20 7.9 Automatic Semicolon Insertion 21 7.9.1 Rules of Automatic Semicolon Insertion 21 7.9.2 Examples of Automatic Semicolon Insertion 22 8 Types 24 8.1 The Undefined Type 24 8.2 The Null Type 24 8.3 The Boolean Type 24 8.4 The String Type 24 8.5 The Number Type 24 8.6 The Object Type 25 8.6.1 Property Attributes 25 8.6.2 Internal Properties and Methods 26 8.7 The Reference Type 29 8.7.1 GetValue (V) 29 8.7.2 PutValue (V, W) 29 8.8 The List Type 30 8.9 The Completion Type 30 9 Type Conversion 30 9.1 ToPrimitive 30 9.2 ToBoolean 30 9.3 ToNumber 31 9.3.1 ToNumber Applied to the String Type 31 9.4 ToInteger 34 9.5 ToInt32: (Signed 32 Bit Integer) 34 9.6 ToUint32: (Unsigned 32 Bit Integer) 34 9.7 ToUint16: (Unsigned 16 Bit Integer) 35 9.8 ToString 35 9.8.1 ToString Applied to the Number Type 35 9.9 ToObject 36 10 Execution Contexts 37 10.1 Definitions 37 10.1.1 Function Objects 37 10.1.2 Types of Executable Code 37 10.1.3 Variable Instantiation 37 10.1.4 Scope Chain and Identifier Resolution 38 10.1.5 Global Object 38 10.1.6 Activation Object 38 - i i i - 10.1.7 This 39 10.1.8 Arguments Object 39 10.2 Entering An Execution Context 39 10.2.1 Global Code 39 10.2.2 Eval Code 39 10.2.3 Function Code 39 11 Expressions 40 11.1 Primary Expressions 40 11.1.1 The this Keyword 40 11.1.2 Identifier Reference 40 11.1.3 Literal Reference 40 11.1.4 Array Initialiser 40 11.1.5 Object Initialiser 41 11.1.6 The Grouping Operator 42 11.2 Left-Hand-Side Expressions 43 11.2.1 Property Accessors 43 11.2.2 The new Operator 44 11.2.3 Function Calls 44 11.2.4 Argument Lists 45 11.2.5 Function Expressions 45 11.3 Postfix Expressions 45 11.3.1 Postfix Increment Operator 45 11.3.2 Postfix Decrement Operator 45 11.4 Unary Operators 46 11.4.1 The delete Operator 46 11.4.2 The void Operator 46 11.4.3 The typeof Operator 46 11.4.4 Prefix Increment Operator 47 11.4.5 Prefix Decrement Operator 47 11.4.6 Unary + Operator 47 11.4.7 Unary - Operator 47 11.4.8 Bitwise NOT Operator ( ~) 48 11.4.9 Logical NOT Operator ( !) 48 11.5 Multiplicative Operators 48 11.5.1 Applying the * Operator 48 11.5.2 Applying the / Operator 49 11.5.3 Applying the % Operator 49 11.6 Additive Operators 50 11.6.1 The Addition operator ( +) 50 11.6.2 The Subtraction Operator ( -) 50 11.6.3 Applying the Additive Operators ( +,- ) to Numbers 51 11.7 Bitwise Shift Operators 51 11.7.1 The Left Shift Operator ( <<) 51 11.7.2 The Signed Right Shift Operator ( >>) 51 11.7.3 The Unsigned Right Shift Operator ( >>>) 52 11.4 Relational Operators 52 11.8.1 The Less-than Operator ( <) 53 11.8.2 The Greater-than Operator ( >) 53 11.8.3 The Less-than-or-equal Operator ( <=) 53 11.8.4 The Greater-than-or-equal Operator ( >=) 53 11.8.5 The Abstract Relational Comparison Algorithm 53 - iv - 11.8.6 The instanceof operator 54 11.8.7 The in operator 54 11.9 Equality Operators 54 11.9.1 The Equals Operator ( ==) 55 11.9.2 The Does-not-equals Operator ( !=) 55 11.9.3 The Abstract Equality Comparison Algorithm 55 11.9.4 The Strict Equals Operator ( ===) 56 11.9.5 The Strict Does-not-equal Operator ( !==) 56 11.9.6 The Strict Equality Comparison Algorithm 56 11.10 Binary Bitwise Operators 57 11.11 Binary Logical Operators 58 11.12 Conditional Operator ( ?: ) 58 11.13 Assignment Operators 59 11.13.1 Simple Assignment ( =) 59 11.13.2 Compound Assignment ( op=) 60 11.14 Comma Operator ( , ) 60 12 Statements 61 12.1 Block 61 12.2 Variable statement 62 12.3 Empty Statement 63 12.4 Expression Statement 63 12.5 The if Statement 63 12.6 Iteration Statements 64 12.6.1 The do-while Statement 64 12.6.2 The while statement 64 12.6.3 The for Statement 65 12.6.4 The for-in Statement 65 12.7 The continue Statement 66 12.8 The break Statement 67 12.9 The return Statement 67 12.10 The with Statement 67 12.11 The switch Statement 68 12.12 Labelled Statements 69 12.13 The throw statement 69 12.14 The try statement 70 13 Function Definition 71 13.1 Definitions 72 13.1.1 Equated Grammar Productions 72 13.1.2 Joined Objects 72 13.2 Creating Function Objects 72 13.2.1 [[Call]] 73 13.2.2 [[Construct]] 74 14 Program 75 15 Native ECMAScript Objects 76 15.1 The Global Object 76 15.1.1 Value Properties of the Global Object 77 15.1.2 Function Properties of the Global Object 77 15.1.3 URI Handling Function Properties 78 - v - 15.1.4 Constructor Properties of the Global Object 83 15.1.5 Other Properties of the Global Object 83 15.2 Object Objects 83 15.2.1 The Object Constructor Called as a Function 83 15.2.2 The Object Constructor 84 15.2.3 Properties of the Object Constructor 84 15.2.4 Properties of the Object Prototype Object 84 15.2.5 Properties of Object Instances 85 15.3 Function Objects 85 ';
if(largeStr !== 'Standard ECMA-2623r d Edition - December 1999S t a n d a r d i z i n g Informat i o n and Commu n i c a t i o n SystemsPhone: +41 22 849.60.00 - Fax: +41 22 849.60.01 - URL: ht tp: / /www.ecma.ch - Internet: helpdesk@ecma.chECMAScript LanguageSpecificationStandard ECMA-2623r d Edition - December 1999S t a n d a r d i z i n g Informat i o n and Commu n i c a t i o n SystemsPhone: +41 22 849.60.00 - Fax: +41 22 849.60.01 - URL: ht tp: / /www.ecma.ch - Internet: helpdesk@ecma.chMB Ecma-262.doc 08-04-02 16,53ECMAScript LanguageSpecificationBrief HistoryThis ECMA Standard is based on several originating technologies, the most well known being JavaScript (Netscape)and JScript (Microsoft). The language was invented by Brendan Eich at Netscape and first appeared in thatcompans Navigator 2.0 browser. It has appeared in all subsequent browsers from Netscape and in all browsers fromMicrosoft starting with Internet Explorer 3.0.The development of this Standard started in November 1996. The first edition of this ECMA Standard was adopted bythe ECMA General Assembly of June 1997.That ECMA Standard was submitted to ISO/IEC JTC 1 for adoption under the fast-track procedure, and approved asinternational standard ISO/IEC 16262, in April 1998. The ECMA General Assembly of June 1998 approved thesecond edition of ECMA-262 to keep it fully aligned with ISO/IEC 16262. Changes between the first and the secondedition are editorial in nature.The current document defines the third edition of the Standard and includes powerful regular expressions, betterstring handling, new control statements, try/catch exception handling, tighter definition of errors, formatting fornumeric output and minor changes in anticipation of forthcoming internationalisation facilities and future languagegrowth.Work on the language is not complete. The technical committee is working on significant enhancements, includingmechanisms for scripts to be created and used across the Internet, and tighter coordination with other standards bodiessuch as groups within the World Wide Web Consortium and the Wireless Application Protocol Forum.This Standard has been adopted as 3rd Edition of ECMA-262 by the ECMA General Assembly in December, 1999.- i -Table of contents1 Scope 12 Conformance 13 References 14 Overview 1 4.1 Web Scripting 2 4.2 Language Overview 2 4.2.1 Objects 3 4.3 Definitions 4 4.3.1 Type 4 4.3.2 Primitive Value 4 4.3.3 Object 4 4.3.4 Constructor 4 4.3.5 Prototype 4 4.3.6 Native Object 4 4.3.7 Built-in Object 4 4.3.8 Host Object 4 4.3.9 Undefined Value 4 4.3.10 Undefined Type 4 4.3.11 Null Value 4 4.3.12 Null Type 4 4.3.13 Boolean Value 4 4.3.14 Boolean Type 4 4.3.15 Boolean Object 5 4.3.16 String Value 5 4.3.17 String Type 5 4.3.18 String Object 5 4.3.19 Number Value 5 4.3.20 Number Type 5 4.3.21 Number Object 5 4.3.22 Infinity 5 4.3.23 NaN 5 5 Notational Conventions 6 5.1 Syntactic and Lexical Grammars 6 5.1.1 Context-Free Grammars 6 5.1.2 The Lexical and RegExp Grammars 6 5.1.3 The Numeric String Grammar 6 5.1.4 The Syntactic Grammar 6 5.1.5 Grammar Notation 7 5.2 Algorithm Conventions 9 6. Source Text 10 7 Lexical Conventions 11 7.1 Unicode Format-Control Characters 11 7.2 White Space 11 7.3 Line Terminators 12 7.4 Comments 12 - ii - 7.5 Tokens 13 7.5.1 Reserved Words 13 7.5.2 Keywords 13 7.5.3 Future Reserved Words 14 7.6 Identifiers 14 7.7 Punctuators 15 7.8 Literals 16 7.8.1 Null Literals 16 7.8.2 Boolean Literals 16 7.8.3 Numeric Literals 16 7.8.4 String Literals 18 7.8.5 Regular Expression Literals 20 7.9 Automatic Semicolon Insertion 21 7.9.1 Rules of Automatic Semicolon Insertion 21 7.9.2 Examples of Automatic Semicolon Insertion 22 8 Types 24 8.1 The Undefined Type 24 8.2 The Null Type 24 8.3 The Boolean Type 24 8.4 The String Type 24 8.5 The Number Type 24 8.6 The Object Type 25 8.6.1 Property Attributes 25 8.6.2 Internal Properties and Methods 26 8.7 The Reference Type 29 8.7.1 GetValue (V) 29 8.7.2 PutValue (V, W) 29 8.8 The List Type 30 8.9 The Completion Type 30 9 Type Conversion 30 9.1 ToPrimitive 30 9.2 ToBoolean 30 9.3 ToNumber 31 9.3.1 ToNumber Applied to the String Type 31 9.4 ToInteger 34 9.5 ToInt32: (Signed 32 Bit Integer) 34 9.6 ToUint32: (Unsigned 32 Bit Integer) 34 9.7 ToUint16: (Unsigned 16 Bit Integer) 35 9.8 ToString 35 9.8.1 ToString Applied to the Number Type 35 9.9 ToObject 36 10 Execution Contexts 37 10.1 Definitions 37 10.1.1 Function Objects 37 10.1.2 Types of Executable Code 37 10.1.3 Variable Instantiation 37 10.1.4 Scope Chain and Identifier Resolution 38 10.1.5 Global Object 38 10.1.6 Activation Object 38 - i i i - 10.1.7 This 39 10.1.8 Arguments Object 39 10.2 Entering An Execution Context 39 10.2.1 Global Code 39 10.2.2 Eval Code 39 10.2.3 Function Code 39 11 Expressions 40 11.1 Primary Expressions 40 11.1.1 The this Keyword 40 11.1.2 Identifier Reference 40 11.1.3 Literal Reference 40 11.1.4 Array Initialiser 40 11.1.5 Object Initialiser 41 11.1.6 The Grouping Operator 42 11.2 Left-Hand-Side Expressions 43 11.2.1 Property Accessors 43 11.2.2 The new Operator 44 11.2.3 Function Calls 44 11.2.4 Argument Lists 45 11.2.5 Function Expressions 45 11.3 Postfix Expressions 45 11.3.1 Postfix Increment Operator 45 11.3.2 Postfix Decrement Operator 45 11.4 Unary Operators 46 11.4.1 The delete Operator 46 11.4.2 The void Operator 46 11.4.3 The typeof Operator 46 11.4.4 Prefix Increment Operator 47 11.4.5 Prefix Decrement Operator 47 11.4.6 Unary + Operator 47 11.4.7 Unary - Operator 47 11.4.8 Bitwise NOT Operator ( ~) 48 11.4.9 Logical NOT Operator ( !) 48 11.5 Multiplicative Operators 48 11.5.1 Applying the * Operator 48 11.5.2 Applying the / Operator 49 11.5.3 Applying the % Operator 49 11.6 Additive Operators 50 11.6.1 The Addition operator ( +) 50 11.6.2 The Subtraction Operator ( -) 50 11.6.3 Applying the Additive Operators ( +,- ) to Numbers 51 11.7 Bitwise Shift Operators 51 11.7.1 The Left Shift Operator ( <<) 51 11.7.2 The Signed Right Shift Operator ( >>) 51 11.7.3 The Unsigned Right Shift Operator ( >>>) 52 11.4 Relational Operators 52 11.8.1 The Less-than Operator ( <) 53 11.8.2 The Greater-than Operator ( >) 53 11.8.3 The Less-than-or-equal Operator ( <=) 53 11.8.4 The Greater-than-or-equal Operator ( >=) 53 11.8.5 The Abstract Relational Comparison Algorithm 53 - iv - 11.8.6 The instanceof operator 54 11.8.7 The in operator 54 11.9 Equality Operators 54 11.9.1 The Equals Operator ( ==) 55 11.9.2 The Does-not-equals Operator ( !=) 55 11.9.3 The Abstract Equality Comparison Algorithm 55 11.9.4 The Strict Equals Operator ( ===) 56 11.9.5 The Strict Does-not-equal Operator ( !==) 56 11.9.6 The Strict Equality Comparison Algorithm 56 11.10 Binary Bitwise Operators 57 11.11 Binary Logical Operators 58 11.12 Conditional Operator ( ?: ) 58 11.13 Assignment Operators 59 11.13.1 Simple Assignment ( =) 59 11.13.2 Compound Assignment ( op=) 60 11.14 Comma Operator ( , ) 60 12 Statements 61 12.1 Block 61 12.2 Variable statement 62 12.3 Empty Statement 63 12.4 Expression Statement 63 12.5 The if Statement 63 12.6 Iteration Statements 64 12.6.1 The do-while Statement 64 12.6.2 The while statement 64 12.6.3 The for Statement 65 12.6.4 The for-in Statement 65 12.7 The continue Statement 66 12.8 The break Statement 67 12.9 The return Statement 67 12.10 The with Statement 67 12.11 The switch Statement 68 12.12 Labelled Statements 69 12.13 The throw statement 69 12.14 The try statement 70 13 Function Definition 71 13.1 Definitions 72 13.1.1 Equated Grammar Productions 72 13.1.2 Joined Objects 72 13.2 Creating Function Objects 72 13.2.1 [[Call]] 73 13.2.2 [[Construct]] 74 14 Program 75 15 Native ECMAScript Objects 76 15.1 The Global Object 76 15.1.1 Value Properties of the Global Object 77 15.1.2 Function Properties of the Global Object 77 15.1.3 URI Handling Function Properties 78 - v - 15.1.4 Constructor Properties of the Global Object 83 15.1.5 Other Properties of the Global Object 83 15.2 Object Objects 83 15.2.1 The Object Constructor Called as a Function 83 15.2.2 The Object Constructor 84 15.2.3 Properties of the Object Constructor 84 15.2.4 Properties of the Object Prototype Object 84 15.2.5 Properties of Object Instances 85 15.3 Function Objects 85 '){
  $ERROR('#2: Large string 8192 bytes');
}
//
////////////////////////////////////////////////////

