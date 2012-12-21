//
//  COGLCocoaWrapper.m
//  Purpose: This sets up an OGL render context 
//
//  Created by Ryan Sheffer on 2012-09-30.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#import "COGLCocoaWrapper.h"
#import "render_globals.h"
#import "COGLContext.h"
#import "CGameInterface.h"
#include "util_perf_timer.h"

// The Render control, where you make all your draw calls etc...
COGLRender *g_pOGLRenderContext = NULL;

// Game Interface, runs the game
CGameInterface *g_pGameInterface = NULL;

// TODO: This should be put into a render context setup class or something.
// We will want to be able to make more than one render context, and switch
// between them as needed.
NSOpenGLContext* g_curContext;

// TODO: These mutexes should be somewhere else
NSLock *mutex_renderlock;

//------------------------------------------------------------
// Main Game Thread Class
//------------------------------------------------------------
@interface MainGameThread : NSObject

// The main game loop
+(void)GameLoop:(id)param;

@end

//------------------------------------------------------------
//------------------------------------------------------------
@implementation MainGameThread

//------------------------------------------------------------
// Purpose: The main game loop
//------------------------------------------------------------
+(void)GameLoop:(id)param
{
    if(!g_curContext)
    {
        NSLog(@"Trying to create the main game thead, but there is no render context!");
        return;
    }
    
    if(!g_pOGLRenderContext)
    {
        NSLog(@"Game thread started with no Render Control!");
    }
    
    CPerfTimer game_start_timer("Game Start", true);
    
    g_pGameInterface = new CGameInterface();
    g_pGameInterface->Init();
    
    game_start_timer.PrintTimer();
    
    // Main Loop
    while(1)
    {
        [mutex_renderlock lock];
        
        // Important MAC note: Only one thread can use a context at a time,
        // and to allow a new thread to use the context, it needs to be reset
        // like I am doing here.
        [g_curContext makeCurrentContext];
        
#ifdef ENABLE_VSYNC
        //const GLint setVal = 0;
        //[g_curContext setValues:&setVal forParameter:NSOpenGLCPSwapInterval];
#endif // ENABLE_VSYNC
        
        g_pGameInterface->GameFrame();
        
        // Simple Render Control Frame Update
        if(g_pOGLRenderContext)
        {
            g_pOGLRenderContext->FrameUpdate();
        }
        
        // Swap the back buffer with the front buffer
        [[NSOpenGLContext currentContext] flushBuffer];
        
        [mutex_renderlock unlock];
    }
}
@end

@implementation NSAppWindow
//------------------------------------------
// Purpose: Key Press Event
//------------------------------------------
- (void) keyDown: (NSEvent *) event
{
    NSString *chars = [event characters];
    
    for(int i = 0; i < [chars length]; ++i)
    {
        if(g_pGameInterface)
        {
            g_pGameInterface->KeyPressed([chars characterAtIndex: i]);
        }
    }
}

//------------------------------------------
// Purpose: Key Up Event
//------------------------------------------
- (void) keyUp: (NSEvent *) event
{
    NSString *chars = [event characters];
    
    for(int i = 0; i < [chars length]; ++i)
    {
        if(g_pGameInterface)
        {
            g_pGameInterface->KeyReleased([chars characterAtIndex: i]);
        }
    }
}

- (void)mouseDown:(NSEvent *)theEvent
{
    if(g_pGameInterface)
    {
        g_pGameInterface->MousePressed(false);
    }
}

- (void)mouseDragged:(NSEvent *)theEvent
{
    //NSPoint windowOrigin;
    //NSWindow *window = [self window];
    
    // windowOrigin = [window frame].origin;
    
    // [self convertPoint:[theEvent locationInWindow] fromView:nil]
    // [theEvent deltaX] [theEvent deltaY]
    
    //printf("Mouse Pos %f and %f\n", [theEvent deltaX], [theEvent deltaY]);
    
    if(g_pGameInterface)
    {
        g_pGameInterface->MouseMoved([theEvent deltaX], [theEvent deltaY]);
    }
}

- (void)mouseUp:(NSEvent *)theEvent
{
    if(g_pGameInterface)
    {
        g_pGameInterface->MouseReleased(false);
    }
}
@end

