#include <GL/gl.h>
#include <GL/glu.h>
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
        fail("Getting wglGetProcAddress failed.");
        return false;
    }

    wglCreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(
            wglGetProcAddress("wglCreateContextAttribsARB"));

    if (wglCreateContextAttribsARB == nullptr) {
        fail("Getting wglGetProcAddress failed.");
        return false;
    }

    glCreateShader = reinterpret_cast<PFNGLCREATESHADERPROC>(wglGetProcAddress("glCreateShader"));

    if (glCreateShader == nullptr) {
        fail("glCreateShader failed.");
        return false;
    }

    glShaderSource = reinterpret_cast<PFNGLSHADERSOURCEPROC>(wglGetProcAddress("glShaderSource"));

    if (glShaderSource == nullptr) {
        fail("glShaderSource failed.");
        return false;
    }

    glCompileShader = reinterpret_cast<PFNGLCOMPILESHADERPROC>(wglGetProcAddress("glCompileShader"));

    if (glCompileShader == nullptr) {
        fail("glCompileShader failed.");
        return false;
    }

    glGetShaderiv = reinterpret_cast<PFNGLGETSHADERIVPROC>(wglGetProcAddress("glGetShaderiv"));

    if (glGetShaderiv == nullptr) {
        fail("glGetShaderiv failed.");
        return false;
    }

    glGetShaderInfoLog = reinterpret_cast<PFNGLGETSHADERINFOLOGPROC>(
            wglGetProcAddress("glGetShaderInfoLog"));

    if (glGetShaderInfoLog == nullptr) {
        fail("glGetShaderInfoLog failed.");
        return false;
    }

    glDeleteShader = reinterpret_cast<PFNGLDELETESHADERPROC>(wglGetProcAddress("glDeleteShader"));

    if (glDeleteShader == nullptr) {
        fail("glDeleteShader failed.");
        return false;
    }

    glCreateProgram = reinterpret_cast<PFNGLCREATEPROGRAMPROC>(wglGetProcAddress("glCreateProgram"));

    if (glCreateProgram == nullptr) {
        fail("glCreateProgram failed.");
        return false;
    }

    glDeleteProgram = reinterpret_cast<PFNGLDELETEPROGRAMPROC>(wglGetProcAddress("glDeleteProgram"));

    if (glDeleteProgram == nullptr) {
        fail("glDeleteProgram failed.");
        return false;
    }

    glAttachShader = reinterpret_cast<PFNGLATTACHSHADERPROC>(wglGetProcAddress("glAttachShader"));

    if (glAttachShader == nullptr) {
        fail("glAttachShader failed.");
        return false;
    }

    glLinkProgram = reinterpret_cast<PFNGLLINKPROGRAMARBPROC>(wglGetProcAddress("glLinkProgramARB"));

    if (glLinkProgram == nullptr) {
        fail("glLinkProgram failed.");
        return false;
    }

    glGetProgramiv = reinterpret_cast<PFNGLGETPROGRAMIVPROC>(wglGetProcAddress("glGetProgramiv"));

    if (glGetProgramiv == nullptr) {
        fail("glGetProgramiv failed.");
        return false;
    }

    glGetProgramInfoLog = reinterpret_cast<PFNGLGETPROGRAMINFOLOGPROC>(wglGetProcAddress("glGetProgramInfoLog"));

    if (glGetProgramInfoLog == nullptr) {
        fail("glGetProgramInfoLog failed.");
        return false;
    }

    glDetachShader = reinterpret_cast<PFNGLDETACHSHADERPROC>(wglGetProcAddress("glDetachShader"));

    if (glDetachShader == nullptr) {
        fail("glDetachShader failed.");
        return false;
    }

    glGenBuffers = reinterpret_cast<PFNGLGENBUFFERSARBPROC>(wglGetProcAddress("glGenBuffersARB"));

    if (glGenBuffers == nullptr) {
        fail("glGenBuffers() failed.");
        return false;
    }

    glBindBuffer = reinterpret_cast<PFNGLBINDBUFFERARBPROC>(wglGetProcAddress("glBindBufferARB"));

    if (glBindBuffer == nullptr) {
        fail("glBindBuffer() failed.");
        return false;
    }

    glBufferData = reinterpret_cast<PFNGLBUFFERDATAARBPROC>(wglGetProcAddress("glBufferDataARB"));

    if (glBufferData == nullptr) {
        fail("glBufferData() failed.");
        return false;
    }

    glGenVertexArrays = reinterpret_cast<PFNGLGENVERTEXARRAYSPROC>(wglGetProcAddress("glGenVertexArrays"));

    if (glGenVertexArrays == nullptr) {
        fail("glGenVertexArrays() failed.");
        return false;
    }

    glBindVertexArray = reinterpret_cast<PFNGLBINDVERTEXARRAYPROC>(wglGetProcAddress("glBindVertexArray"));

    if (glBindVertexArray == nullptr) {
        fail("glBindVertexArray() failed.");
        return false;
    }

    glVertexAttribPointer = reinterpret_cast<PFNGLVERTEXATTRIBPOINTERPROC>(wglGetProcAddress("glVertexAttribPointer"));

    if (glVertexAttribPointer == nullptr) {
        fail("glVertexAttribPointer() failed.");
        return false;
    }

    glDeleteVertexArrays = reinterpret_cast<PFNGLDELETEVERTEXARRAYSPROC >(
            wglGetProcAddress("glDeleteVertexArrays"));

    if (glDeleteVertexArrays == nullptr) {
        fail("glDeleteVertexArrays() failed.");
        return false;
    }

    glUseProgram = reinterpret_cast<PFNGLUSEPROGRAMPROC>(wglGetProcAddress("glUseProgram"));

    if (glUseProgram == nullptr) {
        fail("glUseProgram() failed.");
        return false;
    }

    glEnableVertexAttribArray = reinterpret_cast<PFNGLENABLEVERTEXATTRIBARRAYPROC>(
            wglGetProcAddress("glEnableVertexAttribArray"));

    if (glEnableVertexAttribArray == nullptr) {
        fail("glEnableVertexAttribArray() failed.");
        return false;
    }

    glDisableVertexAttribArray = reinterpret_cast<PFNGLDISABLEVERTEXATTRIBARRAYPROC>(
            wglGetProcAddress("glDisableVertexAttribArray"));

    if (glDisableVertexAttribArray == nullptr) {
        fail("glDisableVertexAttribArray() failed.");
        return false;
    }

    return true;
}