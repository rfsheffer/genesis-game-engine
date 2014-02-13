//
//  graphics.cpp
//  Primary Graphics API for displaying 3D art
//
//  Created by Ryan Sheffer on 2/5/2014.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#include "graphicshead.h"
#include "graphics.h"

static IPlatform   *g_pPlatformInterface = NULL;

/** Just a pointer hookup so utilities can get the platform interface */
IPlatform *GetPlatform(void)
{
    if(g_pPlatformInterface == NULL)
    {
        g_pPlatformInterface = static_cast<IPlatform*>
        (GetInterfaceRegistration()->GetInterface(PLATFORM_INTERFACE_NAME,
                                                  PLATFORM_INTERFACE_VERSION));
    }
    
    return g_pPlatformInterface;
}


void *_CreateGraphics(void)
{
    return new Graphics;
}

void _DestroyGraphics(void *pMem)
{
    delete (Graphics*)pMem;
}

REGISTER_DYNAMIC_INTERFACE_FUNC(_CreateGraphics, _DestroyGraphics,
                                GRAPHICS_INTERFACE_NAME,
                                GRAPHICS_INTERFACE_VERSION);