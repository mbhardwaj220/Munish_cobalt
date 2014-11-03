// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py. DO NOT MODIFY!

#include "config.h"
#include "V8TestTypedefs.h"

#include "bindings/core/v8/ExceptionState.h"
#include "bindings/core/v8/UnionTypesCore.h"
#include "bindings/core/v8/V8DOMConfiguration.h"
#include "bindings/core/v8/V8HiddenValue.h"
#include "bindings/core/v8/V8ObjectConstructor.h"
#include "bindings/core/v8/V8TestCallbackInterface.h"
#include "bindings/core/v8/V8TestInterface.h"
#include "bindings/core/v8/V8TestInterfaceEmpty.h"
#include "core/dom/ContextFeatures.h"
#include "core/dom/Document.h"
#include "core/frame/LocalDOMWindow.h"
#include "platform/RuntimeEnabledFeatures.h"
#include "platform/TraceEvent.h"
#include "wtf/GetPtr.h"
#include "wtf/RefPtr.h"

namespace blink {

const WrapperTypeInfo V8TestTypedefs::wrapperTypeInfo = { gin::kEmbedderBlink, V8TestTypedefs::domTemplate, V8TestTypedefs::refObject, V8TestTypedefs::derefObject, V8TestTypedefs::trace, 0, 0, 0, V8TestTypedefs::installConditionallyEnabledMethods, V8TestTypedefs::installConditionallyEnabledProperties, 0, WrapperTypeInfo::WrapperTypeObjectPrototype, WrapperTypeInfo::ObjectClassId, WrapperTypeInfo::Independent, WrapperTypeInfo::RefCountedObject };

// This static member must be declared by DEFINE_WRAPPERTYPEINFO in TestTypedefs.h.
// For details, see the comment of DEFINE_WRAPPERTYPEINFO in
// bindings/core/v8/ScriptWrappable.h.
const WrapperTypeInfo& TestTypedefs::s_wrapperTypeInfo = V8TestTypedefs::wrapperTypeInfo;

namespace TestTypedefsV8Internal {

static void uLongLongAttributeAttributeGetter(const v8::PropertyCallbackInfo<v8::Value>& info)
{
    v8::Handle<v8::Object> holder = info.Holder();
    TestTypedefs* impl = V8TestTypedefs::toImpl(holder);
    v8SetReturnValue(info, static_cast<double>(impl->uLongLongAttribute()));
}

static void uLongLongAttributeAttributeGetterCallback(v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("blink", "DOMGetter");
    TestTypedefsV8Internal::uLongLongAttributeAttributeGetter(info);
    TRACE_EVENT_SET_SAMPLING_STATE("v8", "V8Execution");
}

static void uLongLongAttributeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::PropertyCallbackInfo<void>& info)
{
    v8::Handle<v8::Object> holder = info.Holder();
    ExceptionState exceptionState(ExceptionState::SetterContext, "uLongLongAttribute", "TestTypedefs", holder, info.GetIsolate());
    TestTypedefs* impl = V8TestTypedefs::toImpl(holder);
    TONATIVE_VOID_EXCEPTIONSTATE(unsigned long long, cppValue, toUInt64(v8Value, exceptionState), exceptionState);
    impl->setULongLongAttribute(cppValue);
}

static void uLongLongAttributeAttributeSetterCallback(v8::Local<v8::String>, v8::Local<v8::Value> v8Value, const v8::PropertyCallbackInfo<void>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("blink", "DOMSetter");
    TestTypedefsV8Internal::uLongLongAttributeAttributeSetter(v8Value, info);
    TRACE_EVENT_SET_SAMPLING_STATE("v8", "V8Execution");
}

static void TestTypedefsConstructorGetter(v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Value>& info)
{
    v8::Handle<v8::Value> data = info.Data();
    ASSERT(data->IsExternal());
    V8PerContextData* perContextData = V8PerContextData::from(info.Holder()->CreationContext());
    if (!perContextData)
        return;
    v8SetReturnValue(info, perContextData->constructorForType(WrapperTypeInfo::unwrap(data)));
}

static void TestTypedefsForceSetAttributeOnThis(v8::Local<v8::String> name, v8::Local<v8::Value> v8Value, const v8::PropertyCallbackInfo<void>& info)
{
    if (info.This()->IsObject())
        v8::Handle<v8::Object>::Cast(info.This())->ForceSet(name, v8Value);
}

static void TestTypedefsForceSetAttributeOnThisCallback(v8::Local<v8::String> name, v8::Local<v8::Value> v8Value, const v8::PropertyCallbackInfo<void>& info)
{
    TestTypedefsV8Internal::TestTypedefsForceSetAttributeOnThis(name, v8Value, info);
}

static void voidMethodArrayOfLongsArgMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "voidMethodArrayOfLongsArg", "TestTypedefs", info.Holder(), info.GetIsolate());
    TestTypedefs* impl = V8TestTypedefs::toImpl(info.Holder());
    Vector<int> arrayOfLongsArg;
    {
        if (UNLIKELY(info.Length() <= 0)) {
            impl->voidMethodArrayOfLongsArg();
            return;
        }
        TONATIVE_VOID_EXCEPTIONSTATE_INTERNAL(arrayOfLongsArg, toImplArray<int>(info[0], 1, info.GetIsolate(), exceptionState), exceptionState);
    }
    impl->voidMethodArrayOfLongsArg(arrayOfLongsArg);
}

static void voidMethodArrayOfLongsArgMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("blink", "DOMMethod");
    TestTypedefsV8Internal::voidMethodArrayOfLongsArgMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("v8", "V8Execution");
}

static void voidMethodFloatArgStringArgMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "voidMethodFloatArgStringArg", "TestTypedefs", info.Holder(), info.GetIsolate());
    if (UNLIKELY(info.Length() < 2)) {
        setMinimumArityTypeError(exceptionState, 2, info.Length());
        exceptionState.throwIfNeeded();
        return;
    }
    TestTypedefs* impl = V8TestTypedefs::toImpl(info.Holder());
    float floatArg;
    V8StringResource<> stringArg;
    {
        TONATIVE_VOID_EXCEPTIONSTATE_INTERNAL(floatArg, toFloat(info[0], exceptionState), exceptionState);
        TOSTRING_VOID_INTERNAL(stringArg, info[1]);
    }
    impl->voidMethodFloatArgStringArg(floatArg, stringArg);
}

static void voidMethodFloatArgStringArgMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("blink", "DOMMethod");
    TestTypedefsV8Internal::voidMethodFloatArgStringArgMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("v8", "V8Execution");
}

static void voidMethodTestCallbackInterfaceTypeArgMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    if (UNLIKELY(info.Length() < 1)) {
        V8ThrowException::throwException(createMinimumArityTypeErrorForMethod(info.GetIsolate(), "voidMethodTestCallbackInterfaceTypeArg", "TestTypedefs", 1, info.Length()), info.GetIsolate());
        return;
    }
    TestTypedefs* impl = V8TestTypedefs::toImpl(info.Holder());
    TestCallbackInterface* testCallbackInterfaceTypeArg;
    {
        if (info.Length() <= 0 || !info[0]->IsFunction()) {
            V8ThrowException::throwTypeError(ExceptionMessages::failedToExecute("voidMethodTestCallbackInterfaceTypeArg", "TestTypedefs", "The callback provided as parameter 1 is not a function."), info.GetIsolate());
            return;
        }
        testCallbackInterfaceTypeArg = V8TestCallbackInterface::create(v8::Handle<v8::Function>::Cast(info[0]), ScriptState::current(info.GetIsolate()));
    }
    impl->voidMethodTestCallbackInterfaceTypeArg(testCallbackInterfaceTypeArg);
}

static void voidMethodTestCallbackInterfaceTypeArgMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("blink", "DOMMethod");
    TestTypedefsV8Internal::voidMethodTestCallbackInterfaceTypeArgMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("v8", "V8Execution");
}

