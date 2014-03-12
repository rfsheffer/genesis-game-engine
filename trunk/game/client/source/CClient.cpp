//
//  CClient.cpp
//  This is the master controller for the client extension. It recieves entity
//  information from the server and updates the shared entities. The ones which
//  have something to draw then get passed onto the graphics interface.
//
//  Created by Ryan Sheffer on 2013-01-25.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include "clienthead.h"
#include "CClient.h"
#include "data_networkunpack.h"
#include "IGraphics.h"

static IPlatform   *g_pPlatformInterface = NULL;
static IGraphics   *g_pGraphicsInterface = NULL;

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

IGraphics *GetGraphics(void)
{
    if(g_pGraphicsInterface == NULL)
    {
        g_pGraphicsInterface = static_cast<IGraphics*>
        (GetInterfaceRegistration()->GetInterface(GRAPHICS_INTERFACE_NAME,
                                                  GRAPHICS_INTERFACE_VERSION));
    }
    
    return g_pGraphicsInterface;
}


static IClient   *g_pClientInterface = NULL;

/** Helper for creation */
void *_CreateClient(void)
{
    if(g_pClientInterface == NULL)
    {
        g_pClientInterface = new CClient;
    }
    
    return g_pClientInterface;
}

/** Helper for destruction */
void _DestroyClient(void *pMem)
{
    g_pClientInterface = NULL;
    delete (CClient*)pMem;
}

REGISTER_DYNAMIC_INTERFACE_FUNC(_CreateClient, _DestroyClient,
                                CLIENT_INTERFACE_NAME,
                                CLIENT_INTERFACE_VERSION);

CClient *GetClient(void)
{
    return (CClient *)g_pClientInterface;
}

//------------------------------------------------------------------------------
/**
 * Initialization of the client. This will happen after the extension
 * manager has been created.
 * @param pExtensions The extension manager which created this extension.
 */
void CClient::Initialize(IExtensions *pExtensions)
{
    m_pExtensions = pExtensions;
    ASSERTION(g_pClientInterface == this, "Trying to create a secondary Client Interface?!");
    
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
}

//------------------------------------------------------------------------------
/**
 * Extension Run method, Called once per tick by the extension manager.
 */
void CClient::Run(void)
{
    // TEMP: Just clearing the window right now to grey.
    // Client will have no graphics code in the end.
    GetPlatform()->ActivateGraphicsContext();
    
    unsigned int width, height;
    GetPlatform()->GetWindowSizePixels(width, height);
    
    glViewport(0, 0, width, height);
    
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    GetPlatform()->SwapGraphicsContextBuffers();
}

//------------------------------------------------------------------------------
/**
 * Called usually at the end of program execution when the client and
 * server are being shutdown. The server is shutdown before the clients.
 */
void CClient::Shutdown()
{

}

//------------------------------------------------------------------------------
/**
 * Recieve a buffer from the extension manager
 * @param pBuffer The buffer to recv
 */
void CClient::RecvBuffer(DataPacking::DataBuffer *pBuffer)
{
    if(pBuffer)
    {
        DataPacking::NetworkUnpackage netUnpack(pBuffer);
        netUnpack.UnpackToMappables((CDataMappable**)m_pSharedEntities,
                                    Foundation::MAX_SHARED_BASE_ENTITIES);
    }
}

//------------------------------------------------------------------------------
/**
 * Registers a new entity as shared
 * @param pEnt The entity to register
 */
unsigned int CClient::RegisterSharedEntity(CEntityBase *pEnt)
{
    // Note: If you want to share some client entities with something, add
    // a new container here.
    return UINT_MAX;
}

//------------------------------------------------------------------------------
/**
 * Registers a local entity
 * @param pEnt The entity to register
 * TODO: This needs a better system, so old slots get refilled.
 */
unsigned int CClient::RegisterLocalEntity(CEntityBase *pEnt)
{
    ASSERTION((m_uiNumLocalEntities < MAX_NUM_LOCAL_ENTITIES),
              "Client: Reached maximum local base entities!");
    
    m_pLocalEntities[m_uiNumLocalEntities] = pEnt;
    return m_uiNumLocalEntities++;
}

//------------------------------------------------------------------------------
/**
 * Overrides for entity handler.
 * TODO: I am not sure this is the greatest idea, maybe we should inject a
 * handler class into the entity factory instead of these goofy global functions?
 */
unsigned int    RegisterSharedEntity(CEntityBase *pEnt)
{
    return GetClient()->RegisterSharedEntity(pEnt);
}
unsigned int    RegisterLocalEntity(CEntityBase *pEnt)
{
    return GetClient()->RegisterLocalEntity(pEnt);
}