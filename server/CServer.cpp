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
#include "data_network_helpers.h"
#include "entity_dictionary.h"

// Allow this extension to be used by the manager as an importable extension.
SETUP_EXTENSION_LINK(Server);

namespace __server_holder
{
    CServer     *pServer;
}

/**
 * Gets the server itself.
 */
CServer     *GetServer(void)
{
    return __server_holder::pServer;
}

/**
 * Initialization of the server. This will happen after the extension
 * manager has been created.
 * @param pExtensions The extension manager which created this extension.
 */
void CServer::Initialize(IExtensions *pExtensions)
{
    m_pExtensions = pExtensions;
    __server_holder::pServer = this;
    
    // Initialize the lists
    int i;
    m_uiNumSharedEntities = 0;
    for(i = 0; i < Foundation::MAX_SHARED_BASE_ENTITIES; ++i)
    {
        m_pSharedEntities[i] = NULL;
    }
    
    m_uiNumLocalEntities = 0;
    for(i = 0; i < MAX_NUM_LOCAL_ENTITIES; ++i)
    {
        m_pLocalEntities[i] = NULL;
    }
    
    // Create a couple of test entities
    CREATE_SHARED_ENTITY_BY_NAME("baseent");
    CREATE_SHARED_ENTITY_BY_NAME("baseent");
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
                                               Foundation::MAX_SHARED_BASE_ENTITIES);
    
 /*   char bla[512];
    for(int i = 0; i < 512; ++i)
    {
        bla[i] = 2;
    }
    
    DataPacking::DataBuffer test(0, Foundation::MAX_SHARED_BASE_ENTITIES);
    test.SetBlockGrowth(10);
    
    for(int i = 0; i < Foundation::MAX_SHARED_BASE_ENTITIES; ++i)
    {
        test.StartWritting("NET_ENTITY_BLOCK");
        
        DataPacking::networked_entity_header_t net_ent_header;
        
        // Write an empty block and stop here if there is no entity.
        net_ent_header.flags = DataPacking::networked_entity_header_t::NET_FLAG_DEAD;
        net_ent_header.num_objs = 0;
        net_ent_header.networkName[0] = '\0';
        
        test.WriteBuffer((char*)&net_ent_header, sizeof(net_ent_header));
        
        //test.WriteBuffer(bla, 512);
        
        test.EndWritting();
    }*/

    
    m_pExtensions->SendBuffer("Client", pNewBuffer);
}

/**
 * Called usually at the end of program execution when the client and
 * server are being shutdown. The server is shutdown before the clients.
 */
void CServer::Shutdown()
{
    int i;
    for(i = 0; i < Foundation::MAX_SHARED_BASE_ENTITIES; ++i)
    {
        if(m_pSharedEntities[i] != NULL)
        {
            delete m_pSharedEntities[i];
            m_pSharedEntities[i] = NULL;
        }
    }
    
    for(i = 0; i < MAX_NUM_LOCAL_ENTITIES; ++i)
    {
        if(m_pLocalEntities[i] != NULL)
        {
            delete m_pLocalEntities[i];
            m_pLocalEntities[i] = NULL;
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

/**
 * Registers a new entity as shared
 * TODO: This needs a better system, so old slots get refilled.
 */
unsigned int CServer::RegisterSharedEntity(CEntityBase *pEnt)
{
    ASSERTION((m_uiNumSharedEntities < Foundation::MAX_SHARED_BASE_ENTITIES),
              "Server: Reached maximum shared base entities!");
    m_pSharedEntities[m_uiNumSharedEntities] = pEnt;
    return m_uiNumSharedEntities++;
}

/**
 * Registers a local entity
 * @param pEnt The entity to register
 * TODO: This needs a better system, so old slots get refilled.
 */
unsigned int CServer::RegisterLocalEntity(CEntityBase *pEnt)
{
    ASSERTION((m_uiNumLocalEntities < MAX_NUM_LOCAL_ENTITIES),
              "Server: Reached maximum local base entities!");
    
    m_pLocalEntities[m_uiNumLocalEntities] = pEnt;
    return m_uiNumLocalEntities++;
}

unsigned int    RegisterSharedEntity(CEntityBase *pEnt)
{
    return GetServer()->RegisterSharedEntity(pEnt);
}
unsigned int    RegisterLocalEntity(CEntityBase *pEnt)
{
    return GetServer()->RegisterLocalEntity(pEnt);
}