//
//  CEngine.cpp
//  The lowest level of a running genesis program, works with the extensions
//  manager to run the application as designed by the developer.
//
//  Created by Ryan Sheffer on 2013-01-27.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include "CEngine.h"

DLL_EXPORT
IEngine *__CreateEngine(void)
{
    return new CEngine();
}

/**
 * Initialize the engine
 */
void CEngine::Initialize(IPlatform *pPlatform)
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
    
    m_pExtensionManager->SetPlatform(pPlatform);
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