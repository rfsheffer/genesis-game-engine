//
//  CExtensions.h
//  An extensions manager designed for a client -> server game
//
//  Created by Ryan Sheffer on 2013-01-25.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef CEXTENSIONS_H
#define CEXTENSIONS_H

#ifdef _WIN
#pragma once
#endif

#include "iExtension.h"

/*! \def MAX_BASE_EXTENSIONS
 \brief The max number of extensions which can be loaded at once.
 * TODO: Get rid of me. Make Dynamic!
 Details.
 */
#define MAX_BASE_EXTENSIONS         5

/*! \def NUM_SEND_BUFFERS
 * This is the number of buffers we can have packed up for sending at a time.
 * TODO: Get rid of me. Make Dynamic!
 */
#define NUM_SEND_BUFFERS            2

/*! \def MAX_EXTENSION_NAME
 * This is the max number of characters in an extensions name.
 */
#define MAX_EXTENSION_NAME          32

/**
 * A message to be sent to an extension.
 */
class send_buffer_t
{
public:
    send_buffer_t() : sendBuffer(1024, 256) {}
    
    char                        szSendName[MAX_EXTENSION_NAME];
    DataPacking::DataBuffer     sendBuffer;
};

/*! An extension manager. */
class CExtensions : public IExtensions
{
public:
    CExtensions();
    ~CExtensions() {}
    
    bool        HookExtension(const char *pszExtensionName);
    void        RunExtensions(void);
    void        DestroyAllExtensions(void);
    void        SendBuffer(const char *pszSendDest, DataPacking::DataBuffer *pBuffer);
    void        DispatchPendingMessages(void);
    
    /**
     * Get a send buffer by index.
     * @param index The index of the buffer to get.
     */
    DataPacking::DataBuffer *GetSendBuffer(unsigned int index)
    {
        ASSERTION(index >= 0 && index < NUM_SEND_BUFFERS,
                  "Getting out of range send buffer!");
        return &m_sendBuffers[index].sendBuffer;
    }
    
    /**
     * The number of buffers we have sendable.
     * Note: This is not the number of active buffers, just the holder size.
     */
    unsigned int        GetNumSendBuffers(void) const
    {
        return NUM_SEND_BUFFERS;
    }
    
    /**
     * Clears all pending send buffers and allows them to be used again.
     */
    void        InvalidateSendBuffers(void)
    {
        m_uiCurSendBuffer = 0;
    }

private:
    
    /** Number of extensions currently loaded. */
    unsigned int    m_uiNumExtensions;
    
    /**
     * The extensions currently loaded.
     * @see m_uiNumExtensions
     */
    iExtension      *m_pExtensions[MAX_BASE_EXTENSIONS];
    DLLHANDLE        m_pDLLsOpen[MAX_BASE_EXTENSIONS];
    
   /**
    * Send Buffers
    * @see m_uiCurSendBuffer
    */
    send_buffer_t               m_sendBuffers[NUM_SEND_BUFFERS];
    
    /** The number of send buffers currently ready to be sent out. */
    unsigned int                m_uiCurSendBuffer;
};


#endif // CEXTENSIONS_H
