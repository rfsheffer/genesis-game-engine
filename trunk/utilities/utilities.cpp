//
//  utilities.cpp
//  utilities
//
//  Created by Ryan Sheffer on 2/5/2014.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

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