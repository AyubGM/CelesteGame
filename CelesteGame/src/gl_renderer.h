#pragma once
#include "../vendor/glcorearb.h"
#define GL_GLEXT_PROTOTYPES
#include "../vendor/wglext.h"
#include "Logger.h"

static PFNGLCREATEPROGRAMPROC glCreateProgram_ptr;
static PFNGLDELETETEXTURESPROC glDeleteTextures_ptr;
static PFNGLGENTEXTURESPROC glGenTextures_ptr;
static PFNGLBINDTEXTUREPROC glBindTexture_ptr;
static PFNGLDRAWBUFFERPROC glDrawBuffer_ptr;
static PFNGLDRAWARRAYSPROC glDrawArrays_ptr;
static PFNGLCREATESHADERPROC glCreateShader_ptr;
static PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation_ptr;
static PFNGLUNIFORM1FPROC glUniform1f_ptr;
static PFNGLUNIFORM2FVPROC glUniform2fv_ptr;
static PFNGLUNIFORM3FVPROC glUniform3fv_ptr;
static PFNGLUNIFORM1IPROC glUniform1i_ptr;
static PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv_ptr;
static PFNGLVERTEXATTRIBDIVISORPROC glVertexAttribDivisor_ptr;
static PFNGLACTIVETEXTUREPROC glActiveTexture_ptr;
static PFNGLBUFFERSUBDATAPROC glBufferSubData_ptr;
static PFNGLDRAWARRAYSINSTANCEDPROC glDrawArraysInstanced_ptr;
static PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer_ptr;
static PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus_ptr;
static PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers_ptr;
static PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D_ptr;
static PFNGLDRAWBUFFERSPROC glDrawBuffers_ptr;
static PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers_ptr;
static PFNGLBLENDFUNCIPROC glBlendFunci_ptr;
static PFNGLBLENDEQUATIONPROC glBlendEquation_ptr;
static PFNGLCLEARBUFFERFVPROC glClearBufferfv_ptr;
static PFNGLSHADERSOURCEPROC glShaderSource_ptr;
static PFNGLCOMPILESHADERPROC glCompileShader_ptr;
static PFNGLGETSHADERIVPROC glGetShaderiv_ptr;
static PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog_ptr;
static PFNGLATTACHSHADERPROC glAttachShader_ptr;
static PFNGLLINKPROGRAMPROC glLinkProgram_ptr;
static PFNGLVALIDATEPROGRAMPROC glValidateProgram_ptr;
static PFNGLGETPROGRAMIVPROC glGetProgramiv_ptr;
static PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog_ptr;
static PFNGLGENBUFFERSPROC glGenBuffers_ptr;
static PFNGLGENVERTEXARRAYSPROC glGenVertexArrays_ptr;
static PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation_ptr;
static PFNGLBINDVERTEXARRAYPROC glBindVertexArray_ptr;
static PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray_ptr;
static PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer_ptr;
static PFNGLBINDBUFFERPROC glBindBuffer_ptr;
static PFNGLBINDBUFFERBASEPROC glBindBufferBase_ptr;
static PFNGLBUFFERDATAPROC glBufferData_ptr;
static PFNGLGETVERTEXATTRIBPOINTERVPROC glGetVertexAttribPointerv_ptr;
static PFNGLUSEPROGRAMPROC glUseProgram_ptr;
static PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays_ptr;
static PFNGLDELETEBUFFERSPROC glDeleteBuffers_ptr;
static PFNGLDELETEPROGRAMPROC glDeleteProgram_ptr;
static PFNGLDETACHSHADERPROC glDetachShader_ptr;
static PFNGLDELETESHADERPROC glDeleteShader_ptr;
static PFNGLDRAWELEMENTSINSTANCEDPROC glDrawElementsInstanced_ptr;
static PFNGLGENERATEMIPMAPPROC glGenerateMipmap_ptr;
static PFNGLDEBUGMESSAGECALLBACKPROC glDebugMessageCallback_ptr;



