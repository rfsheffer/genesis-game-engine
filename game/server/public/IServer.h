//
//  IServer.h
//  server
//
//  Created by Ryan Sheffer on 2013-01-25.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef I_SERVER_H
#define I_SERVER_H

#include "iExtension.h"

#define SERVER_INTERFACE_NAME       "server"
#define SERVER_INTERFACE_VERSION    1

START_EXTENSION_INTERFACE(Server, SERVER_INTERFACE_NAME)
END_EXTENSION_INTERFACE();

#endif // I_SERVER_H
