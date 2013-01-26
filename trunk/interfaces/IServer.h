//
//  IServer.h
//  server
//
//  Created by Ryan Sheffer on 2013-01-25.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef I_SERVER_H
#define I_SERVER_H

class CExtensions;

class IServer
{
public:
    virtual void            Initialize(CExtensions *pExtensions) = 0;
    virtual void            Shutdown() = 0;
};

#endif // I_SERVER_H
