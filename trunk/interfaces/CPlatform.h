//
//  CPlatform.cpp
//  Extension for accessing platform information.
//
//  Created by Ryan Sheffer on 2013-01-27.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef CPLATFORM_H
#define CPLATFORM_H

#include "IPlatform.h"
#include "PlatformWrapper.h"

class CExtensions;

class CPlatform : public IPlatform
{
public:
    void            Initialize(CExtensions *pExtensions);
    void            Run(void){}
    void            Shutdown();
    
    inline bool     GetKeyState(char character) const
    {
        return PlatformWrapper::GetKeyState(character);
    }

    inline bool     GetMouseState(bool left) const
    {
        return PlatformWrapper::GetMouseState(left);
    }
};


#endif // CPLATFORM_H
