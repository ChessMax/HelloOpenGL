#include <GL/gl.h>
#include "gl/glext.h"
#include "gl/wglext.h"

PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = nullptr;
PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;

PFNGLCREATESHADERPROC glCreateShader = nullptr;
PFNGLSHADERSOURCEPROC glShaderSource = nullptr;
PFNGLCOMPILESHADERPROC glCompileShader = nullptr;
PFNGLGETSHADERIVPROC glGetShaderiv = nullptr;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = nullptr;
PFNGLDELETESHADERPROC glDeleteShader = nullptr;

PFNGLCREATEPROGRAMPROC glCreateProgram = nullptr;
PFNGLDELETEPROGRAMPROC glDeleteProgram = nullptr;
PFNGLATTACHSHADERPROC glAttachShader = nullptr;
PFNGLLINKPROGRAMARBPROC glLinkProgram = nullptr;
PFNGLGETPROGRAMIVPROC glGetProgramiv = nullptr;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = nullptr;
PFNGLDETACHSHADERPROC glDetachShader = nullptr;

PFNGLGENBUFFERSARBPROC glGenBuffers = nullptr;
PFNGLBINDBUFFERARBPROC glBindBuffer = nullptr;
PFNGLBUFFERDATAARBPROC glBufferData = nullptr;
PFNGLDELETEBUFFERSPROC glDeleteBuffers = nullptr;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = nullptr;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray = nullptr;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = nullptr;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = nullptr;

PFNGLUSEPROGRAMPROC glUseProgram = nullptr;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = nullptr;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = nullptr;

