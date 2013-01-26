//
//  CServer.cpp
//  server
//
//  Created by Ryan Sheffer on 2013-01-25.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include "CServer.h"

//--------------------------------------------------------------------------
// Purpose: Pushes a variable onto the token stack
//--------------------------------------------------------------------------
DLL_EXPORT
IServer *CreateServer(void)
{
    return new CServer();
}


void CServer::Initialize(CExtensions *pExtensions)
{
    m_pExtensions = pExtensions;
}

void CServer::Shutdown()
{
    
}