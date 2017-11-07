// This file was GENERATED by command:
//     pump.py v8c_callback_function.h.pump
// DO NOT EDIT BY HAND!!!


// Copyright 2017 Google Inc. All Rights Reserved.
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

#ifndef COBALT_SCRIPT_V8C_V8C_CALLBACK_FUNCTION_H_
#define COBALT_SCRIPT_V8C_V8C_CALLBACK_FUNCTION_H_

#include "base/logging.h"
#include "cobalt/script/callback_function.h"
#include "cobalt/script/v8c/conversion_helpers.h"
#include "cobalt/script/v8c/entry_scope.h"
#include "cobalt/script/v8c/scoped_persistent.h"
#include "nb/memory_scope.h"
#include "v8/include/v8.h"

namespace cobalt {
namespace script {
namespace v8c {

// Helper template functions for Callback functions' return values before being
// returned to Cobalt.
// Converts the return value from JavaScript into the correct Cobalt type, or
// sets the exception bit if conversion fails.
template <typename R>
CallbackResult<R> ConvertCallbackReturnValue(v8::Isolate* isolate,
                                             v8::Local<v8::Value> value) {
  // TODO: Pass conversion flags to callback function return value if
  // appropriate.
  const int kConversionFlags = 0;
  CallbackResult<R> callback_result;
  LoggingExceptionState exception_state;
  FromJSValue(isolate, value, kConversionFlags, &exception_state,
              &callback_result.result);
  callback_result.exception = exception_state.is_exception_set();
  return callback_result;
}

template <>
inline CallbackResult<void> ConvertCallbackReturnValue(v8::Isolate* isolate,
                                                       v8::Local<v8::Value>
                                                           value) {
  // No conversion necessary.
  return CallbackResult<void>();
}

// First, we forward declare the Callback class template. This informs the
// compiler that the template only has 1 type parameter which is the base
// CallbackFunction template class with parameters.
//
// See base/callback.h.pump for further discussion on this pattern.
template <typename Sig>
class V8cCallbackFunction;
template <typename R>
class V8cCallbackFunction<R(void)>
    : public ScopedPersistent<v8::Value>,
      public CallbackFunction<R(void)> {
 public:
  typedef CallbackFunction<R()> BaseType;

  V8cCallbackFunction() {}
  V8cCallbackFunction(v8::Isolate* isolate, v8::Local<v8::Value> handle)
      : ScopedPersistent(isolate, handle), isolate_(isolate) {}

  CallbackResult<R> Run()
      const override {
    CallbackResult<R> callback_result;
    DCHECK(!this->IsEmpty());
    if (this->IsEmpty()) {
      DLOG(WARNING) << "Function was garbage collected.";
      callback_result.exception = true;
      return callback_result;
    }

    EntryScope entry_scope(isolate_);
    v8::Local<v8::Context> context = isolate_->GetCurrentContext();

    // https://www.w3.org/TR/WebIDL/#es-invoking-callback-functions
    // Callback 'this' is set to null, unless overridden by other specifications
    v8::Local<v8::Value> this_value = v8::Null(isolate_);
    v8::Local<v8::Value> function = this->NewLocal(isolate_);
    v8::MaybeLocal<v8::Object> maybe_function_as_object =
        function->ToObject(context);
    v8::Local<v8::Object> function_as_object;
    if (!maybe_function_as_object.ToLocal(&function_as_object)) {
      DLOG(WARNING) << "Unexpected failure converting function to object.";
      callback_result.exception = true;
      return callback_result;
    }

    const int argc = 0;
    v8::Local<v8::Value>* argv = nullptr;
    v8::MaybeLocal<v8::Value> maybe_return_value =
        function_as_object->CallAsFunction(context, this_value, argc, argv);
    v8::Local<v8::Value> return_value;
    if (!maybe_return_value.ToLocal(&return_value)) {
      NOTIMPLEMENTED();
      callback_result.exception = true;
    } else {
      callback_result = ConvertCallbackReturnValue<R>(isolate_, return_value);
    }

    return callback_result;
  }

 private:
  v8::Isolate* isolate_;
};
template <typename R, typename A1>
class V8cCallbackFunction<R(A1)>
    : public ScopedPersistent<v8::Value>,
      public CallbackFunction<R(A1)> {
 public:
  typedef CallbackFunction<R(A1)> BaseType;

  V8cCallbackFunction() {}
  V8cCallbackFunction(v8::Isolate* isolate, v8::Local<v8::Value> handle)
      : ScopedPersistent(isolate, handle), isolate_(isolate) {}

  CallbackResult<R> Run(      typename
      base::internal::CallbackParamTraits<A1>::ForwardType a1)
      const override {
    CallbackResult<R> callback_result;
    DCHECK(!this->IsEmpty());
    if (this->IsEmpty()) {
      DLOG(WARNING) << "Function was garbage collected.";
      callback_result.exception = true;
      return callback_result;
    }

    EntryScope entry_scope(isolate_);
    v8::Local<v8::Context> context = isolate_->GetCurrentContext();

    // https://www.w3.org/TR/WebIDL/#es-invoking-callback-functions
    // Callback 'this' is set to null, unless overridden by other specifications
    v8::Local<v8::Value> this_value = v8::Null(isolate_);
    v8::Local<v8::Value> function = this->NewLocal(isolate_);
    v8::MaybeLocal<v8::Object> maybe_function_as_object =
        function->ToObject(context);
    v8::Local<v8::Object> function_as_object;
    if (!maybe_function_as_object.ToLocal(&function_as_object)) {
      DLOG(WARNING) << "Unexpected failure converting function to object.";
      callback_result.exception = true;
      return callback_result;
    }

    const int argc = 1;
    v8::Local<v8::Value> argv[argc];
    ToJSValue(isolate_, a1, &argv[0]);

    v8::MaybeLocal<v8::Value> maybe_return_value =
        function_as_object->CallAsFunction(context, this_value, argc, argv);
    v8::Local<v8::Value> return_value;
    if (!maybe_return_value.ToLocal(&return_value)) {
      NOTIMPLEMENTED();
      callback_result.exception = true;
    } else {
      callback_result = ConvertCallbackReturnValue<R>(isolate_, return_value);
    }

    return callback_result;
  }

 private:
  v8::Isolate* isolate_;
};
template <typename R, typename A1, typename A2>
class V8cCallbackFunction<R(A1, A2)>
    : public ScopedPersistent<v8::Value>,
      public CallbackFunction<R(A1, A2)> {
 public:
  typedef CallbackFunction<R(A1, A2)> BaseType;

  V8cCallbackFunction() {}
  V8cCallbackFunction(v8::Isolate* isolate, v8::Local<v8::Value> handle)
      : ScopedPersistent(isolate, handle), isolate_(isolate) {}

  CallbackResult<R> Run(      typename
      base::internal::CallbackParamTraits<A1>::ForwardType a1,
      typename base::internal::CallbackParamTraits<A2>::ForwardType a2)
      const override {
    CallbackResult<R> callback_result;
    DCHECK(!this->IsEmpty());
    if (this->IsEmpty()) {
      DLOG(WARNING) << "Function was garbage collected.";
      callback_result.exception = true;
      return callback_result;
    }

    EntryScope entry_scope(isolate_);
    v8::Local<v8::Context> context = isolate_->GetCurrentContext();

    // https://www.w3.org/TR/WebIDL/#es-invoking-callback-functions
    // Callback 'this' is set to null, unless overridden by other specifications
    v8::Local<v8::Value> this_value = v8::Null(isolate_);
    v8::Local<v8::Value> function = this->NewLocal(isolate_);
    v8::MaybeLocal<v8::Object> maybe_function_as_object =
        function->ToObject(context);
    v8::Local<v8::Object> function_as_object;
    if (!maybe_function_as_object.ToLocal(&function_as_object)) {
      DLOG(WARNING) << "Unexpected failure converting function to object.";
      callback_result.exception = true;
      return callback_result;
    }

    const int argc = 2;
    v8::Local<v8::Value> argv[argc];
    ToJSValue(isolate_, a1, &argv[0]);
    ToJSValue(isolate_, a2, &argv[1]);

    v8::MaybeLocal<v8::Value> maybe_return_value =
        function_as_object->CallAsFunction(context, this_value, argc, argv);
    v8::Local<v8::Value> return_value;
    if (!maybe_return_value.ToLocal(&return_value)) {
      NOTIMPLEMENTED();
      callback_result.exception = true;
    } else {
      callback_result = ConvertCallbackReturnValue<R>(isolate_, return_value);
    }

    return callback_result;
  }

 private:
  v8::Isolate* isolate_;
};
template <typename R, typename A1, typename A2, typename A3>
class V8cCallbackFunction<R(A1, A2, A3)>
    : public ScopedPersistent<v8::Value>,
      public CallbackFunction<R(A1, A2, A3)> {
 public:
  typedef CallbackFunction<R(A1, A2, A3)> BaseType;

  V8cCallbackFunction() {}
  V8cCallbackFunction(v8::Isolate* isolate, v8::Local<v8::Value> handle)
      : ScopedPersistent(isolate, handle), isolate_(isolate) {}

  CallbackResult<R> Run(      typename
      base::internal::CallbackParamTraits<A1>::ForwardType a1,
      typename base::internal::CallbackParamTraits<A2>::ForwardType a2,
      typename base::internal::CallbackParamTraits<A3>::ForwardType a3)
      const override {
    CallbackResult<R> callback_result;
    DCHECK(!this->IsEmpty());
    if (this->IsEmpty()) {
      DLOG(WARNING) << "Function was garbage collected.";
      callback_result.exception = true;
      return callback_result;
    }

    EntryScope entry_scope(isolate_);
    v8::Local<v8::Context> context = isolate_->GetCurrentContext();

    // https://www.w3.org/TR/WebIDL/#es-invoking-callback-functions
    // Callback 'this' is set to null, unless overridden by other specifications
    v8::Local<v8::Value> this_value = v8::Null(isolate_);
    v8::Local<v8::Value> function = this->NewLocal(isolate_);
    v8::MaybeLocal<v8::Object> maybe_function_as_object =
        function->ToObject(context);
    v8::Local<v8::Object> function_as_object;
    if (!maybe_function_as_object.ToLocal(&function_as_object)) {
      DLOG(WARNING) << "Unexpected failure converting function to object.";
      callback_result.exception = true;
      return callback_result;
    }

    const int argc = 3;
    v8::Local<v8::Value> argv[argc];
    ToJSValue(isolate_, a1, &argv[0]);
    ToJSValue(isolate_, a2, &argv[1]);
    ToJSValue(isolate_, a3, &argv[2]);

    v8::MaybeLocal<v8::Value> maybe_return_value =
        function_as_object->CallAsFunction(context, this_value, argc, argv);
    v8::Local<v8::Value> return_value;
    if (!maybe_return_value.ToLocal(&return_value)) {
      NOTIMPLEMENTED();
      callback_result.exception = true;
    } else {
      callback_result = ConvertCallbackReturnValue<R>(isolate_, return_value);
    }

    return callback_result;
  }

 private:
  v8::Isolate* isolate_;
};
template <typename R, typename A1, typename A2, typename A3, typename A4>
class V8cCallbackFunction<R(A1, A2, A3, A4)>
    : public ScopedPersistent<v8::Value>,
      public CallbackFunction<R(A1, A2, A3, A4)> {
 public:
  typedef CallbackFunction<R(A1, A2, A3, A4)> BaseType;

  V8cCallbackFunction() {}
  V8cCallbackFunction(v8::Isolate* isolate, v8::Local<v8::Value> handle)
      : ScopedPersistent(isolate, handle), isolate_(isolate) {}

  CallbackResult<R> Run(      typename
      base::internal::CallbackParamTraits<A1>::ForwardType a1,
      typename base::internal::CallbackParamTraits<A2>::ForwardType a2,
      typename base::internal::CallbackParamTraits<A3>::ForwardType a3,
      typename base::internal::CallbackParamTraits<A4>::ForwardType a4)
      const override {
    CallbackResult<R> callback_result;
    DCHECK(!this->IsEmpty());
    if (this->IsEmpty()) {
      DLOG(WARNING) << "Function was garbage collected.";
      callback_result.exception = true;
      return callback_result;
    }

    EntryScope entry_scope(isolate_);
    v8::Local<v8::Context> context = isolate_->GetCurrentContext();

    // https://www.w3.org/TR/WebIDL/#es-invoking-callback-functions
    // Callback 'this' is set to null, unless overridden by other specifications
    v8::Local<v8::Value> this_value = v8::Null(isolate_);
    v8::Local<v8::Value> function = this->NewLocal(isolate_);
    v8::MaybeLocal<v8::Object> maybe_function_as_object =
        function->ToObject(context);
    v8::Local<v8::Object> function_as_object;
    if (!maybe_function_as_object.ToLocal(&function_as_object)) {
      DLOG(WARNING) << "Unexpected failure converting function to object.";
      callback_result.exception = true;
      return callback_result;
    }

    const int argc = 4;
    v8::Local<v8::Value> argv[argc];
    ToJSValue(isolate_, a1, &argv[0]);
    ToJSValue(isolate_, a2, &argv[1]);
    ToJSValue(isolate_, a3, &argv[2]);
    ToJSValue(isolate_, a4, &argv[3]);

    v8::MaybeLocal<v8::Value> maybe_return_value =
        function_as_object->CallAsFunction(context, this_value, argc, argv);
    v8::Local<v8::Value> return_value;
    if (!maybe_return_value.ToLocal(&return_value)) {
      NOTIMPLEMENTED();
      callback_result.exception = true;
    } else {
      callback_result = ConvertCallbackReturnValue<R>(isolate_, return_value);
    }

    return callback_result;
  }

 private:
  v8::Isolate* isolate_;
};
template <typename R, typename A1, typename A2, typename A3, typename A4,
    typename A5>
class V8cCallbackFunction<R(A1, A2, A3, A4, A5)>
    : public ScopedPersistent<v8::Value>,
      public CallbackFunction<R(A1, A2, A3, A4, A5)> {
 public:
  typedef CallbackFunction<R(A1, A2, A3, A4, A5)> BaseType;

  V8cCallbackFunction() {}
  V8cCallbackFunction(v8::Isolate* isolate, v8::Local<v8::Value> handle)
      : ScopedPersistent(isolate, handle), isolate_(isolate) {}

  CallbackResult<R> Run(      typename
      base::internal::CallbackParamTraits<A1>::ForwardType a1,
      typename base::internal::CallbackParamTraits<A2>::ForwardType a2,
      typename base::internal::CallbackParamTraits<A3>::ForwardType a3,
      typename base::internal::CallbackParamTraits<A4>::ForwardType a4,
      typename base::internal::CallbackParamTraits<A5>::ForwardType a5)
      const override {
    CallbackResult<R> callback_result;
    DCHECK(!this->IsEmpty());
    if (this->IsEmpty()) {
      DLOG(WARNING) << "Function was garbage collected.";
      callback_result.exception = true;
      return callback_result;
    }

    EntryScope entry_scope(isolate_);
    v8::Local<v8::Context> context = isolate_->GetCurrentContext();

    // https://www.w3.org/TR/WebIDL/#es-invoking-callback-functions
    // Callback 'this' is set to null, unless overridden by other specifications
    v8::Local<v8::Value> this_value = v8::Null(isolate_);
    v8::Local<v8::Value> function = this->NewLocal(isolate_);
    v8::MaybeLocal<v8::Object> maybe_function_as_object =
        function->ToObject(context);
    v8::Local<v8::Object> function_as_object;
    if (!maybe_function_as_object.ToLocal(&function_as_object)) {
      DLOG(WARNING) << "Unexpected failure converting function to object.";
      callback_result.exception = true;
      return callback_result;
    }

    const int argc = 5;
    v8::Local<v8::Value> argv[argc];
    ToJSValue(isolate_, a1, &argv[0]);
    ToJSValue(isolate_, a2, &argv[1]);
    ToJSValue(isolate_, a3, &argv[2]);
    ToJSValue(isolate_, a4, &argv[3]);
    ToJSValue(isolate_, a5, &argv[4]);

    v8::MaybeLocal<v8::Value> maybe_return_value =
        function_as_object->CallAsFunction(context, this_value, argc, argv);
    v8::Local<v8::Value> return_value;
    if (!maybe_return_value.ToLocal(&return_value)) {
      NOTIMPLEMENTED();
      callback_result.exception = true;
    } else {
      callback_result = ConvertCallbackReturnValue<R>(isolate_, return_value);
    }

    return callback_result;
  }

 private:
  v8::Isolate* isolate_;
};
template <typename R, typename A1, typename A2, typename A3, typename A4,
    typename A5, typename A6>
class V8cCallbackFunction<R(A1, A2, A3, A4, A5, A6)>
    : public ScopedPersistent<v8::Value>,
      public CallbackFunction<R(A1, A2, A3, A4, A5, A6)> {
 public:
  typedef CallbackFunction<R(A1, A2, A3, A4, A5, A6)> BaseType;

  V8cCallbackFunction() {}
  V8cCallbackFunction(v8::Isolate* isolate, v8::Local<v8::Value> handle)
      : ScopedPersistent(isolate, handle), isolate_(isolate) {}

  CallbackResult<R> Run(      typename
      base::internal::CallbackParamTraits<A1>::ForwardType a1,
      typename base::internal::CallbackParamTraits<A2>::ForwardType a2,
      typename base::internal::CallbackParamTraits<A3>::ForwardType a3,
      typename base::internal::CallbackParamTraits<A4>::ForwardType a4,
      typename base::internal::CallbackParamTraits<A5>::ForwardType a5,
      typename base::internal::CallbackParamTraits<A6>::ForwardType a6)
      const override {
    CallbackResult<R> callback_result;
    DCHECK(!this->IsEmpty());
    if (this->IsEmpty()) {
      DLOG(WARNING) << "Function was garbage collected.";
      callback_result.exception = true;
      return callback_result;
    }

    EntryScope entry_scope(isolate_);
    v8::Local<v8::Context> context = isolate_->GetCurrentContext();

    // https://www.w3.org/TR/WebIDL/#es-invoking-callback-functions
    // Callback 'this' is set to null, unless overridden by other specifications
    v8::Local<v8::Value> this_value = v8::Null(isolate_);
    v8::Local<v8::Value> function = this->NewLocal(isolate_);
    v8::MaybeLocal<v8::Object> maybe_function_as_object =
        function->ToObject(context);
    v8::Local<v8::Object> function_as_object;
    if (!maybe_function_as_object.ToLocal(&function_as_object)) {
      DLOG(WARNING) << "Unexpected failure converting function to object.";
      callback_result.exception = true;
      return callback_result;
    }

    const int argc = 6;
    v8::Local<v8::Value> argv[argc];
    ToJSValue(isolate_, a1, &argv[0]);
    ToJSValue(isolate_, a2, &argv[1]);
    ToJSValue(isolate_, a3, &argv[2]);
    ToJSValue(isolate_, a4, &argv[3]);
    ToJSValue(isolate_, a5, &argv[4]);
    ToJSValue(isolate_, a6, &argv[5]);

    v8::MaybeLocal<v8::Value> maybe_return_value =
        function_as_object->CallAsFunction(context, this_value, argc, argv);
    v8::Local<v8::Value> return_value;
    if (!maybe_return_value.ToLocal(&return_value)) {
      NOTIMPLEMENTED();
      callback_result.exception = true;
    } else {
      callback_result = ConvertCallbackReturnValue<R>(isolate_, return_value);
    }

    return callback_result;
  }

 private:
  v8::Isolate* isolate_;
};
template <typename R, typename A1, typename A2, typename A3, typename A4,
    typename A5, typename A6, typename A7>
class V8cCallbackFunction<R(A1, A2, A3, A4, A5, A6, A7)>
    : public ScopedPersistent<v8::Value>,
      public CallbackFunction<R(A1, A2, A3, A4, A5, A6, A7)> {
 public:
  typedef CallbackFunction<R(A1, A2, A3, A4, A5, A6, A7)> BaseType;

  V8cCallbackFunction() {}
  V8cCallbackFunction(v8::Isolate* isolate, v8::Local<v8::Value> handle)
      : ScopedPersistent(isolate, handle), isolate_(isolate) {}

  CallbackResult<R> Run(      typename
      base::internal::CallbackParamTraits<A1>::ForwardType a1,
      typename base::internal::CallbackParamTraits<A2>::ForwardType a2,
      typename base::internal::CallbackParamTraits<A3>::ForwardType a3,
      typename base::internal::CallbackParamTraits<A4>::ForwardType a4,
      typename base::internal::CallbackParamTraits<A5>::ForwardType a5,
      typename base::internal::CallbackParamTraits<A6>::ForwardType a6,
      typename base::internal::CallbackParamTraits<A7>::ForwardType a7)
      const override {
    CallbackResult<R> callback_result;
    DCHECK(!this->IsEmpty());
    if (this->IsEmpty()) {
      DLOG(WARNING) << "Function was garbage collected.";
      callback_result.exception = true;
      return callback_result;
    }

    EntryScope entry_scope(isolate_);
    v8::Local<v8::Context> context = isolate_->GetCurrentContext();

    // https://www.w3.org/TR/WebIDL/#es-invoking-callback-functions
    // Callback 'this' is set to null, unless overridden by other specifications
    v8::Local<v8::Value> this_value = v8::Null(isolate_);
    v8::Local<v8::Value> function = this->NewLocal(isolate_);
    v8::MaybeLocal<v8::Object> maybe_function_as_object =
        function->ToObject(context);
    v8::Local<v8::Object> function_as_object;
    if (!maybe_function_as_object.ToLocal(&function_as_object)) {
      DLOG(WARNING) << "Unexpected failure converting function to object.";
      callback_result.exception = true;
      return callback_result;
    }

    const int argc = 7;
    v8::Local<v8::Value> argv[argc];
    ToJSValue(isolate_, a1, &argv[0]);
    ToJSValue(isolate_, a2, &argv[1]);
    ToJSValue(isolate_, a3, &argv[2]);
    ToJSValue(isolate_, a4, &argv[3]);
    ToJSValue(isolate_, a5, &argv[4]);
    ToJSValue(isolate_, a6, &argv[5]);
    ToJSValue(isolate_, a7, &argv[6]);

    v8::MaybeLocal<v8::Value> maybe_return_value =
        function_as_object->CallAsFunction(context, this_value, argc, argv);
    v8::Local<v8::Value> return_value;
    if (!maybe_return_value.ToLocal(&return_value)) {
      NOTIMPLEMENTED();
      callback_result.exception = true;
    } else {
      callback_result = ConvertCallbackReturnValue<R>(isolate_, return_value);
    }

    return callback_result;
  }

 private:
  v8::Isolate* isolate_;
};

template <typename Signature>
struct TypeTraits<CallbackFunction<Signature> > {
  typedef V8cUserObjectHolder<V8cCallbackFunction<Signature> > ConversionType;
  typedef const ScriptValue<CallbackFunction<Signature> >* ReturnType;
};

}  // namespace v8c
}  // namespace script
}  // namespace cobalt

#endif  // COBALT_SCRIPT_V8C_V8C_CALLBACK_FUNCTION_H_
