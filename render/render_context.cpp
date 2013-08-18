//
//  render_context.cpp
//  All generic rendering functionality falls under the render namespace.
//
//  Created by Ryan Sheffer on 2013-04-19.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include "render_context.h"

// Includes for getting lower level access
#include "CClient.h"

namespace render
{
    //--------------------------------------------------------------------------
    /**
     * Initializes the render context with input settings and window index
     * @param windowHandle The handle of the window we want to initialize with a context
     * @param settings The settings to create the context with
     */
    bool CContext::InitializeContext(hWindow windowHandle,
                                     const render_context_settings &settings)
    {
        m_settings = settings;
        
        IPlatform *pPlatform = GetPlatform();
        pPlatform->SetActiveWindow(windowHandle);
        m_windowHandle = windowHandle;
        
        bool created = true; //pPlatform->CreateGraphicsContext(settings);
        
        if(created)
        {
            SettingsChanged();
            RefreshContext();
        }
        
        ASSERTION(created, "CContext::InitializeContext Could not create graphics context!");
        return created;
    }
    
    //--------------------------------------------------------------------------
    /**
     * Activates this context for usage.
     */
    void CContext::ActivateContext(void)
    {
        IPlatform *pPlatform = GetPlatform();
        pPlatform->SetActiveWindow(m_windowHandle);
        pPlatform->ActivateGraphicsContext();
    }
    
    //--------------------------------------------------------------------------
    /**
     * Called when graphics settings have been changed and the GL states need to
     * be updated.
     */
    void CContext::SettingsChanged(void)
    {
        ActivateContext();
        
#ifdef _MAC
        if(m_settings.multiThreadServer)
        {
            ASSERTION(glSetAppleGLThreadedCalls(true),
                      "Could not enable Apple GL Threaded Calls!");
        }
        else
        {
            ASSERTION(glSetAppleGLThreadedCalls(false),
                      "Could not enable Apple GL Threaded Calls!");
        }
#endif
        
        if(m_settings.vsync)
        {
            ASSERTION(glSetVerticalSync(true),
                      "Could not enable Vertical Sync");
        }
        else
        {
            ASSERTION(glSetVerticalSync(false),
                      "Could not disable Vertical Sync");
        }
    }
    
    //--------------------------------------------------------------------------
    /**
     * Refreshes the context information, resyncs the context with the platform.
     * @note This should be called before drawing with the context. It ensures
     * that the viewport is the correct size, and may do some other useful pre
     * checks as well.
     */
    void CContext::RefreshContext(void)
    {
        ActivateContext();
        
        unsigned int pixWidth, pixHeight;
        GetPlatform()->GetWindowSizePixels(pixWidth, pixHeight);
        
        if(pixWidth != m_uiWidthPixels || pixHeight != m_uiHeightPixels)
        {
            m_uiWidthPixels = pixWidth;
            m_uiHeightPixels = pixHeight;
            
            glViewport(0, 0, m_uiWidthPixels, m_uiHeightPixels);
            
            // The viewport itself probably resized too, just update it
            GetPlatform()->GetWindowSize(pixWidth, pixHeight);
            m_uiViewportWidth = pixWidth;
            m_uiViewportHeight = pixHeight;
        }
    }
    
    //--------------------------------------------------------------------------
    /**
     * Presents the fullscreen color buffer to the screen.
     * ( Swaps the back buffer with the front buffer )
     * Note: This should only be called lastly.
     */
    void CContext::SwapBuffers(void)
    {
        ActivateContext();
        GetPlatform()->SwapGraphicsContextBuffers();
    }
    
    //--------------------------------------------------------------------------
    /**
     * Sets up a render context settings structure with safe default settings.
     * @param settings The settings to be defaulted.
     */
    void GetDefaultRenderSettings(render_context_settings &settings)
    {
        settings.windowed = true;
        settings.fullscreen = false;
        
        settings.colorBufferSize = 32;
        settings.depthBufferSize = 8;
        settings.stencilBufferSize = 8;
        settings.accumulationBufferSize = 0;
        
        settings.defaultFullscreen = false;
        
        // TODO: Need to figure out if high res is supported before turning this on.
        settings.highResBackingMode = true;
        
        settings.vsync = true;
#ifdef _MAC
        settings.multiThreadServer = true;
#else
        settings.multiThreadServer = false;
#endif
    }
}