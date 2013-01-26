//
//  CExtensions.cpp
//  genesis
//
//  Created by Ryan Sheffer on 2013-01-25.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include "CExtensions.h"

//------------------------------------------------------------------------------
// Purpose: Creates all extensions
//------------------------------------------------------------------------------
bool CExtensions::CreateAllExtensions(void)
{
    // Create the Server Extension
    pServerHandle = dlopen("./bin/libserver.dylib", RTLD_NOW);
    if(pServerHandle == NULL)
    {
        ASSERTION(pServerHandle, "Unable to connect to server extension!");
        return false;
    }
    
    IServer     *(*CreateServer)(void);
    *(void **)(&CreateServer) = dlsym(pServerHandle, "CreateServer");
    
    if(CreateServer)
    {
        pServerExtension = (*CreateServer)();
    }
    
    // Create the client extension
    pClientHandle = dlopen("./bin/libclient.dylib", RTLD_NOW);
    if(pClientHandle == NULL)
    {
        ASSERTION(pClientHandle, "Unable to connect to client extension!");
        return false;
    }
    
    IClient     *(*CreateClient)(void);
    *(void **)(&CreateClient) = dlsym(pClientHandle, "CreateClient");
    
    if(CreateClient)
    {
        pClientExtension = (*CreateClient)();
    }
    
    pServerExtension->Initialize(this);
    pClientExtension->Initialize(this);
    
    return true;
}

//------------------------------------------------------------------------------
// Purpose: Closes all open extensions
//------------------------------------------------------------------------------
void CExtensions::DestroyAllExtensions(void)
{
    pServerExtension->Shutdown();
    pClientExtension->Shutdown();
    
    dlclose(pServerHandle);
    dlclose(pClientHandle);
}