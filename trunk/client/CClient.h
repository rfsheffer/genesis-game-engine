//
//  CClient.h
//  This is the master controller for the client extension. It recieves entity
//  information from the server and updates the shared entities. It also
//  controls client side only FX such as particles.
//
//  Created by Ryan Sheffer on 2013-01-25.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef CCLIENT_H
#define CCLIENT_H

#include "IClient.h"
#include "ent_base.h"

/*! The client controller. This classes Run method is called every tick. */
class CClient : public IClient
{
public:
    void            Initialize(CExtensions *pExtensions);
    void            Run(void);
    void            Shutdown();
    
    /**
     * Get the extensions manager which created this extension.
     */
    CExtensions     *GetExtensions(void){ return m_pExtensions; }
    
    void            RecvDataBuffer(DataPacking::DataBuffer *pBuffer);
    
private:
    /**
     * Extensions Manager which created this extension
     */
    CExtensions     *m_pExtensions;
    
    /**
     * Entities which exist on both the client and the server
     */
    CEntityBase     *m_pSharedEntities[MAX_NUM_ENTITIES];
};


#endif // CCLIENT_H
