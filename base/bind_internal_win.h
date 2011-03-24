// This file was GENERATED by command:
//     pump.py bind_internal_win.h.pump
// DO NOT EDIT BY HAND!!!



// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Specializations of FunctionTraits<> for Windows specific calling
// conventions.  Please see base/bind_internal.h for more info.

#ifndef BASE_BIND_INTERNAL_WIN_H_
#define BASE_BIND_INTERNAL_WIN_H_
#pragma once

namespace base {
namespace internal {

template <typename Sig>
struct FunctionTraits;

// __stdcall Function: Arity 0.
template <typename R>
struct FunctionTraits<R(__stdcall *)()> {
  typedef R (*NormalizedSig)();
  typedef false_type IsMethod;
};

// __fastcall Function: Arity 0.
template <typename R>
struct FunctionTraits<R(__fastcall *)()> {
  typedef R (*NormalizedSig)();
  typedef false_type IsMethod;
};

// __stdcall Function: Arity 1.
template <typename R, typename X1>
struct FunctionTraits<R(__stdcall *)(X1)> {
  typedef R (*NormalizedSig)(X1);
  typedef false_type IsMethod;
  // Target type for each bound parameter.
  typedef X1 B1;
};

// __fastcall Function: Arity 1.
template <typename R, typename X1>
struct FunctionTraits<R(__fastcall *)(X1)> {
  typedef R (*NormalizedSig)(X1);
  typedef false_type IsMethod;
  // Target type for each bound parameter.
  typedef X1 B1;
};

// __stdcall Function: Arity 2.
template <typename R, typename X1, typename X2>
struct FunctionTraits<R(__stdcall *)(X1, X2)> {
  typedef R (*NormalizedSig)(X1, X2);
  typedef false_type IsMethod;
  // Target type for each bound parameter.
  typedef X1 B1;
  typedef X2 B2;
};

// __fastcall Function: Arity 2.
template <typename R, typename X1, typename X2>
struct FunctionTraits<R(__fastcall *)(X1, X2)> {
  typedef R (*NormalizedSig)(X1, X2);
  typedef false_type IsMethod;
  // Target type for each bound parameter.
  typedef X1 B1;
  typedef X2 B2;
};

// __stdcall Function: Arity 3.
template <typename R, typename X1, typename X2, typename X3>
struct FunctionTraits<R(__stdcall *)(X1, X2, X3)> {
  typedef R (*NormalizedSig)(X1, X2, X3);
  typedef false_type IsMethod;
  // Target type for each bound parameter.
  typedef X1 B1;
  typedef X2 B2;
  typedef X3 B3;
};

// __fastcall Function: Arity 3.
template <typename R, typename X1, typename X2, typename X3>
struct FunctionTraits<R(__fastcall *)(X1, X2, X3)> {
  typedef R (*NormalizedSig)(X1, X2, X3);
  typedef false_type IsMethod;
  // Target type for each bound parameter.
  typedef X1 B1;
  typedef X2 B2;
  typedef X3 B3;
};

// __stdcall Function: Arity 4.
template <typename R, typename X1, typename X2, typename X3, typename X4>
struct FunctionTraits<R(__stdcall *)(X1, X2, X3, X4)> {
  typedef R (*NormalizedSig)(X1, X2, X3, X4);
  typedef false_type IsMethod;
  // Target type for each bound parameter.
  typedef X1 B1;
  typedef X2 B2;
  typedef X3 B3;
  typedef X4 B4;
};

// __fastcall Function: Arity 4.
template <typename R, typename X1, typename X2, typename X3, typename X4>
struct FunctionTraits<R(__fastcall *)(X1, X2, X3, X4)> {
  typedef R (*NormalizedSig)(X1, X2, X3, X4);
  typedef false_type IsMethod;
  // Target type for each bound parameter.
  typedef X1 B1;
  typedef X2 B2;
  typedef X3 B3;
  typedef X4 B4;
};

// __stdcall Function: Arity 5.
template <typename R, typename X1, typename X2, typename X3, typename X4,
    typename X5>
struct FunctionTraits<R(__stdcall *)(X1, X2, X3, X4, X5)> {
  typedef R (*NormalizedSig)(X1, X2, X3, X4, X5);
  typedef false_type IsMethod;
  // Target type for each bound parameter.
  typedef X1 B1;
  typedef X2 B2;
  typedef X3 B3;
  typedef X4 B4;
  typedef X5 B5;
};

// __fastcall Function: Arity 5.
template <typename R, typename X1, typename X2, typename X3, typename X4,
    typename X5>
struct FunctionTraits<R(__fastcall *)(X1, X2, X3, X4, X5)> {
  typedef R (*NormalizedSig)(X1, X2, X3, X4, X5);
  typedef false_type IsMethod;
  // Target type for each bound parameter.
  typedef X1 B1;
  typedef X2 B2;
  typedef X3 B3;
  typedef X4 B4;
  typedef X5 B5;
};

// __stdcall Function: Arity 6.
template <typename R, typename X1, typename X2, typename X3, typename X4,
    typename X5, typename X6>
struct FunctionTraits<R(__stdcall *)(X1, X2, X3, X4, X5, X6)> {
  typedef R (*NormalizedSig)(X1, X2, X3, X4, X5, X6);
  typedef false_type IsMethod;
  // Target type for each bound parameter.
  typedef X1 B1;
  typedef X2 B2;
  typedef X3 B3;
  typedef X4 B4;
  typedef X5 B5;
  typedef X6 B6;
};

// __fastcall Function: Arity 6.
template <typename R, typename X1, typename X2, typename X3, typename X4,
    typename X5, typename X6>
struct FunctionTraits<R(__fastcall *)(X1, X2, X3, X4, X5, X6)> {
  typedef R (*NormalizedSig)(X1, X2, X3, X4, X5, X6);
  typedef false_type IsMethod;
  // Target type for each bound parameter.
  typedef X1 B1;
  typedef X2 B2;
  typedef X3 B3;
  typedef X4 B4;
  typedef X5 B5;
  typedef X6 B6;
};

}  // namespace internal
}  // namespace base

#endif  // BASE_BIND_INTERNAL_WIN_H_
