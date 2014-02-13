//
//  CEngine.cpp
//  The lowest level of a running genesis program, works with the extensions
//  manager to run the application as designed by the developer.
//
//  Created by Ryan Sheffer on 2013-01-27.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include "enginehead.h"
#include "CEngine.h"
#include "AppVarHolder.h"

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

//------------------------------------------------------------------------------
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
    
    // TODO: Which extensions are hooked should be based on the extensions
    // scheme file. Dedicated Servers vs Client etc...
    m_pExtensionManager->HookExtension("server");
    m_pExtensionManager->HookExtension("client");
}

//------------------------------------------------------------------------------
/**
 * Run the engine, called by the main program thread.
 */
void CEngine::Run(void)
{
    ASSERTION(m_pExtensionManager, "Running engine with no extension manager!");
    m_pExtensionManager->RunExtensions();
}

//------------------------------------------------------------------------------
/**
 * Shutdown the engine
 */
void CEngine::Shutdown(void)
{
    m_pExtensionManager->DestroyAllExtensions();
    delete m_pExtensionManager;
}

/** Creates an instance of the engine interface */
void *__CreateEngine(void)
{
    return new CEngine;
}

void __DestroyEngine(void *pMem)
{
    delete (CEngine*)pMem;
}

REGISTER_DYNAMIC_INTERFACE_FUNC(__CreateEngine, __DestroyEngine,
                                    ENGINE_INTERFACE_NAME,
                                    ENGINE_INTERFACE_VERSION);