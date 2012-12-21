//
//  COGLCocoaWrapper.h
//  render_gl
//
//  Created by Ryan Sheffer on 2012-09-30.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSAppWindow : NSWindow
{
    
}

- (void) keyDown: (NSEvent *) event;
- (void) keyUp: (NSEvent *) event;

@end

@interface COGLCocoaWrapper : NSObject <NSApplicationDelegate>
{
    NSOpenGLPixelFormat* m_pFullScreenPixelFmt;
    NSOpenGLPixelFormat* m_pWindowedPixelFmt;
    
    // GL Context pointers.
	NSOpenGLContext* m_pCtxFullScreen;
	NSOpenGLContext* m_pCtxWindowed;
    
    NSOpenGLView *m_pGLView;
    
    Boolean m_bFullscreen;
}

@property (assign) IBOutlet NSAppWindow *window;

-(NSOpenGLPixelFormat*)CreateFullScreenPixelFormat;
-(NSOpenGLPixelFormat*)CreateWindowedPixelFormat;

// Static Create GL context
-(Boolean)SetupGLContext;

-(void)UpdateViewport;

@end
