//
//  CCocoaWrapper.m
//  Our cocoa connection
//
//  Created by Ryan Sheffer on 2012-09-30.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#import "CCocoaWrapper.h"
#include "util_perf_timer.h"
#include "IEngine.h"
#include "CEngineState.h"
#include "CPlatform.h"

/** The cocoa application pointer */
CCocoaWrapper           *pCocoaApp;

//------------------------------------------------------------------------------
/**
 * Main Application Thread Class
 */
@interface MainAppThread : NSObject

// The main application loop
+(void)ApplicationLoop:(id)param;

@end

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
@implementation MainAppThread

//------------------------------------------------------------------------------
/**
 * The main engine thread loop
 */
+(void)ApplicationLoop:(id)param
{
    // We create our platform class here and pass it to the engine. Any operating
    // system specific functions should be put in the platform and setup for all
    // platforms in the manner they require.
    CPlatform platform; platform.Initialize();
    
    // This is nessesary for our file structure. We are not using apples APP
    // package and resource folders because it isn't modder friendly. ~RFS
    chdir(platform.GetAbsoluteApplicationPath());
    
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
    
    pEngine->Initialize(&platform);
    
    CEngineState::enginestate = CEngineState::ENGINE_STATE_RUNNING;
    
    while(!pEngine->FinishedExecution())
    {
        if(CEngineState::engineLockReason == CEngineState::ENGINE_LOCK_QUIT)
        {
            break;
        }
        else if(CEngineState::engineLockReason == CEngineState::ENGINE_LOCK_WAIT)
        {
            usleep(1000);
            continue;
        }
        
        //CPerfTimer engine_timer("Engine Run Time", true);
        
        pEngine->Run();
        
        //engine_timer.PrintTimer();
        
        // TODO: Not sure yet, but I might make a rendering frame here
        // [mutex_renderlock lock];
    }
    
    pEngine->Shutdown();
    
    dlclose(pEngineDLL);
    
    CEngineState::enginestate = CEngineState::ENGINE_STATE_CLOSED;
}
@end

@implementation NSAppWindowDelagate

//------------------------------------------------------------------------------
/**
 * Window resized
 */
//- (NSSize)windowWillResize:(NSWindow *)sender toSize:(NSSize)frameSize
//{
//    NSAppWindow *pWindow = (NSAppWindow *)sender;
//    
//    [pWindow UpdateViewport:frameSize];
//    
//    return frameSize;
//}

@end

@implementation NSAppWindow

//------------------------------------------------------------------------------
/**
 * Constructor
 */
- (id)init
{
    self = [super init];
    if (self)
    {
        // superclass successfully initialized, further
        // initialization happens here ...
        m_delagate = [NSAppWindowDelagate alloc];
        [self setDelegate:m_delagate];
    }
    return self;
}

//------------------------------------------------------------------------------
/**
 * Creates a pixel format for fullscreen mode
 */
