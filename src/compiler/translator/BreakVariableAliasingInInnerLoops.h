//
// Copyright (c) 2016 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// BreakVariableAliasingInInnerLoops.h: To optimize simple assignments, the HLSL compiler frontend
//      may record a variable as aliasing another. Sometimes the alias information gets garbled
//      so we work around this issue by breaking the aliasing chain in inner loops.

#ifndef COMPILER_TRANSLATOR_BREAKVARIABLEALIASINGININNERLOOPS_H_
#define COMPILER_TRANSLATOR_BREAKVARIABLEALIASINGININNERLOOPS_H_

class TIntermNode;

namespace sh
{

void BreakVariableAliasingInInnerLoops(TIntermNode *root);

}  // namespace sh

#endif  // COMPILER_TRANSLATOR_BREAKVARIABLEALIASINGININNERLOOPS_H_
