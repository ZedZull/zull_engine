@echo off

if not defined VisualStudioVersion call "%ProgramFiles(x86)%\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x86

set executable_name=zull
set compiler_flags=/nologo /FC /MT /GR- /EHa- /WX /W4 /wd4100 /wd4996 /wd4244 /wd4702 /wd4189 /Zi /Fe%executable_name% /I..\external\glfw\include /I..\external\LuaJIT-2.0.4\include
set linker_flags=/LIBPATH:..\external\glfw\lib /LIBPATH:..\external\LuaJIT-2.0.4\lib glfw3.lib lua51.lib opengl32.lib gdi32.lib user32.lib shell32.lib /NODEFAULTLIB:LIBCMTD

if not exist build mkdir build

pushd build
cl %compiler_flags% ..\src\unity_build.cpp /link %linker_flags%
popd build
