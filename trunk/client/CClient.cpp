//
//  CClient.cpp
//  client
//
//  Created by Ryan Sheffer on 2013-01-25.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include "CClient.h"

//--------------------------------------------------------------------------
// Purpose: Pushes a variable onto the token stack
//--------------------------------------------------------------------------
DLL_EXPORT
IClient *CreateClient(void)
{
    return new CClient();
}

void CClient::Initialize(CExtensions *pExtensions)
{
    m_pExtensions = pExtensions;
}

void CClient::Shutdown()
{
    
}