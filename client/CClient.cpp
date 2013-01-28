//
//  CClient.cpp
//  client
//
//  Created by Ryan Sheffer on 2013-01-25.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include "CClient.h"

// Allow this extension to be used by the manager as an importable extension.
SETUP_EXTENSION_LINK(Client);

//--------------------------------------------------------------------------
// Purpose: Initialization of the client. This will happen after the extension
// manager has been created.
//--------------------------------------------------------------------------
void CClient::Initialize(CExtensions *pExtensions)
{
    m_pExtensions = pExtensions;
}

//--------------------------------------------------------------------------
// Purpose: Called when the extension manager is told to shutdown
//--------------------------------------------------------------------------
void CClient::Shutdown()
{
    
}