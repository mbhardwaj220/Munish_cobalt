// GENERATED FILE - DO NOT EDIT.
// Generated by generate_entry_points.py using data from gl.xml.
//
// Copyright 2019 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// entry_points_gl_1_0_autogen.h:
//   Defines the GL 1.0 entry points.

#ifndef LIBGL_ENTRY_POINTS_GL_1_0_AUTOGEN_H_
#define LIBGL_ENTRY_POINTS_GL_1_0_AUTOGEN_H_

#include <export.h>
#include "angle_gl.h"

namespace gl
{
ANGLE_EXPORT void GL_APIENTRY Accum(GLenum op, GLfloat value);
ANGLE_EXPORT void GL_APIENTRY AlphaFunc(GLenum func, GLfloat ref);
ANGLE_EXPORT void GL_APIENTRY Begin(GLenum mode);
ANGLE_EXPORT void GL_APIENTRY Bitmap(GLsizei width,
                                     GLsizei height,
                                     GLfloat xorig,
                                     GLfloat yorig,
                                     GLfloat xmove,
                                     GLfloat ymove,
                                     const GLubyte *bitmap);
ANGLE_EXPORT void GL_APIENTRY BlendFunc(GLenum sfactor, GLenum dfactor);
ANGLE_EXPORT void GL_APIENTRY CallList(GLuint list);
ANGLE_EXPORT void GL_APIENTRY CallLists(GLsizei n, GLenum type, const void *lists);
ANGLE_EXPORT void GL_APIENTRY Clear(GLbitfield mask);
ANGLE_EXPORT void GL_APIENTRY ClearAccum(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
ANGLE_EXPORT void GL_APIENTRY ClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
ANGLE_EXPORT void GL_APIENTRY ClearDepth(GLdouble depth);
ANGLE_EXPORT void GL_APIENTRY ClearIndex(GLfloat c);
ANGLE_EXPORT void GL_APIENTRY ClearStencil(GLint s);
ANGLE_EXPORT void GL_APIENTRY ClipPlane(GLenum plane, const GLdouble *equation);
ANGLE_EXPORT void GL_APIENTRY Color3b(GLbyte red, GLbyte green, GLbyte blue);
ANGLE_EXPORT void GL_APIENTRY Color3bv(const GLbyte *v);
ANGLE_EXPORT void GL_APIENTRY Color3d(GLdouble red, GLdouble green, GLdouble blue);
ANGLE_EXPORT void GL_APIENTRY Color3dv(const GLdouble *v);
ANGLE_EXPORT void GL_APIENTRY Color3f(GLfloat red, GLfloat green, GLfloat blue);
ANGLE_EXPORT void GL_APIENTRY Color3fv(const GLfloat *v);
ANGLE_EXPORT void GL_APIENTRY Color3i(GLint red, GLint green, GLint blue);
ANGLE_EXPORT void GL_APIENTRY Color3iv(const GLint *v);
ANGLE_EXPORT void GL_APIENTRY Color3s(GLshort red, GLshort green, GLshort blue);
ANGLE_EXPORT void GL_APIENTRY Color3sv(const GLshort *v);
ANGLE_EXPORT void GL_APIENTRY Color3ub(GLubyte red, GLubyte green, GLubyte blue);
ANGLE_EXPORT void GL_APIENTRY Color3ubv(const GLubyte *v);
ANGLE_EXPORT void GL_APIENTRY Color3ui(GLuint red, GLuint green, GLuint blue);
ANGLE_EXPORT void GL_APIENTRY Color3uiv(const GLuint *v);
ANGLE_EXPORT void GL_APIENTRY Color3us(GLushort red, GLushort green, GLushort blue);
ANGLE_EXPORT void GL_APIENTRY Color3usv(const GLushort *v);
ANGLE_EXPORT void GL_APIENTRY Color4b(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha);
ANGLE_EXPORT void GL_APIENTRY Color4bv(const GLbyte *v);
ANGLE_EXPORT void GL_APIENTRY Color4d(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha);
ANGLE_EXPORT void GL_APIENTRY Color4dv(const GLdouble *v);
ANGLE_EXPORT void GL_APIENTRY Color4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
ANGLE_EXPORT void GL_APIENTRY Color4fv(const GLfloat *v);
ANGLE_EXPORT void GL_APIENTRY Color4i(GLint red, GLint green, GLint blue, GLint alpha);
ANGLE_EXPORT void GL_APIENTRY Color4iv(const GLint *v);
ANGLE_EXPORT void GL_APIENTRY Color4s(GLshort red, GLshort green, GLshort blue, GLshort alpha);
ANGLE_EXPORT void GL_APIENTRY Color4sv(const GLshort *v);
ANGLE_EXPORT void GL_APIENTRY Color4ub(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
ANGLE_EXPORT void GL_APIENTRY Color4ubv(const GLubyte *v);
ANGLE_EXPORT void GL_APIENTRY Color4ui(GLuint red, GLuint green, GLuint blue, GLuint alpha);
ANGLE_EXPORT void GL_APIENTRY Color4uiv(const GLuint *v);
ANGLE_EXPORT void GL_APIENTRY Color4us(GLushort red, GLushort green, GLushort blue, GLushort alpha);
ANGLE_EXPORT void GL_APIENTRY Color4usv(const GLushort *v);
ANGLE_EXPORT void GL_APIENTRY ColorMask(GLboolean red,
                                        GLboolean green,
                                        GLboolean blue,
                                        GLboolean alpha);
ANGLE_EXPORT void GL_APIENTRY ColorMaterial(GLenum face, GLenum mode);
ANGLE_EXPORT void GL_APIENTRY
CopyPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type);
ANGLE_EXPORT void GL_APIENTRY CullFace(GLenum mode);
ANGLE_EXPORT void GL_APIENTRY DeleteLists(GLuint list, GLsizei range);
ANGLE_EXPORT void GL_APIENTRY DepthFunc(GLenum func);
ANGLE_EXPORT void GL_APIENTRY DepthMask(GLboolean flag);
ANGLE_EXPORT void GL_APIENTRY DepthRange(GLdouble n, GLdouble f);
ANGLE_EXPORT void GL_APIENTRY Disable(GLenum cap);
ANGLE_EXPORT void GL_APIENTRY DrawBuffer(GLenum buf);
ANGLE_EXPORT void GL_APIENTRY
DrawPixels(GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels);
ANGLE_EXPORT void GL_APIENTRY EdgeFlag(GLboolean flag);
ANGLE_EXPORT void GL_APIENTRY EdgeFlagv(const GLboolean *flag);
ANGLE_EXPORT void GL_APIENTRY Enable(GLenum cap);
ANGLE_EXPORT void GL_APIENTRY End();
ANGLE_EXPORT void GL_APIENTRY EndList();
ANGLE_EXPORT void GL_APIENTRY EvalCoord1d(GLdouble u);
ANGLE_EXPORT void GL_APIENTRY EvalCoord1dv(const GLdouble *u);
ANGLE_EXPORT void GL_APIENTRY EvalCoord1f(GLfloat u);
ANGLE_EXPORT void GL_APIENTRY EvalCoord1fv(const GLfloat *u);
ANGLE_EXPORT void GL_APIENTRY EvalCoord2d(GLdouble u, GLdouble v);
ANGLE_EXPORT void GL_APIENTRY EvalCoord2dv(const GLdouble *u);
ANGLE_EXPORT void GL_APIENTRY EvalCoord2f(GLfloat u, GLfloat v);
ANGLE_EXPORT void GL_APIENTRY EvalCoord2fv(const GLfloat *u);
ANGLE_EXPORT void GL_APIENTRY EvalMesh1(GLenum mode, GLint i1, GLint i2);
ANGLE_EXPORT void GL_APIENTRY EvalMesh2(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2);
ANGLE_EXPORT void GL_APIENTRY EvalPoint1(GLint i);
ANGLE_EXPORT void GL_APIENTRY EvalPoint2(GLint i, GLint j);
ANGLE_EXPORT void GL_APIENTRY FeedbackBuffer(GLsizei size, GLenum type, GLfloat *buffer);
ANGLE_EXPORT void GL_APIENTRY Finish();
ANGLE_EXPORT void GL_APIENTRY Flush();
ANGLE_EXPORT void GL_APIENTRY Fogf(GLenum pname, GLfloat param);
ANGLE_EXPORT void GL_APIENTRY Fogfv(GLenum pname, const GLfloat *params);
ANGLE_EXPORT void GL_APIENTRY Fogi(GLenum pname, GLint param);
ANGLE_EXPORT void GL_APIENTRY Fogiv(GLenum pname, const GLint *params);
ANGLE_EXPORT void GL_APIENTRY FrontFace(GLenum mode);
ANGLE_EXPORT void GL_APIENTRY Frustum(GLdouble left,
                                      GLdouble right,
                                      GLdouble bottom,
                                      GLdouble top,
                                      GLdouble zNear,
                                      GLdouble zFar);
ANGLE_EXPORT GLuint GL_APIENTRY GenLists(GLsizei range);
ANGLE_EXPORT void GL_APIENTRY GetBooleanv(GLenum pname, GLboolean *data);
ANGLE_EXPORT void GL_APIENTRY GetClipPlane(GLenum plane, GLdouble *equation);
ANGLE_EXPORT void GL_APIENTRY GetDoublev(GLenum pname, GLdouble *data);
ANGLE_EXPORT GLenum GL_APIENTRY GetError();
ANGLE_EXPORT void GL_APIENTRY GetFloatv(GLenum pname, GLfloat *data);
ANGLE_EXPORT void GL_APIENTRY GetIntegerv(GLenum pname, GLint *data);
ANGLE_EXPORT void GL_APIENTRY GetLightfv(GLenum light, GLenum pname, GLfloat *params);
ANGLE_EXPORT void GL_APIENTRY GetLightiv(GLenum light, GLenum pname, GLint *params);
ANGLE_EXPORT void GL_APIENTRY GetMapdv(GLenum target, GLenum query, GLdouble *v);
ANGLE_EXPORT void GL_APIENTRY GetMapfv(GLenum target, GLenum query, GLfloat *v);
ANGLE_EXPORT void GL_APIENTRY GetMapiv(GLenum target, GLenum query, GLint *v);
ANGLE_EXPORT void GL_APIENTRY GetMaterialfv(GLenum face, GLenum pname, GLfloat *params);
ANGLE_EXPORT void GL_APIENTRY GetMaterialiv(GLenum face, GLenum pname, GLint *params);
ANGLE_EXPORT void GL_APIENTRY GetPixelMapfv(GLenum map, GLfloat *values);
ANGLE_EXPORT void GL_APIENTRY GetPixelMapuiv(GLenum map, GLuint *values);
ANGLE_EXPORT void GL_APIENTRY GetPixelMapusv(GLenum map, GLushort *values);
ANGLE_EXPORT void GL_APIENTRY GetPolygonStipple(GLubyte *mask);
ANGLE_EXPORT const GLubyte *GL_APIENTRY GetString(GLenum name);
ANGLE_EXPORT void GL_APIENTRY GetTexEnvfv(GLenum target, GLenum pname, GLfloat *params);
ANGLE_EXPORT void GL_APIENTRY GetTexEnviv(GLenum target, GLenum pname, GLint *params);
ANGLE_EXPORT void GL_APIENTRY GetTexGendv(GLenum coord, GLenum pname, GLdouble *params);
ANGLE_EXPORT void GL_APIENTRY GetTexGenfv(GLenum coord, GLenum pname, GLfloat *params);
ANGLE_EXPORT void GL_APIENTRY GetTexGeniv(GLenum coord, GLenum pname, GLint *params);
ANGLE_EXPORT void GL_APIENTRY
GetTexImage(GLenum target, GLint level, GLenum format, GLenum type, void *pixels);
ANGLE_EXPORT void GL_APIENTRY GetTexLevelParameterfv(GLenum target,
                                                     GLint level,
                                                     GLenum pname,
                                                     GLfloat *params);
ANGLE_EXPORT void GL_APIENTRY GetTexLevelParameteriv(GLenum target,
                                                     GLint level,
                                                     GLenum pname,
                                                     GLint *params);
ANGLE_EXPORT void GL_APIENTRY GetTexParameterfv(GLenum target, GLenum pname, GLfloat *params);
ANGLE_EXPORT void GL_APIENTRY GetTexParameteriv(GLenum target, GLenum pname, GLint *params);
ANGLE_EXPORT void GL_APIENTRY Hint(GLenum target, GLenum mode);
ANGLE_EXPORT void GL_APIENTRY IndexMask(GLuint mask);
ANGLE_EXPORT void GL_APIENTRY Indexd(GLdouble c);
ANGLE_EXPORT void GL_APIENTRY Indexdv(const GLdouble *c);
ANGLE_EXPORT void GL_APIENTRY Indexf(GLfloat c);
ANGLE_EXPORT void GL_APIENTRY Indexfv(const GLfloat *c);
ANGLE_EXPORT void GL_APIENTRY Indexi(GLint c);
ANGLE_EXPORT void GL_APIENTRY Indexiv(const GLint *c);
ANGLE_EXPORT void GL_APIENTRY Indexs(GLshort c);
ANGLE_EXPORT void GL_APIENTRY Indexsv(const GLshort *c);
ANGLE_EXPORT void GL_APIENTRY InitNames();
ANGLE_EXPORT GLboolean GL_APIENTRY IsEnabled(GLenum cap);
ANGLE_EXPORT GLboolean GL_APIENTRY IsList(GLuint list);
ANGLE_EXPORT void GL_APIENTRY LightModelf(GLenum pname, GLfloat param);
ANGLE_EXPORT void GL_APIENTRY LightModelfv(GLenum pname, const GLfloat *params);
ANGLE_EXPORT void GL_APIENTRY LightModeli(GLenum pname, GLint param);
ANGLE_EXPORT void GL_APIENTRY LightModeliv(GLenum pname, const GLint *params);
ANGLE_EXPORT void GL_APIENTRY Lightf(GLenum light, GLenum pname, GLfloat param);
ANGLE_EXPORT void GL_APIENTRY Lightfv(GLenum light, GLenum pname, const GLfloat *params);
ANGLE_EXPORT void GL_APIENTRY Lighti(GLenum light, GLenum pname, GLint param);
ANGLE_EXPORT void GL_APIENTRY Lightiv(GLenum light, GLenum pname, const GLint *params);
ANGLE_EXPORT void GL_APIENTRY LineStipple(GLint factor, GLushort pattern);
ANGLE_EXPORT void GL_APIENTRY LineWidth(GLfloat width);
ANGLE_EXPORT void GL_APIENTRY ListBase(GLuint base);
ANGLE_EXPORT void GL_APIENTRY LoadIdentity();
ANGLE_EXPORT void GL_APIENTRY LoadMatrixd(const GLdouble *m);
ANGLE_EXPORT void GL_APIENTRY LoadMatrixf(const GLfloat *m);
ANGLE_EXPORT void GL_APIENTRY LoadName(GLuint name);
ANGLE_EXPORT void GL_APIENTRY LogicOp(GLenum opcode);
ANGLE_EXPORT void GL_APIENTRY
Map1d(GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble *points);
ANGLE_EXPORT void GL_APIENTRY
Map1f(GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat *points);
ANGLE_EXPORT void GL_APIENTRY Map2d(GLenum target,
                                    GLdouble u1,
                                    GLdouble u2,
                                    GLint ustride,
                                    GLint uorder,
                                    GLdouble v1,
                                    GLdouble v2,
                                    GLint vstride,
                                    GLint vorder,
                                    const GLdouble *points);
ANGLE_EXPORT void GL_APIENTRY Map2f(GLenum target,
                                    GLfloat u1,
                                    GLfloat u2,
                                    GLint ustride,
                                    GLint uorder,
                                    GLfloat v1,
                                    GLfloat v2,
                                    GLint vstride,
                                    GLint vorder,
                                    const GLfloat *points);
ANGLE_EXPORT void GL_APIENTRY MapGrid1d(GLint un, GLdouble u1, GLdouble u2);
ANGLE_EXPORT void GL_APIENTRY MapGrid1f(GLint un, GLfloat u1, GLfloat u2);
ANGLE_EXPORT void GL_APIENTRY
MapGrid2d(GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2);
ANGLE_EXPORT void GL_APIENTRY
MapGrid2f(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2);
ANGLE_EXPORT void GL_APIENTRY Materialf(GLenum face, GLenum pname, GLfloat param);
ANGLE_EXPORT void GL_APIENTRY Materialfv(GLenum face, GLenum pname, const GLfloat *params);
ANGLE_EXPORT void GL_APIENTRY Materiali(GLenum face, GLenum pname, GLint param);
ANGLE_EXPORT void GL_APIENTRY Materialiv(GLenum face, GLenum pname, const GLint *params);
ANGLE_EXPORT void GL_APIENTRY MatrixMode(GLenum mode);
ANGLE_EXPORT void GL_APIENTRY MultMatrixd(const GLdouble *m);
ANGLE_EXPORT void GL_APIENTRY MultMatrixf(const GLfloat *m);
ANGLE_EXPORT void GL_APIENTRY NewList(GLuint list, GLenum mode);
ANGLE_EXPORT void GL_APIENTRY Normal3b(GLbyte nx, GLbyte ny, GLbyte nz);
ANGLE_EXPORT void GL_APIENTRY Normal3bv(const GLbyte *v);
ANGLE_EXPORT void GL_APIENTRY Normal3d(GLdouble nx, GLdouble ny, GLdouble nz);
ANGLE_EXPORT void GL_APIENTRY Normal3dv(const GLdouble *v);
ANGLE_EXPORT void GL_APIENTRY Normal3f(GLfloat nx, GLfloat ny, GLfloat nz);
ANGLE_EXPORT void GL_APIENTRY Normal3fv(const GLfloat *v);
ANGLE_EXPORT void GL_APIENTRY Normal3i(GLint nx, GLint ny, GLint nz);
ANGLE_EXPORT void GL_APIENTRY Normal3iv(const GLint *v);
ANGLE_EXPORT void GL_APIENTRY Normal3s(GLshort nx, GLshort ny, GLshort nz);
ANGLE_EXPORT void GL_APIENTRY Normal3sv(const GLshort *v);
ANGLE_EXPORT void GL_APIENTRY
Ortho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
ANGLE_EXPORT void GL_APIENTRY PassThrough(GLfloat token);
ANGLE_EXPORT void GL_APIENTRY PixelMapfv(GLenum map, GLsizei mapsize, const GLfloat *values);
ANGLE_EXPORT void GL_APIENTRY PixelMapuiv(GLenum map, GLsizei mapsize, const GLuint *values);
ANGLE_EXPORT void GL_APIENTRY PixelMapusv(GLenum map, GLsizei mapsize, const GLushort *values);
ANGLE_EXPORT void GL_APIENTRY PixelStoref(GLenum pname, GLfloat param);
ANGLE_EXPORT void GL_APIENTRY PixelStorei(GLenum pname, GLint param);
ANGLE_EXPORT void GL_APIENTRY PixelTransferf(GLenum pname, GLfloat param);
ANGLE_EXPORT void GL_APIENTRY PixelTransferi(GLenum pname, GLint param);
ANGLE_EXPORT void GL_APIENTRY PixelZoom(GLfloat xfactor, GLfloat yfactor);
ANGLE_EXPORT void GL_APIENTRY PointSize(GLfloat size);
ANGLE_EXPORT void GL_APIENTRY PolygonMode(GLenum face, GLenum mode);
ANGLE_EXPORT void GL_APIENTRY PolygonStipple(const GLubyte *mask);
ANGLE_EXPORT void GL_APIENTRY PopAttrib();
ANGLE_EXPORT void GL_APIENTRY PopMatrix();
ANGLE_EXPORT void GL_APIENTRY PopName();
ANGLE_EXPORT void GL_APIENTRY PushAttrib(GLbitfield mask);
ANGLE_EXPORT void GL_APIENTRY PushMatrix();
ANGLE_EXPORT void GL_APIENTRY PushName(GLuint name);
ANGLE_EXPORT void GL_APIENTRY RasterPos2d(GLdouble x, GLdouble y);
ANGLE_EXPORT void GL_APIENTRY RasterPos2dv(const GLdouble *v);
ANGLE_EXPORT void GL_APIENTRY RasterPos2f(GLfloat x, GLfloat y);
ANGLE_EXPORT void GL_APIENTRY RasterPos2fv(const GLfloat *v);
ANGLE_EXPORT void GL_APIENTRY RasterPos2i(GLint x, GLint y);
ANGLE_EXPORT void GL_APIENTRY RasterPos2iv(const GLint *v);
ANGLE_EXPORT void GL_APIENTRY RasterPos2s(GLshort x, GLshort y);
ANGLE_EXPORT void GL_APIENTRY RasterPos2sv(const GLshort *v);
ANGLE_EXPORT void GL_APIENTRY RasterPos3d(GLdouble x, GLdouble y, GLdouble z);
ANGLE_EXPORT void GL_APIENTRY RasterPos3dv(const GLdouble *v);
ANGLE_EXPORT void GL_APIENTRY RasterPos3f(GLfloat x, GLfloat y, GLfloat z);
ANGLE_EXPORT void GL_APIENTRY RasterPos3fv(const GLfloat *v);
ANGLE_EXPORT void GL_APIENTRY RasterPos3i(GLint x, GLint y, GLint z);
ANGLE_EXPORT void GL_APIENTRY RasterPos3iv(const GLint *v);
ANGLE_EXPORT void GL_APIENTRY RasterPos3s(GLshort x, GLshort y, GLshort z);
ANGLE_EXPORT void GL_APIENTRY RasterPos3sv(const GLshort *v);
ANGLE_EXPORT void GL_APIENTRY RasterPos4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
ANGLE_EXPORT void GL_APIENTRY RasterPos4dv(const GLdouble *v);
ANGLE_EXPORT void GL_APIENTRY RasterPos4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
ANGLE_EXPORT void GL_APIENTRY RasterPos4fv(const GLfloat *v);
ANGLE_EXPORT void GL_APIENTRY RasterPos4i(GLint x, GLint y, GLint z, GLint w);
ANGLE_EXPORT void GL_APIENTRY RasterPos4iv(const GLint *v);
ANGLE_EXPORT void GL_APIENTRY RasterPos4s(GLshort x, GLshort y, GLshort z, GLshort w);
ANGLE_EXPORT void GL_APIENTRY RasterPos4sv(const GLshort *v);
ANGLE_EXPORT void GL_APIENTRY ReadBuffer(GLenum src);
ANGLE_EXPORT void GL_APIENTRY ReadPixels(GLint x,
                                         GLint y,
                                         GLsizei width,
                                         GLsizei height,
                                         GLenum format,
                                         GLenum type,
                                         void *pixels);
ANGLE_EXPORT void GL_APIENTRY Rectd(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
ANGLE_EXPORT void GL_APIENTRY Rectdv(const GLdouble *v1, const GLdouble *v2);
ANGLE_EXPORT void GL_APIENTRY Rectf(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
ANGLE_EXPORT void GL_APIENTRY Rectfv(const GLfloat *v1, const GLfloat *v2);
ANGLE_EXPORT void GL_APIENTRY Recti(GLint x1, GLint y1, GLint x2, GLint y2);
ANGLE_EXPORT void GL_APIENTRY Rectiv(const GLint *v1, const GLint *v2);
ANGLE_EXPORT void GL_APIENTRY Rects(GLshort x1, GLshort y1, GLshort x2, GLshort y2);
ANGLE_EXPORT void GL_APIENTRY Rectsv(const GLshort *v1, const GLshort *v2);
ANGLE_EXPORT GLint GL_APIENTRY RenderMode(GLenum mode);
ANGLE_EXPORT void GL_APIENTRY Rotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
ANGLE_EXPORT void GL_APIENTRY Rotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
ANGLE_EXPORT void GL_APIENTRY Scaled(GLdouble x, GLdouble y, GLdouble z);
ANGLE_EXPORT void GL_APIENTRY Scalef(GLfloat x, GLfloat y, GLfloat z);
ANGLE_EXPORT void GL_APIENTRY Scissor(GLint x, GLint y, GLsizei width, GLsizei height);
ANGLE_EXPORT void GL_APIENTRY SelectBuffer(GLsizei size, GLuint *buffer);
ANGLE_EXPORT void GL_APIENTRY ShadeModel(GLenum mode);
ANGLE_EXPORT void GL_APIENTRY StencilFunc(GLenum func, GLint ref, GLuint mask);
ANGLE_EXPORT void GL_APIENTRY StencilMask(GLuint mask);
ANGLE_EXPORT void GL_APIENTRY StencilOp(GLenum fail, GLenum zfail, GLenum zpass);
ANGLE_EXPORT void GL_APIENTRY TexCoord1d(GLdouble s);
ANGLE_EXPORT void GL_APIENTRY TexCoord1dv(const GLdouble *v);
ANGLE_EXPORT void GL_APIENTRY TexCoord1f(GLfloat s);
ANGLE_EXPORT void GL_APIENTRY TexCoord1fv(const GLfloat *v);
ANGLE_EXPORT void GL_APIENTRY TexCoord1i(GLint s);
ANGLE_EXPORT void GL_APIENTRY TexCoord1iv(const GLint *v);
ANGLE_EXPORT void GL_APIENTRY TexCoord1s(GLshort s);
ANGLE_EXPORT void GL_APIENTRY TexCoord1sv(const GLshort *v);
ANGLE_EXPORT void GL_APIENTRY TexCoord2d(GLdouble s, GLdouble t);
ANGLE_EXPORT void GL_APIENTRY TexCoord2dv(const GLdouble *v);
ANGLE_EXPORT void GL_APIENTRY TexCoord2f(GLfloat s, GLfloat t);
ANGLE_EXPORT void GL_APIENTRY TexCoord2fv(const GLfloat *v);
ANGLE_EXPORT void GL_APIENTRY TexCoord2i(GLint s, GLint t);
ANGLE_EXPORT void GL_APIENTRY TexCoord2iv(const GLint *v);
ANGLE_EXPORT void GL_APIENTRY TexCoord2s(GLshort s, GLshort t);
ANGLE_EXPORT void GL_APIENTRY TexCoord2sv(const GLshort *v);
ANGLE_EXPORT void GL_APIENTRY TexCoord3d(GLdouble s, GLdouble t, GLdouble r);
ANGLE_EXPORT void GL_APIENTRY TexCoord3dv(const GLdouble *v);
ANGLE_EXPORT void GL_APIENTRY TexCoord3f(GLfloat s, GLfloat t, GLfloat r);
ANGLE_EXPORT void GL_APIENTRY TexCoord3fv(const GLfloat *v);
ANGLE_EXPORT void GL_APIENTRY TexCoord3i(GLint s, GLint t, GLint r);
ANGLE_EXPORT void GL_APIENTRY TexCoord3iv(const GLint *v);
ANGLE_EXPORT void GL_APIENTRY TexCoord3s(GLshort s, GLshort t, GLshort r);
ANGLE_EXPORT void GL_APIENTRY TexCoord3sv(const GLshort *v);
ANGLE_EXPORT void GL_APIENTRY TexCoord4d(GLdouble s, GLdouble t, GLdouble r, GLdouble q);
ANGLE_EXPORT void GL_APIENTRY TexCoord4dv(const GLdouble *v);
ANGLE_EXPORT void GL_APIENTRY TexCoord4f(GLfloat s, GLfloat t, GLfloat r, GLfloat q);
ANGLE_EXPORT void GL_APIENTRY TexCoord4fv(const GLfloat *v);
ANGLE_EXPORT void GL_APIENTRY TexCoord4i(GLint s, GLint t, GLint r, GLint q);
ANGLE_EXPORT void GL_APIENTRY TexCoord4iv(const GLint *v);
ANGLE_EXPORT void GL_APIENTRY TexCoord4s(GLshort s, GLshort t, GLshort r, GLshort q);
ANGLE_EXPORT void GL_APIENTRY TexCoord4sv(const GLshort *v);
ANGLE_EXPORT void GL_APIENTRY TexEnvf(GLenum target, GLenum pname, GLfloat param);
ANGLE_EXPORT void GL_APIENTRY TexEnvfv(GLenum target, GLenum pname, const GLfloat *params);
ANGLE_EXPORT void GL_APIENTRY TexEnvi(GLenum target, GLenum pname, GLint param);
ANGLE_EXPORT void GL_APIENTRY TexEnviv(GLenum target, GLenum pname, const GLint *params);
ANGLE_EXPORT void GL_APIENTRY TexGend(GLenum coord, GLenum pname, GLdouble param);
ANGLE_EXPORT void GL_APIENTRY TexGendv(GLenum coord, GLenum pname, const GLdouble *params);
ANGLE_EXPORT void GL_APIENTRY TexGenf(GLenum coord, GLenum pname, GLfloat param);
ANGLE_EXPORT void GL_APIENTRY TexGenfv(GLenum coord, GLenum pname, const GLfloat *params);
ANGLE_EXPORT void GL_APIENTRY TexGeni(GLenum coord, GLenum pname, GLint param);
ANGLE_EXPORT void GL_APIENTRY TexGeniv(GLenum coord, GLenum pname, const GLint *params);
ANGLE_EXPORT void GL_APIENTRY TexImage1D(GLenum target,
                                         GLint level,
                                         GLint internalformat,
                                         GLsizei width,
                                         GLint border,
                                         GLenum format,
                                         GLenum type,
                                         const void *pixels);
ANGLE_EXPORT void GL_APIENTRY TexImage2D(GLenum target,
                                         GLint level,
                                         GLint internalformat,
                                         GLsizei width,
                                         GLsizei height,
                                         GLint border,
                                         GLenum format,
                                         GLenum type,
                                         const void *pixels);
ANGLE_EXPORT void GL_APIENTRY TexParameterf(GLenum target, GLenum pname, GLfloat param);
ANGLE_EXPORT void GL_APIENTRY TexParameterfv(GLenum target, GLenum pname, const GLfloat *params);
ANGLE_EXPORT void GL_APIENTRY TexParameteri(GLenum target, GLenum pname, GLint param);
ANGLE_EXPORT void GL_APIENTRY TexParameteriv(GLenum target, GLenum pname, const GLint *params);
ANGLE_EXPORT void GL_APIENTRY Translated(GLdouble x, GLdouble y, GLdouble z);
ANGLE_EXPORT void GL_APIENTRY Translatef(GLfloat x, GLfloat y, GLfloat z);
ANGLE_EXPORT void GL_APIENTRY Vertex2d(GLdouble x, GLdouble y);
ANGLE_EXPORT void GL_APIENTRY Vertex2dv(const GLdouble *v);
ANGLE_EXPORT void GL_APIENTRY Vertex2f(GLfloat x, GLfloat y);
ANGLE_EXPORT void GL_APIENTRY Vertex2fv(const GLfloat *v);
ANGLE_EXPORT void GL_APIENTRY Vertex2i(GLint x, GLint y);
ANGLE_EXPORT void GL_APIENTRY Vertex2iv(const GLint *v);
ANGLE_EXPORT void GL_APIENTRY Vertex2s(GLshort x, GLshort y);
ANGLE_EXPORT void GL_APIENTRY Vertex2sv(const GLshort *v);
ANGLE_EXPORT void GL_APIENTRY Vertex3d(GLdouble x, GLdouble y, GLdouble z);
ANGLE_EXPORT void GL_APIENTRY Vertex3dv(const GLdouble *v);
ANGLE_EXPORT void GL_APIENTRY Vertex3f(GLfloat x, GLfloat y, GLfloat z);
ANGLE_EXPORT void GL_APIENTRY Vertex3fv(const GLfloat *v);
ANGLE_EXPORT void GL_APIENTRY Vertex3i(GLint x, GLint y, GLint z);
ANGLE_EXPORT void GL_APIENTRY Vertex3iv(const GLint *v);
ANGLE_EXPORT void GL_APIENTRY Vertex3s(GLshort x, GLshort y, GLshort z);
ANGLE_EXPORT void GL_APIENTRY Vertex3sv(const GLshort *v);
ANGLE_EXPORT void GL_APIENTRY Vertex4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
ANGLE_EXPORT void GL_APIENTRY Vertex4dv(const GLdouble *v);
ANGLE_EXPORT void GL_APIENTRY Vertex4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
ANGLE_EXPORT void GL_APIENTRY Vertex4fv(const GLfloat *v);
ANGLE_EXPORT void GL_APIENTRY Vertex4i(GLint x, GLint y, GLint z, GLint w);
ANGLE_EXPORT void GL_APIENTRY Vertex4iv(const GLint *v);
ANGLE_EXPORT void GL_APIENTRY Vertex4s(GLshort x, GLshort y, GLshort z, GLshort w);
ANGLE_EXPORT void GL_APIENTRY Vertex4sv(const GLshort *v);
ANGLE_EXPORT void GL_APIENTRY Viewport(GLint x, GLint y, GLsizei width, GLsizei height);
}  // namespace gl

#endif  // LIBGL_ENTRY_POINTS_GL_1_0_AUTOGEN_H_