bool InitGLBindings() {
    wglChoosePixelFormatARB = reinterpret_cast<PFNWGLCHOOSEPIXELFORMATARBPROC>(
            wglGetProcAddress("wglChoosePixelFormatARB"));

    if (wglChoosePixelFormatARB == nullptr) {
        return fail("Getting wglGetProcAddress failed.");
    }

    wglCreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(
            wglGetProcAddress("wglCreateContextAttribsARB"));

    if (wglCreateContextAttribsARB == nullptr) {
        return fail("Getting wglGetProcAddress failed.");
    }

    glCreateShader = reinterpret_cast<PFNGLCREATESHADERPROC>(wglGetProcAddress("glCreateShader"));

    if (glCreateShader == nullptr) {
        return fail("glCreateShader failed.");
    }

    glShaderSource = reinterpret_cast<PFNGLSHADERSOURCEPROC>(wglGetProcAddress("glShaderSource"));

    if (glShaderSource == nullptr) {
        return fail("glShaderSource failed.");
    }

    glCompileShader = reinterpret_cast<PFNGLCOMPILESHADERPROC>(wglGetProcAddress("glCompileShader"));

    if (glCompileShader == nullptr) {
        return fail("glCompileShader failed.");
    }

    glGetShaderiv = reinterpret_cast<PFNGLGETSHADERIVPROC>(wglGetProcAddress("glGetShaderiv"));

    if (glGetShaderiv == nullptr) {
        return fail("glGetShaderiv failed.");
    }

    glGetShaderInfoLog = reinterpret_cast<PFNGLGETSHADERINFOLOGPROC>(
            wglGetProcAddress("glGetShaderInfoLog"));

    if (glGetShaderInfoLog == nullptr) {
        return fail("glGetShaderInfoLog failed.");
    }

    glDeleteShader = reinterpret_cast<PFNGLDELETESHADERPROC>(wglGetProcAddress("glDeleteShader"));

    if (glDeleteShader == nullptr) {
        return fail("glDeleteShader failed.");
    }

    glCreateProgram = reinterpret_cast<PFNGLCREATEPROGRAMPROC>(wglGetProcAddress("glCreateProgram"));

    if (glCreateProgram == nullptr) {
        return fail("glCreateProgram failed.");
    }

    glDeleteProgram = reinterpret_cast<PFNGLDELETEPROGRAMPROC>(wglGetProcAddress("glDeleteProgram"));

    if (glDeleteProgram == nullptr) {
        return fail("glDeleteProgram failed.");
    }

    glAttachShader = reinterpret_cast<PFNGLATTACHSHADERPROC>(wglGetProcAddress("glAttachShader"));

    if (glAttachShader == nullptr) {
        return fail("glAttachShader failed.");
    }

    glLinkProgram = reinterpret_cast<PFNGLLINKPROGRAMARBPROC>(wglGetProcAddress("glLinkProgramARB"));

    if (glLinkProgram == nullptr) {
        return fail("glLinkProgram failed.");
    }

    glGetProgramiv = reinterpret_cast<PFNGLGETPROGRAMIVPROC>(wglGetProcAddress("glGetProgramiv"));

    if (glGetProgramiv == nullptr) {
        return fail("glGetProgramiv failed.");
    }

    glGetProgramInfoLog = reinterpret_cast<PFNGLGETPROGRAMINFOLOGPROC>(wglGetProcAddress("glGetProgramInfoLog"));

    if (glGetProgramInfoLog == nullptr) {
        return fail("glGetProgramInfoLog failed.");
    }

    glDetachShader = reinterpret_cast<PFNGLDETACHSHADERPROC>(wglGetProcAddress("glDetachShader"));

    if (glDetachShader == nullptr) {
        return fail("glDetachShader failed.");
    }

    glGenBuffers = reinterpret_cast<PFNGLGENBUFFERSARBPROC>(wglGetProcAddress("glGenBuffersARB"));

    if (glGenBuffers == nullptr) {
        return fail("glGenBuffers() failed.");
    }

    glBindBuffer = reinterpret_cast<PFNGLBINDBUFFERARBPROC>(wglGetProcAddress("glBindBufferARB"));

    if (glBindBuffer == nullptr) {
        return fail("glBindBuffer() failed.");
    }

    glBufferData = reinterpret_cast<PFNGLBUFFERDATAARBPROC>(wglGetProcAddress("glBufferDataARB"));

    if (glBufferData == nullptr) {
        return fail("glBufferData() failed.");
    }

    glGenVertexArrays = reinterpret_cast<PFNGLGENVERTEXARRAYSPROC>(wglGetProcAddress("glGenVertexArrays"));

    if (glGenVertexArrays == nullptr) {
        return fail("glGenVertexArrays() failed.");
    }

    glBindVertexArray = reinterpret_cast<PFNGLBINDVERTEXARRAYPROC>(wglGetProcAddress("glBindVertexArray"));

    if (glBindVertexArray == nullptr) {
        return fail("glBindVertexArray() failed.");
    }

    glVertexAttribPointer = reinterpret_cast<PFNGLVERTEXATTRIBPOINTERPROC>(wglGetProcAddress("glVertexAttribPointer"));

    if (glVertexAttribPointer == nullptr) {
        return fail("glVertexAttribPointer() failed.");
    }

    glDeleteVertexArrays = reinterpret_cast<PFNGLDELETEVERTEXARRAYSPROC >(
            wglGetProcAddress("glDeleteVertexArrays"));

    if (glDeleteVertexArrays == nullptr) {
        return fail("glDeleteVertexArrays() failed.");
    }

    glUseProgram = reinterpret_cast<PFNGLUSEPROGRAMPROC>(wglGetProcAddress("glUseProgram"));

    if (glUseProgram == nullptr) {
        return fail("glUseProgram() failed.");
    }

    glEnableVertexAttribArray = reinterpret_cast<PFNGLENABLEVERTEXATTRIBARRAYPROC>(
            wglGetProcAddress("glEnableVertexAttribArray"));

    if (glEnableVertexAttribArray == nullptr) {
        return fail("glEnableVertexAttribArray() failed.");
    }

    glDisableVertexAttribArray = reinterpret_cast<PFNGLDISABLEVERTEXATTRIBARRAYPROC>(
            wglGetProcAddress("glDisableVertexAttribArray"));

    if (glDisableVertexAttribArray == nullptr) {
        return fail("glDisableVertexAttribArray() failed.");
    }

    return true;
}