static void uLongLongMethodTestInterfaceEmptyTypeSequenceArgMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "uLongLongMethodTestInterfaceEmptyTypeSequenceArg", "TestTypedefs", info.Holder(), info.GetIsolate());
    if (UNLIKELY(info.Length() < 1)) {
        setMinimumArityTypeError(exceptionState, 1, info.Length());
        exceptionState.throwIfNeeded();
        return;
    }
    TestTypedefs* impl = V8TestTypedefs::toImpl(info.Holder());
    Vector<RefPtr<TestInterfaceEmpty> > testInterfaceEmptyTypeSequenceArg;
    {
        TONATIVE_VOID_EXCEPTIONSTATE_INTERNAL(testInterfaceEmptyTypeSequenceArg, (toRefPtrNativeArray<TestInterfaceEmpty, V8TestInterfaceEmpty>(info[0], 1, info.GetIsolate(), exceptionState)), exceptionState);
    }
    v8SetReturnValue(info, static_cast<double>(impl->uLongLongMethodTestInterfaceEmptyTypeSequenceArg(testInterfaceEmptyTypeSequenceArg)));
}

static void uLongLongMethodTestInterfaceEmptyTypeSequenceArgMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("blink", "DOMMethod");
    TestTypedefsV8Internal::uLongLongMethodTestInterfaceEmptyTypeSequenceArgMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("v8", "V8Execution");
}

static void testInterfaceOrTestInterfaceEmptyMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TestTypedefs* impl = V8TestTypedefs::toImpl(info.Holder());
    TestInterfaceOrTestInterfaceEmpty result;
    impl->testInterfaceOrTestInterfaceEmptyMethod(result);
    v8SetReturnValue(info, result);
}

static void testInterfaceOrTestInterfaceEmptyMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("blink", "DOMMethod");
    TestTypedefsV8Internal::testInterfaceOrTestInterfaceEmptyMethodMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("v8", "V8Execution");
}

static void domStringOrDoubleMethodMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TestTypedefs* impl = V8TestTypedefs::toImpl(info.Holder());
    StringOrDouble result;
    impl->domStringOrDoubleMethod(result);
    v8SetReturnValue(info, result);
}

static void domStringOrDoubleMethodMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("blink", "DOMMethod");
    TestTypedefsV8Internal::domStringOrDoubleMethodMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("v8", "V8Execution");
}

static void arrayOfStringsMethodArrayOfStringsArgMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "arrayOfStringsMethodArrayOfStringsArg", "TestTypedefs", info.Holder(), info.GetIsolate());
    if (UNLIKELY(info.Length() < 1)) {
        setMinimumArityTypeError(exceptionState, 1, info.Length());
        exceptionState.throwIfNeeded();
        return;
    }
    TestTypedefs* impl = V8TestTypedefs::toImpl(info.Holder());
    Vector<String> arrayOfStringsArg;
    {
        TONATIVE_VOID_EXCEPTIONSTATE_INTERNAL(arrayOfStringsArg, toImplArray<String>(info[0], 1, info.GetIsolate(), exceptionState), exceptionState);
    }
    v8SetReturnValue(info, v8Array(impl->arrayOfStringsMethodArrayOfStringsArg(arrayOfStringsArg), info.Holder(), info.GetIsolate()));
}

static void arrayOfStringsMethodArrayOfStringsArgMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("blink", "DOMMethod");
    TestTypedefsV8Internal::arrayOfStringsMethodArrayOfStringsArgMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("v8", "V8Execution");
}

static void stringArrayMethodStringArrayArgMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    ExceptionState exceptionState(ExceptionState::ExecutionContext, "stringArrayMethodStringArrayArg", "TestTypedefs", info.Holder(), info.GetIsolate());
    if (UNLIKELY(info.Length() < 1)) {
        setMinimumArityTypeError(exceptionState, 1, info.Length());
        exceptionState.throwIfNeeded();
        return;
    }
    TestTypedefs* impl = V8TestTypedefs::toImpl(info.Holder());
    Vector<String> stringArrayArg;
    {
        TONATIVE_VOID_EXCEPTIONSTATE_INTERNAL(stringArrayArg, toImplArray<String>(info[0], 1, info.GetIsolate(), exceptionState), exceptionState);
    }
    v8SetReturnValue(info, v8Array(impl->stringArrayMethodStringArrayArg(stringArrayArg), info.Holder(), info.GetIsolate()));
}

static void stringArrayMethodStringArrayArgMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SET_SAMPLING_STATE("blink", "DOMMethod");
    TestTypedefsV8Internal::stringArrayMethodStringArrayArgMethod(info);
    TRACE_EVENT_SET_SAMPLING_STATE("v8", "V8Execution");
}

static void constructor(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    if (UNLIKELY(info.Length() < 1)) {
        V8ThrowException::throwException(createMinimumArityTypeErrorForConstructor(info.GetIsolate(), "TestTypedefs", 1, info.Length()), info.GetIsolate());
        return;
    }
    V8StringResource<> stringArg;
    {
        TOSTRING_VOID_INTERNAL(stringArg, info[0]);
    }
    RefPtr<TestTypedefs> impl = TestTypedefs::create(stringArg);
    v8::Handle<v8::Object> wrapper = info.Holder();
    impl->associateWithWrapper(&V8TestTypedefs::wrapperTypeInfo, wrapper, info.GetIsolate());
    v8SetReturnValue(info, wrapper);
}

} // namespace TestTypedefsV8Internal

static const V8DOMConfiguration::AttributeConfiguration V8TestTypedefsAttributes[] = {
    {"uLongLongAttribute", TestTypedefsV8Internal::uLongLongAttributeAttributeGetterCallback, TestTypedefsV8Internal::uLongLongAttributeAttributeSetterCallback, 0, 0, 0, static_cast<v8::AccessControl>(v8::DEFAULT), static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::ExposedToAllScripts, V8DOMConfiguration::OnInstance},
    {"tAttribute", TestTypedefsV8Internal::TestTypedefsConstructorGetter, TestTypedefsV8Internal::TestTypedefsForceSetAttributeOnThisCallback, 0, 0, const_cast<WrapperTypeInfo*>(&V8TestInterface::wrapperTypeInfo), static_cast<v8::AccessControl>(v8::DEFAULT), static_cast<v8::PropertyAttribute>(v8::DontEnum), V8DOMConfiguration::ExposedToAllScripts, V8DOMConfiguration::OnInstance},
};

static const V8DOMConfiguration::MethodConfiguration V8TestTypedefsMethods[] = {
    {"voidMethodArrayOfLongsArg", TestTypedefsV8Internal::voidMethodArrayOfLongsArgMethodCallback, 0, 0, V8DOMConfiguration::ExposedToAllScripts},
    {"voidMethodFloatArgStringArg", TestTypedefsV8Internal::voidMethodFloatArgStringArgMethodCallback, 0, 2, V8DOMConfiguration::ExposedToAllScripts},
    {"voidMethodTestCallbackInterfaceTypeArg", TestTypedefsV8Internal::voidMethodTestCallbackInterfaceTypeArgMethodCallback, 0, 1, V8DOMConfiguration::ExposedToAllScripts},
    {"uLongLongMethodTestInterfaceEmptyTypeSequenceArg", TestTypedefsV8Internal::uLongLongMethodTestInterfaceEmptyTypeSequenceArgMethodCallback, 0, 1, V8DOMConfiguration::ExposedToAllScripts},
    {"testInterfaceOrTestInterfaceEmptyMethod", TestTypedefsV8Internal::testInterfaceOrTestInterfaceEmptyMethodMethodCallback, 0, 0, V8DOMConfiguration::ExposedToAllScripts},
    {"domStringOrDoubleMethod", TestTypedefsV8Internal::domStringOrDoubleMethodMethodCallback, 0, 0, V8DOMConfiguration::ExposedToAllScripts},
    {"arrayOfStringsMethodArrayOfStringsArg", TestTypedefsV8Internal::arrayOfStringsMethodArrayOfStringsArgMethodCallback, 0, 1, V8DOMConfiguration::ExposedToAllScripts},
    {"stringArrayMethodStringArrayArg", TestTypedefsV8Internal::stringArrayMethodStringArrayArgMethodCallback, 0, 1, V8DOMConfiguration::ExposedToAllScripts},
};

