//
//  CCocoaWrapper.m
//  Our cocoa connection
//
//  Created by Ryan Sheffer on 2012-09-30.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#import "CCocoaWrapper.h"
#import "render_globals.h"
#include "util_perf_timer.h"
#include "IEngine.h"
#include "CPlatform.h"
#include <dlfcn.h>

enum engine_state
{
    ENGINE_STATE_RUNNING,
    ENGINE_STATE_LOCKED,
    ENGINE_STATE_CLOSED
};

enum engine_lock_reason
{
    ENGINE_UNLOCKED,
    ENGINE_LOCK_WAIT,
    ENGINE_LOCK_QUIT
};

// This is a way for the application to talk with the main loop thread.
// The application can hault the main loop thread for some reason, or use
// this to quit execution of the engine.
engine_lock_reason      engineLockReason = ENGINE_UNLOCKED;
engine_state            enginestate = ENGINE_STATE_CLOSED;

//------------------------------------------------------------------------------
// Main Application Thread Class
//------------------------------------------------------------------------------
@interface MainAppThread : NSObject

// The main application loop
+(void)ApplicationLoop:(id)param;

@end

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
@implementation MainAppThread

//------------------------------------------------------------------------------
// Purpose: The main application thread and loop
//------------------------------------------------------------------------------
+(void)ApplicationLoop:(id)param
{
#ifdef _MAC
    // TODO: Move to platform
    static char szFileLine[2048];
    printf( "working directory: %s\n", getcwd(szFileLine, sizeof(szFileLine)) );
#endif
    
    void *pEngineDLL = dlopen("./bin/libengine.dylib", RTLD_NOW);
    if(pEngineDLL == NULL)
    {
        ASSERTION(pEngineDLL, "Unable to load Engine DLL!");
        return;
    }

    IEngine     *(*__engine)(void);
    *(void **)(&__engine) = dlsym(pEngineDLL, "__CreateEngine");
    
    IEngine *pEngine = NULL;
    if(__engine)
    {
        pEngine = (*__engine)();
    }
    
    if(pEngine == NULL)
    {
        ASSERTION(pEngineDLL, "Engine DLL loaded, but unable to link to __CreateEngine function!");
        return;
    }
    
    // We create our platform class here and pass it to the engine. Any operating
    // system specific functions should be put in the platform and setup for all
    // platforms in the manner they require.
    CPlatform platform; platform.Initialize();
    pEngine->Initialize(&platform);
    
    enginestate = ENGINE_STATE_RUNNING;
    
    while(!pEngine->FinishedExecution())
    {
        if(engineLockReason == ENGINE_LOCK_QUIT)
        {
            break;
        }
        else if(engineLockReason == ENGINE_LOCK_WAIT)
        {
            usleep(1000);
            continue;
        }
        pEngine->Run();
    }
    
    pEngine->Shutdown();
    
    enginestate = ENGINE_STATE_CLOSED;
    
//    if(!g_curContext)
//    {
//        NSLog(@"Trying to create the main game thead, but there is no render context!");
//        return;
//    }
//    
//    if(!g_pOGLRenderContext)
//    {
//        NSLog(@"Game thread started with no Render Control!");
//    }
//    
//    CPerfTimer game_start_timer("Game Start", true);
//    
//    g_pGameInterface = new CGameInterface();
//    g_pGameInterface->Init();
//    
//    game_start_timer.PrintTimer();
//    
//    // Main Loop
//    while(1)
//    {
//        [mutex_renderlock lock];
//        
//        // Important MAC note: Only one thread can use a context at a time,
//        // and to allow a new thread to use the context, it needs to be reset
//        // like I am doing here.
//        [g_curContext makeCurrentContext];
//        
//#ifdef ENABLE_VSYNC
//        //const GLint setVal = 0;
//        //[g_curContext setValues:&setVal forParameter:NSOpenGLCPSwapInterval];
//#endif // ENABLE_VSYNC
//        
//        g_pGameInterface->GameFrame();
//        
//        // Simple Render Control Frame Update
//        if(g_pOGLRenderContext)
//        {
//            g_pOGLRenderContext->FrameUpdate();
//        }
//        
//        // Swap the back buffer with the front buffer
//        [[NSOpenGLContext currentContext] flushBuffer];
//        
//        [mutex_renderlock unlock];
//    }
}
@end

id                      appWindow;

@implementation NSAppWindow
//------------------------------------------------------------------------------
// Purpose: Key Press Event
//------------------------------------------------------------------------------
- (void) keyDown: (NSEvent *) event
{
    NSString *chars = [event characters];
    
    for(int i = 0; i < [chars length]; ++i)
    {
        m_keys[[chars characterAtIndex: i]] = true;
    }
}

//------------------------------------------------------------------------------
// Purpose: Key Up Event
//------------------------------------------------------------------------------
- (void) keyUp: (NSEvent *) event
{
    NSString *chars = [event characters];
    
    for(int i = 0; i < [chars length]; ++i)
    {
        m_keys[[chars characterAtIndex: i]] = false;
    }
}