//------------------------------------------------------------
//------------------------------------------------------------
@implementation COGLCocoaWrapper

//------------------------------------------------------------
// Purpose: The window object itself ( creates getters and setters )
// This object gets set by the xib at runtime.
//------------------------------------------------------------
@synthesize window;

//------------------------------------------------------------
// Purpose: Sets up a GL context in the cocoa framework
//------------------------------------------------------------
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    [self SetupGLContext];
    
    // Create the C++ Render Controller
    g_pOGLRenderContext = new COGLRender;
    if(g_pOGLRenderContext)
    {
        g_pOGLRenderContext->Init();
    }
    
    // Setup global pointer to the current context of this thread.
    g_curContext = [NSOpenGLContext currentContext];
    
#ifdef ENABLE_VSYNC
    const GLint setVal = 0;
    [g_curContext setValues:setVal forParameter:NSOpenGLCPSwapInterval];
#endif // ENABLE_VSYNC
    
    // Create a new mutex for rendering calls.
    mutex_renderlock = [[NSLock alloc] init];
    
    [self UpdateViewport];
    
    // Create the main gameloop thread
    [NSThread detachNewThreadSelector:@selector(GameLoop:) toTarget:[MainGameThread class] withObject:nil];
}

//------------------------------------------------------------
// Purpose: On Shutdown of cocao window
//------------------------------------------------------------
-(void)applicationWillTerminate:(NSNotification *)notification
{
    // Wait for the renderer to finish, then lock it out so it can't do anymore.
    [mutex_renderlock lock];
    
    // Kill the game
    if(g_pGameInterface)
    {
        g_pGameInterface->Shutdown();
        delete g_pGameInterface;
    }
    
    // Kill the Renderer
    if(g_pOGLRenderContext)
    {
        g_pOGLRenderContext->Shutdown();
        delete g_pOGLRenderContext;
    }
    
    // UNDONE: In this mode, no need to manually release
	//[ m_pCtxWindowed release ];
	//[ m_pCtxFullScreen release ];
}

//------------------------------------------------------------
// Purpose: Creates a pixel format for fullscreen mode
//------------------------------------------------------------
-(NSOpenGLPixelFormat*)CreateFullScreenPixelFormat
{
    NSOpenGLPixelFormatAttribute attribs[] =
	{
		NSOpenGLPFANoRecovery,
		NSOpenGLPFAAccelerated,
		NSOpenGLPFADoubleBuffer,
		NSOpenGLPFAColorSize,
		(NSOpenGLPixelFormatAttribute) COLOR_BUFFER_SIZE,
		NSOpenGLPFADepthSize,
		(NSOpenGLPixelFormatAttribute) DEPTH_BUFFER_SIZE,
		NSOpenGLPFAStencilSize,
		(NSOpenGLPixelFormatAttribute) STENCIL_BUFFER_SIZE,
		NSOpenGLPFAAccumSize,
		(NSOpenGLPixelFormatAttribute) ACCUM_BUFFER_SIZE,
		NSOpenGLPFAFullScreen,
		NSOpenGLPFAScreenMask,
		(NSOpenGLPixelFormatAttribute)CGDisplayIDToOpenGLDisplayMask(kCGDirectMainDisplay),
		(NSOpenGLPixelFormatAttribute) 0
	};
	
	NSOpenGLPixelFormat* fmt = [[NSOpenGLPixelFormat alloc] initWithAttributes: attribs];
	
	if (!fmt)
	{
		NSLog(@"Cannot create NSOpenGLPixelFormat for the fullscreen context");
		return nil;
	}
    
    return fmt;
}

