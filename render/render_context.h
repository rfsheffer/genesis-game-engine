//
//  render_context.h
//  All generic rendering functionality falls under the render namespace.
//
//  Created by Ryan Sheffer on 2013-04-18.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef RENDER_CONTEXT_H
#define RENDER_CONTEXT_H

#include "IRender.h"

/** Render Namespace */
namespace render
{
    //--------------------------------------------------------------------------
    /**
     * A render context
     */
    class CContext
    {
    public:
        /** Constructor */
        CContext()
        {
            // Slow memset, but it fits well here, and this happens rarely. ~RFS
            memset(&m_settings, 0, sizeof(render_context_settings));
        }

        bool InitializeContext(hWindow iWindowIndex, const render_context_settings &settings);
        void ActivateContext(void);
        void SettingsChanged(void);
        void RefreshContext(void);
        void SwapBuffers(void);
        
        // Includes all GL wrapped functions inline.
        #include "render_gl_wrapper.h"
        
        /**
         * Sets the viewport size and position for this context
         */
        void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
        {
            m_uiWidthPixels = width;
            m_uiHeightPixels = height;
            
            glViewport(x, y, width, height);
        }
        
        /**
         * Gets the size of the viewport
         */
        void GetViewportSize(unsigned int &width, unsigned int &height) const
        {
            width = m_uiViewportWidth;
            height = m_uiViewportHeight;
        }
        
        /**
         * Gets the size of the viewport in pixels.
         * @note This is usually the same as the viewport size, unless high
         * resolution mode is active on the context, which might double the
         * size of the screen in pixels to account for the doubled screen pixel
         * count. ( High Resolution Monitor )
         */
        void GetViewportSizePixels(unsigned int &width, unsigned int &height) const
        {
            width = m_uiWidthPixels;
            height = m_uiHeightPixels;
        }
        
    private:
        
        /** The width of the context in pixels */
        unsigned int m_uiWidthPixels;
        
        /** The height of the context in pixels */
        unsigned int m_uiHeightPixels;
        
        /** The width of the viewport */
        unsigned int m_uiViewportWidth;
        
        /** The height of the viewport */
        unsigned int m_uiViewportHeight;
        
        /** The window handle for this context */
        hWindow     m_windowHandle;

        /** The settings for this context */
        render_context_settings m_settings;
    };
    
    void GetDefaultRenderSettings(render_context_settings &settings);
}

#endif // RENDER_CONTEXT_H
