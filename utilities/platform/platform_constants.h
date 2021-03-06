//
//  platform.h
//  Platform specific macros and definitions
//
//  Created by Ryan Sheffer on 10-06-28.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef PLATFORM_H
#define PLATFORM_H

// The following macros define the minimum required platform.  The minimum required platform
// is the earliest version of Windows, Internet Explorer etc. that has the necessary features to run 
// your application.  The macros work by enabling all features available on platform versions up to and 
// including the version specified.

#ifdef _WIN
#pragma once
#endif

//****************************************************
// Some handy platform functions.
//****************************************************
#if defined(_WIN)

#define IsPC() true
#define IsLinux() false
#define IsMac() false

#elif defined(_LINUX)
#define IsPC() false
#define IsLinux() true
#define IsMac() false

#elif defined(_MAC)

#define IsPC() false
#define IsLinux() false
#define IsMac() true

#endif

//****************************************************
// Platform Compatibility
//****************************************************

// MOVE THIS TO FILESYSTEM ONCE IT'S WRITTEN!
// Defines MAX_PATH
#ifndef MAX_PATH
#define MAX_PATH  260
#endif

// Long is treated differently by MSVC and GCC so to prevent compatibility
// problems I am disabling it.
// TODO: Too much long usage in our dependancies, look into solution. We shouldn't have to use long at all.
//#define long        do_not_use_long_use_int32_or_int64_instead

//****************************************************
// DLL Import / Export
//****************************************************

#if defined(_WIN)

// Used for dll exporting and importing
#define  DLL_EXPORT   extern "C" __declspec( dllexport )
#define  DLL_IMPORT   extern "C" __declspec( dllimport )

// Can't use extern "C" when DLL exporting a class
#define  DLL_CLASS_EXPORT   __declspec( dllexport )
#define  DLL_CLASS_IMPORT   __declspec( dllimport )

// Can't use extern "C" when DLL exporting a global
#define  DLL_GLOBAL_EXPORT   extern __declspec( dllexport )
#define  DLL_GLOBAL_IMPORT   extern __declspec( dllimport )

#elif defined(_LINUX) || defined(_MAC) // GCC

// Used for dll exporting and importing
#define  DLL_EXPORT   extern "C" __attribute__ ((visibility("default")))
#define  DLL_IMPORT   extern "C" __attribute__ ((visibility("hidden")))

// Can't use extern "C" when DLL exporting a class
#define  DLL_CLASS_EXPORT __attribute__ ((visibility("default")))
#define  DLL_CLASS_IMPORT __attribute__ ((visibility("hidden")))

// Can't use extern "C" when DLL exporting a global
#define  DLL_GLOBAL_EXPORT   extern __attribute ((visibility("default")))
#define  DLL_GLOBAL_IMPORT   extern __attribute ((visibility("hidden")))

#else
#error "Unsupported Platform."
#endif


//****************************************************
// Used for standard calling conventions
//****************************************************
#if defined(_WIN)

#define  STDCALL				__stdcall
#define  FASTCALL				__fastcall
#define  FORCEINLINE			__forceinline

#elif defined(_LINUX) || defined(_MAC) // GCC

#define  STDCALL
#define  FASTCALL
#define FORCEINLINE inline __attribute__((always_inline))

#endif

//****************************************************
// Platform Types
//****************************************************
#define DLLHANDLE void *

// highest possible value of an unsigned int, also the return of a not found string.
static const size_t NPOS = ULLONG_MAX;

#if defined(__GNUC__)
    #undef offsetof
    // Note: can't use builtin offsetof because many use cases (esp. in templates) wouldn't compile due to restrictions on the builtin offsetof
    //#define offsetof( type, var ) __builtin_offsetof( type, var )
    #define offsetof(s,m)    ( (size_t)&(((s *)0x1000000)->m) - 0x1000000u )
#else
    #include <stddef.h>
    #undef offsetof
    #define offsetof(s,m)    (size_t)&(((s *)0)->m)
#endif

// NOTE ABOUT THESE FILE MODES:
// - The 'b' is ignored on all POSIX conforming systems, including Linux.
//   However, on windows using 'b' may actually improve performance because
//   there is no carriage-return etc translation involved. So even though
//   microsoft should be conforming to the standard, which they are bad at,
//   I am still going to keep using it for legacy and windows.

/**
 * Open text file for reading. The stream is positioned at the beginning of the file.
 */
#define FILE_READ           "r"
#define FILE_READ_BINARY           "rb"

/** 
 * Open for reading and writing. The stream is positioned at the beginning of the file.
 */
#define FILE_READ_WRITE     "r+"
#define FILE_READ_WRITE_BINARY     "rb+"

/**
 * Truncate file to zero length or create text file for writing. The stream is
 * positioned at the beginning of the file.
 */
#define FILE_WRITE          "w"
#define FILE_WRITE_BINARY          "wb"

/**
 * Open for reading and writing. The file is created if it does not exist,
 * otherwise it is truncated. The stream is positioned at the beginning of the file.
 */
#define FILE_READ_WRITE_CREATE  "w+"
#define FILE_READ_WRITE_CREATE_BINARY  "wb+"

/**
 * Open for appending (writing at end of file). The file is created if it does
 * not exist. The stream is positioned at the end of the file.
 */
#define FILE_APPEND_CREATE      "a"
#define FILE_APPEND_CREATE_BINARY      "ab"

/**
 * Open for reading and appending (writing at end of file). The file is created
 * if it does not exist. The initial file position for reading is at the
 * beginning of the file, but output is always appended to the end of the file.
 */
#define FILE_READ_APPEND_CREATE     "a+"
#define FILE_READ_APPEND_CREATE_BINARY     "ab+"

#endif // PLATFORM_H

