//
//  network_base.h
//  This is where all the packing is done for networking the server and client.
//
//  Created by Ryan Sheffer on 2012-12-31.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef NETWORK_BASE_H
#define NETWORK_BASE_H

#define DECLARE_NETWORK_TABLE()                 \
    public:                                     \
        virtual void SendNetworkItems(void);    \

#define BEGIN_NETWORK_TABLE(_classname)      \
    void _classname::SendNetworkItems(void)  \
    {                                        \
    }                                        \

#define END_NETWORK_TABLE()

#define NETWORK_PROP_INT(),
#define NETWORK_PROP_FLOAT(),
#define NETWORK_PROP_VECTOR3(),

#endif // NETWORK_BASE_H
