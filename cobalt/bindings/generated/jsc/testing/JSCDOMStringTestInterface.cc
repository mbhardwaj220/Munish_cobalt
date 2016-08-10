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
// Auto-generated from template: bindings/javascriptcore/templates/interface.cc.template

// clang-format off

#include "third_party/WebKit/Source/JavaScriptCore/config.h"

#include "JSCDOMStringTestInterface.h"

#include "base/debug/trace_event.h"
#include "cobalt/base/polymorphic_downcast.h"
#include "cobalt/script/global_object_proxy.h"
#include "cobalt/script/opaque_handle.h"
#include "cobalt/script/script_object.h"

#include "cobalt/script/javascriptcore/constructor_base.h"
#include "cobalt/script/javascriptcore/conversion_helpers.h"
#include "cobalt/script/javascriptcore/prototype_base.h"
#include "cobalt/script/javascriptcore/jsc_callback_function.h"
#include "cobalt/script/javascriptcore/jsc_callback_interface_holder.h"
#include "cobalt/script/javascriptcore/jsc_exception_state.h"
#include "cobalt/script/javascriptcore/jsc_global_object.h"
#include "cobalt/script/javascriptcore/jsc_global_object_proxy.h"
#include "cobalt/script/javascriptcore/jsc_object_handle.h"
#include "cobalt/script/javascriptcore/jsc_object_handle_holder.h"
#include "cobalt/script/javascriptcore/type_traits.h"
#include "cobalt/script/javascriptcore/util/binding_helpers.h"
#include "cobalt/script/javascriptcore/util/exception_helpers.h"
#include "third_party/WebKit/Source/JavaScriptCore/interpreter/Interpreter.h"
#include "third_party/WebKit/Source/JavaScriptCore/runtime/Error.h"
#include "third_party/WebKit/Source/JavaScriptCore/runtime/FunctionPrototype.h"
#include "third_party/WebKit/Source/JavaScriptCore/runtime/Identifier.h"
#include "third_party/WebKit/Source/JavaScriptCore/runtime/JSFunction.h"
#include "third_party/WebKit/Source/JavaScriptCore/runtime/JSGlobalObject.h"
#include "third_party/WebKit/Source/JavaScriptCore/runtime/ObjectPrototype.h"

namespace {
using cobalt::bindings::testing::DOMStringTestInterface;
using cobalt::bindings::testing::JSCDOMStringTestInterface;
using cobalt::script::CallbackInterfaceTraits;
using cobalt::script::GlobalObjectProxy;
using cobalt::script::OpaqueHandle;
using cobalt::script::OpaqueHandleHolder;
using cobalt::script::ScriptObject;
using cobalt::script::Wrappable;

using cobalt::script::javascriptcore::kConversionFlagNullable;
using cobalt::script::javascriptcore::kConversionFlagRestricted;
using cobalt::script::javascriptcore::kConversionFlagTreatNullAsEmptyString;
using cobalt::script::javascriptcore::kConversionFlagTreatUndefinedAsEmptyString;
using cobalt::script::javascriptcore::kNoConversionFlags;
using cobalt::script::javascriptcore::ConstructorBase;
using cobalt::script::javascriptcore::GetWrappableOrSetException;
using cobalt::script::javascriptcore::FromJSValue;
using cobalt::script::javascriptcore::FromWTFString;
using cobalt::script::javascriptcore::JSCCallbackFunction;
using cobalt::script::javascriptcore::JSCCallbackFunctionHolder;
using cobalt::script::javascriptcore::JSCCallbackInterfaceHolder;
using cobalt::script::javascriptcore::JSCEngine;
using cobalt::script::javascriptcore::JSCExceptionState;
using cobalt::script::javascriptcore::JSCObjectHandle;
using cobalt::script::javascriptcore::JSCObjectHandleHolder;
using cobalt::script::javascriptcore::JSCGlobalObject;
using cobalt::script::javascriptcore::JSCGlobalObjectProxy;
using cobalt::script::javascriptcore::JSObjectToWrappable;
using cobalt::script::javascriptcore::ScriptObjectRegistry;
using cobalt::script::javascriptcore::ToJSValue;
using cobalt::script::javascriptcore::ToWTFString;
using cobalt::script::javascriptcore::TypeTraits;
using cobalt::script::javascriptcore::PrototypeBase;
using cobalt::script::javascriptcore::ThreadLocalHashTable;
using cobalt::script::javascriptcore::WrapperBase;
using cobalt::script::javascriptcore::util::HasPropertyOnPrototype;
using cobalt::script::javascriptcore::util::GetStackTrace;
}  // namespace