void* PlatformLoadGLFunction(const char* fnName)
{
	PROC proc = wglGetProcAddress(fnName);

	if (!proc)
	{
		static HMODULE openglDLL = LoadLibraryA("opengl32.dll");
		proc = GetProcAddress(openglDLL, fnName);

		if (!proc)
		{
			SD_ASSERT(false, "Failed to load gl function {}", fnName);
			return nullptr;
		}

	}

	return (void*)proc;
}

void GlLoadFunctions()
{
	glCreateProgram_ptr = (PFNGLCREATEPROGRAMPROC)PlatformLoadGLFunction("glCreateProgram");
	glDeleteTextures_ptr = (PFNGLDELETETEXTURESPROC)PlatformLoadGLFunction("glDeleteTextures");
	glGenTextures_ptr = (PFNGLGENTEXTURESPROC)PlatformLoadGLFunction("glGenTextures");
	glBindTexture_ptr = (PFNGLBINDTEXTUREPROC)PlatformLoadGLFunction("glBindTexture");
	glDrawArrays_ptr = (PFNGLDRAWARRAYSPROC)PlatformLoadGLFunction("glDrawArrays");
	glCreateShader_ptr = (PFNGLCREATESHADERPROC)PlatformLoadGLFunction("glCreateShader");
	glGetUniformLocation_ptr = (PFNGLGETUNIFORMLOCATIONPROC)PlatformLoadGLFunction("glGetUniformLocation");
	glUniform1f_ptr = (PFNGLUNIFORM1FPROC)PlatformLoadGLFunction("glUniform1f");
	glUniform2fv_ptr = (PFNGLUNIFORM2FVPROC)PlatformLoadGLFunction("glUniform2fv");
	glUniform3fv_ptr = (PFNGLUNIFORM3FVPROC)PlatformLoadGLFunction("glUniform3fv");
	glUniform1i_ptr = (PFNGLUNIFORM1IPROC)PlatformLoadGLFunction("glUniform1i");
	glUniformMatrix4fv_ptr = (PFNGLUNIFORMMATRIX4FVPROC)PlatformLoadGLFunction("glUniformMatrix4fv");
	glVertexAttribDivisor_ptr = (PFNGLVERTEXATTRIBDIVISORPROC)PlatformLoadGLFunction("glVertexAttribDivisor");
	glActiveTexture_ptr = (PFNGLACTIVETEXTUREPROC)PlatformLoadGLFunction("glActiveTexture");
	glBufferSubData_ptr = (PFNGLBUFFERSUBDATAPROC)PlatformLoadGLFunction("glBufferSubData");
	glDrawArraysInstanced_ptr = (PFNGLDRAWARRAYSINSTANCEDPROC)PlatformLoadGLFunction("glDrawArraysInstanced");
	glBindFramebuffer_ptr = (PFNGLBINDFRAMEBUFFERPROC)PlatformLoadGLFunction("glBindFramebuffer");
	glCheckFramebufferStatus_ptr = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)PlatformLoadGLFunction("glCheckFramebufferStatus");
	glGenFramebuffers_ptr = (PFNGLGENFRAMEBUFFERSPROC)PlatformLoadGLFunction("glGenFramebuffers");
	glFramebufferTexture2D_ptr = (PFNGLFRAMEBUFFERTEXTURE2DPROC)PlatformLoadGLFunction("glFramebufferTexture2D");
	glDrawBuffers_ptr = (PFNGLDRAWBUFFERSPROC)PlatformLoadGLFunction("glDrawBuffers");
	glDeleteFramebuffers_ptr = (PFNGLDELETEFRAMEBUFFERSPROC)PlatformLoadGLFunction("glDeleteFramebuffers");
	glBlendFunci_ptr = (PFNGLBLENDFUNCIPROC)PlatformLoadGLFunction("glBlendFunci");
	glBlendEquation_ptr = (PFNGLBLENDEQUATIONPROC)PlatformLoadGLFunction("glBlendEquation");
	glClearBufferfv_ptr = (PFNGLCLEARBUFFERFVPROC)PlatformLoadGLFunction("glClearBufferfv");
	glShaderSource_ptr = (PFNGLSHADERSOURCEPROC)PlatformLoadGLFunction("glShaderSource");
	glCompileShader_ptr = (PFNGLCOMPILESHADERPROC)PlatformLoadGLFunction("glCompileShader");
	glGetShaderiv_ptr = (PFNGLGETSHADERIVPROC)PlatformLoadGLFunction("glGetShaderiv");
	glGetShaderInfoLog_ptr = (PFNGLGETSHADERINFOLOGPROC)PlatformLoadGLFunction("glGetShaderInfoLog");
	glAttachShader_ptr = (PFNGLATTACHSHADERPROC)PlatformLoadGLFunction("glAttachShader");
	glLinkProgram_ptr = (PFNGLLINKPROGRAMPROC)PlatformLoadGLFunction("glLinkProgram");
	glValidateProgram_ptr = (PFNGLVALIDATEPROGRAMPROC)PlatformLoadGLFunction("glValidateProgram");
	glGetProgramiv_ptr = (PFNGLGETPROGRAMIVPROC)PlatformLoadGLFunction("glGetProgramiv");
	glGetProgramInfoLog_ptr = (PFNGLGETPROGRAMINFOLOGPROC)PlatformLoadGLFunction("glGetProgramInfoLog");
	glGenBuffers_ptr = (PFNGLGENBUFFERSPROC)PlatformLoadGLFunction("glGenBuffers");
	glGenVertexArrays_ptr = (PFNGLGENVERTEXARRAYSPROC)PlatformLoadGLFunction("glGenVertexArrays");
	glGetAttribLocation_ptr = (PFNGLGETATTRIBLOCATIONPROC)PlatformLoadGLFunction("glGetAttribLocation");
	glBindVertexArray_ptr = (PFNGLBINDVERTEXARRAYPROC)PlatformLoadGLFunction("glBindVertexArray");
	glEnableVertexAttribArray_ptr = (PFNGLENABLEVERTEXATTRIBARRAYPROC)PlatformLoadGLFunction("glEnableVertexAttribArray");
	glVertexAttribPointer_ptr = (PFNGLVERTEXATTRIBPOINTERPROC)PlatformLoadGLFunction("glVertexAttribPointer");
	glBindBuffer_ptr = (PFNGLBINDBUFFERPROC)PlatformLoadGLFunction("glBindBuffer");
	glBindBufferBase_ptr = (PFNGLBINDBUFFERBASEPROC)PlatformLoadGLFunction("glBindBufferBase");
	glBufferData_ptr = (PFNGLBUFFERDATAPROC)PlatformLoadGLFunction("glBufferData");
	glGetVertexAttribPointerv_ptr = (PFNGLGETVERTEXATTRIBPOINTERVPROC)PlatformLoadGLFunction("glGetVertexAttribPointerv");
	glUseProgram_ptr = (PFNGLUSEPROGRAMPROC)PlatformLoadGLFunction("glUseProgram");
	glDeleteVertexArrays_ptr = (PFNGLDELETEVERTEXARRAYSPROC)PlatformLoadGLFunction("glDeleteVertexArrays");
	glDeleteBuffers_ptr = (PFNGLDELETEBUFFERSPROC)PlatformLoadGLFunction("glDeleteBuffers");
	glDeleteProgram_ptr = (PFNGLDELETEPROGRAMPROC)PlatformLoadGLFunction("glDeleteProgram");
	glDetachShader_ptr = (PFNGLDETACHSHADERPROC)PlatformLoadGLFunction("glDetachShader");
	glDeleteShader_ptr = (PFNGLDELETESHADERPROC)PlatformLoadGLFunction("glDeleteShader");
	glDrawElementsInstanced_ptr = (PFNGLDRAWELEMENTSINSTANCEDPROC)PlatformLoadGLFunction("glDrawElementsInstanced");
	glGenerateMipmap_ptr = (PFNGLGENERATEMIPMAPPROC)PlatformLoadGLFunction("glGenerateMipmap");
	glDebugMessageCallback_ptr = (PFNGLDEBUGMESSAGECALLBACKPROC)PlatformLoadGLFunction("glDebugMessageCallback");
}

