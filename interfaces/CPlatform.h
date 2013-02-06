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

/*! A class used for getting access to platform functions. */
class CPlatform : public IPlatform
{
public:
    void            Initialize(CExtensions *pExtensions);
    void            Run(void){}
    void            Shutdown(void);
    void            RecvDataBuffer(DataPacking::DataBuffer *pBuffer){}
    
    /**
     * Gets the state ( true[on] or false[off] of a keyboard key.
     * @param character The key to check.
     */
    inline bool     GetKeyState(char character) const
    {
        return PlatformWrapper::GetKeyState(character);
    }

    /**
     * Gets the state ( true[on] or false[off] of a mouse button.
     * @param left If true, returns the state of the left mouse button.
     */
    inline bool     GetMouseState(bool left) const
    {
        return PlatformWrapper::GetMouseState(left);
    }
};


#endif // CPLATFORM_H
