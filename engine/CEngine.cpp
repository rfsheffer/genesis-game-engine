//
//  CEngine.cpp
//  The lowest level of a running genesis program, works with the extensions
//  manager to run the application as designed by the developer.
//
//  Created by Ryan Sheffer on 2013-01-27.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include "CEngine.h"

/**
 * Initialize the engine
 */
void CEngine::Initialize(void)
{
    // Initialize us as the first
    m_EngineClients[LOCAL_ENGINE_CLIENT_INDEX].InitializeLocal();
    
    m_pExtensionManager = new CExtensions();
    if(!m_pExtensionManager)
    {
        ASSERTION(m_pExtensionManager, "Could not create extensions manager!");
        m_bHaultExecution = true;
        return;
    }
    
    m_pExtensionManager->CreateAllExtensions();
}

/**
 * Run the engine, called by the main program thread.
 */
void CEngine::Run(void)
{
    ASSERTION(m_pExtensionManager, "Running engine with no extension manager!");
    m_pExtensionManager->RunExtensions();
}

/**
 * Shutdown the engine
 */
void CEngine::Shutdown(void)
{
    m_pExtensionManager->DestroyAllExtensions();
    delete m_pExtensionManager;
}

/**
 * Send a buffer to all engine clients
 * @param pBuffer The buffer to send
 * @param pExtensionName The name of the specific system the engine client should
 * send the buffer to. Set to NULL to let the engine use the data.
 */
void CEngine::SendDataBuffer(DataPacking::DataBuffer *pBuffer,
                                        const char *pExtensionName)
{
    if(pExtensionName == NULL)
    {
        // Engine handles
    }
    
    // Sending only the client for now so we can proceed, but I am going
    // to come back and copy this data before it's sent to the extensions.
    // Also, the data will have to be put into a que. We want this to be
    // multi-thread compatible in the future. Also, need to setup networking
    // here with the code written for this. ~RFS
    m_pExtensionManager->RecvDataBuffer(pBuffer, pExtensionName);
    
    // Send the buffer to all engine clients
    //for(int i = 1; i < MAX_ENGINE_CLIENTS; ++i)
    //{
    //
    //}
}