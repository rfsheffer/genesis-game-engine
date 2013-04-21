//
//  CServer.h
//  This is the master controller for the server extension. It dispatches
//  updates for all entities, and sends the new information to the clients.
//
//  Created by Ryan Sheffer on 2013-01-25.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef CSERVER_H
#define CSERVER_H

#include "IServer.h"
#include "ent_base.h"

/*! The server controller. This classes Run method is called every tick. */
class CServer : public IServer
{
public:
    void            Initialize(IExtensions *pExtensions);
    void            Run(void);
    void            Shutdown(void);
    
    unsigned int    RegisterSharedEntity(CEntityBase *pEnt);
    unsigned int    RegisterLocalEntity(CEntityBase *pEnt);
    
    /**
     * Get the extensions manager which created this extension.
     */
    IExtensions     *GetExtensions(void){ return m_pExtensions; }
    
    void            RecvBuffer(DataPacking::DataBuffer *pBuffer);
    
private:
    /**
     * Extensions Manager which created this extension
     */
    IExtensions     *m_pExtensions;
    
    /**
     * The max number of local entities, change as needed.
     */
    static const unsigned int MAX_NUM_LOCAL_ENTITIES = 32;
    
    /**
     * The number of shared entities currently registered
     */
    unsigned int    m_uiNumSharedEntities;
                                         
    /**
     * Entities which can be shared with other systems
     */
    CEntityBase     *m_pSharedEntities[Foundation::MAX_SHARED_BASE_ENTITIES];
    
    /**
     * The number of local entities currently registered
     */
    unsigned int    m_uiNumLocalEntities;
    
    /**
     * Entities which can be shared with other systems
     */
    CEntityBase     *m_pLocalEntities[MAX_NUM_LOCAL_ENTITIES];
};

CServer     *GetServer(void);


#endif // CSERVER_H
