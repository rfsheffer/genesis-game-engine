//
//  IEngine.h
//  Engine Interface for access to the engine from outside sources.
//
//  Created by Ryan Sheffer on 2013-02-05.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef IENGINE_H
#define IENGINE_H

#ifdef _WIN
#pragma once
#endif

#define ENGINE_INTERFACE_NAME           "engine"
#define ENGINE_INTERFACE_VERSION        1

/** Engine Interface */
class IEngine
{
public:
    
    virtual void        Initialize(void) = 0;
    virtual void        Run(void) = 0;
    virtual void        Shutdown(void) = 0;
    virtual bool        FinishedExecution(void) = 0;
};

#endif // IENGINE_H
