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

/*! An extension manager. */
class CExtensions : public IExtensions
{
public:
    CExtensions() : m_uiNumExtensions(0) {}
    
    DECLARE_IMPORT_EXTENSION(Server);
    DECLARE_IMPORT_EXTENSION(Client);
    
    bool        CreateAllExtensions(void);
    void        RunExtensions(void);
    void        DestroyAllExtensions(void);
    void        SendBuffer(const char *pszSendDest, DataPacking::DataBuffer *pBuffer);
    void        RecvBuffer(const char *pszRecvName, DataPacking::DataBuffer *pBuffer);
    
    /**
     * Get a send buffer by index.
     * @param index The index of the buffer to get.
     */
    DataPacking::DataBuffer *GetSendBuffer(unsigned int index)
    {
        ASSERTION(index >= 0 && index < NUM_SEND_BUFFERS,
                  "Getting out of range send buffer!");
        return m_sendBuffers[index];
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
     * Get the platform interface. This interface gives the programmer a number
     * of tools for file control, input, and other important platform systems.
     */
    inline IPlatform   *GetPlatform(){ return pPlatform; }

private:
    
    /** Number of extensions currently loaded. */
    unsigned int    m_uiNumExtensions;
    
    /**
     * The extensions currently loaded.
     * @see m_uiNumExtensions
     */
    iExtension      *pExtensions[MAX_BASE_EXTENSIONS];
    
    /** The platform extension. */
    IPlatform       *pPlatform;
    
   /** Send Buffers */
    DataPacking::DataBuffer     *m_sendBuffers[NUM_SEND_BUFFERS];
};


#endif // CEXTENSIONS_H
