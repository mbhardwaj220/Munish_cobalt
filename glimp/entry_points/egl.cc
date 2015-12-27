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

#include <EGL/egl.h>

#include "glimp/egl/config.h"
#include "glimp/egl/display.h"
#include "glimp/egl/display_registry.h"
#include "glimp/egl/error.h"
#include "glimp/egl/scoped_egl_lock.h"

namespace egl = glimp::egl;

namespace {
// This function will either return the Display object associated with the
// given EGLDisplay, or else set the appropriate EGL error and then return
// NULL.
egl::Display* GetDisplayOrSetError(EGLDisplay egl_display) {
  if (!egl::DisplayRegistry::Valid(egl_display)) {
    egl::SetError(EGL_BAD_DISPLAY);
    return NULL;
  }
  egl::Display* display = egl::DisplayRegistry::ToDisplay(egl_display);
  if (!display) {
    egl::SetError(EGL_NOT_INITIALIZED);
    return NULL;
  }

  return display;
}

}  // namespace

extern "C" {

EGLBoolean EGLAPIENTRY eglChooseConfig(EGLDisplay dpy,
                                       const EGLint* attrib_list,
                                       EGLConfig* configs,
                                       EGLint config_size,
                                       EGLint* num_config) {
  egl::ScopedEGLLock egl_lock;

  egl::Display* display = GetDisplayOrSetError(dpy);
  if (!display) {
    return false;
  }

  return display->ChooseConfig(attrib_list, configs, config_size, num_config);
}

EGLBoolean EGLAPIENTRY eglCopyBuffers(EGLDisplay dpy,
                                      EGLSurface surface,
                                      EGLNativePixmapType target) {
  egl::ScopedEGLLock egl_lock;
  return false;
}

EGLContext EGLAPIENTRY eglCreateContext(EGLDisplay dpy,
                                        EGLConfig config,
                                        EGLContext share_context,
                                        const EGLint* attrib_list) {
  egl::ScopedEGLLock egl_lock;
  return EGL_NO_CONTEXT;
}

EGLSurface EGLAPIENTRY eglCreatePbufferSurface(EGLDisplay dpy,
                                               EGLConfig config,
                                               const EGLint* attrib_list) {
  egl::ScopedEGLLock egl_lock;
  return EGL_NO_SURFACE;
}

EGLSurface EGLAPIENTRY eglCreatePixmapSurface(EGLDisplay dpy,
                                              EGLConfig config,
                                              EGLNativePixmapType pixmap,
                                              const EGLint* attrib_list) {
  egl::ScopedEGLLock egl_lock;
  return EGL_NO_SURFACE;
}

EGLSurface EGLAPIENTRY eglCreateWindowSurface(EGLDisplay dpy,
                                              EGLConfig config,
                                              EGLNativeWindowType win,
                                              const EGLint* attrib_list) {
  egl::ScopedEGLLock egl_lock;

  egl::Display* display = GetDisplayOrSetError(dpy);
  if (!display) {
    return EGL_NO_SURFACE;
  }

  return display->CreateWindowSurface(config, win, attrib_list);
}

EGLBoolean EGLAPIENTRY eglDestroyContext(EGLDisplay dpy, EGLContext ctx) {
  egl::ScopedEGLLock egl_lock;
  return false;
}

EGLBoolean EGLAPIENTRY eglDestroySurface(EGLDisplay dpy, EGLSurface surface) {
  egl::ScopedEGLLock egl_lock;

  egl::Display* display = GetDisplayOrSetError(dpy);
  if (!display) {
    return false;
  }

  return display->DestroySurface(surface);
}

EGLBoolean EGLAPIENTRY eglGetConfigAttrib(EGLDisplay dpy,
                                          EGLConfig config,
                                          EGLint attribute,
                                          EGLint* value) {
  egl::ScopedEGLLock egl_lock;
  return false;
}

EGLBoolean EGLAPIENTRY eglGetConfigs(EGLDisplay dpy,
                                     EGLConfig* configs,
                                     EGLint config_size,
                                     EGLint* num_config) {
  egl::ScopedEGLLock egl_lock;
  return false;
}

EGLDisplay EGLAPIENTRY eglGetCurrentDisplay(void) {
  egl::ScopedEGLLock egl_lock;
  return EGL_NO_DISPLAY;
}

EGLSurface EGLAPIENTRY eglGetCurrentSurface(EGLint readdraw) {
  egl::ScopedEGLLock egl_lock;
  return EGL_NO_SURFACE;
}

EGLDisplay EGLAPIENTRY eglGetDisplay(EGLNativeDisplayType display_id) {
  egl::ScopedEGLLock egl_lock;
  return egl::DisplayRegistry::GetDisplay(display_id);
}

EGLint EGLAPIENTRY eglGetError(void) {
  // No lock needed as this function accesses only thread local data.
  return egl::GetError();
}

EGLBoolean EGLAPIENTRY eglInitialize(EGLDisplay dpy,
                                     EGLint* major,
                                     EGLint* minor) {
  egl::ScopedEGLLock egl_lock;
  if (!egl::DisplayRegistry::Valid(dpy)) {
    egl::SetError(EGL_BAD_DISPLAY);
    return false;
  }
  if (!egl::DisplayRegistry::InitializeDisplay(dpy)) {
    egl::SetError(EGL_NOT_INITIALIZED);
    return false;
  }

  egl::Display* display = egl::DisplayRegistry::ToDisplay(dpy);
  display->GetVersionInfo(major, minor);

  egl::SetError(EGL_SUCCESS);
  return true;
}

EGLBoolean EGLAPIENTRY eglMakeCurrent(EGLDisplay dpy,
                                      EGLSurface draw,
                                      EGLSurface read,
                                      EGLContext ctx) {
  egl::ScopedEGLLock egl_lock;
  return false;
}

EGLBoolean EGLAPIENTRY eglQueryContext(EGLDisplay dpy,
                                       EGLContext ctx,
                                       EGLint attribute,
                                       EGLint* value) {
  egl::ScopedEGLLock egl_lock;
  return false;
}

const char* EGLAPIENTRY eglQueryString(EGLDisplay dpy, EGLint name) {
  egl::ScopedEGLLock egl_lock;
  return NULL;
}

EGLBoolean EGLAPIENTRY eglQuerySurface(EGLDisplay dpy,
                                       EGLSurface surface,
                                       EGLint attribute,
                                       EGLint* value) {
  egl::ScopedEGLLock egl_lock;
  return false;
}

EGLBoolean EGLAPIENTRY eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
  egl::ScopedEGLLock egl_lock;
  return false;
}

