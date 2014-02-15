//
//  macros.h
//  server
//
//  Created by Ryan Sheffer on 2012-12-31.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef MACROS_H
#define MACROS_H

#if defined(_MAC) || defined(_LINUX)

// Source: winnt.h
#define _ARRAYSIZE(A) (sizeof(A)/sizeof((A)[0]))

extern "C++"
template <typename T, size_t N>
char (*RtlpNumberOf( T (&)[N] ))[N];

#define ARRAYSIZE(A) (sizeof(*RtlpNumberOf(A)))

/**
 * __pragma is a feature in VS for putting pragma preprocessor commands into
 * macros. It is used in a couple macros to prevent stupid warnings which GCC
 * does not give. So if there is a GCC version for in macro pragma, replace
 * this define.
 */
#define __pragma(SUB)

#endif // _MAC || _LINUX

#if defined(_MAC) || defined(_LINUX)

#define UNREFERENCED_PARAMETER(P)
#define DBG_UNREFERENCED_PARAMETER(P)
#define DBG_UNREFERENCED_LOCAL_VARIABLE(V)

#elif defined(_WIN) // _MAC || _LINUX

#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(P)          (P)
#endif

#ifndef DBG_UNREFERENCED_PARAMETER
#define DBG_UNREFERENCED_PARAMETER(P)      (P)
#endif

#ifndef DBG_UNREFERENCED_LOCAL_VARIABLE
#define DBG_UNREFERENCED_LOCAL_VARIABLE(V) (V)
#endif

#endif // _WIN

#endif // MACROS_H
