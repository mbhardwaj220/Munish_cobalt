// This file was GENERATED by command:
//     pump.py callback_function.h.pump
// DO NOT EDIT BY HAND!!!


/*
 * Copyright 2015 Google Inc. All Rights Reserved.
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

#ifndef SCRIPT_CALLBACK_FUNCTION_H_
#define SCRIPT_CALLBACK_FUNCTION_H_

#include "base/callback.h"
#include "base/callback_internal.h"
#include "base/memory/ref_counted.h"

// Abstract template interface that represents an IDL callback function
// http://heycam.github.io/webidl/#idl-callback-functions
//
// The JavaScript implementation will instantiate a class that implements this
// interface, and will execute JavaScript code when the Run(...) function is
// executed.

namespace cobalt {
namespace script {

// First, we forward declare the CallbackFunction class template. This informs
// the compiler that the template only has 1 type parameter which is the
// function signature that the CallbackFunction is representing.
//
// See base/callback.h.pump for further discussion on this pattern.
template <typename Sig>
class CallbackFunction;

template <typename R>
class CallbackFunction<R(void)>
    : public base::RefCounted<CallbackFunction<R(void)> > {
 public:
  typedef R Signature(void);
  virtual R Run()
      const = 0;

 protected:
  virtual ~CallbackFunction() {}
  friend class base::RefCounted<CallbackFunction<Signature> >;
};

template <typename R, typename A1>
class CallbackFunction<R(A1)>
    : public base::RefCounted<CallbackFunction<R(A1)> > {
 public:
  typedef R Signature(A1);
  virtual R Run(
      typename base::internal::CallbackParamTraits<A1>::ForwardType a1)
      const = 0;

 protected:
  virtual ~CallbackFunction() {}
  friend class base::RefCounted<CallbackFunction<Signature> >;
};

template <typename R, typename A1, typename A2>
class CallbackFunction<R(A1, A2)>
    : public base::RefCounted<CallbackFunction<R(A1, A2)> > {
 public:
  typedef R Signature(A1, A2);
  virtual R Run(
      typename base::internal::CallbackParamTraits<A1>::ForwardType a1,
      typename base::internal::CallbackParamTraits<A2>::ForwardType a2)
      const = 0;

 protected:
  virtual ~CallbackFunction() {}
  friend class base::RefCounted<CallbackFunction<Signature> >;
};

template <typename R, typename A1, typename A2, typename A3>
class CallbackFunction<R(A1, A2, A3)>
    : public base::RefCounted<CallbackFunction<R(A1, A2, A3)> > {
 public:
  typedef R Signature(A1, A2, A3);
  virtual R Run(
      typename base::internal::CallbackParamTraits<A1>::ForwardType a1,
      typename base::internal::CallbackParamTraits<A2>::ForwardType a2,
      typename base::internal::CallbackParamTraits<A3>::ForwardType a3)
      const = 0;

 protected:
  virtual ~CallbackFunction() {}
  friend class base::RefCounted<CallbackFunction<Signature> >;
};

template <typename R, typename A1, typename A2, typename A3, typename A4>
class CallbackFunction<R(A1, A2, A3, A4)>
    : public base::RefCounted<CallbackFunction<R(A1, A2, A3, A4)> > {
 public:
  typedef R Signature(A1, A2, A3, A4);
  virtual R Run(
      typename base::internal::CallbackParamTraits<A1>::ForwardType a1,
      typename base::internal::CallbackParamTraits<A2>::ForwardType a2,
      typename base::internal::CallbackParamTraits<A3>::ForwardType a3,
      typename base::internal::CallbackParamTraits<A4>::ForwardType a4)
      const = 0;

 protected:
  virtual ~CallbackFunction() {}
  friend class base::RefCounted<CallbackFunction<Signature> >;
};

template <typename R, typename A1, typename A2, typename A3, typename A4,
    typename A5>
class CallbackFunction<R(A1, A2, A3, A4, A5)>
    : public base::RefCounted<CallbackFunction<R(A1, A2, A3, A4, A5)> > {
 public:
  typedef R Signature(A1, A2, A3, A4, A5);
  virtual R Run(
      typename base::internal::CallbackParamTraits<A1>::ForwardType a1,
      typename base::internal::CallbackParamTraits<A2>::ForwardType a2,
      typename base::internal::CallbackParamTraits<A3>::ForwardType a3,
      typename base::internal::CallbackParamTraits<A4>::ForwardType a4,
      typename base::internal::CallbackParamTraits<A5>::ForwardType a5)
      const = 0;

 protected:
  virtual ~CallbackFunction() {}
  friend class base::RefCounted<CallbackFunction<Signature> >;
};

template <typename R, typename A1, typename A2, typename A3, typename A4,
    typename A5, typename A6>
class CallbackFunction<R(A1, A2, A3, A4, A5, A6)>
    : public base::RefCounted<CallbackFunction<R(A1, A2, A3, A4, A5, A6)> > {
 public:
  typedef R Signature(A1, A2, A3, A4, A5, A6);
  virtual R Run(
      typename base::internal::CallbackParamTraits<A1>::ForwardType a1,
      typename base::internal::CallbackParamTraits<A2>::ForwardType a2,
      typename base::internal::CallbackParamTraits<A3>::ForwardType a3,
      typename base::internal::CallbackParamTraits<A4>::ForwardType a4,
      typename base::internal::CallbackParamTraits<A5>::ForwardType a5,
      typename base::internal::CallbackParamTraits<A6>::ForwardType a6)
      const = 0;

 protected:
  virtual ~CallbackFunction() {}
  friend class base::RefCounted<CallbackFunction<Signature> >;
};

template <typename R, typename A1, typename A2, typename A3, typename A4,
    typename A5, typename A6, typename A7>
class CallbackFunction<R(A1, A2, A3, A4, A5, A6, A7)>
    : public base::RefCounted<CallbackFunction<R(A1, A2, A3, A4, A5, A6,
        A7)> > {
 public:
  typedef R Signature(A1, A2, A3, A4, A5, A6, A7);
  virtual R Run(
      typename base::internal::CallbackParamTraits<A1>::ForwardType a1,
      typename base::internal::CallbackParamTraits<A2>::ForwardType a2,
      typename base::internal::CallbackParamTraits<A3>::ForwardType a3,
      typename base::internal::CallbackParamTraits<A4>::ForwardType a4,
      typename base::internal::CallbackParamTraits<A5>::ForwardType a5,
      typename base::internal::CallbackParamTraits<A6>::ForwardType a6,
      typename base::internal::CallbackParamTraits<A7>::ForwardType a7)
      const = 0;

 protected:
  virtual ~CallbackFunction() {}
  friend class base::RefCounted<CallbackFunction<Signature> >;
};


}  // namespace script
}  // namespace cobalt

#endif  // SCRIPT_CALLBACK_FUNCTION_H_
