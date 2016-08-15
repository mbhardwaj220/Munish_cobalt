/*
 * Copyright 2016 Google Inc. All Rights Reserved.
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

// This file has been auto-generated by bindings/code_generator_cobalt.py. DO NOT MODIFY!
// Auto-generated from template: bindings/mozjs/templates/interface.cc.template

// clang-format off

#include "MozjsWindow.h"

#include "base/debug/trace_event.h"
#include "cobalt/base/polymorphic_downcast.h"
#include "cobalt/script/global_object_proxy.h"
#include "cobalt/script/opaque_handle.h"
#include "cobalt/script/script_object.h"
#include "MozjsAnonymousIndexedGetterInterface.h"
#include "MozjsAnonymousNamedGetterInterface.h"
#include "MozjsAnonymousNamedIndexedGetterInterface.h"
#include "MozjsArbitraryInterface.h"
#include "MozjsBaseInterface.h"
#include "MozjsBooleanTypeTestInterface.h"
#include "MozjsCallbackFunctionInterface.h"
#include "MozjsCallbackInterfaceInterface.h"
#include "MozjsConditionalInterface.h"
#include "MozjsConstantsInterface.h"
#include "MozjsConstructorInterface.h"
#include "MozjsConstructorWithArgumentsInterface.h"
#include "MozjsDOMStringTestInterface.h"
#include "MozjsDerivedGetterSetterInterface.h"
#include "MozjsDerivedInterface.h"
#include "MozjsDisabledInterface.h"
#include "MozjsEnumerationInterface.h"
#include "MozjsExceptionObjectInterface.h"
#include "MozjsExceptionsInterface.h"
#include "MozjsExtendedIDLAttributesInterface.h"
#include "MozjsGetOpaqueRootInterface.h"
#include "MozjsGlobalInterfaceParent.h"
#include "MozjsImplementedInterface.h"
#include "MozjsIndexedGetterInterface.h"
#include "MozjsInterfaceWithUnsupportedProperties.h"
#include "MozjsNamedConstructorInterface.h"
#include "MozjsNamedGetterInterface.h"
#include "MozjsNamedIndexedGetterInterface.h"
#include "MozjsNestedPutForwardsInterface.h"
#include "MozjsNoConstructorInterface.h"
#include "MozjsNoInterfaceObjectInterface.h"
#include "MozjsNullableTypesTestInterface.h"
#include "MozjsNumericTypesTestInterface.h"
#include "MozjsObjectTypeBindingsInterface.h"
#include "MozjsOperationsTestInterface.h"
#include "MozjsPutForwardsInterface.h"
#include "MozjsSingleOperationInterface.h"
#include "MozjsStaticPropertiesInterface.h"
#include "MozjsStringifierAnonymousOperationInterface.h"
#include "MozjsStringifierAttributeInterface.h"
#include "MozjsStringifierOperationInterface.h"
#include "MozjsTargetInterface.h"
#include "MozjsUnionTypesInterface.h"
#include "MozjsWindow.h"
#include "cobalt/bindings/testing/anonymous_indexed_getter_interface.h"
#include "cobalt/bindings/testing/anonymous_named_getter_interface.h"
#include "cobalt/bindings/testing/anonymous_named_indexed_getter_interface.h"
#include "cobalt/bindings/testing/arbitrary_interface.h"
#include "cobalt/bindings/testing/base_interface.h"
#include "cobalt/bindings/testing/boolean_type_test_interface.h"
#include "cobalt/bindings/testing/callback_function_interface.h"
#include "cobalt/bindings/testing/callback_interface_interface.h"
#include "cobalt/bindings/testing/conditional_interface.h"
#include "cobalt/bindings/testing/constants_interface.h"
#include "cobalt/bindings/testing/constructor_interface.h"
#include "cobalt/bindings/testing/constructor_with_arguments_interface.h"
#include "cobalt/bindings/testing/derived_getter_setter_interface.h"
#include "cobalt/bindings/testing/derived_interface.h"
#include "cobalt/bindings/testing/disabled_interface.h"
#include "cobalt/bindings/testing/dom_string_test_interface.h"
#include "cobalt/bindings/testing/enumeration_interface.h"
#include "cobalt/bindings/testing/exception_object_interface.h"
#include "cobalt/bindings/testing/exceptions_interface.h"
#include "cobalt/bindings/testing/extended_idl_attributes_interface.h"
#include "cobalt/bindings/testing/get_opaque_root_interface.h"
#include "cobalt/bindings/testing/global_interface_parent.h"
#include "cobalt/bindings/testing/implemented_interface.h"
#include "cobalt/bindings/testing/indexed_getter_interface.h"
#include "cobalt/bindings/testing/interface_with_unsupported_properties.h"
#include "cobalt/bindings/testing/named_constructor_interface.h"
#include "cobalt/bindings/testing/named_getter_interface.h"
#include "cobalt/bindings/testing/named_indexed_getter_interface.h"
#include "cobalt/bindings/testing/nested_put_forwards_interface.h"
#include "cobalt/bindings/testing/no_constructor_interface.h"
#include "cobalt/bindings/testing/no_interface_object_interface.h"
#include "cobalt/bindings/testing/nullable_types_test_interface.h"
#include "cobalt/bindings/testing/numeric_types_test_interface.h"
#include "cobalt/bindings/testing/object_type_bindings_interface.h"
#include "cobalt/bindings/testing/operations_test_interface.h"
#include "cobalt/bindings/testing/put_forwards_interface.h"
#include "cobalt/bindings/testing/single_operation_interface.h"
#include "cobalt/bindings/testing/static_properties_interface.h"
#include "cobalt/bindings/testing/stringifier_anonymous_operation_interface.h"
#include "cobalt/bindings/testing/stringifier_attribute_interface.h"
#include "cobalt/bindings/testing/stringifier_operation_interface.h"
#include "cobalt/bindings/testing/target_interface.h"
#include "cobalt/bindings/testing/union_types_interface.h"
#include "cobalt/bindings/testing/window.h"

#include "base/lazy_instance.h"
#include "cobalt/script/mozjs/callback_function_conversion.h"
#include "cobalt/script/exception_state.h"
#include "cobalt/script/mozjs/conversion_helpers.h"
#include "cobalt/script/mozjs/mozjs_exception_state.h"
#include "cobalt/script/mozjs/mozjs_callback_function.h"
#include "cobalt/script/mozjs/mozjs_global_object_proxy.h"
#include "cobalt/script/mozjs/mozjs_object_handle.h"
#include "cobalt/script/mozjs/mozjs_property_enumerator.h"
#include "cobalt/script/mozjs/mozjs_user_object_holder.h"
#include "cobalt/script/mozjs/proxy_handler.h"
#include "cobalt/script/mozjs/type_traits.h"
#include "cobalt/script/mozjs/wrapper_factory.h"
#include "cobalt/script/mozjs/wrapper_private.h"
#include "cobalt/script/property_enumerator.h"
#include "third_party/mozjs/js/src/jsapi.h"
#include "third_party/mozjs/js/src/jsfriendapi.h"

namespace {
using cobalt::bindings::testing::Window;
using cobalt::bindings::testing::MozjsWindow;
using cobalt::bindings::testing::AnonymousIndexedGetterInterface;
using cobalt::bindings::testing::AnonymousNamedGetterInterface;
using cobalt::bindings::testing::AnonymousNamedIndexedGetterInterface;
using cobalt::bindings::testing::ArbitraryInterface;
using cobalt::bindings::testing::BaseInterface;
using cobalt::bindings::testing::BooleanTypeTestInterface;
using cobalt::bindings::testing::CallbackFunctionInterface;
using cobalt::bindings::testing::CallbackInterfaceInterface;
#if defined(ENABLE_CONDITIONAL_INTERFACE)
using cobalt::bindings::testing::ConditionalInterface;
#endif  // defined(ENABLE_CONDITIONAL_INTERFACE)
using cobalt::bindings::testing::ConstantsInterface;
using cobalt::bindings::testing::ConstructorInterface;
using cobalt::bindings::testing::ConstructorWithArgumentsInterface;
using cobalt::bindings::testing::DOMStringTestInterface;
using cobalt::bindings::testing::DerivedGetterSetterInterface;
using cobalt::bindings::testing::DerivedInterface;
#if defined(NO_ENABLE_CONDITIONAL_INTERFACE)
using cobalt::bindings::testing::DisabledInterface;
#endif  // defined(NO_ENABLE_CONDITIONAL_INTERFACE)
using cobalt::bindings::testing::EnumerationInterface;
using cobalt::bindings::testing::ExceptionObjectInterface;
using cobalt::bindings::testing::ExceptionsInterface;
using cobalt::bindings::testing::ExtendedIDLAttributesInterface;
using cobalt::bindings::testing::GetOpaqueRootInterface;
using cobalt::bindings::testing::GlobalInterfaceParent;
using cobalt::bindings::testing::ImplementedInterface;
using cobalt::bindings::testing::IndexedGetterInterface;
using cobalt::bindings::testing::InterfaceWithUnsupportedProperties;
using cobalt::bindings::testing::MozjsAnonymousIndexedGetterInterface;
using cobalt::bindings::testing::MozjsAnonymousNamedGetterInterface;
using cobalt::bindings::testing::MozjsAnonymousNamedIndexedGetterInterface;
using cobalt::bindings::testing::MozjsArbitraryInterface;
using cobalt::bindings::testing::MozjsBaseInterface;
using cobalt::bindings::testing::MozjsBooleanTypeTestInterface;
using cobalt::bindings::testing::MozjsCallbackFunctionInterface;
using cobalt::bindings::testing::MozjsCallbackInterfaceInterface;
#if defined(ENABLE_CONDITIONAL_INTERFACE)
using cobalt::bindings::testing::MozjsConditionalInterface;
#endif  // defined(ENABLE_CONDITIONAL_INTERFACE)
using cobalt::bindings::testing::MozjsConstantsInterface;
using cobalt::bindings::testing::MozjsConstructorInterface;
using cobalt::bindings::testing::MozjsConstructorWithArgumentsInterface;
using cobalt::bindings::testing::MozjsDOMStringTestInterface;
using cobalt::bindings::testing::MozjsDerivedGetterSetterInterface;
using cobalt::bindings::testing::MozjsDerivedInterface;
#if defined(NO_ENABLE_CONDITIONAL_INTERFACE)
using cobalt::bindings::testing::MozjsDisabledInterface;
#endif  // defined(NO_ENABLE_CONDITIONAL_INTERFACE)
using cobalt::bindings::testing::MozjsEnumerationInterface;
using cobalt::bindings::testing::MozjsExceptionObjectInterface;
using cobalt::bindings::testing::MozjsExceptionsInterface;
using cobalt::bindings::testing::MozjsExtendedIDLAttributesInterface;
using cobalt::bindings::testing::MozjsGetOpaqueRootInterface;
using cobalt::bindings::testing::MozjsGlobalInterfaceParent;
using cobalt::bindings::testing::MozjsImplementedInterface;
using cobalt::bindings::testing::MozjsIndexedGetterInterface;
using cobalt::bindings::testing::MozjsInterfaceWithUnsupportedProperties;
using cobalt::bindings::testing::MozjsNamedConstructorInterface;
using cobalt::bindings::testing::MozjsNamedGetterInterface;
using cobalt::bindings::testing::MozjsNamedIndexedGetterInterface;
using cobalt::bindings::testing::MozjsNestedPutForwardsInterface;
using cobalt::bindings::testing::MozjsNoConstructorInterface;
using cobalt::bindings::testing::MozjsNoInterfaceObjectInterface;
using cobalt::bindings::testing::MozjsNullableTypesTestInterface;
using cobalt::bindings::testing::MozjsNumericTypesTestInterface;
using cobalt::bindings::testing::MozjsObjectTypeBindingsInterface;
using cobalt::bindings::testing::MozjsOperationsTestInterface;
using cobalt::bindings::testing::MozjsPutForwardsInterface;
using cobalt::bindings::testing::MozjsSingleOperationInterface;
using cobalt::bindings::testing::MozjsStaticPropertiesInterface;
using cobalt::bindings::testing::MozjsStringifierAnonymousOperationInterface;
using cobalt::bindings::testing::MozjsStringifierAttributeInterface;
using cobalt::bindings::testing::MozjsStringifierOperationInterface;
using cobalt::bindings::testing::MozjsTargetInterface;
using cobalt::bindings::testing::MozjsUnionTypesInterface;
using cobalt::bindings::testing::MozjsWindow;
using cobalt::bindings::testing::NamedConstructorInterface;
using cobalt::bindings::testing::NamedGetterInterface;
using cobalt::bindings::testing::NamedIndexedGetterInterface;
using cobalt::bindings::testing::NestedPutForwardsInterface;
using cobalt::bindings::testing::NoConstructorInterface;
using cobalt::bindings::testing::NoInterfaceObjectInterface;
using cobalt::bindings::testing::NullableTypesTestInterface;
using cobalt::bindings::testing::NumericTypesTestInterface;
using cobalt::bindings::testing::ObjectTypeBindingsInterface;
using cobalt::bindings::testing::OperationsTestInterface;
using cobalt::bindings::testing::PutForwardsInterface;
using cobalt::bindings::testing::SingleOperationInterface;
using cobalt::bindings::testing::StaticPropertiesInterface;
using cobalt::bindings::testing::StringifierAnonymousOperationInterface;
using cobalt::bindings::testing::StringifierAttributeInterface;
using cobalt::bindings::testing::StringifierOperationInterface;
using cobalt::bindings::testing::TargetInterface;
using cobalt::bindings::testing::UnionTypesInterface;
using cobalt::bindings::testing::Window;
using cobalt::script::CallbackInterfaceTraits;
using cobalt::script::GlobalObjectProxy;
using cobalt::script::OpaqueHandle;
using cobalt::script::OpaqueHandleHolder;
using cobalt::script::ScriptObject;
using cobalt::script::Wrappable;

using cobalt::script::CallbackFunction;
using cobalt::script::CallbackInterfaceTraits;
using cobalt::script::ExceptionState;
using cobalt::script::mozjs::FromJSValue;
using cobalt::script::mozjs::kConversionFlagNullable;
using cobalt::script::mozjs::kConversionFlagRestricted;
using cobalt::script::mozjs::kConversionFlagTreatNullAsEmptyString;
using cobalt::script::mozjs::kConversionFlagTreatUndefinedAsEmptyString;
using cobalt::script::mozjs::kNoConversionFlags;
using cobalt::script::mozjs::InterfaceData;
using cobalt::script::mozjs::MozjsCallbackFunction;
using cobalt::script::mozjs::MozjsExceptionState;
using cobalt::script::mozjs::MozjsGlobalObjectProxy;
using cobalt::script::mozjs::MozjsUserObjectHolder;
using cobalt::script::mozjs::MozjsPropertyEnumerator;
using cobalt::script::mozjs::ProxyHandler;
using cobalt::script::mozjs::ToJSValue;
using cobalt::script::mozjs::TypeTraits;
using cobalt::script::mozjs::WrapperPrivate;
using cobalt::script::mozjs::WrapperFactory;
using cobalt::script::Wrappable;
}  // namespace

namespace cobalt {
namespace bindings {
namespace testing {

namespace {

class MozjsWindowHandler : public ProxyHandler {
 public:
  MozjsWindowHandler()
      : ProxyHandler(indexed_property_hooks, named_property_hooks) {}

 private:
  static NamedPropertyHooks named_property_hooks;
  static IndexedPropertyHooks indexed_property_hooks;
};

ProxyHandler::NamedPropertyHooks
MozjsWindowHandler::named_property_hooks = {
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
};
ProxyHandler::IndexedPropertyHooks
MozjsWindowHandler::indexed_property_hooks = {
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
};

static base::LazyInstance<MozjsWindowHandler>
    proxy_handler;


InterfaceData* CreateCachedInterfaceData() {
  InterfaceData* interface_data = new InterfaceData();
  memset(&interface_data->instance_class_definition, 0,
         sizeof(interface_data->instance_class_definition));
  memset(&interface_data->prototype_class_definition, 0,
         sizeof(interface_data->prototype_class_definition));
  memset(&interface_data->interface_object_class_definition, 0,
         sizeof(interface_data->interface_object_class_definition));

  JSClass* instance_class = &interface_data->instance_class_definition;
  const int kGlobalFlags = JSCLASS_GLOBAL_FLAGS;
  instance_class->name = "Window";
  instance_class->flags = kGlobalFlags | JSCLASS_HAS_PRIVATE;
  instance_class->addProperty = JS_PropertyStub;
  instance_class->delProperty = JS_DeletePropertyStub;
  instance_class->getProperty = JS_PropertyStub;
  instance_class->setProperty = JS_StrictPropertyStub;
  instance_class->enumerate = JS_EnumerateStub;
  instance_class->resolve = JS_ResolveStub;
  instance_class->convert = JS_ConvertStub;
  // Function to be called before on object of this class is garbage collected.
  instance_class->finalize = &WrapperPrivate::Finalizer;
  // Called to trace objects that can be referenced from this object.
  instance_class->trace = &WrapperPrivate::Trace;

  JSClass* prototype_class = &interface_data->prototype_class_definition;
  prototype_class->name = "WindowPrototype";
  prototype_class->flags = 0;
  prototype_class->addProperty = JS_PropertyStub;
  prototype_class->delProperty = JS_DeletePropertyStub;
  prototype_class->getProperty = JS_PropertyStub;
  prototype_class->setProperty = JS_StrictPropertyStub;
  prototype_class->enumerate = JS_EnumerateStub;
  prototype_class->resolve = JS_ResolveStub;
  prototype_class->convert = JS_ConvertStub;

  JSClass* interface_object_class =
      &interface_data->interface_object_class_definition;
  interface_object_class->name = "WindowConstructor";
  interface_object_class->flags = 0;
  interface_object_class->addProperty = JS_PropertyStub;
  interface_object_class->delProperty = JS_DeletePropertyStub;
  interface_object_class->getProperty = JS_PropertyStub;
  interface_object_class->setProperty = JS_StrictPropertyStub;
  interface_object_class->enumerate = JS_EnumerateStub;
  interface_object_class->resolve = JS_ResolveStub;
  interface_object_class->convert = JS_ConvertStub;
  return interface_data;
}

JSBool get_windowProperty(
    JSContext* context, JS::HandleObject object, JS::HandleId id,
    JS::MutableHandleValue vp) {
  MozjsExceptionState exception_state(context);
  JS::RootedValue result_value(context);

  WrapperPrivate* wrapper_private =
      WrapperPrivate::GetFromObject(context, object);
  Window* impl =
      wrapper_private->wrappable<Window>().get();

  if (!exception_state.is_exception_set()) {
    ToJSValue(context,
              impl->window_property(),
              &result_value);
  }
  if (!exception_state.is_exception_set()) {
    vp.set(result_value);
  }
  return !exception_state.is_exception_set();
}

JSBool set_windowProperty(
    JSContext* context, JS::HandleObject object, JS::HandleId id,
    JSBool strict, JS::MutableHandleValue vp) {
  MozjsExceptionState exception_state(context);
  JS::RootedValue result_value(context);

  WrapperPrivate* wrapper_private =
      WrapperPrivate::GetFromObject(context, object);
  Window* impl =
      wrapper_private->wrappable<Window>().get();
  TypeTraits<std::string >::ConversionType value;
  FromJSValue(context, vp, kNoConversionFlags, &exception_state,
              &value);
  if (exception_state.is_exception_set()) {
    return false;
  }

  impl->set_window_property(value);
  result_value.set(JS::UndefinedHandleValue);
  return !exception_state.is_exception_set();
}

JSBool fcn_getStackTrace(
    JSContext* context, uint32_t argc, JS::Value *vp) {
  JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
  // Compute the 'this' value.
  JS::RootedValue this_value(context, JS_ComputeThis(context, vp));
  // 'this' should be an object.
  JS::RootedObject object(context);
  if (JS_TypeOfValue(context, this_value) != JSTYPE_OBJECT) {
    NOTREACHED();
    return false;
  }
  if (!JS_ValueToObject(context, this_value, object.address())) {
    NOTREACHED();
    return false;
  }
  MozjsExceptionState exception_state(context);
  JS::RootedValue result_value(context);

  WrapperPrivate* wrapper_private =
      WrapperPrivate::GetFromObject(context, object);
  Window* impl =
      wrapper_private->wrappable<Window>().get();
  MozjsGlobalObjectProxy* global_object_proxy =
      static_cast<MozjsGlobalObjectProxy*>(JS_GetContextPrivate(context));

  if (!exception_state.is_exception_set()) {
    ToJSValue(context,
              impl->GetStackTrace(global_object_proxy->GetStackTrace()),
              &result_value);
  }
  if (!exception_state.is_exception_set()) {
    args.rval().set(result_value);
  }
  return !exception_state.is_exception_set();
}

JSBool fcn_windowOperation(
    JSContext* context, uint32_t argc, JS::Value *vp) {
  JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
  // Compute the 'this' value.
  JS::RootedValue this_value(context, JS_ComputeThis(context, vp));
  // 'this' should be an object.
  JS::RootedObject object(context);
  if (JS_TypeOfValue(context, this_value) != JSTYPE_OBJECT) {
    NOTREACHED();
    return false;
  }
  if (!JS_ValueToObject(context, this_value, object.address())) {
    NOTREACHED();
    return false;
  }
  MozjsExceptionState exception_state(context);
  JS::RootedValue result_value(context);

  WrapperPrivate* wrapper_private =
      WrapperPrivate::GetFromObject(context, object);
  Window* impl =
      wrapper_private->wrappable<Window>().get();

  impl->WindowOperation();
  result_value.set(JS::UndefinedHandleValue);
  return !exception_state.is_exception_set();
}


const JSPropertySpec prototype_properties[] = {
  {  // Read/Write property
      "windowProperty", 0,
      JSPROP_SHARED | JSPROP_ENUMERATE,
      JSOP_WRAPPER(&get_windowProperty),
      JSOP_WRAPPER(&set_windowProperty),
  },
  JS_PS_END
};

const JSFunctionSpec prototype_functions[] = {
  {
      "getStackTrace",
      JSOP_WRAPPER(&fcn_getStackTrace),
      0,
      JSPROP_ENUMERATE,
      NULL,
  },
  {
      "windowOperation",
      JSOP_WRAPPER(&fcn_windowOperation),
      0,
      JSPROP_ENUMERATE,
      NULL,
  },
  JS_FS_END
};

const JSPropertySpec interface_object_properties[] = {
  JS_PS_END
};

const JSFunctionSpec interface_object_functions[] = {
  JS_FS_END
};

const JSPropertySpec own_properties[] = {
  JS_PS_END
};

void InitializePrototypeAndInterfaceObject(
    InterfaceData* interface_data, JSContext* context) {
  DCHECK(!interface_data->prototype);
  DCHECK(!interface_data->interface_object);

  MozjsGlobalObjectProxy* global_object_proxy =
      static_cast<MozjsGlobalObjectProxy*>(JS_GetContextPrivate(context));
  JS::RootedObject global_object(context, global_object_proxy->global_object());
  DCHECK(global_object);
  JS::RootedObject parent_prototype(
      context, bindings::testing::MozjsGlobalInterfaceParent::GetPrototype(context));
  DCHECK(parent_prototype);

  // Create the Prototype object.
  interface_data->prototype = JS_NewObjectWithGivenProto(
      context, &interface_data->prototype_class_definition, parent_prototype,
      NULL);
  bool success = JS_DefineProperties(
      context, interface_data->prototype, prototype_properties);
  DCHECK(success);
  success = JS_DefineFunctions(
      context, interface_data->prototype, prototype_functions);
  DCHECK(success);

  JS::RootedObject function_prototype(
      context, JS_GetFunctionPrototype(context, global_object));
  DCHECK(function_prototype);
  // Create the Interface object.
  interface_data->interface_object = JS_NewObjectWithGivenProto(
      context, &interface_data->interface_object_class_definition,
      function_prototype, NULL);

  // Add the InterfaceObject.name property.
  JS::RootedObject rooted_interface_object(
      context, interface_data->interface_object);
  JS::RootedValue name_value(context);
  const char name[] =
      "Window";
  name_value.setString(JS_NewStringCopyZ(context, name));
  success =
      JS_DefineProperty(context, rooted_interface_object, "name", name_value,
                        JS_PropertyStub, JS_StrictPropertyStub,
                        JSPROP_READONLY);
  DCHECK(success);

  // Define interface object properties (including constants).
  success = JS_DefineProperties(context, rooted_interface_object,
                                interface_object_properties);
  DCHECK(success);
  // Define interface object functions (static).
  success = JS_DefineFunctions(context, rooted_interface_object,
                               interface_object_functions);
  DCHECK(success);


  // Set the Prototype.constructor and Constructor.prototype properties.
  DCHECK(interface_data->interface_object);
  DCHECK(interface_data->prototype);
  JS::RootedObject rooted_prototype(context, interface_data->prototype);
  success = JS_LinkConstructorAndPrototype(
      context,
      rooted_interface_object,
      rooted_prototype);
  DCHECK(success);
}

InterfaceData* GetInterfaceData(JSContext* context) {
  MozjsGlobalObjectProxy* global_object_proxy =
      static_cast<MozjsGlobalObjectProxy*>(JS_GetContextPrivate(context));
  // Use the address of the properties definition for this interface as a
  // unique key for looking up the InterfaceData for this interface.
  intptr_t key = reinterpret_cast<intptr_t>(&own_properties);
  InterfaceData* interface_data = global_object_proxy->GetInterfaceData(key);
  if (!interface_data) {
    interface_data = CreateCachedInterfaceData();
    DCHECK(interface_data);
    global_object_proxy->CacheInterfaceData(key, interface_data);
    DCHECK_EQ(interface_data, global_object_proxy->GetInterfaceData(key));
  }
  return interface_data;
}

}  // namespace

JSObject* MozjsWindow::CreateProxy(
    JSContext* context, const scoped_refptr<Wrappable>& wrappable) {
  InterfaceData* interface_data = GetInterfaceData(context);
  JS::RootedObject global_object(
      context, JS_NewGlobalObject(context,
                                  &interface_data->instance_class_definition,
                                  NULL));
  DCHECK(global_object);

  // Initialize standard JS constructors prototypes and top-level functions such
  // as Object, isNan, etc.
  JSAutoCompartment auto_compartment(context, global_object);
  bool success = JS_InitStandardClasses(context, global_object);

  JS::RootedObject parent_prototype(
      context, JS_GetObjectPrototype(context, global_object));

  // Set the global object pointer, so we can access the standard classes such
  // as the base Object prototype when looking up our prototype.
  MozjsGlobalObjectProxy* global_object_proxy =
      static_cast<MozjsGlobalObjectProxy*>(JS_GetContextPrivate(context));
  global_object_proxy->SetGlobalObject(global_object);

  JS::RootedObject prototype(context, MozjsWindow::GetPrototype(context));
  DCHECK(prototype);
  JS_SetPrototype(context, global_object, prototype);

  // Add own properties.
  success = JS_DefineProperties(context, global_object, own_properties);
  DCHECK(success);

  JS::RootedObject proxy(context,
      ProxyHandler::NewProxy(context, global_object, prototype, NULL,
                             proxy_handler.Pointer()));
  WrapperPrivate::AddPrivateData(proxy, wrappable);
  return proxy;
}

//static
const JSClass* MozjsWindow::PrototypeClass(
      JSContext* context) {
  JS::RootedObject prototype(context, GetPrototype(context));
  JSClass* proto_class = JS_GetClass(*prototype.address());
  return proto_class;
}

// static
JSObject* MozjsWindow::GetPrototype(JSContext* context) {
  InterfaceData* interface_data = GetInterfaceData(context);
  if (!interface_data->prototype) {
    // Create new prototype that has all the props and methods
    InitializePrototypeAndInterfaceObject(interface_data, context);
  }
  DCHECK(interface_data->prototype);
  return interface_data->prototype;
}

// static
JSObject* MozjsWindow::GetInterfaceObject(JSContext* context) {
  InterfaceData* interface_data = GetInterfaceData(context);
  if (!interface_data->interface_object) {
    InitializePrototypeAndInterfaceObject(interface_data, context);
  }
  DCHECK(interface_data->interface_object);
  return interface_data->interface_object;
}


namespace {
}  // namespace


}  // namespace testing
}  // namespace bindings

namespace script {

template<>
void GlobalObjectProxy::CreateGlobalObject<Window>(
    const scoped_refptr<Window>& global_interface,
    EnvironmentSettings* environment_settings) {
  MozjsGlobalObjectProxy* mozjs_global_object_proxy =
      base::polymorphic_downcast<MozjsGlobalObjectProxy*>(this);
  JSContext* context = mozjs_global_object_proxy->context();

  JSAutoRequest auto_request(context);
  MozjsWindow::CreateProxy(
      context, global_interface);
  mozjs_global_object_proxy->SetEnvironmentSettings(environment_settings);

  WrapperFactory* wrapper_factory = mozjs_global_object_proxy->wrapper_factory();
  wrapper_factory->RegisterWrappableType(
      AnonymousIndexedGetterInterface::AnonymousIndexedGetterInterfaceWrappableType(),
      base::Bind(MozjsAnonymousIndexedGetterInterface::CreateProxy),
      base::Bind(MozjsAnonymousIndexedGetterInterface::PrototypeClass));
  wrapper_factory->RegisterWrappableType(
      AnonymousNamedGetterInterface::AnonymousNamedGetterInterfaceWrappableType(),
      base::Bind(MozjsAnonymousNamedGetterInterface::CreateProxy),
      base::Bind(MozjsAnonymousNamedGetterInterface::PrototypeClass));
  wrapper_factory->RegisterWrappableType(
      AnonymousNamedIndexedGetterInterface::AnonymousNamedIndexedGetterInterfaceWrappableType(),
      base::Bind(MozjsAnonymousNamedIndexedGetterInterface::CreateProxy),
      base::Bind(MozjsAnonymousNamedIndexedGetterInterface::PrototypeClass));
  wrapper_factory->RegisterWrappableType(
      ArbitraryInterface::ArbitraryInterfaceWrappableType(),
      base::Bind(MozjsArbitraryInterface::CreateProxy),
      base::Bind(MozjsArbitraryInterface::PrototypeClass));
  wrapper_factory->RegisterWrappableType(
      BaseInterface::BaseInterfaceWrappableType(),
      base::Bind(MozjsBaseInterface::CreateProxy),
      base::Bind(MozjsBaseInterface::PrototypeClass));
  wrapper_factory->RegisterWrappableType(
      BooleanTypeTestInterface::BooleanTypeTestInterfaceWrappableType(),
      base::Bind(MozjsBooleanTypeTestInterface::CreateProxy),
      base::Bind(MozjsBooleanTypeTestInterface::PrototypeClass));
  wrapper_factory->RegisterWrappableType(
      CallbackFunctionInterface::CallbackFunctionInterfaceWrappableType(),
      base::Bind(MozjsCallbackFunctionInterface::CreateProxy),
      base::Bind(MozjsCallbackFunctionInterface::PrototypeClass));
  wrapper_factory->RegisterWrappableType(
      CallbackInterfaceInterface::CallbackInterfaceInterfaceWrappableType(),
      base::Bind(MozjsCallbackInterfaceInterface::CreateProxy),
      base::Bind(MozjsCallbackInterfaceInterface::PrototypeClass));
#if defined(ENABLE_CONDITIONAL_INTERFACE)
  wrapper_factory->RegisterWrappableType(
      ConditionalInterface::ConditionalInterfaceWrappableType(),
      base::Bind(MozjsConditionalInterface::CreateProxy),
      base::Bind(MozjsConditionalInterface::PrototypeClass));
#endif  // defined(ENABLE_CONDITIONAL_INTERFACE)
  wrapper_factory->RegisterWrappableType(
      ConstantsInterface::ConstantsInterfaceWrappableType(),
      base::Bind(MozjsConstantsInterface::CreateProxy),
      base::Bind(MozjsConstantsInterface::PrototypeClass));
  wrapper_factory->RegisterWrappableType(
      ConstructorInterface::ConstructorInterfaceWrappableType(),
      base::Bind(MozjsConstructorInterface::CreateProxy),
      base::Bind(MozjsConstructorInterface::PrototypeClass));
  wrapper_factory->RegisterWrappableType(
      ConstructorWithArgumentsInterface::ConstructorWithArgumentsInterfaceWrappableType(),
      base::Bind(MozjsConstructorWithArgumentsInterface::CreateProxy),
      base::Bind(MozjsConstructorWithArgumentsInterface::PrototypeClass));
  wrapper_factory->RegisterWrappableType(
      DOMStringTestInterface::DOMStringTestInterfaceWrappableType(),
      base::Bind(MozjsDOMStringTestInterface::CreateProxy),
      base::Bind(MozjsDOMStringTestInterface::PrototypeClass));
  wrapper_factory->RegisterWrappableType(
      DerivedGetterSetterInterface::DerivedGetterSetterInterfaceWrappableType(),
      base::Bind(MozjsDerivedGetterSetterInterface::CreateProxy),
      base::Bind(MozjsDerivedGetterSetterInterface::PrototypeClass));
  wrapper_factory->RegisterWrappableType(
      DerivedInterface::DerivedInterfaceWrappableType(),
      base::Bind(MozjsDerivedInterface::CreateProxy),
      base::Bind(MozjsDerivedInterface::PrototypeClass));
#if defined(NO_ENABLE_CONDITIONAL_INTERFACE)
  wrapper_factory->RegisterWrappableType(
      DisabledInterface::DisabledInterfaceWrappableType(),
      base::Bind(MozjsDisabledInterface::CreateProxy),
      base::Bind(MozjsDisabledInterface::PrototypeClass));
#endif  // defined(NO_ENABLE_CONDITIONAL_INTERFACE)
  wrapper_factory->RegisterWrappableType(
      EnumerationInterface::EnumerationInterfaceWrappableType(),
      base::Bind(MozjsEnumerationInterface::CreateProxy),
      base::Bind(MozjsEnumerationInterface::PrototypeClass));
  wrapper_factory->RegisterWrappableType(
      ExceptionObjectInterface::ExceptionObjectInterfaceWrappableType(),
      base::Bind(MozjsExceptionObjectInterface::CreateProxy),
      base::Bind(MozjsExceptionObjectInterface::PrototypeClass));
  wrapper_factory->RegisterWrappableType(
      ExceptionsInterface::ExceptionsInterfaceWrappableType(),
      base::Bind(MozjsExceptionsInterface::CreateProxy),
      base::Bind(MozjsExceptionsInterface::PrototypeClass));
  wrapper_factory->RegisterWrappableType(
      ExtendedIDLAttributesInterface::ExtendedIDLAttributesInterfaceWrappableType(),
      base::Bind(MozjsExtendedIDLAttributesInterface::CreateProxy),
      base::Bind(MozjsExtendedIDLAttributesInterface::PrototypeClass));
  wrapper_factory->RegisterWrappableType(
      GetOpaqueRootInterface::GetOpaqueRootInterfaceWrappableType(),
      base::Bind(MozjsGetOpaqueRootInterface::CreateProxy),
      base::Bind(MozjsGetOpaqueRootInterface::PrototypeClass));
  wrapper_factory->RegisterWrappableType(
      GlobalInterfaceParent::GlobalInterfaceParentWrappableType(),
      base::Bind(MozjsGlobalInterfaceParent::CreateProxy),
      base::Bind(MozjsGlobalInterfaceParent::PrototypeClass));
  wrapper_factory->RegisterWrappableType(
      ImplementedInterface::ImplementedInterfaceWrappableType(),
      base::Bind(MozjsImplementedInterface::CreateProxy),
      base::Bind(MozjsImplementedInterface::PrototypeClass));
  wrapper_factory->RegisterWrappableType(
      IndexedGetterInterface::IndexedGetterInterfaceWrappableType(),
      base::Bind(MozjsIndexedGetterInterface::CreateProxy),
      base::Bind(MozjsIndexedGetterInterface::PrototypeClass));
  wrapper_factory->RegisterWrappableType(
      InterfaceWithUnsupportedProperties::InterfaceWithUnsupportedPropertiesWrappableType(),
      base::Bind(MozjsInterfaceWithUnsupportedProperties::CreateProxy),
      base::Bind(MozjsInterfaceWithUnsupportedProperties::PrototypeClass));
  wrapper_factory->RegisterWrappableType(
      NamedConstructorInterface::NamedConstructorInterfaceWrappableType(),
      base::Bind(MozjsNamedConstructorInterface::CreateProxy),
      base::Bind(MozjsNamedConstructorInterface::PrototypeClass));
  wrapper_factory->RegisterWrappableType(
      NamedGetterInterface::NamedGetterInterfaceWrappableType(),
      base::Bind(MozjsNamedGetterInterface::CreateProxy),
      base::Bind(MozjsNamedGetterInterface::PrototypeClass));
  wrapper_factory->RegisterWrappableType(
      NamedIndexedGetterInterface::NamedIndexedGetterInterfaceWrappableType(),
      base::Bind(MozjsNamedIndexedGetterInterface::CreateProxy),
      base::Bind(MozjsNamedIndexedGetterInterface::PrototypeClass));
  wrapper_factory->RegisterWrappableType(
      NestedPutForwardsInterface::NestedPutForwardsInterfaceWrappableType(),
      base::Bind(MozjsNestedPutForwardsInterface::CreateProxy),
      base::Bind(MozjsNestedPutForwardsInterface::PrototypeClass));
  wrapper_factory->RegisterWrappableType(
      NoConstructorInterface::NoConstructorInterfaceWrappableType(),
      base::Bind(MozjsNoConstructorInterface::CreateProxy),
      base::Bind(MozjsNoConstructorInterface::PrototypeClass));
  wrapper_factory->RegisterWrappableType(
      NoInterfaceObjectInterface::NoInterfaceObjectInterfaceWrappableType(),
      base::Bind(MozjsNoInterfaceObjectInterface::CreateProxy),
      base::Bind(MozjsNoInterfaceObjectInterface::PrototypeClass));
  wrapper_factory->RegisterWrappableType(
      NullableTypesTestInterface::NullableTypesTestInterfaceWrappableType(),
      base::Bind(MozjsNullableTypesTestInterface::CreateProxy),
      base::Bind(MozjsNullableTypesTestInterface::PrototypeClass));
  wrapper_factory->RegisterWrappableType(
      NumericTypesTestInterface::NumericTypesTestInterfaceWrappableType(),
      base::Bind(MozjsNumericTypesTestInterface::CreateProxy),
      base::Bind(MozjsNumericTypesTestInterface::PrototypeClass));
  wrapper_factory->RegisterWrappableType(
      ObjectTypeBindingsInterface::ObjectTypeBindingsInterfaceWrappableType(),
      base::Bind(MozjsObjectTypeBindingsInterface::CreateProxy),
      base::Bind(MozjsObjectTypeBindingsInterface::PrototypeClass));
  wrapper_factory->RegisterWrappableType(
      OperationsTestInterface::OperationsTestInterfaceWrappableType(),
      base::Bind(MozjsOperationsTestInterface::CreateProxy),
      base::Bind(MozjsOperationsTestInterface::PrototypeClass));
  wrapper_factory->RegisterWrappableType(
      PutForwardsInterface::PutForwardsInterfaceWrappableType(),
      base::Bind(MozjsPutForwardsInterface::CreateProxy),
      base::Bind(MozjsPutForwardsInterface::PrototypeClass));
  wrapper_factory->RegisterWrappableType(
      StaticPropertiesInterface::StaticPropertiesInterfaceWrappableType(),
      base::Bind(MozjsStaticPropertiesInterface::CreateProxy),
      base::Bind(MozjsStaticPropertiesInterface::PrototypeClass));
  wrapper_factory->RegisterWrappableType(
      StringifierAnonymousOperationInterface::StringifierAnonymousOperationInterfaceWrappableType(),
      base::Bind(MozjsStringifierAnonymousOperationInterface::CreateProxy),
      base::Bind(MozjsStringifierAnonymousOperationInterface::PrototypeClass));
  wrapper_factory->RegisterWrappableType(
      StringifierAttributeInterface::StringifierAttributeInterfaceWrappableType(),
      base::Bind(MozjsStringifierAttributeInterface::CreateProxy),
      base::Bind(MozjsStringifierAttributeInterface::PrototypeClass));
  wrapper_factory->RegisterWrappableType(
      StringifierOperationInterface::StringifierOperationInterfaceWrappableType(),
      base::Bind(MozjsStringifierOperationInterface::CreateProxy),
      base::Bind(MozjsStringifierOperationInterface::PrototypeClass));
  wrapper_factory->RegisterWrappableType(
      TargetInterface::TargetInterfaceWrappableType(),
      base::Bind(MozjsTargetInterface::CreateProxy),
      base::Bind(MozjsTargetInterface::PrototypeClass));
  wrapper_factory->RegisterWrappableType(
      UnionTypesInterface::UnionTypesInterfaceWrappableType(),
      base::Bind(MozjsUnionTypesInterface::CreateProxy),
      base::Bind(MozjsUnionTypesInterface::PrototypeClass));

}

// MSVS compiler does not need this explicit instantiation, and generates a
// compiler error.
#if !defined(_MSC_VER)
// Explicitly instantiate the template function for template type Window
// This is needed to prevent link errors when trying to resolve the template
// instantiation.
template
void GlobalObjectProxy::CreateGlobalObject<Window>(
    const scoped_refptr<Window>& global_interface,
    EnvironmentSettings* environment_settings);
#endif

}  // namespace script
}  // namespace cobalt
