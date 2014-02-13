//
//  graphics.h
//  Primary Graphics API for displaying 3D art
//
//  Created by Ryan Sheffer on 2/5/2014.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#ifndef GRAPHICS_H
#define GRAPHICS_H

#ifdef _WIN
#pragma once
#endif

#include "igraphics.h"

class Graphics : public IGraphics
{
public:
    
    void Initialize(IExtensions *pExtensions){}
    void Run(void){}
    void Shutdown(){}
    void RecvBuffer(DataPacking::DataBuffer *pBuffer) {}
};

#endif // GRAPHICS_H