// Exposed API

GLAPI GLuint APIENTRY glCreateProgram(void)
{
	return glCreateProgram_ptr();
}

GLAPI void APIENTRY glDeleteTextures(GLsizei n, const GLuint* textures)
{
	glDeleteTextures_ptr(n, textures);
}

GLAPI void APIENTRY glGenTextures(GLsizei n, GLuint* textures)
{
	glGenTextures_ptr(n, textures);
}

GLAPI void APIENTRY glBindTexture(GLenum target, GLuint texture)
{
	glBindTexture_ptr(target, texture);
}

void glDrawArrays(GLenum mode, GLint first, GLsizei count)
{
	glDrawArrays_ptr(mode, first, count);
}

GLuint glCreateShader(GLenum shaderType)
{
	return glCreateShader_ptr(shaderType);
}

GLint glGetUniformLocation(GLuint program, const GLchar* name)
{
	return glGetUniformLocation_ptr(program, name);
}

void glUniform1f(GLint location, GLfloat v0)
{
	glUniform1f_ptr(location, v0);
}

void glUniform2fv(GLint location, GLsizei count, const GLfloat* value)
{
	glUniform2fv_ptr(location, count, value);
}

void glUniform3fv(GLint location, GLsizei count, const GLfloat* value)
{
	glUniform3fv_ptr(location, count, value);
}

