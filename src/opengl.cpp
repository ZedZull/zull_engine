// "Magic" that ensures the correct calling convention is used
#ifndef APIENTRY
#define APIENTRY
#endif
#ifndef APIENTRYP
#define APIENTRYP APIENTRY *
#endif

// OpenGL type definitions
typedef unsigned int GLenum;
typedef float GLfloat;
typedef unsigned int GLbitfield;

// OpenGL constants
#define GL_COLOR_BUFFER_BIT 0x00004000
#define GL_SRC_ALPHA 0x0302
#define GL_ONE_MINUS_SRC_ALPHA 0x0303
#define GL_CULL_FACE 0x0B44
#define GL_BLEND 0x0BE2

// OpenGL function type definitions
typedef void (APIENTRYP PFNGLBLENDFUNCPROC) (GLenum sfactor, GLenum dfactor);
typedef void (APIENTRYP PFNGLCLEARPROC) (GLbitfield mask);
typedef void (APIENTRYP PFNGLCLEARCOLORPROC) (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
typedef void (APIENTRYP PFNGLENABLEPROC) (GLenum cap);

// OpenGL function prototypes
PFNGLCLEARPROC glClear;
PFNGLCLEARCOLORPROC glClearColor;
PFNGLENABLEPROC glEnable;
PFNGLBLENDFUNCPROC glBlendFunc;

void load_opengl_functions() {
    glBlendFunc = (PFNGLBLENDFUNCPROC)glfwGetProcAddress("glBlendFunc");
    glClear = (PFNGLCLEARPROC)glfwGetProcAddress("glClear");
    glClearColor = (PFNGLCLEARCOLORPROC)glfwGetProcAddress("glClearColor");
    glEnable = (PFNGLENABLEPROC)glfwGetProcAddress("glEnable");
}
