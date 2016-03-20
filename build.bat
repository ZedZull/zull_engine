@echo off

set executable_name=zull
set compiler_flags=/nologo /FC /MT /GR- /EHa- /WX /W4 /wd4100 /wd4996 /wd4244 /wd4702 /wd4189 /Zi /Fe%executable_name% /I..\external\glfw\include /I..\external\lua-5.3.2\include
set linker_flags=/LIBPATH:..\external\glfw\lib /LIBPATH:..\external\lua-5.3.2\lib glfw3.lib lua5.3.2.lib opengl32.lib gdi32.lib user32.lib shell32.lib /NODEFAULTLIB:LIBCMTD

if not exist build mkdir build

pushd build
cl %compiler_flags% ..\src\unity_build.cpp /link %linker_flags%
popd build
