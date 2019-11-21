// GENERATED FILE - DO NOT EDIT.
// Generated by generate_entry_points.py using data from gl.xml and gl_angle_ext.xml.
//
// Copyright 2019 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// validationES1_autogen.h:
//   Validation functions for the OpenGL ES 1.0 entry points.

#ifndef LIBANGLE_VALIDATION_ES1_AUTOGEN_H_
#define LIBANGLE_VALIDATION_ES1_AUTOGEN_H_

#include "common/PackedEnums.h"

namespace gl
{
class Context;

bool ValidateAlphaFunc(Context *context, AlphaTestFunc funcPacked, GLfloat ref);
bool ValidateAlphaFuncx(Context *context, AlphaTestFunc funcPacked, GLfixed ref);
bool ValidateClearColorx(Context *context, GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
bool ValidateClearDepthx(Context *context, GLfixed depth);
bool ValidateClientActiveTexture(Context *context, GLenum texture);
bool ValidateClipPlanef(Context *context, GLenum p, const GLfloat *eqn);
bool ValidateClipPlanex(Context *context, GLenum plane, const GLfixed *equation);
bool ValidateColor4f(Context *context, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
bool ValidateColor4ub(Context *context, GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
bool ValidateColor4x(Context *context, GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
bool ValidateColorPointer(Context *context,
                          GLint size,
                          VertexAttribType typePacked,
                          GLsizei stride,
                          const void *pointer);
bool ValidateDepthRangex(Context *context, GLfixed n, GLfixed f);
bool ValidateDisableClientState(Context *context, ClientVertexArrayType arrayPacked);
bool ValidateEnableClientState(Context *context, ClientVertexArrayType arrayPacked);
bool ValidateFogf(Context *context, GLenum pname, GLfloat param);
bool ValidateFogfv(Context *context, GLenum pname, const GLfloat *params);
bool ValidateFogx(Context *context, GLenum pname, GLfixed param);
bool ValidateFogxv(Context *context, GLenum pname, const GLfixed *param);
bool ValidateFrustumf(Context *context,
                      GLfloat l,
                      GLfloat r,
                      GLfloat b,
                      GLfloat t,
                      GLfloat n,
                      GLfloat f);
bool ValidateFrustumx(Context *context,
                      GLfixed l,
                      GLfixed r,
                      GLfixed b,
                      GLfixed t,
                      GLfixed n,
                      GLfixed f);
bool ValidateGetClipPlanef(Context *context, GLenum plane, GLfloat *equation);
bool ValidateGetClipPlanex(Context *context, GLenum plane, GLfixed *equation);
bool ValidateGetFixedv(Context *context, GLenum pname, GLfixed *params);
bool ValidateGetLightfv(Context *context,
                        GLenum light,
                        LightParameter pnamePacked,
                        GLfloat *params);
bool ValidateGetLightxv(Context *context,
                        GLenum light,
                        LightParameter pnamePacked,
                        GLfixed *params);
bool ValidateGetMaterialfv(Context *context,
                           GLenum face,
                           MaterialParameter pnamePacked,
                           GLfloat *params);
bool ValidateGetMaterialxv(Context *context,
                           GLenum face,
                           MaterialParameter pnamePacked,
                           GLfixed *params);
bool ValidateGetTexEnvfv(Context *context,
                         TextureEnvTarget targetPacked,
                         TextureEnvParameter pnamePacked,
                         GLfloat *params);
bool ValidateGetTexEnviv(Context *context,
                         TextureEnvTarget targetPacked,
                         TextureEnvParameter pnamePacked,
                         GLint *params);
bool ValidateGetTexEnvxv(Context *context,
                         TextureEnvTarget targetPacked,
                         TextureEnvParameter pnamePacked,
                         GLfixed *params);
bool ValidateGetTexParameterxv(Context *context,
                               TextureType targetPacked,
                               GLenum pname,
                               GLfixed *params);
bool ValidateLightModelf(Context *context, GLenum pname, GLfloat param);
bool ValidateLightModelfv(Context *context, GLenum pname, const GLfloat *params);
bool ValidateLightModelx(Context *context, GLenum pname, GLfixed param);
bool ValidateLightModelxv(Context *context, GLenum pname, const GLfixed *param);
bool ValidateLightf(Context *context, GLenum light, LightParameter pnamePacked, GLfloat param);
bool ValidateLightfv(Context *context,
                     GLenum light,
                     LightParameter pnamePacked,
                     const GLfloat *params);
bool ValidateLightx(Context *context, GLenum light, LightParameter pnamePacked, GLfixed param);
bool ValidateLightxv(Context *context,
                     GLenum light,
                     LightParameter pnamePacked,
                     const GLfixed *params);
bool ValidateLineWidthx(Context *context, GLfixed width);
bool ValidateLoadIdentity(Context *context);
bool ValidateLoadMatrixf(Context *context, const GLfloat *m);
bool ValidateLoadMatrixx(Context *context, const GLfixed *m);
bool ValidateLogicOp(Context *context, LogicalOperation opcodePacked);
bool ValidateMaterialf(Context *context, GLenum face, MaterialParameter pnamePacked, GLfloat param);
bool ValidateMaterialfv(Context *context,
                        GLenum face,
                        MaterialParameter pnamePacked,
                        const GLfloat *params);
bool ValidateMaterialx(Context *context, GLenum face, MaterialParameter pnamePacked, GLfixed param);
bool ValidateMaterialxv(Context *context,
                        GLenum face,
                        MaterialParameter pnamePacked,
                        const GLfixed *param);
bool ValidateMatrixMode(Context *context, MatrixType modePacked);
bool ValidateMultMatrixf(Context *context, const GLfloat *m);
bool ValidateMultMatrixx(Context *context, const GLfixed *m);
bool ValidateMultiTexCoord4f(Context *context,
                             GLenum target,
                             GLfloat s,
                             GLfloat t,
                             GLfloat r,
                             GLfloat q);
bool ValidateMultiTexCoord4x(Context *context,
                             GLenum texture,
                             GLfixed s,
                             GLfixed t,
                             GLfixed r,
                             GLfixed q);
bool ValidateNormal3f(Context *context, GLfloat nx, GLfloat ny, GLfloat nz);
bool ValidateNormal3x(Context *context, GLfixed nx, GLfixed ny, GLfixed nz);
bool ValidateNormalPointer(Context *context,
                           VertexAttribType typePacked,
                           GLsizei stride,
                           const void *pointer);
bool ValidateOrthof(Context *context,
                    GLfloat l,
                    GLfloat r,
                    GLfloat b,
                    GLfloat t,
                    GLfloat n,
                    GLfloat f);
bool ValidateOrthox(Context *context,
                    GLfixed l,
                    GLfixed r,
                    GLfixed b,
                    GLfixed t,
                    GLfixed n,
                    GLfixed f);
bool ValidatePointParameterf(Context *context, PointParameter pnamePacked, GLfloat param);
bool ValidatePointParameterfv(Context *context, PointParameter pnamePacked, const GLfloat *params);
bool ValidatePointParameterx(Context *context, PointParameter pnamePacked, GLfixed param);
bool ValidatePointParameterxv(Context *context, PointParameter pnamePacked, const GLfixed *params);
bool ValidatePointSize(Context *context, GLfloat size);
bool ValidatePointSizex(Context *context, GLfixed size);
bool ValidatePolygonOffsetx(Context *context, GLfixed factor, GLfixed units);
bool ValidatePopMatrix(Context *context);
bool ValidatePushMatrix(Context *context);
bool ValidateRotatef(Context *context, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
bool ValidateRotatex(Context *context, GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
bool ValidateSampleCoveragex(Context *context, GLclampx value, GLboolean invert);
bool ValidateScalef(Context *context, GLfloat x, GLfloat y, GLfloat z);
bool ValidateScalex(Context *context, GLfixed x, GLfixed y, GLfixed z);
bool ValidateShadeModel(Context *context, ShadingModel modePacked);
bool ValidateTexCoordPointer(Context *context,
                             GLint size,
                             VertexAttribType typePacked,
                             GLsizei stride,
                             const void *pointer);
bool ValidateTexEnvf(Context *context,
                     TextureEnvTarget targetPacked,
                     TextureEnvParameter pnamePacked,
                     GLfloat param);
bool ValidateTexEnvfv(Context *context,
                      TextureEnvTarget targetPacked,
                      TextureEnvParameter pnamePacked,
                      const GLfloat *params);
bool ValidateTexEnvi(Context *context,
                     TextureEnvTarget targetPacked,
                     TextureEnvParameter pnamePacked,
                     GLint param);
bool ValidateTexEnviv(Context *context,
                      TextureEnvTarget targetPacked,
                      TextureEnvParameter pnamePacked,
                      const GLint *params);
bool ValidateTexEnvx(Context *context,
                     TextureEnvTarget targetPacked,
                     TextureEnvParameter pnamePacked,
                     GLfixed param);
bool ValidateTexEnvxv(Context *context,
                      TextureEnvTarget targetPacked,
                      TextureEnvParameter pnamePacked,
                      const GLfixed *params);
bool ValidateTexParameterx(Context *context, TextureType targetPacked, GLenum pname, GLfixed param);
bool ValidateTexParameterxv(Context *context,
                            TextureType targetPacked,
                            GLenum pname,
                            const GLfixed *params);
bool ValidateTranslatef(Context *context, GLfloat x, GLfloat y, GLfloat z);
bool ValidateTranslatex(Context *context, GLfixed x, GLfixed y, GLfixed z);
bool ValidateVertexPointer(Context *context,
                           GLint size,
                           VertexAttribType typePacked,
                           GLsizei stride,
                           const void *pointer);
}  // namespace gl

#endif  // LIBANGLE_VALIDATION_ES1_AUTOGEN_H_
