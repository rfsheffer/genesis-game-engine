//
//  util_stdlib.h
//  Utilities Standard C library. Anything we need to declare for platform support goes here.
//  Generally, we will be supporting the standard library that comes with the OS unless
//  we really see a reason (performance reason or other) to redeclare a standard C function
//  here.
//
//  Created by Ryan Sheffer on 14-02-08.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#ifndef UTIL_STDLIB_H
#define UTIL_STDLIB_H

#ifdef _WIN
#pragma once
#endif

//------------------------------------------------------------------------------
/** Missing C99 functions for windows platform support */
#ifdef _WIN

inline int c99_vsnprintf(char* str, size_t size, const char* format, va_list ap)
{
    int count = -1;

    if (size != 0)
        count = _vsnprintf_s(str, size, _TRUNCATE, format, ap);
    if (count == -1)
        count = _vscprintf(format, ap);

    return count;
}

inline int c99_snprintf(char* str, size_t size, const char* format, ...)
{
    int count;
    va_list ap;

    va_start(ap, format);
    count = c99_vsnprintf(str, size, format, ap);
    va_end(ap);

    return count;
}

#define snprintf c99_snprintf

// Microsoft "safe" versions
#define vsnprintf vsnprintf_s
#define strncat strncat_s

#endif // _WIN

//------------------------------------------------------------------------------
/**
* Standard Library Functions with safeguards in _DEBUG mode
*/
UTILITIES_FUNCTION void     util_memset(void *dest, int fill, int count);
UTILITIES_FUNCTION void     util_memcpy(void *dest, const void *src, int count);
UTILITIES_FUNCTION void     util_memmove(void *dest, const void *src, int count);
UTILITIES_FUNCTION int      util_memcmp(const void *m1, const void *m2, int count);
UTILITIES_FUNCTION void     util_strncpy(char *pDest, const char *pSrc, int maxLen);
UTILITIES_FUNCTION int      util_stricmp(const char *pStr1, const char *pStr2);
UTILITIES_FUNCTION int      util_strnicmp(const char *pStr1, const char *pStr2, int maxLen);

#endif // UTIL_STDLIB_H