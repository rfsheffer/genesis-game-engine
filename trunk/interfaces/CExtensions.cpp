//
//  CExtensions.cpp
//  Base Extension Manager
//
//  Created by Ryan Sheffer on 2013-01-25.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include "CExtensions.h"
#include "CPlatform.h"

// Adds an extension to the extension list, and initializes it.
// Note: The order of added extensions is the order of extension execution.
#define ADD_EXTENSION(name) \
    pExtensions[m_uiNumExtensions++] = Get##name(); \
    Get##name()->Initialize(this);

//------------------------------------------------------------------------------
// Purpose: Creates all extensions
//------------------------------------------------------------------------------
bool CExtensions::CreateAllExtensions(void)
{
    pPlatform = new CPlatform();
    
    DEFINE_IMPORT_EXTENSION("./bin/libserver.dylib", Server);
    DEFINE_IMPORT_EXTENSION("./bin/libclient.dylib", Client);
    
    ADD_EXTENSION(Platform);
    ADD_EXTENSION(Server);
    ADD_EXTENSION(Client);
    
    return true;
}

//------------------------------------------------------------------------------
// Purpose: Executes the extensions in the order of creation
//------------------------------------------------------------------------------
void CExtensions::RunExtensions(void)
{
    for(unsigned int i = 0; i < m_uiNumExtensions; ++i)
    {
        pExtensions[i]->Run();
    }
}

//------------------------------------------------------------------------------
// Purpose: Closes all open extensions
//------------------------------------------------------------------------------
void CExtensions::DestroyAllExtensions(void)
{
    GetServer()->Shutdown();
    GetClient()->Shutdown();
    GetPlatform()->Shutdown();
    
    CLOSE_IMPORT_EXTENSION(Server);
    CLOSE_IMPORT_EXTENSION(Client);
}