//
//  CPlatform.cpp
//  Extension for platform control.
//
//  Created by Ryan Sheffer on 2013-01-27.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include "allhead.h"
#include "CPlatform.h"

#ifdef _WIN
#   define cpuid    __cpuid
#else
void cpuid(int CPUInfo[4],int InfoType){
    __asm__ __volatile__ (
        "cpuid":
        "=a" (CPUInfo[0]),
        "=b" (CPUInfo[1]),
        "=c" (CPUInfo[2]),
        "=d" (CPUInfo[3]) :
        "a" (InfoType)
    );
}
#endif

//------------------------------------------------------------------------------
/**
* Initializes platform independent stuff
*/
void CPlatform::InitializePlatformCapabilities(void)
{
    memset(&m_platCaps, 0, sizeof(platform_caps));

    int info[4];
    cpuid(info, 0);
    int nIds = info[0];

    cpuid(info, 0x80000000);
    int nExIds = info[0];

    //  Detect Instruction Set
    if (nIds >= 1)
    {
        cpuid(info, 0x00000001);
        m_platCaps.MMX   = (info[3] & ((int)1 << 23)) != 0;
        m_platCaps.SSE   = (info[3] & ((int)1 << 25)) != 0;
        m_platCaps.SSE2  = (info[3] & ((int)1 << 26)) != 0;
        m_platCaps.SSE3  = (info[2] & ((int)1 <<  0)) != 0;

        m_platCaps.SSSE3 = (info[2] & ((int)1 <<  9)) != 0;
        m_platCaps.SSE41 = (info[2] & ((int)1 << 19)) != 0;
        m_platCaps.SSE42 = (info[2] & ((int)1 << 20)) != 0;

        m_platCaps.AVX   = (info[2] & ((int)1 << 28)) != 0;
        m_platCaps.FMA3  = (info[2] & ((int)1 << 12)) != 0;
    }

    if (nExIds >= 0x80000001)
    {
        cpuid(info, 0x80000001);
        m_platCaps.X64   = (info[3] & ((int)1 << 29)) != 0;
        m_platCaps.SSE4a = (info[2] & ((int)1 <<  6)) != 0;
        m_platCaps.FMA4  = (info[2] & ((int)1 << 16)) != 0;
        m_platCaps.XOP   = (info[2] & ((int)1 << 11)) != 0;
    }

    // Test to ensure the enum and caps struct are aligned
    ASSERTION(HasPlatformCap(PLAT_CAP_X64) == m_platCaps.X64, "enum to caps inconsistency X64");
    ASSERTION(HasPlatformCap(PLAT_CAP_MMX) == m_platCaps.MMX, "enum to caps inconsistency MMX");
    ASSERTION(HasPlatformCap(PLAT_CAP_SSE) == m_platCaps.SSE, "enum to caps inconsistency SSE");
    ASSERTION(HasPlatformCap(PLAT_CAP_SSE2) == m_platCaps.SSE2, "enum to caps inconsistency SSE2");
    ASSERTION(HasPlatformCap(PLAT_CAP_SSE3) == m_platCaps.SSE3, "enum to caps inconsistency SSE3");
    ASSERTION(HasPlatformCap(PLAT_CAP_SSSE3) == m_platCaps.SSSE3, "enum to caps inconsistency SSSE3");
    ASSERTION(HasPlatformCap(PLAT_CAP_SSE41) == m_platCaps.SSE41, "enum to caps inconsistency SSE41");
    ASSERTION(HasPlatformCap(PLAT_CAP_SSE42) == m_platCaps.SSE42, "enum to caps inconsistency SSE42");
    ASSERTION(HasPlatformCap(PLAT_CAP_SSE4a) == m_platCaps.SSE4a, "enum to caps inconsistency SSE4a");
    ASSERTION(HasPlatformCap(PLAT_CAP_AVX) == m_platCaps.AVX, "enum to caps inconsistency AVX");
    ASSERTION(HasPlatformCap(PLAT_CAP_XOP) == m_platCaps.XOP, "enum to caps inconsistency XOP");
    ASSERTION(HasPlatformCap(PLAT_CAP_FMA3) == m_platCaps.FMA3, "enum to caps inconsistency FMA3");
    ASSERTION(HasPlatformCap(PLAT_CAP_FMA4) == m_platCaps.FMA4, "enum to caps inconsistency FMA4");
}

//------------------------------------------------------------------------------
/**
* Gets all the platform capabilities. Consider using HasPlatformCap.
*/
const platform_caps *CPlatform::GetPlatformCaps(void) const
{
    return &m_platCaps;
}

//------------------------------------------------------------------------------
/**
* Gets a specific platform cap
*/
bool CPlatform::HasPlatformCap(platform_caps_e cap) const
{
    return *((bool*)(((unsigned char *)&m_platCaps) + (cap * sizeof(bool))));
}

//------------------------------------------------------------------------------
/**
* Logs Platform Caps
*/
void CPlatform::LogPlatformCaps(void) const
{
    Logging::Msg("--------------------------------------------------------------------------------");
    Logging::Msg("Capabilities Spew:");
    Logging::Msg("X64:      %s\n", HasPlatformCap(PLAT_CAP_X64)?  "Availible":"Unavailible");
    Logging::Msg("MMX:      %s\n", HasPlatformCap(PLAT_CAP_MMX)?  "Availible":"Unavailible");
    Logging::Msg("SSE:      %s\n", HasPlatformCap(PLAT_CAP_SSE)?  "Availible":"Unavailible");
    Logging::Msg("SSE2:     %s\n", HasPlatformCap(PLAT_CAP_SSE2)? "Availible":"Unavailible");
    Logging::Msg("SSE3:     %s\n", HasPlatformCap(PLAT_CAP_SSE3)? "Availible":"Unavailible");
    Logging::Msg("SSSE3:    %s\n", HasPlatformCap(PLAT_CAP_SSSE3)?"Availible":"Unavailible");
    Logging::Msg("SSE41:    %s\n", HasPlatformCap(PLAT_CAP_SSE41)?"Availible":"Unavailible");
    Logging::Msg("SSE42:    %s\n", HasPlatformCap(PLAT_CAP_SSE42)?"Availible":"Unavailible");
    Logging::Msg("SSE4a:    %s\n", HasPlatformCap(PLAT_CAP_SSE4a)?"Availible":"Unavailible");
    Logging::Msg("AVX:      %s\n", HasPlatformCap(PLAT_CAP_AVX)?  "Availible":"Unavailible");
    Logging::Msg("XOP:      %s\n", HasPlatformCap(PLAT_CAP_XOP)?  "Availible":"Unavailible");
    Logging::Msg("FMA3:     %s\n", HasPlatformCap(PLAT_CAP_FMA3)? "Availible":"Unavailible");
    Logging::Msg("FMA4:     %s\n", HasPlatformCap(PLAT_CAP_FMA4)? "Availible":"Unavailible");
    Logging::Msg("--------------------------------------------------------------------------------");
}