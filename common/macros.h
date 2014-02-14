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

#endif // _MAC || _LINUX

#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(P)          (P)
#endif

#ifndef DBG_UNREFERENCED_PARAMETER
#define DBG_UNREFERENCED_PARAMETER(P)      (P)
#endif

#ifndef DBG_UNREFERENCED_LOCAL_VARIABLE
#define DBG_UNREFERENCED_LOCAL_VARIABLE(V) (V)
#endif

#endif // MACROS_H
