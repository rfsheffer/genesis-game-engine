//
//  CClient.cpp
//  This is the master controller for the client extension. It recieves entity
//  information from the server and updates the shared entities. It also
//  controls rendering and client side only FX such as particles.
//
//  Created by Ryan Sheffer on 2013-01-25.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include "CClient.h"
#include "data_pack.h"
#include "data_networkunpack.h"
#include "render_context.h"
#include "CBasicRender.h"

// Allow this extension to be used by the manager as an importable extension.
SETUP_EXTENSION_LINK(Client);

namespace __client_holder
{
    CClient     *pClient;
}

//------------------------------------------------------------------------------
/**
 * Gets the client itself.
 */
CClient     *GetClient(void)
{
    return __client_holder::pClient;
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
    __client_holder::pClient = this;
    
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
    
    window_info info;
    info.x = 0;
    info.y = 0;
    info.width = 800;
    info.height = 600;
    
    hWindow wind = pExtensions->GetPlatform()->CreateContentWindow(info);
    ASSERTION(wind != -1, "Cannot create window for client!");
    
    render::render_context_settings settings;
    render::GetDefaultRenderSettings(settings);
    
    render::CContext *pContext = new render::CContext;
    pContext->InitializeContext(wind, settings);
    
    m_renderContext = pContext;
}

//------------------------------------------------------------------------------
/**
 * Extension Run method, Called once per tick by the extension manager.
 */
void CClient::Run(void)
{
   m_renderContext->RefreshContext();
    
    // TEST TEST
   CBasicRender render;
   render.Setup(m_renderContext);
   render.Draw(m_renderContext);
    
    m_renderContext->SwapBuffers();
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
        netUnpack.UnpackToEntities(m_pSharedEntities, Foundation::MAX_SHARED_BASE_ENTITIES);
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