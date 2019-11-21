// GENERATED FILE - DO NOT EDIT.
// Generated by generate_entry_points.py using data from gl.xml.
//
// Copyright 2019 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// entry_points_gl_4_3_autogen.h:
//   Defines the GL 4.3 entry points.

#ifndef LIBGL_ENTRY_POINTS_GL_4_3_AUTOGEN_H_
#define LIBGL_ENTRY_POINTS_GL_4_3_AUTOGEN_H_

#include <export.h>
#include "angle_gl.h"

namespace gl
{
ANGLE_EXPORT void GL_APIENTRY BindVertexBuffer(GLuint bindingindex,
                                               GLuint buffer,
                                               GLintptr offset,
                                               GLsizei stride);
ANGLE_EXPORT void GL_APIENTRY
ClearBufferData(GLenum target, GLenum internalformat, GLenum format, GLenum type, const void *data);
ANGLE_EXPORT void GL_APIENTRY ClearBufferSubData(GLenum target,
                                                 GLenum internalformat,
                                                 GLintptr offset,
                                                 GLsizeiptr size,
                                                 GLenum format,
                                                 GLenum type,
                                                 const void *data);
ANGLE_EXPORT void GL_APIENTRY CopyImageSubData(GLuint srcName,
                                               GLenum srcTarget,
                                               GLint srcLevel,
                                               GLint srcX,
                                               GLint srcY,
                                               GLint srcZ,
                                               GLuint dstName,
                                               GLenum dstTarget,
                                               GLint dstLevel,
                                               GLint dstX,
                                               GLint dstY,
                                               GLint dstZ,
                                               GLsizei srcWidth,
                                               GLsizei srcHeight,
                                               GLsizei srcDepth);
ANGLE_EXPORT void GL_APIENTRY DebugMessageCallback(GLDEBUGPROC callback, const void *userParam);
ANGLE_EXPORT void GL_APIENTRY DebugMessageControl(GLenum source,
                                                  GLenum type,
                                                  GLenum severity,
                                                  GLsizei count,
                                                  const GLuint *ids,
                                                  GLboolean enabled);
ANGLE_EXPORT void GL_APIENTRY DebugMessageInsert(GLenum source,
                                                 GLenum type,
                                                 GLuint id,
                                                 GLenum severity,
                                                 GLsizei length,
                                                 const GLchar *buf);
ANGLE_EXPORT void GL_APIENTRY DispatchCompute(GLuint num_groups_x,
                                              GLuint num_groups_y,
                                              GLuint num_groups_z);
ANGLE_EXPORT void GL_APIENTRY DispatchComputeIndirect(GLintptr indirect);
ANGLE_EXPORT void GL_APIENTRY FramebufferParameteri(GLenum target, GLenum pname, GLint param);
ANGLE_EXPORT GLuint GL_APIENTRY GetDebugMessageLog(GLuint count,
                                                   GLsizei bufSize,
                                                   GLenum *sources,
                                                   GLenum *types,
                                                   GLuint *ids,
                                                   GLenum *severities,
                                                   GLsizei *lengths,
                                                   GLchar *messageLog);
ANGLE_EXPORT void GL_APIENTRY GetFramebufferParameteriv(GLenum target, GLenum pname, GLint *params);
ANGLE_EXPORT void GL_APIENTRY GetInternalformati64v(GLenum target,
                                                    GLenum internalformat,
                                                    GLenum pname,
                                                    GLsizei bufSize,
                                                    GLint64 *params);
ANGLE_EXPORT void GL_APIENTRY
GetObjectLabel(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei *length, GLchar *label);
ANGLE_EXPORT void GL_APIENTRY GetObjectPtrLabel(const void *ptr,
                                                GLsizei bufSize,
                                                GLsizei *length,
                                                GLchar *label);
ANGLE_EXPORT void GL_APIENTRY GetProgramInterfaceiv(GLuint program,
                                                    GLenum programInterface,
                                                    GLenum pname,
                                                    GLint *params);
ANGLE_EXPORT GLuint GL_APIENTRY GetProgramResourceIndex(GLuint program,
                                                        GLenum programInterface,
                                                        const GLchar *name);
ANGLE_EXPORT GLint GL_APIENTRY GetProgramResourceLocation(GLuint program,
                                                          GLenum programInterface,
                                                          const GLchar *name);
ANGLE_EXPORT GLint GL_APIENTRY GetProgramResourceLocationIndex(GLuint program,
                                                               GLenum programInterface,
                                                               const GLchar *name);
ANGLE_EXPORT void GL_APIENTRY GetProgramResourceName(GLuint program,
                                                     GLenum programInterface,
                                                     GLuint index,
                                                     GLsizei bufSize,
                                                     GLsizei *length,
                                                     GLchar *name);
ANGLE_EXPORT void GL_APIENTRY GetProgramResourceiv(GLuint program,
                                                   GLenum programInterface,
                                                   GLuint index,
                                                   GLsizei propCount,
                                                   const GLenum *props,
                                                   GLsizei bufSize,
                                                   GLsizei *length,
                                                   GLint *params);
ANGLE_EXPORT void GL_APIENTRY InvalidateBufferData(GLuint buffer);
ANGLE_EXPORT void GL_APIENTRY InvalidateBufferSubData(GLuint buffer,
                                                      GLintptr offset,
                                                      GLsizeiptr length);
ANGLE_EXPORT void GL_APIENTRY InvalidateFramebuffer(GLenum target,
                                                    GLsizei numAttachments,
                                                    const GLenum *attachments);
ANGLE_EXPORT void GL_APIENTRY InvalidateSubFramebuffer(GLenum target,
                                                       GLsizei numAttachments,
                                                       const GLenum *attachments,
                                                       GLint x,
                                                       GLint y,
                                                       GLsizei width,
                                                       GLsizei height);
ANGLE_EXPORT void GL_APIENTRY InvalidateTexImage(GLuint texture, GLint level);
ANGLE_EXPORT void GL_APIENTRY InvalidateTexSubImage(GLuint texture,
                                                    GLint level,
                                                    GLint xoffset,
                                                    GLint yoffset,
                                                    GLint zoffset,
                                                    GLsizei width,
                                                    GLsizei height,
                                                    GLsizei depth);
ANGLE_EXPORT void GL_APIENTRY MultiDrawArraysIndirect(GLenum mode,
                                                      const void *indirect,
                                                      GLsizei drawcount,
                                                      GLsizei stride);
ANGLE_EXPORT void GL_APIENTRY MultiDrawElementsIndirect(GLenum mode,
                                                        GLenum type,
                                                        const void *indirect,
                                                        GLsizei drawcount,
                                                        GLsizei stride);
ANGLE_EXPORT void GL_APIENTRY ObjectLabel(GLenum identifier,
                                          GLuint name,
                                          GLsizei length,
                                          const GLchar *label);
ANGLE_EXPORT void GL_APIENTRY ObjectPtrLabel(const void *ptr, GLsizei length, const GLchar *label);
ANGLE_EXPORT void GL_APIENTRY PopDebugGroup();
ANGLE_EXPORT void GL_APIENTRY PushDebugGroup(GLenum source,
                                             GLuint id,
                                             GLsizei length,
                                             const GLchar *message);
ANGLE_EXPORT void GL_APIENTRY ShaderStorageBlockBinding(GLuint program,
                                                        GLuint storageBlockIndex,
                                                        GLuint storageBlockBinding);
ANGLE_EXPORT void GL_APIENTRY TexBufferRange(GLenum target,
                                             GLenum internalformat,
                                             GLuint buffer,
                                             GLintptr offset,
                                             GLsizeiptr size);
ANGLE_EXPORT void GL_APIENTRY TexStorage2DMultisample(GLenum target,
                                                      GLsizei samples,
                                                      GLenum internalformat,
                                                      GLsizei width,
                                                      GLsizei height,
                                                      GLboolean fixedsamplelocations);
ANGLE_EXPORT void GL_APIENTRY TexStorage3DMultisample(GLenum target,
                                                      GLsizei samples,
                                                      GLenum internalformat,
                                                      GLsizei width,
                                                      GLsizei height,
                                                      GLsizei depth,
                                                      GLboolean fixedsamplelocations);
ANGLE_EXPORT void GL_APIENTRY TextureView(GLuint texture,
                                          GLenum target,
                                          GLuint origtexture,
                                          GLenum internalformat,
                                          GLuint minlevel,
                                          GLuint numlevels,
                                          GLuint minlayer,
                                          GLuint numlayers);
ANGLE_EXPORT void GL_APIENTRY VertexAttribBinding(GLuint attribindex, GLuint bindingindex);
ANGLE_EXPORT void GL_APIENTRY VertexAttribFormat(GLuint attribindex,
                                                 GLint size,
                                                 GLenum type,
                                                 GLboolean normalized,
                                                 GLuint relativeoffset);
ANGLE_EXPORT void GL_APIENTRY VertexAttribIFormat(GLuint attribindex,
                                                  GLint size,
                                                  GLenum type,
                                                  GLuint relativeoffset);
ANGLE_EXPORT void GL_APIENTRY VertexAttribLFormat(GLuint attribindex,
                                                  GLint size,
                                                  GLenum type,
                                                  GLuint relativeoffset);
ANGLE_EXPORT void GL_APIENTRY VertexBindingDivisor(GLuint bindingindex, GLuint divisor);
}  // namespace gl

#endif  // LIBGL_ENTRY_POINTS_GL_4_3_AUTOGEN_H_
