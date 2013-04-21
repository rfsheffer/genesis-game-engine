//
//  CPlatform.cpp
//  Extension for platform control on the MAC.
//
//  Created by Ryan Sheffer on 2013-01-27.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include "CPlatform.h"
#import "CCocoaWrapper.h"

extern CCocoaWrapper           *pCocoaApp;

//------------------------------------------------------------------------------
/**
 * Initialization of the platform. This will happen after the extension
 * manager has been created.
 */
void CPlatform::Initialize(void)
{
    
}

//------------------------------------------------------------------------------
/**
 * Called usually at the end of program execution.
 */
void CPlatform::Shutdown(void)
{
    
}

#define ACTIVE_WINDOW_ASSERT(str)  ASSERTION([pCocoaApp m_activeWindow] != NULL, "Active window is invalid in " str)

//------------------------------------------------------------------------------
/**
 * Gets the state ( true[on] or false[off] of a keyboard key.
 * @param character The key to check.
 */
bool CPlatform::GetKeyState(char character) const
{
    ACTIVE_WINDOW_ASSERT("GetKeyState");
    
    return [[pCocoaApp m_activeWindow] GetKeyState:character];
}

//------------------------------------------------------------------------------
/**
 * Gets the state ( true[on] or false[off] of a mouse button.
 * @param left If true, returns the state of the left mouse button.
 */
bool CPlatform::GetMouseState(bool left) const
{
    ACTIVE_WINDOW_ASSERT("GetMouseState");
    
    return [[pCocoaApp m_activeWindow] GetMouseState:left];
}

//------------------------------------------------------------------------------
/**
 * Creates a content window
 */
hWindow CPlatform::CreateContentWindow(const window_info &info) const
{
    return [pCocoaApp CreateContentWindow: info];
}

//------------------------------------------------------------------------------
/**
 * Sets the active window to update
 * @param index The index of the active window.
 */
void CPlatform::SetActiveWindow(hWindow index) const
{
    [pCocoaApp SetActiveWindow:index];
}

//------------------------------------------------------------------------------
/**
 * Gets the size of the active window in pixels
 * @param width Width will be put in this reference variable
 * @param height Height will be put in this reference variable
 */
void CPlatform::GetWindowSizePixels(unsigned int &width, unsigned int &height) const
{
    ACTIVE_WINDOW_ASSERT("GetWindowSizePixels");
    
    [[pCocoaApp m_activeWindow] GetWindowSizePixels:width GetHeight:height];
}

//------------------------------------------------------------------------------
/**
 * Gets the size of the active windows graphics area
 * @param width Width will be put in this reference variable
 * @param height Height will be put in this reference variable
 */
void CPlatform::GetWindowSize(unsigned int &width, unsigned int &height) const
{
    ACTIVE_WINDOW_ASSERT("GetWindowSize");
    
    [[pCocoaApp m_activeWindow] GetWindowSize:width GetHeight:height];
}

//------------------------------------------------------------------------------
/**
 * Creates a graphics context for the active window with the settings provided.
 * @param settings The settings to create the context with.
 */
bool CPlatform::CreateGraphicsContext(const render::render_context_settings &settings) const
{
    ACTIVE_WINDOW_ASSERT("CreateGraphicsContext");
    
    return [[pCocoaApp m_activeWindow] CreateGraphicsContext:settings];
}

//------------------------------------------------------------------------------
/**
 * Shuts down the active graphics context.
 */
void CPlatform::ShutdownActiveGraphicsContext(void) const
{
    ACTIVE_WINDOW_ASSERT("ShutdownActiveGraphicsContext");
    
    [[pCocoaApp m_activeWindow] DestroyGraphicsContext];
}

//------------------------------------------------------------------------------
/**
 * Activates the graphics context for the current active window.
 */
void CPlatform::ActivateGraphicsContext(void) const
{
    ACTIVE_WINDOW_ASSERT("ActivateGraphicsContext");
    
    return [[pCocoaApp m_activeWindow] ActivateGraphicsContext];
}

//------------------------------------------------------------------------------
/**
 * Presents the fullscreen color buffer to the screen.
 */
void CPlatform::SwapGraphicsContextBuffers(void) const
{
    ACTIVE_WINDOW_ASSERT("ActivateGraphicsContext");
    
    [[pCocoaApp m_activeWindow] SwapGraphicsContextBuffers];
}

//------------------------------------------------------------------------------
/**
 * Gets the absolute path to the application executable.
 */
const char *CPlatform::GetAbsoluteApplicationPath(void) const
{
    static char szFileLine[PATH_MAX];
    static const char *appdir = [[[NSBundle mainBundle] bundlePath] UTF8String];
    strncat(szFileLine, appdir, PATH_MAX);
    
    // Take off the file name
    for(int i = PATH_MAX - 1; i >= 0; --i)
    {
        if(szFileLine[i] == '/')
        {
            break;
        }

        szFileLine[i] = '\0';
    }
    
    return szFileLine;
}