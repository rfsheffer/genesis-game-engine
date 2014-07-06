//
//  types.h
//  Data types which can be used across the whole engine
//
//  Created by Ryan Sheffer on 2012-10-31.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef TYPES_H
#define TYPES_H

#ifdef _WIN
#pragma once
#endif

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

#elif defined(_WIN)

/** The handle type for a window */

#ifdef INCLUDE_WINDOWS_HEADER
#define hWindow     HWND
#else
#define hWindow     int // If windows changes the standard, we are in trouble.
#endif

#endif

/** File Handle */
typedef FILE *  FileHandle;

/**
 * This is a struct sent to the platform containing information about a window,
 * Usually for window creation.
 */
struct window_info
{
    /** Window Position X */
    int x;
    
    /** Window Position Y */
    int y;
    
    /** Window Height */
    int height;
    
    /** Window Width */
    int width;
    
    /** Maximum Window Width */
    int maxWidth;
    
    /** Maxiumum Window Height */
    int maxHeight;
    
    /** The title to be appended to the top of the window. */
    const char *windowTitle;
    
    /** Should window ignore x and y and just be centered? */
    bool centered;
};

#endif // TYPES_H
