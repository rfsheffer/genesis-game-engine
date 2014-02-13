//
//  utilities.h
//
//  Created by Ryan Sheffer on 2/6/2014.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#ifndef UTILITIES_H
#define UTILITIES_H

#ifdef _WIN
#pragma once
#endif

#ifdef UTILITIES_EXPORT

#if defined(_WIN)

// Used for dll exporting and importing
#define  UTILITIES_FUNCTION   extern "C" __declspec( dllexport )

// Can't use extern "C" when DLL exporting a class
#define  UTILITIES_CLASS   __declspec( dllexport )

// Can't use extern "C" when DLL exporting a global
#define  UTILITIES_GLOBAL   extern __declspec( dllexport )

#elif defined(_LINUX) || defined(_MAC) // GCC

// Used for dll exporting and importing
#define  UTILITIES_FUNCTION   extern "C" __attribute__ ((visibility("default")))
#define  UTILITIES_FUNCTION   extern "C" __attribute__ ((visibility("hidden")))

// Can't use extern "C" when DLL exporting a class
#define  UTILITIES_CLASS __attribute__ ((visibility("default")))
#define  UTILITIES_CLASS __attribute__ ((visibility("hidden")))

// Can't use extern "C" when DLL exporting a global
#define  UTILITIES_GLOBAL   extern __attribute ((visibility("default")))
#define  UTILITIES_GLOBAL   extern __attribute ((visibility("hidden")))

#else
#error "Unsupported Platform."
#endif

#else

#if defined(_WIN)

// Used for dll exporting and importing
#define  UTILITIES_FUNCTION   extern "C" __declspec( dllimport )

// Can't use extern "C" when DLL exporting a class
#define  UTILITIES_CLASS   __declspec( dllimport )

// Can't use extern "C" when DLL exporting a global
#define  UTILITIES_GLOBAL   extern __declspec( dllimport )

#elif defined(_LINUX) || defined(_MAC) // GCC

// Used for dll exporting and importing
#define  UTILITIES_FUNCTION   extern "C" __attribute__ ((visibility("hidden")))

// Can't use extern "C" when DLL exporting a class
#define  UTILITIES_CLASS __attribute__ ((visibility("hidden")))

// Can't use extern "C" when DLL exporting a global
#define  UTILITIES_GLOBAL   extern __attribute ((visibility("hidden")))

#else
#error "Unsupported Platform."
#endif

#endif

#endif // UTILITIES_H