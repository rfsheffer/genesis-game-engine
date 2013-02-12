//
//  CPlatform.cpp
//  Extension for accessing platform information.
//
//  Created by Ryan Sheffer on 2013-01-27.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include "CPlatform.h"

/**
 * Initialization of the platform. This will happen after the extension
 * manager has been created.
 * @param pExtensions The extension manager which created this extension.
 */
void CPlatform::Initialize(IExtensions *pExtensions)
{
#ifdef _MAC
    // TODO: Move to platform
    static char szFileLine[2048];
    printf( "working directory: %s\n", getcwd(szFileLine, sizeof(szFileLine)) );
#endif
}

/**
 * Called usually at the end of program execution.
 */
void CPlatform::Shutdown(void)
{
    
}