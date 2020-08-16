// Copyright 2020 The Cobalt Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// clang-format off

// This file has been auto-generated by bindings/code_generator_cobalt.py. DO NOT MODIFY!
// Auto-generated from template: bindings/mozjs45/templates/dictionary-conversion.cc.template

#include "mozjs_gen_type_conversion.h"

#include "cobalt/bindings/testing/derived_dictionary.h"

#include "cobalt/script/exception_state.h"
#include "third_party/mozjs-45/js/src/jsapi.h"
#include "cobalt/bindings/testing/test_dictionary.h"

using cobalt::bindings::testing::DerivedDictionary;
using cobalt::bindings::testing::TestDictionary;

namespace cobalt {
namespace script {
namespace mozjs {

void ToJSValue(
    JSContext* context,
    const DerivedDictionary& in_dictionary,
    JS::MutableHandleValue out_value) {
  // Create a new object that will hold the dictionary values.
  JS::RootedObject dictionary_object(
      context, JS_NewObject(context, nullptr));
  const int kPropertyAttributes = JSPROP_ENUMERATE;
  if (in_dictionary.has_additional_member()) {
    JS::RootedValue member_value(context);
    ToJSValue(context, in_dictionary.additional_member(), &member_value);
    if (!JS_DefineProperty(context, dictionary_object,
                           "additionalMember",
                           member_value, kPropertyAttributes, nullptr, nullptr)) {
      // Some internal error occurred.
      NOTREACHED();
      return;
    }
  }
  out_value.setObject(*dictionary_object);
}

void FromJSValue(JSContext* context, JS::HandleValue value,
                 int conversion_flags, ExceptionState* exception_state,
                 DerivedDictionary* out_dictionary) {
  DCHECK_EQ(0, conversion_flags) << "Unexpected conversion flags.";
  MozjsExceptionState* mozjs_exception_state = base::polymorphic_downcast<MozjsExceptionState*>(exception_state);
  DCHECK(!mozjs_exception_state->is_exception_set());

  FromJSValue(context, value, conversion_flags, exception_state,
      static_cast<cobalt::bindings::testing::TestDictionary*>(out_dictionary));
  if (mozjs_exception_state->is_exception_set()) {
    return;
  }
  // https://heycam.github.io/webidl/#es-dictionary

  if (value.isUndefined() || value.isNull()) {
    // The default constructor will assign appropriate values to dictionary
    // members with default values and leave the others unset.
    *out_dictionary = DerivedDictionary();
    return;
  }
  if (!value.isObject()) {
    // 1. If Type(V) is not Undefined, Null or Object, then throw a TypeError.
    exception_state->SetSimpleException(kNotObjectType);
    return;
  }
  JS::RootedObject dictionary_object(context, &value.toObject());
  JS::RootedValue additional_member(context);
  if (!JS_GetProperty(context, dictionary_object,
                      "additionalMember",
                      &additional_member)) {
    exception_state->SetSimpleException(kSimpleError);
    return;
  }
  if (!additional_member.isUndefined()) {
    bool converted_value;
    FromJSValue(context,
                additional_member,
                kNoConversionFlags,
                exception_state,
                &converted_value);
    if (context->isExceptionPending()) {
      return;
    }
    out_dictionary->set_additional_member(converted_value);
  }
}

}  // namespace mozjs
}  // namespace script
}  // namespace cobalt
