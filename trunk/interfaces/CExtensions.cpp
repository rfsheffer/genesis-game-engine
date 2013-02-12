//
//  CExtensions.cpp
//  Base Extension Manager
//
//  Created by Ryan Sheffer on 2013-01-25.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include "CExtensions.h"
#include "CPlatform.h"

/*! \def ADD_EXTENSION(name)
 \brief Adds an extension to the extension list, and initializes it.
 Note: The order of added extensions is the order of extension execution.
 
 Details.
 */
#define ADD_EXTENSION(name) \
    ASSERTION(strlen(#name) > 0 && strlen(#name) < MAX_EXTENSION_NAME, "Bad Extension Name Length!"); \
    Get##name()->Initialize(this); \
    pExtensions[m_uiNumExtensions++] = Get##name();

/**
 * Creates all extensions.
 */
bool CExtensions::CreateAllExtensions(void)
{
    pPlatform = new CPlatform();
    
    DEFINE_IMPORT_EXTENSION("./bin/libserver.dylib", Server);
    DEFINE_IMPORT_EXTENSION("./bin/libclient.dylib", Client);
    
    ADD_EXTENSION(Platform);
    ADD_EXTENSION(Server);
    ADD_EXTENSION(Client);
    
    m_uiCurSendBuffer = 0;
    
    return true;
}

/**
 * Executes the extensions in the order of creation.
 */
void CExtensions::RunExtensions(void)
{
    for(unsigned int i = 0; i < m_uiNumExtensions; ++i)
    {
        // Dispatch pending messages
        DispatchPendingMessages();
        
        // Run the extension
        pExtensions[i]->Run();
    }
}

/**
 * Sends all new cross extension messages to their owners
 */
void CExtensions::DispatchPendingMessages(void)
{
    for(int i = 0; i < m_uiCurSendBuffer; ++i)
    {
        // TODO: Get rid of this string lookup.
        if(strcmp(m_sendBuffers[i].szSendName, "Client") == 0)
        {
            GetClient()->RecvBuffer(&m_sendBuffers[i].sendBuffer);
        }
        else if(strcmp(m_sendBuffers[i].szSendName, "Server") == 0)
        {
            GetServer()->RecvBuffer(&m_sendBuffers[i].sendBuffer);
        }
    }
    
    m_uiCurSendBuffer = 0;
}

/**
 * Closes all open extensions.
 */
void CExtensions::DestroyAllExtensions(void)
{
    GetServer()->Shutdown();
    GetClient()->Shutdown();
    GetPlatform()->Shutdown();
    
    CLOSE_IMPORT_EXTENSION(Server);
    CLOSE_IMPORT_EXTENSION(Client);
}

/**
 * This will add a buffer to the list of send buffers that should be sent.
 * Note: This could also be called by the engine because of a network message.
 * @param pszSendName The name of the extension to recieve this message.
 * @param pBuffer The buffer to send to the extension.
 */
void CExtensions::SendBuffer(const char *pszSendName, DataPacking::DataBuffer *pBuffer)
{
    ASSERTION(pszSendName && pBuffer, "Incomplete parameters in SendBuffer!");
    
    strncpy(m_sendBuffers[m_uiCurSendBuffer].szSendName, pszSendName, MAX_EXTENSION_NAME);
    m_sendBuffers[m_uiCurSendBuffer].sendBuffer = *pBuffer;
    
    ++m_uiCurSendBuffer;
}