namespace cobalt {
namespace bindings {
namespace testing {

namespace {
JSC::JSValue getJSproperty(
    JSC::ExecState* exec_state,
    JSC::JSValue slot_base,
    JSC::PropertyName property_name);
void setJSproperty(
    JSC::ExecState* exec,
    JSC::JSObject* this_object,
    JSC::JSValue value);
JSC::JSValue getJSreadOnlyProperty(
    JSC::ExecState* exec_state,
    JSC::JSValue slot_base,
    JSC::PropertyName property_name);
JSC::JSValue getJSreadOnlyTokenProperty(
    JSC::ExecState* exec_state,
    JSC::JSValue slot_base,
    JSC::PropertyName property_name);
JSC::JSValue getJSnullIsEmptyProperty(
    JSC::ExecState* exec_state,
    JSC::JSValue slot_base,
    JSC::PropertyName property_name);
void setJSnullIsEmptyProperty(
    JSC::ExecState* exec,
    JSC::JSObject* this_object,
    JSC::JSValue value);
JSC::JSValue getJSundefinedIsEmptyProperty(
    JSC::ExecState* exec_state,
    JSC::JSValue slot_base,
    JSC::PropertyName property_name);
void setJSundefinedIsEmptyProperty(
    JSC::ExecState* exec,
    JSC::JSObject* this_object,
    JSC::JSValue value);
JSC::JSValue getJSnullableUndefinedIsEmptyProperty(
    JSC::ExecState* exec_state,
    JSC::JSValue slot_base,
    JSC::PropertyName property_name);
void setJSnullableUndefinedIsEmptyProperty(
    JSC::ExecState* exec,
    JSC::JSObject* this_object,
    JSC::JSValue value);

// These are declared unconditionally, but only defined if needed by the
// interface.
JSC::JSValue NamedPropertyGetter(JSC::ExecState* exec_state,
    JSC::JSValue slot_base, JSC::PropertyName property_name);
void NamedPropertySetter(JSC::JSCell* cell, JSC::ExecState* exec_state,
    JSC::PropertyName property_name, JSC::JSValue jsc_value);
bool NamedPropertyDeleter(JSC::JSCell* cell, JSC::ExecState* exec_state,
    JSC::PropertyName property_name);
bool QueryNamedProperty(JSC::JSCell* cell, JSC::ExecState* exec_state,
    JSC::PropertyName property_name);
JSC::JSValue OnGetMissingProperty(JSC::ExecState* exec_state,
    JSC::JSValue slot_base, JSC::PropertyName property_name);
bool OnSetMissingProperty(JSC::JSCell* cell, JSC::ExecState* exec_state,
    JSC::PropertyName property_name, JSC::JSValue value);

const bool s_has_named_getter = false;
const bool s_has_named_setter = false;
#if !defined(COBALT_BUILD_TYPE_GOLD)
const bool s_use_debug_missing_property_handler = true;
#else
const bool s_use_debug_missing_property_handler = false;
#endif
}  // namespace

// Class that defines a JS Object representing this interface's Interface Object
// https://www.w3.org/TR/WebIDL/#interface-object
class JSCDOMStringTestInterface::InterfaceObject : public ConstructorBase {
 public:
  // Get the Interface Object. Will create a new Interface Object if necessary,
  // otherwise it will return the cached one.
  static JSC::JSObject* GetInstance(JSC::ExecState* exec);
  DECLARE_CLASSINFO();

  // Needed when JSC::OverridesGetOwnPropertySlot StructureFlag is set
  // Must be public so that it can be accessible from getStaticValueSlot<>.
  static bool getOwnPropertySlot(JSC::JSCell* cell, JSC::ExecState* exec,
                                 JSC::PropertyName property_name,
                                 JSC::PropertySlot& slot) {
    InterfaceObject* this_object = JSC::jsCast<InterfaceObject*>(cell);
    ASSERT_GC_OBJECT_INHERITS(this_object, &s_info);

    // Same process as JSC::getStaticPropertySlot<>, which is defined in Lookup.h
    // Since JSFunction::getOwnPropertySlot is protected, we can't call it from
    // the helper function.
    const JSC::HashEntry* entry =
        GetPropertyTable(exec)->entry(exec, property_name);

    if (!entry) // not found, forward to parent
      return Base::getOwnPropertySlot(this_object, exec, property_name, slot);

    if (entry->attributes() & JSC::Function)
        return setUpStaticFunctionSlot(exec, entry, this_object, property_name, slot);

    slot.setCacheableCustom(this_object, entry->propertyGetter());
    return true;
  }

  // static override. Needed to support setting a property.
  static void put(JSC::JSCell* cell, JSC::ExecState* exec_state,
                  JSC::PropertyName property_name, JSC::JSValue value,
                  JSC::PutPropertySlot& slot) {
    InterfaceObject* this_object = JSC::jsCast<InterfaceObject*>(cell);
    ASSERT_GC_OBJECT_INHERITS(this_object, &s_info);
    bool found_property = JSC::lookupPut<InterfaceObject>(
        exec_state, property_name, value, GetPropertyTable(exec_state),
        this_object, slot.isStrictMode());
    DLOG_IF(INFO, !found_property) << "Did not find property named " <<
        WTF::String(property_name.publicName()).utf8().data() <<
        " to set on interface object for JSCDOMStringTestInterface";
    if (!found_property) {
      BaseClass::put(cell, exec_state, property_name, value, slot);
    }
  }

  // static override. This prevents this object from being called as a normal
  // function, throwing a TypeError if the user attempts to do so.
  static JSC::CallType getCallData(JSC::JSCell*, JSC::CallData&) {
    return JSC::CallTypeNone;
  }

  // static override. This prevents this object from being called as a
  // constructor, throwing a TypeError if the user attempts to do so.
  //
  // This method is defined when no constructors are defined on the IDL.
  static JSC::ConstructType getConstructData(JSC::JSCell*, JSC::ConstructData&) {
    return JSC::ConstructTypeNone;
  }

 private:
  typedef ConstructorBase BaseClass;

  static const unsigned StructureFlags =
      JSC::ImplementsHasInstance |
      JSC::OverridesGetOwnPropertySlot |
      BaseClass::StructureFlags;

