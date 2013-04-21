//
//  CPlatform.h
//  Extension for platform control.
//
//  Created by Ryan Sheffer on 2013-01-27.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef CPLATFORM_H
#define CPLATFORM_H

#include "IPlatform.h"

class CExtensions;

/*! A class used for getting access to platform functions. */
class CPlatform : public IPlatform
{
public:
    void            Initialize(void);
    void            Shutdown(void);
    
    bool            GetKeyState(char character) const;
    bool            GetMouseState(bool left) const;
    
    hWindow         CreateContentWindow(const window_info &info) const;
    void            SetActiveWindow(hWindow index) const;
    void            GetWindowSizePixels(unsigned int &width, unsigned int &height) const;
    void            GetWindowSize(unsigned int &width, unsigned int &height) const;
    
    bool            CreateGraphicsContext(const render::render_context_settings &settings) const;
    void            ShutdownActiveGraphicsContext(void) const;
    void            ActivateGraphicsContext(void) const;
    void            SwapGraphicsContextBuffers(void) const;
    
    const char      *GetAbsoluteApplicationPath(void) const;
};


#endif // CPLATFORM_H
