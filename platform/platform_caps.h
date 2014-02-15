//
//  platform_caps.h
//  Extension for platform control.
//
//  Created by Ryan Sheffer on 2013-01-27.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef PLATFORM_CAPS_H
#define PLATFORM_CAPS_H

/**
 * Platform Capabilities Enum.
 * Note: These have to be aligned with platform_caps
 */
enum platform_caps_e
{
    PLAT_CAP_X64,
    PLAT_CAP_MMX,
    PLAT_CAP_SSE,
    PLAT_CAP_SSE2,
    PLAT_CAP_SSE3,
    PLAT_CAP_SSSE3,
    PLAT_CAP_SSE41,
    PLAT_CAP_SSE42,
    PLAT_CAP_SSE4a,
    PLAT_CAP_AVX,
    PLAT_CAP_XOP,
    PLAT_CAP_FMA3,
    PLAT_CAP_FMA4,
};

/**
 * Platform Capabilities Structure
 * Note: These have to be aligned with platform_caps_e
 * This is a list of bools ONLY, no other types. Create a new structure for
 * a different type of platform caps if nessesary.
 */
struct platform_caps
{
    bool     X64;
    bool     MMX;
    bool     SSE;
    bool     SSE2;
    bool     SSE3;
    bool     SSSE3;
    bool     SSE41;
    bool     SSE42;
    bool     SSE4a;
    bool     AVX;
    bool     XOP;
    bool     FMA3;
    bool     FMA4;
};

#endif // PLATFORM_CAPS_H