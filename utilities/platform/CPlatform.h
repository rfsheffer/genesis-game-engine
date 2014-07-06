//
//  CPlatform.h
//  Extension for platform control.
//
//  Created by Ryan Sheffer on 2013-01-27.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef CPLATFORM_H
#define CPLATFORM_H

#ifdef _WIN
#pragma once
#endif

#include "IPlatform.h"

class CExtensions;

/*! A class used for getting access to platform functions. */
class CPlatform : public IPlatform
{
public:
    void            Initialize(void);
    void            InitializePlatformCapabilities(void);
    void            Shutdown(void);
    
    bool            GetKeyState(char character) const;
    bool            GetMouseState(bool left) const;
    
    hWindow         GetWindowHandle(const char *pszWindowName) const;
    
    void            SetActiveWindow(hWindow index) const;
    void            GetWindowSizePixels(unsigned int &width, unsigned int &height) const;
    void            GetWindowSize(unsigned int &width, unsigned int &height) const;
    
    void            ActivateGraphicsContext(void) const;
    void            SwapGraphicsContextBuffers(void) const;
    
    const char      *GetAbsoluteApplicationPath(void) const;
    
    // File I/O
    FileHandle FileOpen(const char *pszFileName, const char *pszOptions) const;
    size_t FileRead(void *ptr, size_t chunkSize, size_t chunkCount, FileHandle pFile) const;
    size_t FileWrite(const void *ptr, size_t chunkSize, size_t chunkCount, FileHandle pFile) const;
    size_t GetFileSize(FileHandle pFile) const;

    // Library Loading
    DLLHANDLE LoadDLL(const char *pszLibraryFileName);
    void UnloadDLL(DLLHANDLE dllHandle);
    const char *GetDLLExtension(void);

    // Platform Caps
    const platform_caps *GetPlatformCaps(void) const;
    bool HasPlatformCap(platform_caps_e cap) const;
    void LogPlatformCaps(void) const;

private:
    platform_caps m_platCaps;
};


#endif // CPLATFORM_H
