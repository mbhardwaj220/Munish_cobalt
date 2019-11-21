// GENERATED FILE - DO NOT EDIT.
// Generated by generate_entry_points.py using data from gl.xml.
//
// Copyright 2019 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Context_gl_1_4_autogen.h: Creates a macro for interfaces in Context.

#ifndef ANGLE_CONTEXT_GL_1_4_AUTOGEN_H_
#define ANGLE_CONTEXT_GL_1_4_AUTOGEN_H_

#define ANGLE_GL_1_4_CONTEXT_API                                                              \
    void fogCoordPointer(GLenum type, GLsizei stride, const void *pointer);                   \
    void fogCoordd(GLdouble coord);                                                           \
    void fogCoorddv(const GLdouble *coord);                                                   \
    void fogCoordf(GLfloat coord);                                                            \
    void fogCoordfv(const GLfloat *coord);                                                    \
    void pointParameteri(GLenum pname, GLint param);                                          \
    void pointParameteriv(GLenum pname, const GLint *params);                                 \
    void secondaryColor3b(GLbyte red, GLbyte green, GLbyte blue);                             \
    void secondaryColor3bv(const GLbyte *v);                                                  \
    void secondaryColor3d(GLdouble red, GLdouble green, GLdouble blue);                       \
    void secondaryColor3dv(const GLdouble *v);                                                \
    void secondaryColor3f(GLfloat red, GLfloat green, GLfloat blue);                          \
    void secondaryColor3fv(const GLfloat *v);                                                 \
    void secondaryColor3i(GLint red, GLint green, GLint blue);                                \
    void secondaryColor3iv(const GLint *v);                                                   \
    void secondaryColor3s(GLshort red, GLshort green, GLshort blue);                          \
    void secondaryColor3sv(const GLshort *v);                                                 \
    void secondaryColor3ub(GLubyte red, GLubyte green, GLubyte blue);                         \
    void secondaryColor3ubv(const GLubyte *v);                                                \
    void secondaryColor3ui(GLuint red, GLuint green, GLuint blue);                            \
    void secondaryColor3uiv(const GLuint *v);                                                 \
    void secondaryColor3us(GLushort red, GLushort green, GLushort blue);                      \
    void secondaryColor3usv(const GLushort *v);                                               \
    void secondaryColorPointer(GLint size, GLenum type, GLsizei stride, const void *pointer); \
    void windowPos2d(GLdouble x, GLdouble y);                                                 \
    void windowPos2dv(const GLdouble *v);                                                     \
    void windowPos2f(GLfloat x, GLfloat y);                                                   \
    void windowPos2fv(const GLfloat *v);                                                      \
    void windowPos2i(GLint x, GLint y);                                                       \
    void windowPos2iv(const GLint *v);                                                        \
    void windowPos2s(GLshort x, GLshort y);                                                   \
    void windowPos2sv(const GLshort *v);                                                      \
    void windowPos3d(GLdouble x, GLdouble y, GLdouble z);                                     \
    void windowPos3dv(const GLdouble *v);                                                     \
    void windowPos3f(GLfloat x, GLfloat y, GLfloat z);                                        \
    void windowPos3fv(const GLfloat *v);                                                      \
    void windowPos3i(GLint x, GLint y, GLint z);                                              \
    void windowPos3iv(const GLint *v);                                                        \
    void windowPos3s(GLshort x, GLshort y, GLshort z);                                        \
    void windowPos3sv(const GLshort *v);

#endif  // ANGLE_CONTEXT_API_1_4_AUTOGEN_H_
