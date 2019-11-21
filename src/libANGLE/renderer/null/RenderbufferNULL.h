//
// Copyright 2016 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// RenderbufferNULL.h:
//    Defines the class interface for RenderbufferNULL, implementing RenderbufferImpl.
//

#ifndef LIBANGLE_RENDERER_NULL_RENDERBUFFERNULL_H_
#define LIBANGLE_RENDERER_NULL_RENDERBUFFERNULL_H_

#include "libANGLE/renderer/RenderbufferImpl.h"

namespace rx
{

class RenderbufferNULL : public RenderbufferImpl
{
  public:
    RenderbufferNULL(const gl::RenderbufferState &state);
    ~RenderbufferNULL() override;

    angle::Result setStorage(const gl::Context *context,
                             GLenum internalformat,
                             size_t width,
                             size_t height) override;
    angle::Result setStorageMultisample(const gl::Context *context,
                                        size_t samples,
                                        GLenum internalformat,
                                        size_t width,
                                        size_t height) override;

    angle::Result setStorageEGLImageTarget(const gl::Context *context, egl::Image *image) override;

    angle::Result initializeContents(const gl::Context *context,
                                     const gl::ImageIndex &imageIndex) override;
};

}  // namespace rx

#endif  // LIBANGLE_RENDERER_NULL_RENDERBUFFERNULL_H_