void V8TestTypedefs::constructorCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    TRACE_EVENT_SCOPED_SAMPLING_STATE("blink", "DOMConstructor");
    if (!info.IsConstructCall()) {
        V8ThrowException::throwTypeError(ExceptionMessages::constructorNotCallableAsFunction("TestTypedefs"), info.GetIsolate());
        return;
    }

    if (ConstructorMode::current(info.GetIsolate()) == ConstructorMode::WrapExistingObject) {
        v8SetReturnValue(info, info.Holder());
        return;
    }

    TestTypedefsV8Internal::constructor(info);
}

static void installV8TestTypedefsTemplate(v8::Handle<v8::FunctionTemplate> functionTemplate, v8::Isolate* isolate)
{
    functionTemplate->ReadOnlyPrototype();

    v8::Local<v8::Signature> defaultSignature;
    defaultSignature = V8DOMConfiguration::installDOMClassTemplate(functionTemplate, "TestTypedefs", v8::Local<v8::FunctionTemplate>(), V8TestTypedefs::internalFieldCount,
        V8TestTypedefsAttributes, WTF_ARRAY_LENGTH(V8TestTypedefsAttributes),
        0, 0,
        V8TestTypedefsMethods, WTF_ARRAY_LENGTH(V8TestTypedefsMethods),
        isolate);
    functionTemplate->SetCallHandler(V8TestTypedefs::constructorCallback);
    functionTemplate->SetLength(1);
    v8::Local<v8::ObjectTemplate> instanceTemplate = functionTemplate->InstanceTemplate();
    ALLOW_UNUSED_LOCAL(instanceTemplate);
    v8::Local<v8::ObjectTemplate> prototypeTemplate = functionTemplate->PrototypeTemplate();
    ALLOW_UNUSED_LOCAL(prototypeTemplate);

    // Custom toString template
    functionTemplate->Set(v8AtomicString(isolate, "toString"), V8PerIsolateData::from(isolate)->toStringTemplate());
}

v8::Handle<v8::FunctionTemplate> V8TestTypedefs::domTemplate(v8::Isolate* isolate)
{
    return V8DOMConfiguration::domClassTemplate(isolate, const_cast<WrapperTypeInfo*>(&wrapperTypeInfo), installV8TestTypedefsTemplate);
}

bool V8TestTypedefs::hasInstance(v8::Handle<v8::Value> v8Value, v8::Isolate* isolate)
{
    return V8PerIsolateData::from(isolate)->hasInstance(&wrapperTypeInfo, v8Value);
}

v8::Handle<v8::Object> V8TestTypedefs::findInstanceInPrototypeChain(v8::Handle<v8::Value> v8Value, v8::Isolate* isolate)
{
    return V8PerIsolateData::from(isolate)->findInstanceInPrototypeChain(&wrapperTypeInfo, v8Value);
}

TestTypedefs* V8TestTypedefs::toImplWithTypeCheck(v8::Isolate* isolate, v8::Handle<v8::Value> value)
{
    return hasInstance(value, isolate) ? blink::toScriptWrappableBase(v8::Handle<v8::Object>::Cast(value))->toImpl<TestTypedefs>() : 0;
}

void V8TestTypedefs::refObject(ScriptWrappableBase* scriptWrappableBase)
{
    scriptWrappableBase->toImpl<TestTypedefs>()->ref();
}

void V8TestTypedefs::derefObject(ScriptWrappableBase* scriptWrappableBase)
{
    scriptWrappableBase->toImpl<TestTypedefs>()->deref();
}

template<>
v8::Handle<v8::Value> toV8NoInline(TestTypedefs* impl, v8::Handle<v8::Object> creationContext, v8::Isolate* isolate)
{
    return toV8(impl, creationContext, isolate);
}

} // namespace blink