  InterfaceObject(JSC::ExecState* exec_state, JSC::JSGlobalObject* global_object, JSC::Structure* structure)
      : BaseClass(exec_state, global_object, structure) { }
  void finishCreation(JSC::ExecState* exec_state,
                      JSC::NativeExecutable* native_executable, int length,
                      const String& name);

  static const JSC::HashTable* GetPropertyTable(JSC::ExecState* exec_state);

  static const JSC::HashTableValue property_table_values[];
  static const JSC::HashTable property_table_prototype;
};

const JSC::HashTableValue JSCDOMStringTestInterface::InterfaceObject::property_table_values[] = {
    // static functions will also go here.
    { 0, 0, 0, 0, static_cast<JSC::Intrinsic>(0) }
};  // JSCDOMStringTestInterface::InterfaceObject::property_table_values

// static
const JSC::HashTable
JSCDOMStringTestInterface::InterfaceObject::property_table_prototype = {
    // Sizes will be calculated based on the number of static functions as well.
    2,  // compactSize
    1,  // compactSizeMask
    property_table_values,
    NULL  // table allocated at runtime
};  // JSCDOMStringTestInterface::InterfaceObject::property_table_prototype

// static
const JSC::HashTable*
JSCDOMStringTestInterface::InterfaceObject::GetPropertyTable(
    JSC::ExecState* exec_state) {
  return ThreadLocalHashTable::GetInstance()->GetHashTable(
      JSCDOMStringTestInterface::InterfaceObject::s_classinfo(),
      property_table_prototype);
}

const JSC::ClassInfo JSCDOMStringTestInterface::InterfaceObject::s_info = {
    "DOMStringTestInterfaceConstructor",  // className
    BaseClass::s_classinfo(),  // parentClass
    NULL,  // static hash-table of properties (not used)
    GetPropertyTable,  // function pointer to get hash-table of properties
    CREATE_METHOD_TABLE(JSCDOMStringTestInterface::InterfaceObject)
};  // JSCDOMStringTestInterface::InterfaceObject::s_info

void JSCDOMStringTestInterface::InterfaceObject::finishCreation(
    JSC::ExecState* exec_state, JSC::NativeExecutable* native_executable,
    int length, const String& name) {
  BaseClass::finishCreation(exec_state, native_executable, length, name);
  ASSERT(inherits(&s_info));
  // Add a 'prototype' property whose value is the prototype object.
  putDirect(exec_state->globalData(),
            exec_state->propertyNames().prototype,
            JSCDOMStringTestInterface::GetPrototype(exec_state->lexicalGlobalObject()),
            JSC::DontDelete | JSC::ReadOnly | JSC::DontEnum);
  DCHECK(hasOwnProperty(exec_state, JSC::Identifier(exec_state, "prototype")));
}

// static
JSC::JSObject* JSCDOMStringTestInterface::InterfaceObject::GetInstance(
    JSC::ExecState* exec_state) {
  JSCGlobalObject* global_object =
      static_cast<JSCGlobalObject*>(exec_state->lexicalGlobalObject());
  ASSERT_GC_OBJECT_INHERITS(global_object, JSCGlobalObject::s_classinfo());

  // Try to get the cached interface object, and create a new one if needed.
  JSC::JSObject* interface_object = global_object->object_cache()->GetCachedConstructor(&s_info);
  if (interface_object == NULL) {
    JSC::JSGlobalData& global_data = global_object->globalData();
    JSC::JSObject* parent_prototype = global_object->functionPrototype();
    JSC::TypeInfo type_info(JSC::ObjectType, StructureFlags);
    JSC::Structure* structure = JSC::Structure::create(
        global_data,
        global_object,
        JSC::JSValue(parent_prototype),
        type_info,
        &s_info);

    const int kNumArguments = 0;
    // NativeExecutable must be non-null even if this is not actually callable.
    JSC::NativeExecutable* executable = global_data.getHostFunction(NULL, NULL);

    // Create the new interface object.
    InterfaceObject* new_interface_object =
        new (NotNull, JSC::allocateCell<InterfaceObject>(global_data.heap))
        InterfaceObject(exec_state, global_object, structure);
    new_interface_object->finishCreation(exec_state, executable, kNumArguments, "DOMStringTestInterface");
    // Add the interface object to the cache.
    global_object->object_cache()->CacheConstructor(&s_info, new_interface_object);
    interface_object = new_interface_object;
  }
  DCHECK_EQ(global_object->object_cache()->GetCachedConstructor(&s_info), interface_object);
  return interface_object;
}

// End of JSCDOMStringTestInterface::InterfaceObject class

// Class that defines a JS Object representing this interface's prototype
class JSCDOMStringTestInterface::Prototype : public PrototypeBase {
 public:
  // Get the prototype. Will create a new prototype if necessary, otherwise it
  // will return a cached prototype.
  static JSC::JSObject* GetInstance(JSC::JSGlobalObject* global_object);
  DECLARE_CLASSINFO();

  // Needed when JSC::OverridesGetOwnPropertySlot StructureFlag is set
  // Must be public so that it can be accessible from getStaticValueSlot<>.
  static bool getOwnPropertySlot(JSC::JSCell*, JSC::ExecState*,
                                 JSC::PropertyName,
                                 JSC::PropertySlot&);

 private:
  typedef PrototypeBase BaseClass;

  static const unsigned StructureFlags =
      JSC::OverridesGetOwnPropertySlot |
      BaseClass::StructureFlags;

