//
//  CClient.h
//  client
//
//  Created by Ryan Sheffer on 2013-01-25.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef CCLIENT_H
#define CCLIENT_H

#include "IClient.h"

class CClient : public IClient
{
public:
    void            Initialize(CExtensions *pExtensions);
    void            Shutdown();
    
    CExtensions     *GetExtensions(void){ return m_pExtensions; }
    
private:
    CExtensions     *m_pExtensions;
};


#endif // CCLIENT_H