void glUniform1i(GLint location, GLint v0)
{
	glUniform1i_ptr(location, v0);
}

void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	glUniformMatrix4fv_ptr(location, count, transpose, value);
}

void glVertexAttribDivisor(GLuint index, GLuint divisor)
{
	glVertexAttribDivisor_ptr(index, divisor);
}

void glActiveTexture(GLenum texture)
{
	glActiveTexture_ptr(texture);
}

void glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void* data)
{
	glBufferSubData_ptr(target, offset, size, data);
}

void glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instanceCount)
{
	glDrawArraysInstanced_ptr(mode, first, count, instanceCount);
}

void glBindFramebuffer(GLenum target, GLuint framebuffer)
{
	glBindFramebuffer_ptr(target, framebuffer);
}

GLenum glCheckFramebufferStatus(GLenum target)
{
	return glCheckFramebufferStatus_ptr(target);
}

void glGenFramebuffers(GLsizei n, GLuint* framebuffers)
{
	glGenFramebuffers_ptr(n, framebuffers);
}

void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
	glFramebufferTexture2D_ptr(target, attachment, textarget, texture, level);
}

void glDrawBuffers(GLsizei n, const GLenum* bufs)
{
	glDrawBuffers_ptr(n, bufs);
}

void glDeleteFramebuffers(GLsizei n, const GLuint* framebuffers)
{
	glDeleteFramebuffers_ptr(n, framebuffers);
}

void glBlendFunci(GLuint buf, GLenum src, GLenum dst)
{
	glBlendFunci_ptr(buf, src, dst);
}

void glBlendEquation(GLenum mode)
{
	glBlendEquation_ptr(mode);
}

void glClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat* value)
{
	glClearBufferfv_ptr(buffer, drawbuffer, value);
}

void glShaderSource(GLuint shader, GLsizei count, const GLchar* const* strings, const GLint* lengths)
{
	glShaderSource_ptr(shader, count, strings, lengths);
}

