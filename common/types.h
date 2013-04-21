//
//  types.h
//  Global data types
//
//  Created by Ryan Sheffer on 2012-10-31.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef TYPES_H
#define TYPES_H

//****************************************************
// Standard Types
//****************************************************
#if defined(_WIN) || defined(_LINUX) || defined(_MAC)

/** The byte type */
typedef unsigned char byte;

#define FLOAT   float
#define INT     int
#define UINT    unsigned int

#if !defined(TRUE)
#define TRUE true
#endif

#if !defined(FALSE)
#define FALSE false
#endif

#else

#error "Unsupported Platform."

#endif

#if defined(_LINUX) || defined(_MAC)

#define INT32       int32_t
#define UINT32      uint32_t
#define INT64       int64_t
#define UINT64      uint64_t

/** The handle type for a window */
typedef int hWindow;

#endif

#endif // TYPES_H
