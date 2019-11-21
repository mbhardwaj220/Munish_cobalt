// GENERATED FILE - DO NOT EDIT.
// Generated by generate_entry_points.py using data from gl.xml and wgl.xml.
//
// Copyright 2019 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// validationGL13_autogen.h:
//   Validation functions for the OpenGL 1.3 entry points.

#ifndef LIBANGLE_VALIDATION_GL13_AUTOGEN_H_
#define LIBANGLE_VALIDATION_GL13_AUTOGEN_H_

#include "common/PackedEnums.h"

namespace gl
{
class Context;

bool ValidateCompressedTexImage1D(Context *context,
                                  GLenum target,
                                  GLint level,
                                  GLenum internalformat,
                                  GLsizei width,
                                  GLint border,
                                  GLsizei imageSize,
                                  const void *data);
bool ValidateCompressedTexSubImage1D(Context *context,
                                     GLenum target,
                                     GLint level,
                                     GLint xoffset,
                                     GLsizei width,
                                     GLenum format,
                                     GLsizei imageSize,
                                     const void *data);
bool ValidateGetCompressedTexImage(Context *context, GLenum target, GLint level, void *img);
bool ValidateLoadTransposeMatrixd(Context *context, const GLdouble *m);
bool ValidateLoadTransposeMatrixf(Context *context, const GLfloat *m);
bool ValidateMultTransposeMatrixd(Context *context, const GLdouble *m);
bool ValidateMultTransposeMatrixf(Context *context, const GLfloat *m);
bool ValidateMultiTexCoord1d(Context *context, GLenum target, GLdouble s);
bool ValidateMultiTexCoord1dv(Context *context, GLenum target, const GLdouble *v);
bool ValidateMultiTexCoord1f(Context *context, GLenum target, GLfloat s);
bool ValidateMultiTexCoord1fv(Context *context, GLenum target, const GLfloat *v);
bool ValidateMultiTexCoord1i(Context *context, GLenum target, GLint s);
bool ValidateMultiTexCoord1iv(Context *context, GLenum target, const GLint *v);
bool ValidateMultiTexCoord1s(Context *context, GLenum target, GLshort s);
bool ValidateMultiTexCoord1sv(Context *context, GLenum target, const GLshort *v);
bool ValidateMultiTexCoord2d(Context *context, GLenum target, GLdouble s, GLdouble t);
bool ValidateMultiTexCoord2dv(Context *context, GLenum target, const GLdouble *v);
bool ValidateMultiTexCoord2f(Context *context, GLenum target, GLfloat s, GLfloat t);
bool ValidateMultiTexCoord2fv(Context *context, GLenum target, const GLfloat *v);
bool ValidateMultiTexCoord2i(Context *context, GLenum target, GLint s, GLint t);
bool ValidateMultiTexCoord2iv(Context *context, GLenum target, const GLint *v);
bool ValidateMultiTexCoord2s(Context *context, GLenum target, GLshort s, GLshort t);
bool ValidateMultiTexCoord2sv(Context *context, GLenum target, const GLshort *v);
bool ValidateMultiTexCoord3d(Context *context, GLenum target, GLdouble s, GLdouble t, GLdouble r);
bool ValidateMultiTexCoord3dv(Context *context, GLenum target, const GLdouble *v);
bool ValidateMultiTexCoord3f(Context *context, GLenum target, GLfloat s, GLfloat t, GLfloat r);
bool ValidateMultiTexCoord3fv(Context *context, GLenum target, const GLfloat *v);
bool ValidateMultiTexCoord3i(Context *context, GLenum target, GLint s, GLint t, GLint r);
bool ValidateMultiTexCoord3iv(Context *context, GLenum target, const GLint *v);
bool ValidateMultiTexCoord3s(Context *context, GLenum target, GLshort s, GLshort t, GLshort r);
bool ValidateMultiTexCoord3sv(Context *context, GLenum target, const GLshort *v);
bool ValidateMultiTexCoord4d(Context *context,
                             GLenum target,
                             GLdouble s,
                             GLdouble t,
                             GLdouble r,
                             GLdouble q);
bool ValidateMultiTexCoord4dv(Context *context, GLenum target, const GLdouble *v);
bool ValidateMultiTexCoord4fv(Context *context, GLenum target, const GLfloat *v);
bool ValidateMultiTexCoord4i(Context *context, GLenum target, GLint s, GLint t, GLint r, GLint q);
bool ValidateMultiTexCoord4iv(Context *context, GLenum target, const GLint *v);
bool ValidateMultiTexCoord4s(Context *context,
                             GLenum target,
                             GLshort s,
                             GLshort t,
                             GLshort r,
                             GLshort q);
bool ValidateMultiTexCoord4sv(Context *context, GLenum target, const GLshort *v);
}  // namespace gl

#endif  // LIBANGLE_VALIDATION_GL13_AUTOGEN_H_
