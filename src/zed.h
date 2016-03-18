/////////////////////////////////////////////////////////////////////////////////////////
//
// zed.h - public domain general purpose utilities
// (inspired by the excellent stb libraries: https://github.com/nothings/stb)
//
// This header file contains a collection of useful typedefs and utilities that I use
// often in my projects.
//
// LICENSE
//
//    This software is in the public domain. Where that dedication is not recognized, you
//    are granted a perpetual, irrevocable license to copy, distribute, and modify this
//    file as you see fit.
//
// USAGE
//
//    #define the symbol ZED_IMPLEMENTATION in *one* C/C++ file before the #include of
//    this file; the implementation will be generated in that file.
//
//    If you define the symbol ZED_STATIC, then the implementation will be private to
//    that file.
//
//    Immediately after this block comment is the "header file" section. This section
//    includes documentation for each API function.
//

#pragma once

#ifdef ZED_STATIC
#define ZED_DEF static
#else
#define ZED_DEF extern
#endif

#include <stdio.h>
#include <stdlib.h>

/////////////////////////////////////////////////////////////////////////////////////////
//
// GENERAL DEFINITIONS
//

#define internal static
#define persist static

typedef signed char s8;
typedef short s16;
typedef int s32;
typedef long long s64;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef float f32;
typedef double f64;

// Calculates the number of elements in an array
#define array_count(array) (sizeof(array) / sizeof((array)[0]))

// Outputs a printf-style formatted error message and immediately terminates the program
#define fatal(...) do { fprintf(stderr, "(%s:%d) Fatal error: ", __FILE__, __LINE__); fprintf(stderr, __VA_ARGS__); fputs("\n", stderr); exit(1); } while (0)

/////////////////////////////////////////////////////////////////////////////////////////
//
// FILE I/O
//

// Allocates and returns a buffer with the contents of a file
//    char *filename    -- the name of the file to read
//    size_t *length    -- outputs the length of the file 
ZED_DEF void *read_file(char *filename, size_t *length);

// Writes data to a file
//    char *filename    -- the name of the file to write
//    void *data        -- the data to write to the file
//    size_t length     -- the length of 'data'
ZED_DEF bool write_file(char *filename, void *data, size_t length);

#ifdef ZED_IMPLEMENTATION

ZED_DEF void *read_file(char *filename, size_t *length) {
    FILE *fp = fopen(filename, "rb");

    if (!fp) {
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    size_t len = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    u8 *buffer = (u8 *)malloc(len + 1);
    fread(buffer, 1, len, fp);
    buffer[len] = 0;

    fclose(fp);

    if (length) {
        *length = len;
    }

    return buffer;
}

ZED_DEF bool write_file(char *filename, void *data, size_t length) {
    FILE *fp = fopen(filename, "wb");

    if (fp) {
        fwrite(data, 1, length, fp);
        fclose(fp);
    }

    return (fp != NULL);
}

#endif // ZED_IMPLEMENTATION
