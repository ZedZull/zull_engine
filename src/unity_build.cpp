#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define ZED_IMPLEMENTATION
#include "zed.h"

#include "input.cpp"
#include "opengl.cpp"
#include "graphics.cpp"
#include "scripting.cpp"

#include "main.cpp"
