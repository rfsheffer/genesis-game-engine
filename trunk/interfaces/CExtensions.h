//
//  CExtensions.h
//  genesis
//
//  Created by Ryan Sheffer on 2013-01-25.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef CEXTENSIONS_H
#define CEXTENSIONS_H

#include "IServer.h"
#include "IClient.h"

class CExtensions
{
public:
    bool        CreateAllExtensions(void);
    
    IServer     *GetServer(){ return pServerExtension; }
    IClient     *GetClient(){ return pClientExtension; }
    
    void        DestroyAllExtensions(void);
    
private:
    
    void        *pServerHandle;
    IServer     *pServerExtension;
    
    void        *pClientHandle;
    IClient     *pClientExtension;
};


#endif // CEXTENSIONS_H
