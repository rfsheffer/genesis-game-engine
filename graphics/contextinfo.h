//
//  contextinfo.h
//  Graphics Context Information
//
//  Created by Ryan Sheffer on 2/4/2014.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#ifndef GRAPHICS_CONTEXT_INFO_H
#define GRAPHICS_CONTEXT_INFO_H

namespace graphics
{
    
//--------------------------------------------------------------------------
/**
 * A Settings structure to send with the creation call of a graphics context
 * on an active window.
 * @note fullscreen and windowed can be true at the same time, it will create both;
 * @note setting a size to 0 will not create said buffer.
 */
struct context_info
{
    /** Size in bits of a color buffer texel */
    unsigned int    colorBufferSize;
    
    /** Size in bits of a depth buffer texel */
    unsigned int    depthBufferSize;
    
    /** Size in bits of a stencil buffer texel */
    unsigned int    stencilBufferSize;
    
    /** Size in bits of an accumulation buffer texel */
    unsigned int    accumulationBufferSize;
    
    /** Make a fullscreen context? */
    bool            fullscreen;
    
    /** Make a windowed context? */
    bool            windowed;
    
    /** Default to fullscreen */
    bool            defaultFullscreen;
    
    /** High resolution monitor enabled */
    bool            highResBackingMode;
    
    /** Vertical sync mode */
    bool            vsync;
    
    /**
     * Enables the MAC specific multi-threading for OpenGL. Apples documentation
     * says this feature basically threads some of the internal workings of the
     * OpenGL server calls which 'could' improve performace.
     */
    bool            multiThreadServer;
};
    
}

#endif // GRAPHICS_CONTEXT_INFO_H
