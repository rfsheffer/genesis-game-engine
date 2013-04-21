//
//  IRender.h
//  Interface the renderer for cross extension vision
//
//  Created by Ryan Sheffer on 2013-04-19.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef I_RENDER_H
#define I_RENDER_H

namespace render
{
    // forward declaration
    class CContext;
    
    //--------------------------------------------------------------------------
    /**
     * A Settings structure to send with the creation call of a graphics context
     * on an active window.
     * @note fullscreen and windowed can be true at the same time, it will create both;
     * @note setting a size to 0 will not create said buffer.
     */
    struct render_context_settings
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
    
    /**
     * Interface for setting up a rendering pipeline.
     */
    class IRenderPipeline
    {
    public:
        virtual void    Setup(CContext *pContext) = 0;
        virtual void    SetupProjection(CContext *pContext) = 0;
        virtual void    SetupModelView(CContext *pContext) = 0;
        virtual void    Draw(CContext *pContext) = 0;
    };
}

#endif // I_RENDER_H
