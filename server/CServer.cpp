//
//  CServer.cpp
//  This is the master controller for the server extension. It dispatches
//  updates for all entities, and sends the new information to the clients.
//
//  Created by Ryan Sheffer on 2013-01-25.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include "CServer.h"
#include "ent_base.h"
#include "data_networkpack.h"

// Allow this extension to be used by the manager as an importable extension.
SETUP_EXTENSION_LINK(Server);

/**
 * Initialization of the server. This will happen after the extension
 * manager has been created.
 * @param pExtensions The extension manager which created this extension.
 */
void CServer::Initialize(IExtensions *pExtensions)
{
    m_pExtensions = pExtensions;
    
    // Initialize the list
    for(int i = 0; i < MAX_NUM_ENTITIES; ++i)
    {
        m_pSharedEntities[i] = NULL;
    }
    
    // Create a couple of test entities
    m_pSharedEntities[0] = new CEntityBase;
    m_pSharedEntities[0]->_InitBaseEntity(0);
    m_pSharedEntities[1] = new CEntityBase;
    m_pSharedEntities[1]->_InitBaseEntity(1);
}

/**
 * Extension Run method, Called once per tick by the extension manager.
 */
void CServer::Run(void)
{
    // Package up the entities
    DataPacking::NetworkPackage     networkPackage;
    DataPacking::DataBuffer *pNewBuffer =
                                networkPackage.PackageEntities(m_pSharedEntities,
                                                               MAX_NUM_ENTITIES);
    
    m_pExtensions->SendBuffer("Client", pNewBuffer);
}

/**
 * Called usually at the end of program execution when the client and
 * server are being shutdown. The server is shutdown before the clients.
 */
void CServer::Shutdown()
{
    for(int i = 0; i < MAX_NUM_ENTITIES; ++i)
    {
        if(m_pSharedEntities[i] != NULL)
        {
            delete m_pSharedEntities[i];
            m_pSharedEntities[i] = NULL;
        }
    }
}

/**
 * Recieve a buffer from the extension manager
 * @param pBuffer The buffer to recv
 * @param pExtensionName The name of the specific system to give the data to.
 */
void CServer::RecvBuffer(DataPacking::DataBuffer *pBuffer)
{
    // This will be a small buffer from the clients which contains
    // data such as input commands.
}