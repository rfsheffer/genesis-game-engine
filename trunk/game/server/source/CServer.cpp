//
//  CServer.cpp
//  This is the master controller for the server extension. It dispatches
//  updates for all entities, and sends the new information to the clients.
//
//  Created by Ryan Sheffer on 2013-01-25.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include "serverhead.h"
#include "CServer.h"
#include "ent_base.h"
#include "data_networkpack.h"
#include "data_network_helpers.h"
#include "entity_dictionary.h"

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


static IServer   *g_pServerInterface = NULL;

void *_CreateServer(void)
{
    if(g_pServerInterface == NULL)
    {
        g_pServerInterface = new CServer;
    }
    
    return g_pServerInterface;
}

/** Helper for destruction */
void _DestroyServer(void *pMem)
{
    g_pServerInterface = NULL;
    delete (CServer*)pMem;
}

REGISTER_DYNAMIC_INTERFACE_FUNC(_CreateServer, _DestroyServer,
                                SERVER_INTERFACE_NAME,
                                SERVER_INTERFACE_VERSION);

CServer *GetServer(void)
{
    return (CServer *)g_pServerInterface;
}

//------------------------------------------------------------------------------
/**
 * Initialization of the server. This will happen after the extension
 * manager has been created.
 * @param pExtensions The extension manager which created this extension.
 */
void CServer::Initialize(IExtensions *pExtensions)
{
    m_pExtensions = pExtensions;
    ASSERTION(g_pServerInterface == this, "Trying to create a secondary Server Interface?!");
    
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
    //CREATE_SHARED_ENTITY_BY_NAME("baseent");
    //CREATE_SHARED_ENTITY_BY_NAME("baseent");
}

//------------------------------------------------------------------------------
/**
 * Extension Run method, Called once per tick by the extension manager.
 */
void CServer::Run(void)
{
    // Package up the entities
    // TODO: Need better solution, no entity indicies, send only updating ents
    //       with a GUID assigned or something. We are just testing so this is ok
    //       for now but it is unacceptable for release product.
    DataPacking::NetworkPackage     networkPackage;
    DataPacking::DataBuffer *pNewBuffer =
                networkPackage.PackageMappables((CDataMappable **)m_pSharedEntities,
                                               Foundation::MAX_SHARED_BASE_ENTITIES);
    
    m_pExtensions->SendBuffer("Client", pNewBuffer);
}

//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
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