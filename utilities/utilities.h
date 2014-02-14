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

// Used for dll exporting and importing
#   define  UTILITIES_FUNCTION   DLL_EXPORT

// Can't use extern "C" when DLL exporting a class
#   define  UTILITIES_CLASS   DLL_CLASS_EXPORT

// Can't use extern "C" when DLL exporting a global
#   define  UTILITIES_GLOBAL   DLL_GLOBAL_EXPORT

#else

// Used for dll exporting and importing
#   define  UTILITIES_FUNCTION   DLL_IMPORT

// Can't use extern "C" when DLL exporting a class
#   define  UTILITIES_CLASS   DLL_CLASS_IMPORT

// Can't use extern "C" when DLL exporting a global
#   define  UTILITIES_GLOBAL   DLL_GLOBAL_IMPORT

#endif

#endif // UTILITIES_H