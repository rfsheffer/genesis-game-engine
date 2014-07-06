//
//  pywrap_main.h
//  pywrap
//
//  Created by Ryan Sheffer on 2014-07-05.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#ifndef PYWRAP_MAIN_H
#define PYWRAP_MAIN_H

#ifdef _WIN
#pragma once
#endif

#ifdef PYWRAP_EXPORT

// Used for dll exporting and importing
#   define  PYWRAP_FUNC       DLL_EXPORT

// Can't use extern "C" when DLL exporting a class
#   define  PYWRAP_CLASS   DLL_CLASS_EXPORT

// Can't use extern "C" when DLL exporting a global
#   define  PYWRAP_GLOBAL   DLL_GLOBAL_EXPORT

#else

// Used for dll exporting and importing
#   define  PYWRAP_FUNCTION   DLL_IMPORT

// Can't use extern "C" when DLL exporting a class
#   define  PYWRAP_CLASS   DLL_CLASS_IMPORT

// Can't use extern "C" when DLL exporting a global
#   define  PYWRAP_GLOBAL   DLL_GLOBAL_IMPORT

#endif

PYWRAP_FUNC int pywrap_test(int argc, const char * argv[]);

#endif // PYWRAP_MAIN_H