void glCompileShader(GLuint shader)
{
	glCompileShader_ptr(shader);
}

void glGetShaderiv(GLuint shader, GLenum pname, GLint* params)
{
	glGetShaderiv_ptr(shader, pname, params);
}

void glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog)
{
	glGetShaderInfoLog_ptr(shader, bufSize, length, infoLog);
}

void glAttachShader(GLuint program, GLuint shader)
{
	glAttachShader_ptr(program, shader);
}

void glLinkProgram(GLuint program)
{
	glLinkProgram_ptr(program);
}

void glValidateProgram(GLuint program)
{
	glValidateProgram_ptr(program);
}

void glGetProgramiv(GLuint program, GLenum pname, GLint* params)
{
	glGetProgramiv_ptr(program, pname, params);
}

void glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog)
{
	glGetProgramInfoLog_ptr(program, bufSize, length, infoLog);
}

void glGenBuffers(GLsizei n, GLuint* buffers)
{
	glGenBuffers_ptr(n, buffers);
}

void glGenVertexArrays(GLsizei n, GLuint* arrays)
{
	glGenVertexArrays_ptr(n, arrays);
}

GLint glGetAttribLocation(GLuint program, const GLchar* name)
{
	return glGetAttribLocation_ptr(program, name);
}

void glBindVertexArray(GLuint array)
{
	glBindVertexArray_ptr(array);
}

void glEnableVertexAttribArray(GLuint index)
{
	glEnableVertexAttribArray_ptr(index);
}

void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
{
	glVertexAttribPointer_ptr(index, size, type, normalized, stride, pointer);
}

void glBindBuffer(GLenum target, GLuint buffer)
{
	glBindBuffer_ptr(target, buffer);
}

void glBindBufferBase(GLenum target, GLuint index, GLuint buffer)
{
	glBindBufferBase_ptr(target, index, buffer);
}

void glBufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage)
{
	glBufferData_ptr(target, size, data, usage);
}

void glGetVertexAttribPointerv(GLuint index, GLenum pname, void** pointer)
{
	glGetVertexAttribPointerv_ptr(index, pname, pointer);
}

void glUseProgram(GLuint program)
{
	glUseProgram_ptr(program);
}

void glDeleteVertexArrays(GLsizei n, const GLuint* arrays)
{
	glDeleteVertexArrays_ptr(n, arrays);
}

void glDeleteBuffers(GLsizei n, const GLuint* buffers)
{
	glDeleteBuffers_ptr(n, buffers);
}

void glDeleteProgram(GLuint program)
{
	glDeleteProgram_ptr(program);
}

void glDetachShader(GLuint program, GLuint shader)
{
	glDetachShader_ptr(program, shader);
}

void glDeleteShader(GLuint shader)
{
	glDeleteShader_ptr(shader);
}

void glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount)
{
	glDrawElementsInstanced_ptr(mode, count, type, indices, instancecount);
}

void glGenerateMipmap(GLenum target)
{
	glGenerateMipmap_ptr(target);
}

void glDebugMessageCallback(GLDEBUGPROC callback, const void* userParam)
{
	glDebugMessageCallback_ptr(callback, userParam);
}