//------------------------------------------------------------
// Purpose: Creates a pixel format for windowed mode
//------------------------------------------------------------
-(NSOpenGLPixelFormat*)CreateWindowedPixelFormat
{
    //setup the window gl context
	NSOpenGLPixelFormatAttribute attribs1[] =
	{
		NSOpenGLPFANoRecovery,
		NSOpenGLPFAAccelerated,
		NSOpenGLPFADoubleBuffer,
		NSOpenGLPFAColorSize,
		(NSOpenGLPixelFormatAttribute) COLOR_BUFFER_SIZE,
		NSOpenGLPFADepthSize,
		(NSOpenGLPixelFormatAttribute) DEPTH_BUFFER_SIZE,
		NSOpenGLPFAStencilSize,
		(NSOpenGLPixelFormatAttribute) STENCIL_BUFFER_SIZE,
		NSOpenGLPFAAccumSize,
		(NSOpenGLPixelFormatAttribute) ACCUM_BUFFER_SIZE,
		NSOpenGLPFAWindow,
		(NSOpenGLPixelFormatAttribute) 0,
	};
    
	
	NSOpenGLPixelFormat* fmt = [[NSOpenGLPixelFormat alloc] initWithAttributes: attribs1];
	
	
	if (!fmt)
	{
		NSLog(@"Cannot create NSOpenGLPixelFormat for the windowed context");
		return nil;
	}
    
    return fmt;
}

//------------------------------------------------------------
// Purpose: Sets up a GL context in the cocoa framework
//------------------------------------------------------------
-(Boolean)SetupGLContext
{
    m_pFullScreenPixelFmt = [self CreateFullScreenPixelFormat];
    if(!m_pFullScreenPixelFmt)
        return false;
	
	m_pCtxFullScreen = [[NSOpenGLContext alloc] initWithFormat: m_pFullScreenPixelFmt
                                                  shareContext: nil];
	
	if (!m_pCtxFullScreen)
	{
		NSLog(@"Could not create Fullscreen GL Context!");
		return false;
	}
	
    m_pWindowedPixelFmt = [self CreateWindowedPixelFormat];
    if(!m_pWindowedPixelFmt)
        return false;
	
	m_pCtxWindowed = [[NSOpenGLContext alloc] initWithFormat: m_pWindowedPixelFmt
                                                shareContext: m_pCtxFullScreen];
	
	if (!m_pCtxWindowed)
	{
		NSLog(@"Could not create Windowed GL Context!");
		return false;
	}
	
	
	if( FULLSCREEN_DEFAULT )
	{
		//displays.Capture(0);
		//displays.SetDisplayMode(0, CGSizeMake( SCREEN_WIDTH, SCREEN_HEIGHT ), 32, 75);
		
		[m_pCtxFullScreen setFullScreen];
		[m_pCtxFullScreen makeCurrentContext];
		[NSCursor hide];
		m_bFullscreen = true;
	}
	else
	{
		m_pGLView = [[NSOpenGLView alloc]
                              initWithFrame:NSMakeRect(0,
                                                       0,
                                                       LOWEST_SCREEN_WIDTH,
                                                       LOWEST_SCREEN_HEIGHT)];
        
        if(HIGH_RES_BACKING_MODE)
        {
            [m_pGLView setWantsBestResolutionOpenGLSurface:YES];
            [m_pGLView convertRectToBacking:[m_pGLView bounds]];
        }
		
		[ window setContentView: m_pGLView ];
		[ m_pCtxWindowed setView:m_pGLView ];
		[ m_pGLView setOpenGLContext:m_pCtxWindowed ];
		
		//[ m_pCtxWindowed copyAttributesFromContext:m_pCtxFullScreen withMask:GL_ALL_ATTRIB_BITS ];
		[ m_pCtxWindowed makeCurrentContext ];
		m_bFullscreen = false;
	}
	
    return true;
}

//------------------------------------------------------------
// Purpose: If the resolution changes, this should be called to correct the
// screen pixels
//------------------------------------------------------------
-(void)UpdateViewport
{
    // Gotta lock the render thread so we can do this.
    // TODO: We should send a message to the render thread asking for a resolution
    // change.
   [mutex_renderlock lock];
    
    [g_curContext makeCurrentContext];
    
    // Get view dimensions in pixels
    NSRect backingBounds = [m_pGLView convertRectToBacking:[m_pGLView bounds]];
    
    GLsizei backingPixelWidth  = (GLsizei)(backingBounds.size.width),
    backingPixelHeight = (GLsizei)(backingBounds.size.height);
    
    g_pOGLRenderContext->SetViewport(0, 0, backingPixelWidth, backingPixelHeight);
    
    [mutex_renderlock unlock];
}

@end
