//
//  CPlatform.cpp
//  Extension for accessing platform information.
//
//  Created by Ryan Sheffer on 2013-01-27.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include "CPlatform.h"

//------------------------------------------------------------------------------
// Purpose: Initialization
//------------------------------------------------------------------------------
void CPlatform::Initialize(CExtensions *pExtensions)
{
#ifdef _MAC
    // TODO: Move to platform
    static char szFileLine[2048];
    printf( "working directory: %s\n", getcwd(szFileLine, sizeof(szFileLine)) );
#endif
}

//------------------------------------------------------------------------------
// Purpose: Shutdown
//------------------------------------------------------------------------------
void CPlatform::Shutdown()
{
    
}