EGLBoolean EGLAPIENTRY eglTerminate(EGLDisplay dpy) {
  egl::ScopedEGLLock egl_lock;
  if (!egl::DisplayRegistry::Valid(dpy)) {
    egl::SetError(EGL_BAD_DISPLAY);
    return false;
  }

  egl::DisplayRegistry::TerminateDisplay(dpy);

  egl::SetError(EGL_SUCCESS);
  return true;
}

EGLBoolean EGLAPIENTRY eglWaitGL(void) {
  egl::ScopedEGLLock egl_lock;
  return false;
}

EGLBoolean EGLAPIENTRY eglWaitNative(EGLint engine) {
  egl::ScopedEGLLock egl_lock;
  return false;
}

EGLBoolean EGLAPIENTRY eglBindTexImage(EGLDisplay dpy,
                                       EGLSurface surface,
                                       EGLint buffer) {
  egl::ScopedEGLLock egl_lock;
  return false;
}

EGLBoolean EGLAPIENTRY eglReleaseTexImage(EGLDisplay dpy,
                                          EGLSurface surface,
                                          EGLint buffer) {
  egl::ScopedEGLLock egl_lock;
  return false;
}

EGLBoolean EGLAPIENTRY eglSurfaceAttrib(EGLDisplay dpy,
                                        EGLSurface surface,
                                        EGLint attribute,
                                        EGLint value) {
  egl::ScopedEGLLock egl_lock;
  return false;
}

