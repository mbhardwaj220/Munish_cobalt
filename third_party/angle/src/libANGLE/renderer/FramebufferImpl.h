//
// Copyright 2014 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// FramebufferImpl.h: Defines the abstract rx::FramebufferImpl class.

#ifndef LIBANGLE_RENDERER_FRAMEBUFFERIMPL_H_
#define LIBANGLE_RENDERER_FRAMEBUFFERIMPL_H_

#include "angle_gl.h"
#include "common/angleutils.h"
#include "libANGLE/Error.h"
#include "libANGLE/Framebuffer.h"

namespace gl
{
class State;
class Framebuffer;
class FramebufferAttachment;
struct Rectangle;
}

namespace rx
{
class DisplayImpl;

class FramebufferImpl : angle::NonCopyable
{
  public:
    explicit FramebufferImpl(const gl::FramebufferState &state) : mState(state) {}
    virtual ~FramebufferImpl() {}
    virtual void destroy(ContextImpl *contextImpl) {}
    virtual void destroyDefault(DisplayImpl *displayImpl) {}

    virtual gl::Error discard(size_t count, const GLenum *attachments)    = 0;
    virtual gl::Error invalidate(size_t count, const GLenum *attachments) = 0;
    virtual gl::Error invalidateSub(size_t count,
                                    const GLenum *attachments,
                                    const gl::Rectangle &area) = 0;

    virtual gl::Error clear(ContextImpl *context, GLbitfield mask) = 0;
    virtual gl::Error clearBufferfv(ContextImpl *context,
                                    GLenum buffer,
                                    GLint drawbuffer,
                                    const GLfloat *values) = 0;
    virtual gl::Error clearBufferuiv(ContextImpl *context,
                                     GLenum buffer,
                                     GLint drawbuffer,
                                     const GLuint *values) = 0;
    virtual gl::Error clearBufferiv(ContextImpl *context,
                                    GLenum buffer,
                                    GLint drawbuffer,
                                    const GLint *values) = 0;
    virtual gl::Error clearBufferfi(ContextImpl *context,
                                    GLenum buffer,
                                    GLint drawbuffer,
                                    GLfloat depth,
                                    GLint stencil) = 0;

    virtual GLenum getImplementationColorReadFormat() const = 0;
    virtual GLenum getImplementationColorReadType() const   = 0;
    virtual gl::Error readPixels(ContextImpl *context,
                                 const gl::Rectangle &area,
                                 GLenum format,
                                 GLenum type,
                                 void *pixels) const = 0;

    virtual gl::Error blit(ContextImpl *context,
                           const gl::Rectangle &sourceArea,
                           const gl::Rectangle &destArea,
                           GLbitfield mask,
                           GLenum filter) = 0;

    virtual bool checkStatus() const = 0;

    virtual void syncState(ContextImpl *contextImpl,
                           const gl::Framebuffer::DirtyBits &dirtyBits) = 0;

    virtual gl::Error getSamplePosition(size_t index, GLfloat *xy) const = 0;

    const gl::FramebufferState &getState() const { return mState; }

  protected:
    const gl::FramebufferState &mState;
};
}

#endif  // LIBANGLE_RENDERER_FRAMEBUFFERIMPL_H_