-(NSOpenGLPixelFormat*)CreateFullScreenPixelFormat:(const render::render_context_settings &) info
{
    NSOpenGLPixelFormatAttribute attribs[] =
	{
		NSOpenGLPFANoRecovery,
		NSOpenGLPFAAccelerated,
		NSOpenGLPFADoubleBuffer,
		NSOpenGLPFAColorSize,
		(NSOpenGLPixelFormatAttribute) info.colorBufferSize,
		NSOpenGLPFADepthSize,
		(NSOpenGLPixelFormatAttribute) info.depthBufferSize,
		NSOpenGLPFAStencilSize,
		(NSOpenGLPixelFormatAttribute) info.stencilBufferSize,
		NSOpenGLPFAAccumSize,
		(NSOpenGLPixelFormatAttribute) info.accumulationBufferSize,
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
/**
 * Creates a pixel format for windowed mode
 */
-(NSOpenGLPixelFormat*)CreateWindowedPixelFormat:(const render::render_context_settings &) info
{
    //setup the window gl context
	NSOpenGLPixelFormatAttribute attribs[] =
	{
		NSOpenGLPFANoRecovery,
		NSOpenGLPFAAccelerated,
		NSOpenGLPFADoubleBuffer,
		NSOpenGLPFAColorSize,
		(NSOpenGLPixelFormatAttribute) info.colorBufferSize,
		NSOpenGLPFADepthSize,
		(NSOpenGLPixelFormatAttribute) info.depthBufferSize,
		NSOpenGLPFAStencilSize,
		(NSOpenGLPixelFormatAttribute) info.stencilBufferSize,
		NSOpenGLPFAAccumSize,
		(NSOpenGLPixelFormatAttribute) info.accumulationBufferSize,
		NSOpenGLPFAWindow,
		(NSOpenGLPixelFormatAttribute) 0,
	};
    
	
	NSOpenGLPixelFormat* fmt = [[NSOpenGLPixelFormat alloc] initWithAttributes: attribs];
	
	if (!fmt)
	{
		NSLog(@"Cannot create NSOpenGLPixelFormat for the windowed context");
		return nil;
	}
    
    return fmt;
}

//------------------------------------------------------------------------------
/**
 * Creates a graphics context for this window
 */
- (Boolean)CreateGraphicsContext:(const render::render_context_settings &) info
{
    ASSERTION(info.fullscreen || info.windowed, "Trying to create context with "
              "neither fullscreen or windowed specified!");
    
    if(info.fullscreen)
    {
        if(m_pFullScreenPixelFmt != nil)
        {
            [m_pFullScreenPixelFmt release];
            m_pFullScreenPixelFmt = nil;
        }
        
        if(m_pCtxFullScreen != nil)
        {
            [m_pCtxFullScreen release];
            m_pCtxFullScreen = nil;
        }
            
        m_pFullScreenPixelFmt = [self CreateFullScreenPixelFormat:info];
        if(m_pFullScreenPixelFmt == nil)
        {
            NSLog(@"Could not create Fullscreen context on window. Bad input settings?");
            return false;
        }
        
        m_pCtxFullScreen = [[NSOpenGLContext alloc] initWithFormat: m_pFullScreenPixelFmt
                                                      shareContext: nil];
        
        if(m_pCtxFullScreen == nil)
        {
            NSLog(@"Could not create Fullscreen GL Context!");
            return false;
        }
    }
    
    if(info.windowed)
    {
        if(m_pWindowedPixelFmt != nil)
        {
            [m_pWindowedPixelFmt release];
            m_pWindowedPixelFmt = nil;
        }
        
        if(m_pCtxWindowed != nil)
        {
            [m_pCtxWindowed release];
            m_pCtxWindowed = nil;
        }
        
        m_pWindowedPixelFmt = [self CreateWindowedPixelFormat:info];
        if(m_pWindowedPixelFmt == nil)
        {
            NSLog(@"Could not create Windowed context on window. Bad input settings?");
            return false;
        }
        
        m_pCtxWindowed = [[NSOpenGLContext alloc] initWithFormat: m_pWindowedPixelFmt
                                                    shareContext: nil]; // m_pCtxFullScreen
        
        if (m_pCtxWindowed == nil)
        {
            NSLog(@"Could not create Windowed GL Context!");
            return false;
        }
    }
    
    // TODO: This doesn't work, figure out why... ~RFS
    if(info.fullscreen && info.defaultFullscreen)
    {
        //displays.Capture(0);
        //displays.SetDisplayMode(0, CGSizeMake( SCREEN_WIDTH, SCREEN_HEIGHT ), 32, 75);
        
        if(m_pGLView != nil)
        {
            [m_pGLView release];
            m_pGLView = nil;
        }
        
        [m_pCtxFullScreen setFullScreen];
        [m_pCtxFullScreen makeCurrentContext];
        
        // TODO: We need proper cursor control.
        //[NSCursor hide];
        
        m_bFullscreen = true;
    }
    else
    {
        if(m_pGLView == nil)
        {
            NSSize myNSWindowSize = [[self contentView]frame].size;
            m_pGLView = [[NSOpenGLView alloc]initWithFrame:NSMakeRect(0,
                                                                      0,
                                                                      myNSWindowSize.width,
                                                                      myNSWindowSize.height)];
            
            ASSERTION(m_pGLView != nil, "Could not create GLView!");
        }
        
        if(info.highResBackingMode)
        {
            [m_pGLView setWantsBestResolutionOpenGLSurface:YES];
            [m_pGLView convertRectToBacking:[m_pGLView bounds]];
        }
        
        [self setContentView: m_pGLView];
        [m_pCtxWindowed setView:m_pGLView];
        [m_pGLView setOpenGLContext:m_pCtxWindowed];
        [m_pGLView setPixelFormat:m_pWindowedPixelFmt];
        
        //[ m_pCtxWindowed copyAttributesFromContext:m_pCtxFullScreen withMask:GL_ALL_ATTRIB_BITS ];
        //[m_pCtxWindowed makeCurrentContext];
        m_bFullscreen = false;
    }

    return true;
}

//------------------------------------------------------------------------------
/**
 * If the resolution changes, this should be called to correct the screen pixels
 */
- (void)DestroyGraphicsContext
{
    if(m_pFullScreenPixelFmt != nil)
    {
        [m_pFullScreenPixelFmt release];
        m_pFullScreenPixelFmt = nil;
    }
    
    if(m_pCtxFullScreen != nil)
    {
        [m_pCtxFullScreen release];
        m_pCtxFullScreen = nil;
    }
    
    if(m_pWindowedPixelFmt != nil)
    {
        [m_pWindowedPixelFmt release];
        m_pWindowedPixelFmt = nil;
    }
    
    if(m_pCtxWindowed != nil)
    {
        [m_pCtxWindowed release];
        m_pCtxWindowed = nil;
    }
    
    if(m_pGLView != nil)
    {
        [m_pGLView release];
        m_pGLView = nil;
    }
}

//------------------------------------------------------------------------------
/**
 * Gets the window size in pixels.
 */
-(void) GetWindowSizePixels:(unsigned int &)width GetHeight:(unsigned int &)height
{
    if(m_pGLView != nil)
    {
        // Get view dimensions in pixels
        NSRect backingBounds = [m_pGLView convertRectToBacking:[m_pGLView bounds]];
        
        width = backingBounds.size.width;
        height = backingBounds.size.height;
    }
    else
    {
        [self GetWindowSize:width GetHeight:height];
    }
}

//------------------------------------------------------------------------------
/**
 * Gets the window size
 */
-(void) GetWindowSize:(unsigned int &)width GetHeight:(unsigned int &)height
{
    NSSize myNSWindowSize = [[self contentView]frame].size;
    
    width = myNSWindowSize.width;
    height = myNSWindowSize.height;
}

//------------------------------------------------------------------------------
/**
 * Activates the graphics context
 */
- (void)ActivateGraphicsContext
{
    if(m_bFullscreen)
    {
        ASSERTION(m_pCtxFullScreen != nil,
                  "ActivateGraphicsContext: Graphics context (m_pCtxFullScreen) is nil!");
        [m_pCtxFullScreen makeCurrentContext];
    }
    else
    {
        ASSERTION(m_pCtxWindowed != nil,
                  "ActivateGraphicsContext: Graphics context (m_pCtxWindowed) is nil!");
        [m_pCtxWindowed makeCurrentContext];
    }
}

//------------------------------------------------------------------------------
/**
 * Presents the fullscreen color buffer to the screen.
 */
- (void)SwapGraphicsContextBuffers
{
    if(m_bFullscreen)
    {
        ASSERTION(m_pCtxFullScreen != nil,
                  "ActivateGraphicsContext: Graphics context (m_pCtxFullScreen) is nil!");
        [m_pCtxFullScreen flushBuffer];
    }
    else
    {
        ASSERTION(m_pCtxWindowed != nil,
                  "ActivateGraphicsContext: Graphics context (m_pCtxWindowed) is nil!");
        [m_pCtxWindowed flushBuffer];
    }
}

//------------------------------------------------------------------------------
/**
 * Keyboard press event from the window
 */
- (void) keyDown: (NSEvent *) event
{
    NSString *chars = [event characters];
    
    for(int i = 0; i < [chars length]; ++i)
    {
        m_keys[[chars characterAtIndex: i]] = true;
    }
}

//------------------------------------------------------------------------------
/**
 * Keyboard up event from the window
 */
- (void) keyUp: (NSEvent *) event
{
    NSString *chars = [event characters];
    
    for(int i = 0; i < [chars length]; ++i)
    {
        m_keys[[chars characterAtIndex: i]] = false;
    }
}

//------------------------------------------------------------------------------
/**
 * Mouse down event from the window
 */
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

//------------------------------------------------------------------------------
/**
 * Mouse up event from the window
 */
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

//------------------------------------------------------------------------------
/**
 * Mouse dragged event from the window
 */
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

//------------------------------------------------------------------------------
/**
 * Get Key state
 */
- (Boolean) GetKeyState: (char) character
{
    return m_keys[character];
}

//------------------------------------------------------------------------------
/**
 * Get Mouse state
 */
- (Boolean) GetMouseState: (Boolean) left
{
    if(left)
        return m_mouseBtns[0];
    else
        return m_mouseBtns[1];
}

@end

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
@implementation CCocoaWrapper

- (NSAppWindow*) m_activeWindow
{
    return m_activeWindow;
}

//------------------------------------------------------------------------------
/**
 * Application finished launching, setup the engine and platform
 */
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
    
    for(int i = 0; i < Foundation::MAX_PLATFORM_WINDOWS; ++i)
    {
        m_windows[i] = NULL;
    }
    
    // Set the application pointer for C++ access
    pCocoaApp = self;
    
    // Create the main gameloop thread
    [NSThread detachNewThreadSelector:@selector(ApplicationLoop:)
                             toTarget:[MainAppThread class] withObject:nil];
}

//------------------------------------------------------------------------------
/**
 * Application is about the terminate, clean up platform specific stuff
 */
- (void)applicationWillTerminate:(NSNotification *)aNotification
{
    // Release any windows
    for(int i = 0; i < Foundation::MAX_PLATFORM_WINDOWS; ++i)
    {
        if(m_windows[i])
        {
            [m_windows[i] release];
            m_windows[i] = NULL;
        }
    }
}

//------------------------------------------------------------------------------
/**
 * On quit button pressed, tell the engine thread to terminate
 */
- (IBAction)QuitButton:(id)sender
{
    while(CEngineState::enginestate != CEngineState::ENGINE_STATE_CLOSED)
    {
        CEngineState::engineLockReason = CEngineState::ENGINE_LOCK_QUIT;
        usleep(1000); // wait awhile
    }
    
    [NSApp terminate:self];
}

//------------------------------------------------------------------------------
/**
 * Creates a new window test
 * @param info Contains information to create the window
 * @return int The index of the window created, or -1 if the window could not be
 * created.
 */
- (int)CreateContentWindow:(const window_info &) info
{
    for(int i = 0; i < Foundation::MAX_PLATFORM_WINDOWS; ++i)
    {
        if(m_windows[i] == NULL)
        {
            NSAppWindow* window = [[NSAppWindow alloc]
                                   initWithContentRect: NSMakeRect(info.x, info.y, info.width, info.height)
                                   styleMask: NSTitledWindowMask | NSMiniaturizableWindowMask | NSResizableWindowMask
                                   backing: NSBackingStoreBuffered
                                   defer: NO];
            
            [window setTitle: @"Genesis Window"];
            [window center];
            [window makeKeyAndOrderFront:self];
            [window setBackgroundColor:[NSColor blackColor]];
            
            m_windows[i] = window;
            return i;
        }
    }
    
    ASSERTION(false, "Tried to create a content window, but ran out of windows!");
    
    return -1;
}

//------------------------------------------------------------------------------
/**
 * Sets the active window
 */
- (void)SetActiveWindow:(int)index
{
    ASSERTION(index >= 0 && index < Foundation::MAX_PLATFORM_WINDOWS,
              "Trying to set active window to a bad index! Not recoverable!");
    
    m_activeWindow = m_windows[index];
}

@end
