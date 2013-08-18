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
#include "IPlatform.h"

/*! The client controller. This classes Run method is called every tick. */
class CClient : public IClient
{
public:
    void            Initialize(IExtensions *pExtensions);
    void            Run(void);
    void            Shutdown();
    
    unsigned int    RegisterSharedEntity(CEntityBase *pEnt);
    unsigned int    RegisterLocalEntity(CEntityBase *pEnt);
    
    /** Get the extensions manager which created this extension. */
    IExtensions     *GetExtensions(void){ return m_pExtensions; }
    
    void            RecvBuffer(DataPacking::DataBuffer *pBuffer);
    
private:
    /** Extensions Manager which created this extension */
    IExtensions     *m_pExtensions;
    
    /** The max number of local entities, change as needed. */
    static const unsigned int MAX_NUM_LOCAL_ENTITIES = 32;
    
    /** The number of shared entities currently registered */
    unsigned int    m_uiNumSharedEntities;
    
    /** Entities which can be shared with other systems */
    CEntityBase     *m_pSharedEntities[Foundation::MAX_SHARED_BASE_ENTITIES];
    
    /** The number of local entities currently registered */
    unsigned int    m_uiNumLocalEntities;
    
    /** Entities which can be shared with other systems */
    CEntityBase     *m_pLocalEntities[MAX_NUM_LOCAL_ENTITIES];
    
    /** The main render context being used by this client */
    render::CContext    *m_renderContext;
};

CClient     *GetClient(void);


#endif // CCLIENT_H