- (void)mouseDown:(NSEvent *)theEvent
{
    if([theEvent eventNumber] == NSLeftMouseDown)
    {
        m_mouseBtns[0] = true;
    }
    else
    {
        m_mouseBtns[1] = true;
    }
}

- (void)mouseUp:(NSEvent *)theEvent
{
    if([theEvent eventNumber] == NSLeftMouseUp)
    {
        m_mouseBtns[0] = false;
    }
    else
    {
        m_mouseBtns[1] = false;
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
    
//    if(g_pGameInterface)
//    {
//        g_pGameInterface->MouseMoved([theEvent deltaX], [theEvent deltaY]);
//    }
}

- (Boolean) GetKeyState: (char) character
{
    return m_keys[character];
}

- (Boolean) GetMouseState: (Boolean) left
{
    if(left)
        return m_mouseBtns[0];
    else
        return m_mouseBtns[1];
}

@end

namespace PlatformWrapper
{
//------------------------------------------------------------------------------
// Purpose: C functions for access to platform information ( key presses, etc )
//------------------------------------------------------------------------------
bool    GetKeyState(char character)
{
    return [appWindow GetKeyState:character];
}

bool    GetMouseState(bool left)
{
    return [appWindow GetMouseState:left];
}
} // PlatformWrapper

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
@implementation CCocoaWrapper

//------------------------------------------------------------------------------
// Purpose: The window object itself ( creates getters and setters )
// This object gets set by the xib at runtime.
//------------------------------------------------------------------------------
@synthesize genesisWindow;

//------------------------------------------------------------------------------
// Purpose: Sets up a GL context in the cocoa framework
//------------------------------------------------------------------------------
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
//    [self SetupGLContext];
//    
//    // Create the C++ Render Controller
//    g_pOGLRenderContext = new COGLRender;
//    if(g_pOGLRenderContext)
//    {
//        g_pOGLRenderContext->Init();
//    }
//    
//    // Setup global pointer to the current context of this thread.
//    g_curContext = [NSOpenGLContext currentContext];
//    
//#ifdef ENABLE_VSYNC
//    const GLint setVal = 0;
//    [g_curContext setValues:setVal forParameter:NSOpenGLCPSwapInterval];
//#endif // ENABLE_VSYNC
//    
//    // Create a new mutex for rendering calls.
//    mutex_renderlock = [[NSLock alloc] init];
//    
//    [self UpdateViewport];
    
    // Create a new mutex for rendering calls.
    //mutexEngineLock = [[NSLock alloc] init];
    
    appWindow = [genesisWindow self];

    // Create the main gameloop thread
    [NSThread detachNewThreadSelector:@selector(ApplicationLoop:)
                             toTarget:[MainAppThread class] withObject:nil];
}

//------------------------------------------------------------------------------
// Purpose: On quit button pressed, tell the engine thread to terminate
//------------------------------------------------------------------------------
- (IBAction)QuitButton:(id)sender
{
    while(enginestate != ENGINE_STATE_CLOSED)
    {
        engineLockReason = ENGINE_LOCK_QUIT;
        usleep(1000); // wait awhile
    }
    
    [NSApp terminate:self];
}

//------------------------------------------------------------------------------
// Purpose: Creates a pixel format for fullscreen mode
//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
// Purpose: Creates a pixel format for windowed mode
//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
// Purpose: Sets up a GL context in the cocoa framework
//------------------------------------------------------------------------------
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
		
		[ genesisWindow setContentView: m_pGLView ];
		[ m_pCtxWindowed setView:m_pGLView ];
		[ m_pGLView setOpenGLContext:m_pCtxWindowed ];
		
		//[ m_pCtxWindowed copyAttributesFromContext:m_pCtxFullScreen withMask:GL_ALL_ATTRIB_BITS ];
		[ m_pCtxWindowed makeCurrentContext ];
		m_bFullscreen = false;
	}
	
    return true;
}

//------------------------------------------------------------------------------
// Purpose: If the resolution changes, this should be called to correct the
// screen pixels
//------------------------------------------------------------------------------
-(void)UpdateViewport
{
    // Gotta lock the render thread so we can do this.
    // TODO: We should send a message to the render thread asking for a resolution
    // change.
//   [mutex_renderlock lock];
//    
//    [g_curContext makeCurrentContext];
//    
//    // Get view dimensions in pixels
//    NSRect backingBounds = [m_pGLView convertRectToBacking:[m_pGLView bounds]];
//    
//    GLsizei backingPixelWidth  = (GLsizei)(backingBounds.size.width),
//    backingPixelHeight = (GLsizei)(backingBounds.size.height);
//    
//    g_pOGLRenderContext->SetViewport(0, 0, backingPixelWidth, backingPixelHeight);
//    
//    [mutex_renderlock unlock];
}
@end
