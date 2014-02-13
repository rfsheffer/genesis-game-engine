//
//  iExtension.h
//  Base Extension
//
//  Created by Ryan Sheffer on 2013-01-27.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef IEXTENSION_H
#define IEXTENSION_H

#ifdef _WIN
#pragma once
#endif

#include "iExtensions.h"

/*! \file iExtension.h
 \brief Extension Interface Macros and Interface class.
 
 Details.
 */

/*! Extension Interface */
class iExtension
{
public:
    virtual void            Initialize(IExtensions *pExtensions) = 0;
    virtual void            Run(void) = 0;
    virtual void            Shutdown() = 0;
    virtual void            RecvBuffer(DataPacking::DataBuffer *pBuffer) = 0;
    virtual const char      *GetInterfaceName(void) = 0;
};

/*! \def START_EXTENSION_INTERFACE(name)
 \brief A macro for starting a new interface. Declare any variables or functions
 after this macro is placed.
 
 Details.
 */
#define START_EXTENSION_INTERFACE(name, interfacename) \
\
class I##name : public iExtension \
{ \
public: \
    const char              *GetInterfaceName(void) { return interfacename; }

/*! \def END_EXTENSION_INTERFACE()
 \brief A macro for ending a new extension.
 
 Details.
 */
#define END_EXTENSION_INTERFACE() };

#endif // IEXTENSION_H