//
//  CExtensions.h
//  An extensions manager designed for a client -> server game
//
//  Created by Ryan Sheffer on 2013-01-25.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef CEXTENSIONS_H
#define CEXTENSIONS_H

#include "IServer.h"
#include "IClient.h"
#include "IPlatform.h"
#include "iExtension.h"

/*! \def MAX_BASE_EXTENSIONS
 \brief The max number of extensions which can be loaded at once.
 
 Details.
 */
#define MAX_BASE_EXTENSIONS         5

/**
 * This is the number of buffers we can have packed up for sending at a time.
 */
#define NUM_SEND_BUFFERS            2

/**
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
    CExtensions() : m_uiNumExtensions(0) {}
    ~CExtensions() {}
    
    DECLARE_IMPORT_EXTENSION(Server);
    DECLARE_IMPORT_EXTENSION(Client);
    
    bool        CreateAllExtensions(void);
    void        RunExtensions(void);
    void        DestroyAllExtensions(void);
    void        SendBuffer(const char *pszSendDest, DataPacking::DataBuffer *pBuffer);
    void        DispatchPendingMessages(void);
    
    /**
     * Sets the platform interface to be used for this application
     * @param pPlatform The platform to set as primary platform for this application.
     */
    virtual void        SetPlatform(IPlatform *pPlatform)
    {
        m_pPlatform = pPlatform;
    }
    
    /**
     * Get the platform interface. This interface gives the programmer a number
     * of tools for file control, input, and other important platform systems.
     * @param return The platform wrapper for this application.
     */
    virtual IPlatform   *GetPlatform(void){ return m_pPlatform; }
    
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
    
    /** The platform extension. */
    IPlatform       *m_pPlatform;
    
   /**
    * Send Buffers
    * @see m_uiCurSendBuffer
    */
    send_buffer_t               m_sendBuffers[NUM_SEND_BUFFERS];
    
    /** The number of send buffers currently ready to be sent out. */
    unsigned int                m_uiCurSendBuffer;
};


#endif // CEXTENSIONS_H