EGLBoolean EGLAPIENTRY eglSwapInterval(EGLDisplay dpy, EGLint interval) {
  egl::ScopedEGLLock egl_lock;
  return false;
}

EGLBoolean EGLAPIENTRY eglBindAPI(EGLenum api) {
  egl::ScopedEGLLock egl_lock;
  return false;
}

EGLenum EGLAPIENTRY eglQueryAPI(void) {
  egl::ScopedEGLLock egl_lock;
  return 0;
}

EGLSurface EGLAPIENTRY
eglCreatePbufferFromClientBuffer(EGLDisplay dpy,
                                 EGLenum buftype,
                                 EGLClientBuffer buffer,
                                 EGLConfig config,
                                 const EGLint* attrib_list) {
  egl::ScopedEGLLock egl_lock;
  return EGL_NO_SURFACE;
}

EGLBoolean EGLAPIENTRY eglReleaseThread(void) {
  egl::ScopedEGLLock egl_lock;
  return false;
}

EGLBoolean EGLAPIENTRY eglWaitClient(void) {
  egl::ScopedEGLLock egl_lock;
  return false;
}

EGLContext EGLAPIENTRY eglGetCurrentContext(void) {
  egl::ScopedEGLLock egl_lock;
  return EGL_NO_CONTEXT;
}

EGLSync EGLAPIENTRY eglCreateSync(EGLDisplay dpy,
                                  EGLenum type,
                                  const EGLAttrib* attrib_list) {
  egl::ScopedEGLLock egl_lock;
  return 0;
}

EGLBoolean EGLAPIENTRY eglDestroySync(EGLDisplay dpy, EGLSync sync) {
  egl::ScopedEGLLock egl_lock;
  return false;
}

EGLint EGLAPIENTRY eglClientWaitSync(EGLDisplay dpy,
                                     EGLSync sync,
                                     EGLint flags,
                                     EGLTime timeout) {
  egl::ScopedEGLLock egl_lock;
  return 0;
}

EGLBoolean EGLAPIENTRY eglGetSyncAttrib(EGLDisplay dpy,
                                        EGLSync sync,
                                        EGLint attribute,
                                        EGLAttrib* value) {
  egl::ScopedEGLLock egl_lock;
  return false;
}

EGLImage EGLAPIENTRY eglCreateImage(EGLDisplay dpy,
                                    EGLContext ctx,
                                    EGLenum target,
                                    EGLClientBuffer buffer,
                                    const EGLAttrib* attrib_list) {
  egl::ScopedEGLLock egl_lock;
  return 0;
}

EGLBoolean EGLAPIENTRY eglDestroyImage(EGLDisplay dpy, EGLImage image) {
  egl::ScopedEGLLock egl_lock;
  return false;
}

EGLDisplay EGLAPIENTRY eglGetPlatformDisplay(EGLenum platform,
                                             void* native_display,
                                             const EGLAttrib* attrib_list) {
  egl::ScopedEGLLock egl_lock;
  return EGL_NO_DISPLAY;
}

EGLSurface EGLAPIENTRY
eglCreatePlatformWindowSurface(EGLDisplay dpy,
                               EGLConfig config,
                               void* native_window,
                               const EGLAttrib* attrib_list) {
  egl::ScopedEGLLock egl_lock;
  return EGL_NO_SURFACE;
}

EGLSurface EGLAPIENTRY
eglCreatePlatformPixmapSurface(EGLDisplay dpy,
                               EGLConfig config,
                               void* native_pixmap,
                               const EGLAttrib* attrib_list) {
  egl::ScopedEGLLock egl_lock;
  return EGL_NO_SURFACE;
}

EGLBoolean EGLAPIENTRY eglWaitSync(EGLDisplay dpy, EGLSync sync, EGLint flags) {
  egl::ScopedEGLLock egl_lock;
  return false;
}

__eglMustCastToProperFunctionPointerType EGLAPIENTRY
eglGetProcAddress(const char* procname) {
  egl::ScopedEGLLock egl_lock;
  return NULL;
}

}  // extern "C"
