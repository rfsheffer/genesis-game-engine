//
//  CServer.h
//  server
//
//  Created by Ryan Sheffer on 2013-01-25.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef CSERVER_H
#define CSERVER_H

#include "IServer.h"

class CServer : public IServer
{
public:
    void            Initialize(CExtensions *pExtensions);
    void            Run(void){}
    void            Shutdown();
    
    CExtensions     *GetExtensions(void){ return m_pExtensions; }
    
private:
    CExtensions     *m_pExtensions;
};


#endif // CSERVER_H
