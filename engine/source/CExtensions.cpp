//
//  CExtensions.cpp
//  Base Extension Manager
//
//  Created by Ryan Sheffer on 2013-01-25.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include "CExtensions.h"
#include "keyvalues.h"

//------------------------------------------------------------------------------
/**
 * Constructor
 */
CExtensions::CExtensions() :
m_uiNumExtensions(0),
m_uiCurSendBuffer(0)
{
    
}

//------------------------------------------------------------------------------
/**
 * Hooks up an extension by interface
 */
bool CExtensions::HookExtension(const char *pszExtensionName)
{
    void *pDLLHandle = NULL;
    iExtension *pExtension =
        (iExtension *)GetInterfaceRegistration()->GetInterface(pszExtensionName, -1);
    
    if(pExtension == NULL)
    {
        char dllpath[MAX_PATH]; dllpath[0] = '\0';
        strncat(dllpath, pszExtensionName, MAX_PATH);
        strncat(dllpath, ".dylib", MAX_PATH);
        
        void *pDLLHandle = dlopen(dllpath, RTLD_NOW);
        if(pDLLHandle == NULL)
        {
            ASSERTION(pDLLHandle, "Unable to connect extension dll for %s!", pszExtensionName);
            return false;
        }
        
        pExtension = (iExtension *)GetInterfaceRegistration()->GetInterface(pszExtensionName, -1);
        if(!pExtension)
        {
            dlclose(pDLLHandle);
            
            ASSERTION(false, "Unable to create extension %s from dynamic lib, "
                                "missing interface!", pszExtensionName);
            return false;
        }
    }
    
    pExtension->Initialize(this);
    m_pExtensions[m_uiNumExtensions] = pExtension;
    m_pDLLsOpen[m_uiNumExtensions] = pDLLHandle;
    
    ++m_uiNumExtensions;
    
    return true;
}

//------------------------------------------------------------------------------
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
        m_pExtensions[i]->Run();
    }
}

//------------------------------------------------------------------------------
/**
 * Sends all new cross extension messages to their owners
 */
void CExtensions::DispatchPendingMessages(void)
{
    for(int i = 0; i < m_uiCurSendBuffer; ++i)
    {
        const char *pMsgExtensionName = m_sendBuffers[i].szSendName;
        
        for(int j = 0; j < m_uiNumExtensions; ++j)
        {
            if(m_pExtensions[j] &&
               strcmp(pMsgExtensionName, m_pExtensions[j]->GetInterfaceName()) == 0)
            {
                m_pExtensions[j]->RecvBuffer(&m_sendBuffers[i].sendBuffer);
            }
        }
    }
    
    m_uiCurSendBuffer = 0;
}

//------------------------------------------------------------------------------
/**
 * Closes all open extensions.
 */
void CExtensions::DestroyAllExtensions(void)
{
    for(int i = 0; i < m_uiNumExtensions; ++i)
    {
        m_pExtensions[i]->Shutdown();
        
        // Now we kill the interface (if nessesary)
        GetInterfaceRegistration()->ReleaseInterfacePointer(m_pExtensions[i]->GetInterfaceName(), m_pExtensions[i]);
        
        // Close the DLL if one was linked
        if(m_pDLLsOpen[i] != NULL)
        {
            dlclose(m_pDLLsOpen[i]);
        }
    }
}

//------------------------------------------------------------------------------
/**
 * This will add a buffer to the list of send buffers that should be sent.
 * Note: This could also be called by the engine because of a network message.
 * @param pszSendName The name of the extension to recieve this message.
 * @param pBuffer The buffer to send to the extension.
 */
void CExtensions::SendBuffer(const char *pszSendName, DataPacking::DataBuffer *pBuffer)
{
    ASSERTION(pszSendName && pBuffer, "Incomplete parameters in SendBuffer!");
    ASSERTION(m_uiCurSendBuffer < NUM_SEND_BUFFERS, "Ran out of extension send buffers! Raise Limit!");
    
    strncpy(m_sendBuffers[m_uiCurSendBuffer].szSendName, pszSendName, MAX_EXTENSION_NAME);
    m_sendBuffers[m_uiCurSendBuffer].sendBuffer = *pBuffer;
    
    ++m_uiCurSendBuffer;
}