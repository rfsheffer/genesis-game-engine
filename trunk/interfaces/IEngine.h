//
//  IEngine.h
//  Engine Interface for access to the engine from outside sources.
//
//  Created by Ryan Sheffer on 2013-02-05.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef IENGINE_H
#define IENGINE_H

class IPlatform;

/** Engine Interface */
class IEngine
{
public:
    
    virtual void        Initialize(IPlatform *pPlatform) = 0;
    virtual void        Run(void) = 0;
    virtual void        Shutdown(void) = 0;
    virtual bool        FinishedExecution(void) = 0;    
};

#endif // IENGINE_H