// Loaded by default it seems, but I kept them here, just in case, must be OpenGL 1.0, and static linking
/*
static PFNGLTEXIMAGE2DPROC glTexImage2D_ptr;
static PFNGLTEXPARAMETERIPROC glTexParameteri_ptr;
static PFNGLTEXPARAMETERFVPROC glTexParameterfv_ptr;
static PFNGLCLEARPROC glClear_ptr;
static PFNGLCLEARCOLORPROC glClearColor_ptr;
static PFNGLREADBUFFERPROC glReadBuffer_ptr;
static PFNGLDEPTHMASKPROC glDepthMask_ptr;
static PFNGLDISABLEPROC glDisable_ptr;
static PFNGLENABLEPROC glEnable_ptr;
static PFNGLSCISSORPROC glScissor_ptr;
static PFNGLVIEWPORTPROC glViewport_ptr;
static PFNGLDEPTHFUNCPROC glDepthFunc_ptr;
static PFNGLCULLFACEPROC glCullFace_ptr;
static PFNGLBLENDFUNCPROC glBlendFunc_ptr;
static PFNGLFRONTFACEPROC glFrontFace_ptr;

glTexImage2D_ptr = (PFNGLTEXIMAGE2DPROC)platform_load_gl_function("glTexImage2D");
glTexParameteri_ptr = (PFNGLTEXPARAMETERIPROC)platform_load_gl_function("glTexParameteri");
glTexParameterfv_ptr = (PFNGLTEXPARAMETERFVPROC)platform_load_gl_function("glTexParameterfv");
glClear_ptr = (PFNGLCLEARPROC)platform_load_gl_function("glClear");
glClearColor_ptr = (PFNGLCLEARCOLORPROC)platform_load_gl_function("glClearColor");
glReadBuffer_ptr = (PFNGLREADBUFFERPROC)platform_load_gl_function("glReadBuffer");
glDepthMask_ptr = (PFNGLDEPTHMASKPROC)platform_load_gl_function("glDepthMask");
glDisable_ptr = (PFNGLDISABLEPROC)platform_load_gl_function("glDisable");
glEnable_ptr = (PFNGLENABLEPROC)platform_load_gl_function("glEnable");
glScissor_ptr = (PFNGLSCISSORPROC)platform_load_gl_function("glScissor");
glViewport_ptr = (PFNGLVIEWPORTPROC)platform_load_gl_function("glViewport");
glDepthFunc_ptr = (PFNGLDEPTHFUNCPROC)platform_load_gl_function("glDepthFunc");
glCullFace_ptr = (PFNGLCULLFACEPROC)platform_load_gl_function("glCullFace");
glBlendFunc_ptr = (PFNGLBLENDFUNCPROC)platform_load_gl_function("glBlendFunc");
glFrontFace_ptr = (PFNGLFRONTFACEPROC)platform_load_gl_function("glFrontFace");

GLAPI void APIENTRY glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width,
								  GLsizei height, GLint border, GLenum format, GLenum type,
								  const void *pixels)
{
  glTexImage2D_ptr(target, level, internalformat, width, height,
				   border, format, type, pixels);
}

GLAPI void APIENTRY glTexParameteri (GLenum target, GLenum pname, GLint param)
{
  glTexParameteri_ptr(target, pname, param);
}

GLAPI void APIENTRY glTexParameterfv (GLenum target, GLenum pname, const GLfloat *params)
{
  glTexParameterfv_ptr(target, pname, params);
}

GLAPI void APIENTRY glClear (GLbitfield mask)
{
  glClear_ptr(mask);
}

GLAPI void APIENTRY glClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
  glClearColor_ptr(red, green, blue, alpha);
}

void glReadBuffer(GLenum mode)
{
	glReadBuffer_ptr(mode);
}

void glDepthMask(GLboolean flag)
{
	glDepthMask_ptr(flag);
}

void glDisable(GLenum cap)
{
	glDisable_ptr(cap);
}

void glEnable(GLenum cap)
{
	glEnable_ptr(cap);
}

void glScissor(GLint x, GLint y, GLsizei width, GLsizei height)
{
	glScissor_ptr(x, y, width, height);
}

void glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
	glViewport_ptr(x, y, width, height);
}

void glDepthFunc(GLenum func)
{
	glDepthFunc_ptr(func);
}

void glCullFace(GLenum mode)
{
	glCullFace_ptr(mode);
}

void glBlendFunc(GLenum sfactor, GLenum dfactor)
{
	glBlendFunc_ptr(sfactor, dfactor);
}

void glFrontFace(GLenum mode)
{
	glFrontFace_ptr(mode);
}
*/