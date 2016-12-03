/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sts=4 et sw=4 tw=99:
 *
 * Copyright 2015 Mozilla Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef asmjs_wasm_stubs_h
#define asmjs_wasm_stubs_h

#include "asmjs/Wasm.h"

namespace js {

class AsmJSModule;
namespace jit { class MacroAssembler; }

namespace wasm {

typedef Vector<uint32_t> FuncOffsetVector;

bool
GenerateStubs(jit::MacroAssembler& masm, AsmJSModule& module, const FuncOffsetVector& funcOffsets);

} // namespace wasm
} // namespace js
#endif // asmjs_wasm_stubs_h
