//
//  CEngine.cpp
//  genesis
//
//  Created by Ryan Sheffer on 2013-01-27.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include "CEngine.h"

//------------------------------------------------------------------------------
// Purpose: Initialize of the engine
//------------------------------------------------------------------------------
void CEngine::Initialize(void)
{
    m_pExtensionManager = new CExtensions();
    if(!m_pExtensionManager)
    {
        ASSERTION(m_pExtensionManager, "Could not create extensions manager!");
        m_bHaultExecution = true;
        return;
    }
    
    m_pExtensionManager->CreateAllExtensions();
}

//------------------------------------------------------------------------------
// Purpose: Run the engine
//------------------------------------------------------------------------------
void CEngine::Run(void)
{
    ASSERTION(m_pExtensionManager, "Running engine with no extension manager!");
    m_pExtensionManager->RunExtensions();
}

//------------------------------------------------------------------------------
// Purpose: Shutdown the engine.
//------------------------------------------------------------------------------
void CEngine::Shutdown(void)
{
    m_pExtensionManager->DestroyAllExtensions();
    delete m_pExtensionManager;
}