//
// Copyright(c) 2016 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// entry_points_gles_3_1.h : Defines the GLES 3.1 entry points.

#ifndef LIBGLESV2_ENTRYPOINTGLES31_H_
#define LIBGLESV2_ENTRYPOINTGLES31_H_

#include <GLES3/gl31.h>
#include <export.h>

// we include the platform.h header since it undefines the conflicting MemoryBarrier macro
#include "common/platform.h"

namespace gl
{

ANGLE_EXPORT void GL_APIENTRY DispatchCompute(GLuint numGroupsX,
                                              GLuint numGroupsY,
                                              GLuint numGroupsZ);
ANGLE_EXPORT void GL_APIENTRY DispatchComputeIndirect(GLintptr indirect);
ANGLE_EXPORT void GL_APIENTRY DrawArraysIndirect(GLenum mode, const void *indirect);
ANGLE_EXPORT void GL_APIENTRY DrawElementsIndirect(GLenum mode, GLenum type, const void *indirect);
ANGLE_EXPORT void GL_APIENTRY FramebufferParameteri(GLenum target, GLenum pname, GLint param);
ANGLE_EXPORT void GL_APIENTRY GetFramebufferParameteriv(GLenum target, GLenum pname, GLint *params);
ANGLE_EXPORT void GL_APIENTRY GetProgramInterfaceiv(GLuint program,
                                                    GLenum programInterface,
                                                    GLenum pname,
                                                    GLint *params);
ANGLE_EXPORT GLuint GL_APIENTRY GetProgramResourceIndex(GLuint program,
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
ANGLE_EXPORT GLint GL_APIENTRY GetProgramResourceLocation(GLuint program,
                                                          GLenum programInterface,
                                                          const GLchar *name);
ANGLE_EXPORT void GL_APIENTRY UseProgramStages(GLuint pipeline, GLbitfield stages, GLuint program);
ANGLE_EXPORT void GL_APIENTRY ActiveShaderProgram(GLuint pipeline, GLuint program);
ANGLE_EXPORT GLuint GL_APIENTRY CreateShaderProgramv(GLenum type,
                                                     GLsizei count,
                                                     const GLchar *const *strings);
ANGLE_EXPORT void GL_APIENTRY BindProgramPipeline(GLuint pipeline);
ANGLE_EXPORT void GL_APIENTRY DeleteProgramPipelines(GLsizei n, const GLuint *pipelines);
ANGLE_EXPORT void GL_APIENTRY GenProgramPipelines(GLsizei n, GLuint *pipelines);
ANGLE_EXPORT GLboolean GL_APIENTRY IsProgramPipeline(GLuint pipeline);
ANGLE_EXPORT void GL_APIENTRY GetProgramPipelineiv(GLuint pipeline, GLenum pname, GLint *params);
ANGLE_EXPORT void GL_APIENTRY ProgramUniform1i(GLuint program, GLint location, GLint v0);
ANGLE_EXPORT void GL_APIENTRY ProgramUniform2i(GLuint program, GLint location, GLint v0, GLint v1);
ANGLE_EXPORT void GL_APIENTRY
ProgramUniform3i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
ANGLE_EXPORT void GL_APIENTRY
ProgramUniform4i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
ANGLE_EXPORT void GL_APIENTRY ProgramUniform1ui(GLuint program, GLint location, GLuint v0);
ANGLE_EXPORT void GL_APIENTRY ProgramUniform2ui(GLuint program,
                                                GLint location,
                                                GLuint v0,
                                                GLuint v1);
ANGLE_EXPORT void GL_APIENTRY
ProgramUniform3ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
ANGLE_EXPORT void GL_APIENTRY
ProgramUniform4ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
ANGLE_EXPORT void GL_APIENTRY ProgramUniform1f(GLuint program, GLint location, GLfloat v0);
ANGLE_EXPORT void GL_APIENTRY ProgramUniform2f(GLuint program,
                                               GLint location,
                                               GLfloat v0,
                                               GLfloat v1);
ANGLE_EXPORT void GL_APIENTRY
ProgramUniform3f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
ANGLE_EXPORT void GL_APIENTRY
ProgramUniform4f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
ANGLE_EXPORT void GL_APIENTRY ProgramUniform1iv(GLuint program,
                                                GLint location,
                                                GLsizei count,
                                                const GLint *value);
ANGLE_EXPORT void GL_APIENTRY ProgramUniform2iv(GLuint program,
                                                GLint location,
                                                GLsizei count,
                                                const GLint *value);
ANGLE_EXPORT void GL_APIENTRY ProgramUniform3iv(GLuint program,
                                                GLint location,
                                                GLsizei count,
                                                const GLint *value);
ANGLE_EXPORT void GL_APIENTRY ProgramUniform4iv(GLuint program,
                                                GLint location,
                                                GLsizei count,
                                                const GLint *value);
ANGLE_EXPORT void GL_APIENTRY ProgramUniform1uiv(GLuint program,
                                                 GLint location,
                                                 GLsizei count,
                                                 const GLuint *value);
ANGLE_EXPORT void GL_APIENTRY ProgramUniform2uiv(GLuint program,
                                                 GLint location,
                                                 GLsizei count,
                                                 const GLuint *value);
ANGLE_EXPORT void GL_APIENTRY ProgramUniform3uiv(GLuint program,
                                                 GLint location,
                                                 GLsizei count,
                                                 const GLuint *value);
ANGLE_EXPORT void GL_APIENTRY ProgramUniform4uiv(GLuint program,
                                                 GLint location,
                                                 GLsizei count,
                                                 const GLuint *value);
ANGLE_EXPORT void GL_APIENTRY ProgramUniform1fv(GLuint program,
                                                GLint location,
                                                GLsizei count,
                                                const GLfloat *value);
ANGLE_EXPORT void GL_APIENTRY ProgramUniform2fv(GLuint program,
                                                GLint location,
                                                GLsizei count,
                                                const GLfloat *value);
ANGLE_EXPORT void GL_APIENTRY ProgramUniform3fv(GLuint program,
                                                GLint location,
                                                GLsizei count,
                                                const GLfloat *value);
ANGLE_EXPORT void GL_APIENTRY ProgramUniform4fv(GLuint program,
                                                GLint location,
                                                GLsizei count,
                                                const GLfloat *value);
ANGLE_EXPORT void GL_APIENTRY ProgramUniformMatrix2fv(GLuint program,
                                                      GLint location,
                                                      GLsizei count,
                                                      GLboolean transpose,
                                                      const GLfloat *value);
ANGLE_EXPORT void GL_APIENTRY ProgramUniformMatrix3fv(GLuint program,
                                                      GLint location,
                                                      GLsizei count,
                                                      GLboolean transpose,
                                                      const GLfloat *value);
ANGLE_EXPORT void GL_APIENTRY ProgramUniformMatrix4fv(GLuint program,
                                                      GLint location,
                                                      GLsizei count,
                                                      GLboolean transpose,
                                                      const GLfloat *value);
ANGLE_EXPORT void GL_APIENTRY ProgramUniformMatrix2x3fv(GLuint program,
                                                        GLint location,
                                                        GLsizei count,
                                                        GLboolean transpose,
                                                        const GLfloat *value);
ANGLE_EXPORT void GL_APIENTRY ProgramUniformMatrix3x2fv(GLuint program,
                                                        GLint location,
                                                        GLsizei count,
                                                        GLboolean transpose,
                                                        const GLfloat *value);
ANGLE_EXPORT void GL_APIENTRY ProgramUniformMatrix2x4fv(GLuint program,
                                                        GLint location,
                                                        GLsizei count,
                                                        GLboolean transpose,
                                                        const GLfloat *value);
ANGLE_EXPORT void GL_APIENTRY ProgramUniformMatrix4x2fv(GLuint program,
                                                        GLint location,
                                                        GLsizei count,
                                                        GLboolean transpose,
                                                        const GLfloat *value);
ANGLE_EXPORT void GL_APIENTRY ProgramUniformMatrix3x4fv(GLuint program,
                                                        GLint location,
                                                        GLsizei count,
                                                        GLboolean transpose,
                                                        const GLfloat *value);
ANGLE_EXPORT void GL_APIENTRY ProgramUniformMatrix4x3fv(GLuint program,
                                                        GLint location,
                                                        GLsizei count,
                                                        GLboolean transpose,
                                                        const GLfloat *value);
ANGLE_EXPORT void GL_APIENTRY ValidateProgramPipeline(GLuint pipeline);
ANGLE_EXPORT void GL_APIENTRY GetProgramPipelineInfoLog(GLuint pipeline,
                                                        GLsizei bufSize,
                                                        GLsizei *length,
                                                        GLchar *infoLog);
ANGLE_EXPORT void GL_APIENTRY BindImageTexture(GLuint unit,
                                               GLuint texture,
                                               GLint level,
                                               GLboolean layered,
                                               GLint layer,
                                               GLenum access,
                                               GLenum format);
ANGLE_EXPORT void GL_APIENTRY GetBooleani_v(GLenum target, GLuint index, GLboolean *data);

ANGLE_EXPORT void GL_APIENTRY MemoryBarrier(GLbitfield barriers);
ANGLE_EXPORT void GL_APIENTRY MemoryBarrierByRegion(GLbitfield barriers);
ANGLE_EXPORT void GL_APIENTRY TexStorage2DMultisample(GLenum target,
                                                      GLsizei samples,
                                                      GLenum internalformat,
                                                      GLsizei width,
                                                      GLsizei height,
                                                      GLboolean fixedsamplelocations);
ANGLE_EXPORT void GL_APIENTRY GetMultisamplefv(GLenum pname, GLuint index, GLfloat *val);
ANGLE_EXPORT void GL_APIENTRY SampleMaski(GLuint maskNumber, GLbitfield mask);
ANGLE_EXPORT void GL_APIENTRY GetTexLevelParameteriv(GLenum target,
                                                     GLint level,
                                                     GLenum pname,
                                                     GLint *params);
ANGLE_EXPORT void GL_APIENTRY GetTexLevelParameterfv(GLenum target,
                                                     GLint level,
                                                     GLenum pname,
                                                     GLfloat *params);
ANGLE_EXPORT void GL_APIENTRY BindVertexBuffer(GLuint bindingindex,
                                               GLuint buffer,
                                               GLintptr offset,
                                               GLsizei stride);
ANGLE_EXPORT void GL_APIENTRY VertexAttribFormat(GLuint attribindex,
                                                 GLint size,
                                                 GLenum type,
                                                 GLboolean normalized,
                                                 GLuint relativeoffset);
ANGLE_EXPORT void GL_APIENTRY VertexAttribIFormat(GLuint attribindex,
                                                  GLint size,
                                                  GLenum type,
                                                  GLuint relativeoffset);
ANGLE_EXPORT void GL_APIENTRY VertexAttribBinding(GLuint attribindex, GLuint bindingindex);
ANGLE_EXPORT void GL_APIENTRY VertexBindingDivisor(GLuint bindingindex, GLuint divisor);
};

#endif  // LIBGLESV2_ENTRYPOINTGLES31_H_
