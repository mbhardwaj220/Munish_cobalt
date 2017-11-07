
/*
 * Copyright 2017 Google Inc. All Rights Reserved.
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

// clang-format off

// This file has been auto-generated by bindings/code_generator_cobalt.py. DO NOT MODIFY!
// Auto-generated from template: bindings/v8c/templates/enumeration-conversion.cc.template

#include "cobalt/bindings/testing/test_enum.h"

#include "v8c_gen_type_conversion.h"
#include "base/logging.h"
#include "cobalt/script/exception_state.h"
#include "v8/include/v8.h"

using cobalt::bindings::testing::TestEnum;

namespace cobalt {
namespace script {
namespace v8c {

void ToJSValue(
    v8::Isolate* isolate,
    TestEnum in_enum,
    v8::Local<v8::Value>* out_value) {
  switch (in_enum) {
    case cobalt::bindings::testing::kTestEnumAlpha:
      ToJSValue(isolate, std::string("alpha"), out_value);
      return;
    case cobalt::bindings::testing::kTestEnumBeta:
      ToJSValue(isolate, std::string("beta"), out_value);
      return;
    case cobalt::bindings::testing::kTestEnumGamma:
      ToJSValue(isolate, std::string("gamma"), out_value);
      return;
    case cobalt::bindings::testing::kTestEnumEnumWithDashes:
      ToJSValue(isolate, std::string("enum-with-dashes"), out_value);
      return;
    case cobalt::bindings::testing::kTestEnumEnumWithSpaces:
      ToJSValue(isolate, std::string("enum with spaces"), out_value);
      return;
    case cobalt::bindings::testing::kTestEnumTerribleEnum:
      ToJSValue(isolate, std::string("terrible----enum"), out_value);
      return;
    case cobalt::bindings::testing::kTestEnumThisIsATerribleEnum:
      ToJSValue(isolate, std::string("this is a terrible @#$%#$% enum"), out_value);
      return;
    default:
      NOTREACHED();
      *out_value = v8::Null(isolate);
  }
}

void FromJSValue(v8::Isolate* isolate, v8::Local<v8::Value> value,
                 int conversion_flags, ExceptionState* exception_state,
                 TestEnum* out_enum) {
  DCHECK_EQ(0, conversion_flags) << "Unexpected conversion flags.";
  // JSValue -> IDL enum algorithm described here:
  // http://heycam.github.io/webidl/#es-enumeration
  // 1. Let S be the result of calling ToString(V).
  v8::MaybeLocal<v8::String> maybe_string = value->ToString(isolate->GetCurrentContext());
  v8::Local<v8::String> string;
  if (!maybe_string.ToLocal(&string)) {
    exception_state->SetSimpleException(cobalt::script::kConvertToEnumFailed);
    return;
  }

  bool match = false;
// 3. Return the enumeration value of type E that is equal to S.
 if (
      v8::String::NewFromUtf8(isolate, "alpha", v8::NewStringType::kInternalized).ToLocalChecked()->Equals(value))
  {
    *out_enum = cobalt::bindings::testing::kTestEnumAlpha;
  }
 else  if (
      v8::String::NewFromUtf8(isolate, "beta", v8::NewStringType::kInternalized).ToLocalChecked()->Equals(value))
  {
    *out_enum = cobalt::bindings::testing::kTestEnumBeta;
  }
 else  if (
      v8::String::NewFromUtf8(isolate, "gamma", v8::NewStringType::kInternalized).ToLocalChecked()->Equals(value))
  {
    *out_enum = cobalt::bindings::testing::kTestEnumGamma;
  }
 else  if (
      v8::String::NewFromUtf8(isolate, "enum-with-dashes", v8::NewStringType::kInternalized).ToLocalChecked()->Equals(value))
  {
    *out_enum = cobalt::bindings::testing::kTestEnumEnumWithDashes;
  }
 else  if (
      v8::String::NewFromUtf8(isolate, "enum with spaces", v8::NewStringType::kInternalized).ToLocalChecked()->Equals(value))
  {
    *out_enum = cobalt::bindings::testing::kTestEnumEnumWithSpaces;
  }
 else  if (
      v8::String::NewFromUtf8(isolate, "terrible----enum", v8::NewStringType::kInternalized).ToLocalChecked()->Equals(value))
  {
    *out_enum = cobalt::bindings::testing::kTestEnumTerribleEnum;
  }
 else  if (
      v8::String::NewFromUtf8(isolate, "this is a terrible @#$%#$% enum", v8::NewStringType::kInternalized).ToLocalChecked()->Equals(value))
  {
    *out_enum = cobalt::bindings::testing::kTestEnumThisIsATerribleEnum;
  }
  else {
    // 2. If S is not one of E's enumeration values, then throw a TypeError.
    exception_state->SetSimpleException(cobalt::script::kConvertToEnumFailed);
    return;
  }
}

}  // namespace v8c
}  // namespace script
}  // namespace cobalt
