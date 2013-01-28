//
//  CServer.cpp
//  server
//
//  Created by Ryan Sheffer on 2013-01-25.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include "CServer.h"

// Allow this extension to be used by the manager as an importable extension.
SETUP_EXTENSION_LINK(Server);

void CServer::Initialize(CExtensions *pExtensions)
{
    m_pExtensions = pExtensions;
}

void CServer::Shutdown()
{
    
}