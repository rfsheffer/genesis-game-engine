//
//  COGLCocoaWrapper.h
//  Our cocoa connection
//
//  Created by Ryan Sheffer on 2012-09-30.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AppKit/NSApplication.h>

//------------------------------------------------------------------------------
// Main window, we get input from this.
//------------------------------------------------------------------------------
@interface NSAppWindow : NSWindow
{
    Boolean m_keys[255];
    Boolean m_mouseBtns[2];
}

- (void) keyDown: (NSEvent *) event;
- (void) keyUp: (NSEvent *) event;

- (Boolean) GetKeyState: (char) character;

@end

//------------------------------------------------------------------------------
// Main Cocoa Application
//------------------------------------------------------------------------------
@interface CCocoaWrapper : NSObject <NSApplicationDelegate>
{
    NSOpenGLPixelFormat* m_pFullScreenPixelFmt;
    NSOpenGLPixelFormat* m_pWindowedPixelFmt;
    
    // GL Context pointers.
	NSOpenGLContext* m_pCtxFullScreen;
	NSOpenGLContext* m_pCtxWindowed;
    
    NSOpenGLView *m_pGLView;
    
    Boolean m_bFullscreen;
}

@property (assign) IBOutlet NSAppWindow *genesisWindow;

- (IBAction)QuitButton:(id)sender;

-(NSOpenGLPixelFormat*)CreateFullScreenPixelFormat;
-(NSOpenGLPixelFormat*)CreateWindowedPixelFormat;

// Static Create GL context
-(Boolean)SetupGLContext;

-(void)UpdateViewport;

@end