  Prototype(JSC::JSGlobalObject* global_object, JSC::Structure* structure)
      : BaseClass(global_object, structure) { }

  static JSC::JSValue GetConstructor(JSC::ExecState* exec_state,
      JSC::JSValue slot_base,
      JSC::PropertyName property_name);
  static const JSC::HashTable* GetPropertyTable(JSC::ExecState* exec_state);

  static const JSC::HashTableValue property_table_values[];
  static const JSC::HashTable property_table_prototype;
};

const JSC::HashTableValue JSCDOMStringTestInterface::Prototype::property_table_values[] = {
    { "constructor",
        JSC::DontDelete | JSC::DontEnum,
        reinterpret_cast<intptr_t>(JSCDOMStringTestInterface::Prototype::GetConstructor),
        static_cast<intptr_t>(0),
        JSC::NoIntrinsic
    },
    { 0, 0, 0, 0, static_cast<JSC::Intrinsic>(0) }
};  // JSCDOMStringTestInterface::Prototype::property_table_values

// static
const JSC::HashTable JSCDOMStringTestInterface::Prototype::property_table_prototype = {
    4,  // compactSize
    3,  // compactSizeMask
    property_table_values,
    NULL  // table allocated at runtime
};  // JSCDOMStringTestInterface::Prototype::property_table_prototype

// static
const JSC::HashTable* JSCDOMStringTestInterface::Prototype::GetPropertyTable(
    JSC::ExecState* exec_state) {
  return ThreadLocalHashTable::GetInstance()->GetHashTable(
      JSCDOMStringTestInterface::Prototype::s_classinfo(), property_table_prototype);
}

const JSC::ClassInfo JSCDOMStringTestInterface::Prototype::s_info = {
    "DOMStringTestInterfacePrototype",  // className
    BaseClass::s_classinfo(),  // parentClass
    NULL,  // static hash-table of properties (not used)
    GetPropertyTable,  // function pointer to get hash-table of properties
    CREATE_METHOD_TABLE(JSCDOMStringTestInterface::Prototype)
};  // JSCDOMStringTestInterface::Prototype::s_info

// Look up property slot for querying property values.
bool JSCDOMStringTestInterface::Prototype::getOwnPropertySlot(JSC::JSCell* cell,
    JSC::ExecState* exec, JSC::PropertyName property_name,
    JSC::PropertySlot& slot) {
  Prototype* this_object = JSC::jsCast<Prototype*>(cell);
  ASSERT_GC_OBJECT_INHERITS(this_object, &s_info);
  return JSC::getStaticPropertySlot<Prototype, JSC::JSObject>(
      exec, GetPropertyTable(exec), this_object, property_name, slot);
}

// static
JSC::JSObject* JSCDOMStringTestInterface::Prototype::GetInstance(
    JSC::JSGlobalObject* base_global_object) {
  JSCGlobalObject* global_object =
      static_cast<JSCGlobalObject*>(base_global_object);
  ASSERT_GC_OBJECT_INHERITS(global_object, JSCGlobalObject::s_classinfo());

  // Try to get the cached prototype, and create a new one if needed.
  JSC::JSObject* prototype = global_object->object_cache()->GetCachedPrototype(&s_info);
  if (prototype == NULL) {
    JSC::JSGlobalData& global_data = global_object->globalData();
    JSC::JSLockHolder lock(&global_data);

    JSC::JSObject* parent_prototype = global_object->objectPrototype();
    JSC::TypeInfo type_info(JSC::ObjectType, StructureFlags);
    JSC::Structure* structure = JSC::Structure::create(
        global_data,
        global_object,
        JSC::JSValue(parent_prototype),
        type_info,
        &s_info);

    // Create the new prototype object.
    Prototype* new_prototype =
        new (NotNull, JSC::allocateCell<Prototype>(
            global_data.heap))
        Prototype(global_object, structure);
    new_prototype->finishCreation(global_data);
    // Add the prototype to the cache.
    global_object->object_cache()->CachePrototype(&s_info, new_prototype);
    prototype = new_prototype;
  }
  DCHECK_EQ(global_object->object_cache()->GetCachedPrototype(&s_info), prototype);
  return prototype;
}

// End of JSCDOMStringTestInterface::Prototype class

const JSC::HashTableValue JSCDOMStringTestInterface::property_table_values[] = {
    { "property",
        JSC::DontDelete ,
        reinterpret_cast<intptr_t>(getJSproperty),
        reinterpret_cast<intptr_t>(setJSproperty),
        JSC::NoIntrinsic
    },
    { "readOnlyProperty",
        JSC::DontDelete | JSC::ReadOnly,
        reinterpret_cast<intptr_t>(getJSreadOnlyProperty),
        0,
        JSC::NoIntrinsic
    },
    { "readOnlyTokenProperty",
        JSC::DontDelete | JSC::ReadOnly,
        reinterpret_cast<intptr_t>(getJSreadOnlyTokenProperty),
        0,
        JSC::NoIntrinsic
    },
    { "nullIsEmptyProperty",
        JSC::DontDelete ,
        reinterpret_cast<intptr_t>(getJSnullIsEmptyProperty),
        reinterpret_cast<intptr_t>(setJSnullIsEmptyProperty),
        JSC::NoIntrinsic
    },
    { "undefinedIsEmptyProperty",
        JSC::DontDelete ,
        reinterpret_cast<intptr_t>(getJSundefinedIsEmptyProperty),
        reinterpret_cast<intptr_t>(setJSundefinedIsEmptyProperty),
        JSC::NoIntrinsic
    },
    { "nullableUndefinedIsEmptyProperty",
        JSC::DontDelete ,
        reinterpret_cast<intptr_t>(getJSnullableUndefinedIsEmptyProperty),
        reinterpret_cast<intptr_t>(setJSnullableUndefinedIsEmptyProperty),
        JSC::NoIntrinsic
    },
    { 0, 0, 0, 0, static_cast<JSC::Intrinsic>(0) }
};  // JSCDOMStringTestInterface::property_table_values

// static
const JSC::HashTable JSCDOMStringTestInterface::property_table_prototype = {
    21,  // compactSize
    15,  // compactSizeMask
    property_table_values,
    NULL  // table allocated at runtime
};  // JSCDOMStringTestInterface::property_table_prototype

// static
const JSC::HashTable* JSCDOMStringTestInterface::GetPropertyTable(
    JSC::ExecState* exec_state) {
  return ThreadLocalHashTable::GetInstance()->GetHashTable(
      JSCDOMStringTestInterface::s_classinfo(), property_table_prototype);
}

#ifdef __LB_SHELL__FORCE_LOGGING__
base::LazyInstance<JSCDOMStringTestInterface::NonTrivialStaticFields>
    JSCDOMStringTestInterface::non_trivial_static_fields = LAZY_INSTANCE_INITIALIZER;
#endif  // __LB_SHELL__FORCE_LOGGING__

const JSC::ClassInfo JSCDOMStringTestInterface::s_info = {
    "DOMStringTestInterface",  // className
    BaseClass::s_classinfo(),  // parentClass
    NULL,  // static hash-table of properties (not used)
    GetPropertyTable,  // function pointer to get hash-table of properties
    CREATE_METHOD_TABLE(JSCDOMStringTestInterface)
};  // JSCDOMStringTestInterface::s_info

// static
JSC::JSObject* JSCDOMStringTestInterface::GetPrototype(
    JSC::JSGlobalObject* global_object) {
  return Prototype::GetInstance(global_object);
}

// static
JSC::JSObject* JSCDOMStringTestInterface::GetConstructor(
    JSC::ExecState* exec_state) {
  return InterfaceObject::GetInstance(exec_state);
}

// static
JSC::JSValue JSCDOMStringTestInterface::Prototype::GetConstructor(
      JSC::ExecState* exec_state,
      JSC::JSValue slot_base,
      JSC::PropertyName property_name) {
  return JSC::JSValue(InterfaceObject::GetInstance(exec_state));
}

// static
JSC::JSObject* JSCDOMStringTestInterface::Create(
    JSCGlobalObject* global_object,
    const scoped_refptr<Wrappable>& wrappable) {
  if (!(wrappable->GetWrappableType() == DOMStringTestInterface::DOMStringTestInterfaceWrappableType())) {
    NOTREACHED() << "Type of wrappable does not match DOMStringTestInterface::DOMStringTestInterfaceWrappableType()";
    return NULL;
  }
  DOMStringTestInterface* impl_ptr =
      base::polymorphic_downcast<DOMStringTestInterface*>(wrappable.get());

  JSC::JSGlobalData& global_data = global_object->globalData();

  // Get or Create the prototype object for this interface.
  JSC::JSObject* prototype = Prototype::GetInstance(global_object);
  DCHECK(prototype);

  JSC::JSLockHolder lock(global_data);
  // Create a JSC::Structure object for this instance.
  JSC::TypeInfo type_info(JSC::ObjectType, StructureFlags);
  JSC::Structure* structure = JSC::Structure::create(
      global_data,
      global_object,
      JSC::JSValue(prototype),
      type_info,
      &s_info);

  // Instantiate a new garbage-collected wrapper object.
  JSCDOMStringTestInterface* wrapper =
      new (NotNull, JSC::allocateCell<JSCDOMStringTestInterface>(global_data.heap))
      JSCDOMStringTestInterface(
          &global_data,
          structure,
          global_object->script_object_registry(),
          make_scoped_refptr(impl_ptr));
  wrapper->finishCreation(global_data);
  return wrapper;
}
JSCDOMStringTestInterface::JSCDOMStringTestInterface(
    JSC::JSGlobalData* global_data,
    JSC::Structure* structure,
    ScriptObjectRegistry* script_object_registry,
    const scoped_refptr<DOMStringTestInterface>& impl)
    : BaseClass(global_data, structure, script_object_registry, impl) {
}

void JSCDOMStringTestInterface::finishCreation(JSC::JSGlobalData& global_data) {
  BaseClass::finishCreation(global_data);
  DCHECK(inherits(&s_info));
}

JSCDOMStringTestInterface::~JSCDOMStringTestInterface() {
  // Empty destructor
}

// Look up property slot for querying property values.
bool JSCDOMStringTestInterface::getOwnPropertySlot(JSC::JSCell* cell,
    JSC::ExecState* exec, JSC::PropertyName property_name,
    JSC::PropertySlot& slot) {
  JSCDOMStringTestInterface* this_object = JSC::jsCast<JSCDOMStringTestInterface*>(cell);
  ASSERT_GC_OBJECT_INHERITS(this_object, &s_info);
  bool found_property_slot = JSC::getStaticValueSlot<JSCDOMStringTestInterface, BaseClass>(
      exec, GetPropertyTable(exec), this_object, property_name, slot);
  if (s_has_named_getter || s_use_debug_missing_property_handler) {
    bool found_property_on_prototype_chain = false;
    if (!found_property_slot && cell->isObject()) {
      JSC::JSValue prototype_value = JSC::asObject(cell)->prototype();
      if (prototype_value.isObject()) {
        JSC::JSObject* prototype = JSC::asObject(prototype_value);
        found_property_on_prototype_chain =
            prototype->hasProperty(exec, property_name);
      }
    }
    if (s_has_named_getter) {
      if (!found_property_slot && !found_property_on_prototype_chain) {
        if (QueryNamedProperty(this_object, exec, property_name)) {
          slot.setCustom(cell, &NamedPropertyGetter);
          found_property_slot = true;
        }
      }
    }
    if (s_use_debug_missing_property_handler) {
      // The property was not found as an own-property, nor was it found on the
      // prototype chain, so set the missing property handler to be called
      // when getting this property value.
      if (!found_property_slot && !found_property_on_prototype_chain) {
        slot.setCustom(cell, &OnGetMissingProperty);
        found_property_slot = true;
      }
    }
  }
  return found_property_slot;
}

// Look up property slot and put the |value|.
void JSCDOMStringTestInterface::put(JSC::JSCell* cell, JSC::ExecState* exec,
    JSC::PropertyName property_name, JSC::JSValue value,
    JSC::PutPropertySlot& slot) {
  JSCDOMStringTestInterface* this_object = JSC::jsCast<JSCDOMStringTestInterface*>(cell);
  ASSERT_GC_OBJECT_INHERITS(this_object, &s_info);
  bool property_handled = false;
  if (s_has_named_setter || s_use_debug_missing_property_handler) {
    // Need to look up the property manually.
    bool has_property = HasOwnPropertyOrPrototypeProperty(
        cell, exec, property_name);

    if (s_has_named_setter) {
      // We didn't find the property on the object or prototype chain, so
      // set or create a new named property.
      if (!has_property) {
        std::string property_name_utf8 = FromWTFString(property_name.publicName());
        NamedPropertySetter(cell, exec, property_name, value);
        property_handled = true;
      }
    }
    if (s_use_debug_missing_property_handler) {
      if (!has_property && !property_handled) {
        property_handled = OnSetMissingProperty(cell, exec, property_name, value);
      }
    }
#ifdef __LB_SHELL__FORCE_LOGGING__
    std::string property_name_utf8 = FromWTFString(property_name.publicName());

    base::AutoLock lock(non_trivial_static_fields.Get().lock_);
    base::hash_set<std::string>& properties_warned_about =
        non_trivial_static_fields.Get().properties_warned_about;

    if (properties_warned_about.find(property_name_utf8) ==
        properties_warned_about.end()) {
      properties_warned_about.insert(property_name_utf8);
      WTF::String class_name = cell->className();
      DLOG_IF(WARNING, !has_property) << "Did not find property named " <<
              property_name_utf8 << " to set on wrapper for "
              << FromWTFString(class_name)
              << std::endl << StackTraceToString(GetStackTrace(exec, 32))
              << std::endl;
    }
#endif  // __LB_SHELL__FORCE_LOGGING__
  }

  if (!property_handled) {
    JSC::lookupPut<JSCDOMStringTestInterface, BaseClass>(
        exec, property_name, value, GetPropertyTable(exec), this_object, slot);
  }
}

bool JSCDOMStringTestInterface::HasOwnPropertyOrPrototypeProperty(
    JSC::JSCell* cell, JSC::ExecState* exec_state,
    JSC::PropertyName property_name) {
  JSCDOMStringTestInterface* this_object = JSC::jsCast<JSCDOMStringTestInterface*>(cell);
  JSC::PropertySlot lookup_slot;
  bool has_property = JSC::getStaticPropertySlot<JSCDOMStringTestInterface, BaseClass>(
      exec_state, GetPropertyTable(exec_state), this_object, property_name,
      lookup_slot);
  return has_property || HasPropertyOnPrototype(exec_state, cell, property_name);
}

namespace {

JSC::JSValue getJSproperty(
    JSC::ExecState* exec_state,
    JSC::JSValue slot_base,
    JSC::PropertyName property_name) {
  TRACE_EVENT0("JSCDOMStringTestInterface", "get property");
  JSCGlobalObject* global_object =
      JSC::jsCast<JSCGlobalObject*>(exec_state->lexicalGlobalObject());
  DOMStringTestInterface* impl =
      GetWrappableOrSetException<DOMStringTestInterface>(exec_state, slot_base);
  if (!impl) {
    return exec_state->exception();
  }

  JSC::JSValue result = ToJSValue(
      global_object,
      impl->property());
  return result;
}

void setJSproperty(
    JSC::ExecState* exec_state,
    JSC::JSObject* this_object,
    JSC::JSValue value) {
  TRACE_EVENT0("JSCDOMStringTestInterface", "set property");
  JSCGlobalObject* global_object =
      JSC::jsCast<JSCGlobalObject*>(exec_state->lexicalGlobalObject());
  JSCExceptionState exception_state(global_object);
  DOMStringTestInterface* impl =
      GetWrappableOrSetException<DOMStringTestInterface>(exec_state, this_object);
  if (!impl) {
    return;
  }
  TypeTraits<std::string >::ConversionType cobalt_value;
  FromJSValue(exec_state, value,
      kNoConversionFlags, &exception_state,
      &cobalt_value);
  if (exception_state.is_exception_set()) {
    JSC::throwError(exec_state, exception_state.exception_object());
    return;
  }
  // Check if argument conversion raised an exception.
  if (!exec_state->hadException()) {
    impl->set_property(cobalt_value);
  }
}

JSC::JSValue getJSreadOnlyProperty(
    JSC::ExecState* exec_state,
    JSC::JSValue slot_base,
    JSC::PropertyName property_name) {
  TRACE_EVENT0("JSCDOMStringTestInterface", "get readOnlyProperty");
  JSCGlobalObject* global_object =
      JSC::jsCast<JSCGlobalObject*>(exec_state->lexicalGlobalObject());
  DOMStringTestInterface* impl =
      GetWrappableOrSetException<DOMStringTestInterface>(exec_state, slot_base);
  if (!impl) {
    return exec_state->exception();
  }

  JSC::JSValue result = ToJSValue(
      global_object,
      impl->read_only_property());
  return result;
}

JSC::JSValue getJSreadOnlyTokenProperty(
    JSC::ExecState* exec_state,
    JSC::JSValue slot_base,
    JSC::PropertyName property_name) {
  TRACE_EVENT0("JSCDOMStringTestInterface", "get readOnlyTokenProperty");
  JSCGlobalObject* global_object =
      JSC::jsCast<JSCGlobalObject*>(exec_state->lexicalGlobalObject());
  DOMStringTestInterface* impl =
      GetWrappableOrSetException<DOMStringTestInterface>(exec_state, slot_base);
  if (!impl) {
    return exec_state->exception();
  }

  JSC::JSValue result = ToJSValue(
      global_object,
      impl->read_only_token_property());
  return result;
}

JSC::JSValue getJSnullIsEmptyProperty(
    JSC::ExecState* exec_state,
    JSC::JSValue slot_base,
    JSC::PropertyName property_name) {
  TRACE_EVENT0("JSCDOMStringTestInterface", "get nullIsEmptyProperty");
  JSCGlobalObject* global_object =
      JSC::jsCast<JSCGlobalObject*>(exec_state->lexicalGlobalObject());
  DOMStringTestInterface* impl =
      GetWrappableOrSetException<DOMStringTestInterface>(exec_state, slot_base);
  if (!impl) {
    return exec_state->exception();
  }

  JSC::JSValue result = ToJSValue(
      global_object,
      impl->null_is_empty_property());
  return result;
}

void setJSnullIsEmptyProperty(
    JSC::ExecState* exec_state,
    JSC::JSObject* this_object,
    JSC::JSValue value) {
  TRACE_EVENT0("JSCDOMStringTestInterface", "set nullIsEmptyProperty");
  JSCGlobalObject* global_object =
      JSC::jsCast<JSCGlobalObject*>(exec_state->lexicalGlobalObject());
  JSCExceptionState exception_state(global_object);
  DOMStringTestInterface* impl =
      GetWrappableOrSetException<DOMStringTestInterface>(exec_state, this_object);
  if (!impl) {
    return;
  }
  TypeTraits<std::string >::ConversionType cobalt_value;
  FromJSValue(exec_state, value,
      (kConversionFlagTreatNullAsEmptyString), &exception_state,
      &cobalt_value);
  if (exception_state.is_exception_set()) {
    JSC::throwError(exec_state, exception_state.exception_object());
    return;
  }
  // Check if argument conversion raised an exception.
  if (!exec_state->hadException()) {
    impl->set_null_is_empty_property(cobalt_value);
  }
}

JSC::JSValue getJSundefinedIsEmptyProperty(
    JSC::ExecState* exec_state,
    JSC::JSValue slot_base,
    JSC::PropertyName property_name) {
  TRACE_EVENT0("JSCDOMStringTestInterface", "get undefinedIsEmptyProperty");
  JSCGlobalObject* global_object =
      JSC::jsCast<JSCGlobalObject*>(exec_state->lexicalGlobalObject());
  DOMStringTestInterface* impl =
      GetWrappableOrSetException<DOMStringTestInterface>(exec_state, slot_base);
  if (!impl) {
    return exec_state->exception();
  }

  JSC::JSValue result = ToJSValue(
      global_object,
      impl->undefined_is_empty_property());
  return result;
}

void setJSundefinedIsEmptyProperty(
    JSC::ExecState* exec_state,
    JSC::JSObject* this_object,
    JSC::JSValue value) {
  TRACE_EVENT0("JSCDOMStringTestInterface", "set undefinedIsEmptyProperty");
  JSCGlobalObject* global_object =
      JSC::jsCast<JSCGlobalObject*>(exec_state->lexicalGlobalObject());
  JSCExceptionState exception_state(global_object);
  DOMStringTestInterface* impl =
      GetWrappableOrSetException<DOMStringTestInterface>(exec_state, this_object);
  if (!impl) {
    return;
  }
  TypeTraits<std::string >::ConversionType cobalt_value;
  FromJSValue(exec_state, value,
      (kConversionFlagTreatUndefinedAsEmptyString), &exception_state,
      &cobalt_value);
  if (exception_state.is_exception_set()) {
    JSC::throwError(exec_state, exception_state.exception_object());
    return;
  }
  // Check if argument conversion raised an exception.
  if (!exec_state->hadException()) {
    impl->set_undefined_is_empty_property(cobalt_value);
  }
}

JSC::JSValue getJSnullableUndefinedIsEmptyProperty(
    JSC::ExecState* exec_state,
    JSC::JSValue slot_base,
    JSC::PropertyName property_name) {
  TRACE_EVENT0("JSCDOMStringTestInterface", "get nullableUndefinedIsEmptyProperty");
  JSCGlobalObject* global_object =
      JSC::jsCast<JSCGlobalObject*>(exec_state->lexicalGlobalObject());
  DOMStringTestInterface* impl =
      GetWrappableOrSetException<DOMStringTestInterface>(exec_state, slot_base);
  if (!impl) {
    return exec_state->exception();
  }

  JSC::JSValue result = ToJSValue(
      global_object,
      impl->nullable_undefined_is_empty_property());
  return result;
}

void setJSnullableUndefinedIsEmptyProperty(
    JSC::ExecState* exec_state,
    JSC::JSObject* this_object,
    JSC::JSValue value) {
  TRACE_EVENT0("JSCDOMStringTestInterface", "set nullableUndefinedIsEmptyProperty");
  JSCGlobalObject* global_object =
      JSC::jsCast<JSCGlobalObject*>(exec_state->lexicalGlobalObject());
  JSCExceptionState exception_state(global_object);
  DOMStringTestInterface* impl =
      GetWrappableOrSetException<DOMStringTestInterface>(exec_state, this_object);
  if (!impl) {
    return;
  }
  TypeTraits<base::optional<std::string > >::ConversionType cobalt_value;
  FromJSValue(exec_state, value,
      (kConversionFlagNullable | kConversionFlagTreatUndefinedAsEmptyString), &exception_state,
      &cobalt_value);
  if (exception_state.is_exception_set()) {
    JSC::throwError(exec_state, exception_state.exception_object());
    return;
  }
  // Check if argument conversion raised an exception.
  if (!exec_state->hadException()) {
    impl->set_nullable_undefined_is_empty_property(cobalt_value);
  }
}
JSC::JSValue NamedPropertyGetter(JSC::ExecState* exec_state,
    JSC::JSValue slot_base, JSC::PropertyName property_name) {
  NOTREACHED();
  return JSC::jsUndefined();
}
bool QueryNamedProperty(JSC::JSCell* cell, JSC::ExecState* exec_state,
    JSC::PropertyName property_name) {
  NOTREACHED();
  return false;
}
void NamedPropertySetter(JSC::JSCell* cell, JSC::ExecState* exec_state,
    JSC::PropertyName property_name, JSC::JSValue jsc_value) {
  NOTREACHED();
}

bool NamedPropertyDeleter(JSC::JSCell* cell, JSC::ExecState* exec_state,
    JSC::PropertyName property_name) {
  return false;
}

#if !defined(COBALT_BUILD_TYPE_GOLD)
JSC::JSValue OnGetMissingProperty(JSC::ExecState* exec_state,
    JSC::JSValue slot_base, JSC::PropertyName property_name) {
  JSCGlobalObject* global_object =
      JSC::jsCast<JSCGlobalObject*>(exec_state->lexicalGlobalObject());
  JSC::JSValue callable = global_object->get(
      exec_state, JSC::Identifier(exec_state, "__onGetMissingProperty"));
  if (!callable.isUndefined()) {
    JSC::CallData call_data;
    JSC::CallType call_type = JSC::getCallData(callable, call_data);
    if (call_type != JSC::CallTypeNone) {
      // The function called __onGetMissingProperty exists, so call this and
      // return the result as the value for this property.
      JSC::MarkedArgumentBuffer args;
      args.append(slot_base);
      args.append(JSC::JSValue(
              JSC::JSString::create(
                  global_object->globalData(), property_name.publicName())));
      JSC::JSValue retval = JSC::call(
          exec_state, callable, call_type, call_data, global_object, args);
      return retval;
    }
  }
  return JSC::jsUndefined();
}

bool OnSetMissingProperty(JSC::JSCell* cell, JSC::ExecState* exec_state,
    JSC::PropertyName property_name, JSC::JSValue value) {
  JSCGlobalObject* global_object =
      JSC::jsCast<JSCGlobalObject*>(exec_state->lexicalGlobalObject());
  JSC::JSValue callable = global_object->get(
      exec_state, JSC::Identifier(exec_state, "__onSetMissingProperty"));
  if (!callable.isUndefined()) {
    JSC::CallData call_data;
    JSC::CallType call_type = JSC::getCallData(callable, call_data);
    if (call_type != JSC::CallTypeNone) {
      // The function called __onSetMissingProperty exists, so call this with
      // the value to be set. The missing property handler returns true if it
      // has handled the setting of this property.
      JSC::MarkedArgumentBuffer args;
      args.append(cell);
      args.append(JSC::JSValue(
              JSC::JSString::create(
                  global_object->globalData(), property_name.publicName())));
      args.append(value);
      JSC::JSValue retval = JSC::call(
          exec_state, callable, call_type, call_data, global_object, args);
      return retval.toBoolean(exec_state);
    }
  }
  return false;
}
#else
JSC::JSValue OnGetMissingProperty(JSC::ExecState* exec_state,
    JSC::JSValue slot_base, JSC::PropertyName property_name) {
  NOTREACHED();
  return JSC::jsUndefined();
}
bool OnSetMissingProperty(JSC::JSCell* cell, JSC::ExecState* exec_state,
    JSC::PropertyName property_name, JSC::JSValue value) {
  NOTREACHED();
  return false;
}
#endif
}  // namespace

}  // namespace testing
}  // namespace bindings
}  // namespace cobalt
