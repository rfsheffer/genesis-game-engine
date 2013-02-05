//
//  CClient.cpp
//  This is the master controller for the client extension. It recieves entity
//  information from the server and updates the shared entities. It also
//  controls client side only FX such as particles.
//
//  Created by Ryan Sheffer on 2013-01-25.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include "CClient.h"

// Allow this extension to be used by the manager as an importable extension.
SETUP_EXTENSION_LINK(Client);

/**
 * Initialization of the client. This will happen after the extension
 * manager has been created.
 * @param pExtensions The extension manager which created this extension.
 */
void CClient::Initialize(CExtensions *pExtensions)
{
    m_pExtensions = pExtensions;
    
    // Initialize the list
    for(int i = 0; i < MAX_NUM_ENTITIES; ++i)
    {
        m_pSharedEntities[i] = NULL;
    }
}

/**
 * Extension Run method, Called once per tick by the extension manager.
 */
void CClient::Run(void)
{
    
}

/**
 * Called usually at the end of program execution when the client and
 * server are being shutdown. The server is shutdown before the clients.
 */
void CClient::Shutdown()
{
    
}