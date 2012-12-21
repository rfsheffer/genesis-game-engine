//
//  IGraphicsContext.h
//  Derive from this interface if you want to create a new context type.
//
//  Created by Ryan Sheffer on 2012-09-30.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef I_GRAPHICS_CONTEXT_H
#define I_GRAPHICS_CONTEXT_H

// A bunch of global settings for all renderers
#include "render_globals.h"

class IGraphicsContext
{
public:
    
    virtual void Init(void) = 0;
    
    virtual void SetViewport(unsigned int x,
                             unsigned int y,
                             unsigned int width,
                             unsigned int height) = 0;
    
    virtual void FrameUpdate(void) = 0;
    
    virtual void Shutdown(void) = 0;
};

#endif // I_GRAPHICS_CONTEXT_H
