//
//  IClient.h
//  Client
//
//  Created by Ryan Sheffer on 2013-01-25.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef I_CLIENT_H
#define I_CLIENT_H

#ifdef _WIN
#pragma once
#endif

#include "IExtension.h"

#define CLIENT_INTERFACE_NAME       "client"
#define CLIENT_INTERFACE_VERSION    1

START_EXTENSION_INTERFACE(Client, CLIENT_INTERFACE_NAME)
END_EXTENSION_INTERFACE();

#endif // I_CLIENT_H
