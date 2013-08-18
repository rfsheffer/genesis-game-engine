//
//  COGLCocoaWrapper.h
//  The Application class
//
//  Created by Ryan Sheffer on 2012-09-30.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

// Objective-C headers go here
#ifdef __OBJC__
#import <Cocoa/Cocoa.h>
#endif

#import <CoreFoundation/CoreFoundation.h>
#import <CoreServices/CoreServices.h>
#import <Foundation/Foundation.h>
#import <AppKit/NSApplication.h>

// Carbon, the low level graphics API for MAC
#include <Carbon/Carbon.h>

// This is so we can see what data is comming in from whatever extension is
// requesting render context manipulation or creation.
#include "IRender.h"

/**
 * Application window delagate. We can add more methods here to see what the
 * user is doing to the window.
 */
@interface NSAppWindowDelagate : NSObject <NSWindowDelegate>
{
    
}

//- (NSSize)windowWillResize:(NSWindow *)sender toSize:(NSSize)frameSize;

@end

//------------------------------------------------------------------------------
/**
 * A window created by the application.
 */
@interface NSAppWindow : NSWindow
{
    /**
     * The name of the window
     */
    NSString *m_pWindowName;
    
    /**
     * Mouse button states
     */
    Boolean m_keys[255];
    Boolean m_mouseBtns[2];
    
    /**
     * Pointers to the pixel format created for the content area of the window
     */
    NSOpenGLPixelFormat* m_pFullScreenPixelFmt;
    NSOpenGLPixelFormat* m_pWindowedPixelFmt;
    
    /**
     * Pointers to OpenGL contexts for the window
     */
	NSOpenGLContext* m_pCtxFullScreen;
	NSOpenGLContext* m_pCtxWindowed;
    
    NSOpenGLView    *m_pGLView;
    
    /**
     * Should this window be fullscreen?
     */
    Boolean m_bFullscreen;
    
    /**
     * The delagate for this window
     */
    NSAppWindowDelagate *m_delagate;
}

- (void) SetWindowName: (NSString *) str;
- (NSString *) GetWindowName;

- (void)CreateGLView;

- (Boolean)CreateGraphicsContext:(const render::render_context_settings &) info;
- (void)DestroyGraphicsContext;
- (void)ActivateGraphicsContext;
- (void)SwapGraphicsContextBuffers;

- (void) keyDown: (NSEvent *) event;
- (void) keyUp: (NSEvent *) event;

- (Boolean) GetKeyState: (char) character;
- (Boolean) GetMouseState: (Boolean) left;

-(void) GetWindowSizePixels:(unsigned int &)width GetHeight:(unsigned int &)height;
-(void) GetWindowSize:(unsigned int &)width GetHeight:(unsigned int &)height;

@end

//------------------------------------------------------------------------------
/**
 * Application wrapper for our cocoa application
 */
@interface CCocoaWrapper : NSObject <NSApplicationDelegate>
{
    /**
     * An array whoes elements may be valid pointers to open windows created
     * by the engine. These get released on application termination, or by
     * request of the engine.
     */
    NSAppWindow *m_windows[Foundation::MAX_PLATFORM_WINDOWS];
    
    /**
     * The active window in the m_windows array
     * @see m_windows
     */
    NSAppWindow *m_activeWindow;
}

- (NSAppWindow *)m_activeWindow;

// Overrides
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification;
- (void)applicationWillTerminate:(NSNotification *)aNotification;

// Methods
- (int)CreateContentWindow: (const window_info &) info;
- (void)SetActiveWindow:(int)index;

-(int)GetWindowHandleByName: (NSString *) str;

- (IBAction)QuitButton:(id)sender;

@end
