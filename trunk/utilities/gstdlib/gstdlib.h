//
//  gstdlib.h
//  Genesis Standard C library. Anything we need to declare for platform support goes here.
//  Generally, we will be supporting the standard library that comes with the OS unless
//  we really see a reason (performance reason or other) to redeclare a standard C function
//  here.
//
//  Created by Ryan Sheffer on 14-02-08.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#ifndef G_STDLIB_H
#define G_STDLIB_H

#ifdef _WIN
#pragma once
#endif

//---------------------------------------------------------------------------------------------
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
#define strcasecmp stricmp

#endif // _WIN

#endif // G_STDLIB_H