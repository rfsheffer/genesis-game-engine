//
//  IPlatform.h
//  Extension for accessing platform information.
//
//  Created by Ryan Sheffer on 2013-01-27.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef IPLATFORM_H
#define IPLATFORM_H

namespace render
{
    struct render_context_settings;
}

/**
 * Interface for the Platform Extension
 */
class IPlatform
{
public:
    
    /**
     * Platform initialization.
     */
    virtual void    Initialize(void) = 0;
    
    /**
     * Platform shutdown.
     */
    virtual void    Shutdown(void) = 0;
    
    /**
     * Gets the state ( true[on] or false[off] of a keyboard key.
     * @param character The key to check.
     */
    virtual bool    GetKeyState(char character) const = 0;
    
    /**
     * Gets the state ( true[on] or false[off] of a mouse button.
     * @param left If true, returns the state of the left mouse button.
     */
    virtual bool    GetMouseState(bool left) const = 0;
    
    /**
     * Creates a new window test
     * @return int The index of the window created, or -1 if the window could not be
     * created.
     */
    virtual hWindow CreateContentWindow(const window_info &info) const = 0;
    
    /**
     * Sets the active window to update
     * @param index The index of the active window. 
     */
    virtual void    SetActiveWindow(hWindow index) const = 0;
    
    /**
     * Gets the size of the active window in pixels
     * @param width Width will be put in this reference variable
     * @param height Height will be put in this reference variable
     */
    virtual void    GetWindowSizePixels(unsigned int &width, unsigned int &height) const = 0;
    
    /**
     * Gets the size of the active windows graphics area
     * @param width Width will be put in this reference variable
     * @param height Height will be put in this reference variable
     */
    virtual void    GetWindowSize(unsigned int &width, unsigned int &height) const = 0;
    
    /**
     * Creates a graphics context on the currently active window.
     */
    virtual bool    CreateGraphicsContext(const render::render_context_settings &settings) const = 0;
    
    /**
     * Shuts down the active graphics context.
     */
    virtual void    ShutdownActiveGraphicsContext(void) const = 0;
    
    /**
     * Activates the graphics context for the currently active window.
     */
    virtual void    ActivateGraphicsContext(void) const = 0;
    
    /**
     * Presents the fullscreen color buffer to the screen.
     */
    virtual void    SwapGraphicsContextBuffers(void) const = 0;
    
    /**
     * Gets the absolute path to the application directory.
     */
    virtual const char *GetAbsoluteApplicationPath(void) const = 0;
};

#endif // IPLATFORM_H
