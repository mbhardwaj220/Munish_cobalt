// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Windows doesn't support pthread_key_create's destr_function, and in fact
// it's a bit tricky to get code to run when a thread exits.  This is
// cargo-cult magic from http://www.codeproject.com/threads/tls.asp.
// We are trying to be compatible with both a LoadLibrary style invocation, as
// well as static linking. This code only needs to be included if we use
// LoadLibrary, but it hooks into the "standard" set of TLS callbacks that are
// provided for static linking.

// This code is deliberately written to match the style of calls seen in
// base/threading/thread_local_storage_win.cc.  Please keep the two in sync if
// coding conventions are changed.

// WARNING: Do *NOT* try to include this in the construction of the base
// library, even though it potentially drives code in
// base/threading/thread_local_storage_win.cc.  If you do, some users will end
// up getting duplicate definition of DllMain() in some of their later links.

// Force a reference to _tls_used to make the linker create the TLS directory
// if it's not already there (that is, even if __declspec(thread) is not used).
// To make sure we really traverse the whole list, we put down two elements, and
// then check that we called both functions when we scanned the list.
// Force a reference to p_thread_callback_dllmain_first_entry and
// p_thread_callback_dllmain_first_entry to prevent whole program optimization
// from discarding the variables.

#include <windows.h>

#include "base/logging.h"

// Indicate if another service is scanning the callbacks.  When this becomes
// set to true, then DllMain() will stop supporting the callback service. This
// value is set to true the first time any of our callbacks are called, as that
// shows that some other service is handling callbacks.
static bool linker_notifications_are_active = false;

// This will be our mostly no-op callback that we'll list (twice).  We won't
// deliberately call it, and if it is called, that means we don't need to do any
// of the callbacks anymore.  We expect such a call to arrive via a
// THREAD_ATTACH message, long before we'd have to perform our THREAD_DETACH
// callbacks.
static void NTAPI on_callback(PVOID h, DWORD reason, PVOID reserved);

#ifdef _WIN64

#pragma comment(linker, "/INCLUDE:_tls_used")
#pragma comment(linker, "/INCLUDE:p_thread_callback_dllmain_first_entry")
#pragma comment(linker, "/INCLUDE:p_thread_callback_dllmain_later_entry")

#else  // _WIN64

#pragma comment(linker, "/INCLUDE:__tls_used")
#pragma comment(linker, "/INCLUDE:_p_thread_callback_dllmain_first_entry")
#pragma comment(linker, "/INCLUDE:_p_thread_callback_dllmain_later_entry")

#endif  // _WIN64

// extern "C" suppresses C++ name mangling so we know the symbol names for the
// linker /INCLUDE:symbol pragmas above.
extern "C" {
#ifdef _WIN64

// .CRT section is merged with .rdata on x64 so it must be constant data.
#pragma data_seg(push, old_seg)
// Use earliest possible name in the .CRT$XL? list of segments.
#pragma const_seg(".CRT$XLA")
// When defining a const variable, it must have external linkage to be sure the
// linker doesn't discard it.
extern const PIMAGE_TLS_CALLBACK p_thread_callback_dllmain_first_entry;
const PIMAGE_TLS_CALLBACK p_thread_callback_dllmain_first_entry = on_callback;
// The latest possible name in the .CRT$XL? (other than *Z, which has a NULL).
#pragma const_seg(".CRT$XLY")
extern const PIMAGE_TLS_CALLBACK p_thread_callback_dllmain_later_entry;
const PIMAGE_TLS_CALLBACK p_thread_callback_dllmain_later_entry = on_callback;
#pragma data_seg(pop, old_seg)

#else  // _WIN64

#pragma data_seg(push, old_seg)
// Use earliest possible name in the .CRT$XL? list of segments.
#pragma data_seg(".CRT$XLA")
PIMAGE_TLS_CALLBACK p_thread_callback_dllmain_first_entry = on_callback;
// The latest possible name in the .CRT$XL? (other than *Z, which has a NULL).
#pragma data_seg(".CRT$XLY")
PIMAGE_TLS_CALLBACK p_thread_callback_dllmain_later_entry = on_callback;
#pragma data_seg(pop, old_seg)

#endif  // _WIN64
}  // extern "C"


// Make DllMain call the listed callbacks.  This way any third parties that are
// linked in will also be called.
BOOL WINAPI DllMain(PVOID h, DWORD reason, PVOID reserved) {
  if (DLL_THREAD_DETACH != reason && DLL_PROCESS_DETACH != reason)
    return true;  // We won't service THREAD_ATTACH calls.

  if (linker_notifications_are_active)
    return true;  // Some other service is doing this work.

  // Use our first entry as a starting point, but don't call it.
  PIMAGE_TLS_CALLBACK* it = &p_thread_callback_dllmain_first_entry;
  while(*++it) {
    if (*it == p_thread_callback_dllmain_later_entry)
      continue;  // Don't bother to call our own callbacks.
    (*it)(h, reason, reserved);
  }
  // Guarantee that we did a full list, and didn't get "stuck" on some NULL
  // ahead of time.  The fear is that there migtht be another null in ".CRT$XLA"
  // the way there is guaranteed to be a NULL in ".CRT$XLZ"
  // We use a CHECK to ensure that the release bulid, no matter how created, is
  // compliant with this arrangement.
  CHECK_GT(*it, p_thread_callback_dllmain_later_entry);
  return true;
}

static void NTAPI on_callback(PVOID h, DWORD reason, PVOID reserved) {
  // Do nothing.  We were just a place holder in the list used to test that we
  // call all items.
  // If we are called, it means that some other system is scanning the callbacks
  // and we don't need to do so in DllMain().
  linker_notifications_are_active = true;
  // Note: If some other routine some how plays this same game... we could both
  // decide not to do the scanning <sigh>, but this trick should suppress
  // duplicate calls on Vista, where the runtime takes care of the callbacks,
  // and allow us to do the callbacks on XP, where we are currently devoid of
  // callbacks (due to an explicit LoadLibrary call).
}
