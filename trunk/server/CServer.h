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
    void            Initialize(CExtensions *pExtensions);
    void            Run(void);
    void            Shutdown(void);
    
    /**
     * Get the extensions manager which created this extension.
     */
    CExtensions     *GetExtensions(void){ return m_pExtensions; }
    
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


#endif // CSERVER_H
