//
//  CCocoaWrapper.m
//  Our cocoa connection
//
//  Created by Ryan Sheffer on 2012-09-30.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#import "CCocoaWrapper.h"
#include "CPlatform.h"

// Engine
#include "IEngine.h"

// Utilities lib
#include "util_perf_timer.h"
#include "keyvalues.h"
#include "memory_interface.h"

// Graphics Lib
#include "contextinfo.h"

/** The cocoa application pointer */
CCocoaWrapper           *pCocoaApp;

/** Engine Lockout Mutex */
NSLock                  *mutexEngineLock;

/** Engine States */
enum engine_state_e
{
    ENGINE_STATE_INACTIVE,
    ENGINE_STATE_ACTIVE,
    ENGINE_STATE_CLOSING,
};

/** The State the engine is currently in.
 * NOTE: Only change this state if you have an engine mutex lock */
engine_state_e engineState = ENGINE_STATE_INACTIVE;

//------------------------------------------------------------------------------
/**
 * Main Application Thread Class
 */
@interface MainAppThread : NSObject

// The main application loop
+(void)ApplicationLoop:(id)param;

@end

/** This is the pointer to the MAC specific platform interface */
static CPlatform g_platform;
IPlatform *GetPlatform(void)
{
    return &g_platform;
}

/** The platform is registered early on so all systems can access it */
REGISTER_STATIC_INTERFACE(g_platform,
                          PLATFORM_INTERFACE_NAME,
                          PLATFORM_INTERFACE_VERSION);

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
@implementation MainAppThread

//------------------------------------------------------------------------------
/**
 * Main Loop Thread, runs the engine
 */
+(void)ApplicationLoop:(id)param
{
    // This is nessesary for our file structure. We are not using apples APP
    // package and resource folders because it isn't modder friendly. ~RFS
    chdir(GetPlatform()->GetAbsoluteApplicationPath());
    Logging::Msg("Setting Application Path to %s\n", GetPlatform()->GetAbsoluteApplicationPath());
    
    void *pEngineDLL = dlopen("engine.dylib", RTLD_NOW);
    if(pEngineDLL == NULL)
    {
        ASSERTION(pEngineDLL, "Unable to load Engine DLL!");
        return;
    }
    
    IEngine *pEngine = static_cast<IEngine *>
            (GetInterfaceRegistration()->GetInterface(ENGINE_INTERFACE_NAME,
                                                      ENGINE_INTERFACE_VERSION));
    
    if(pEngine == NULL)
    {
        ASSERTION(pEngineDLL, "Engine DLL loaded, but unable to create an interface to it!");
        return;
    }
    
    pEngine->Initialize();
    
    while(true)
    {
        [mutexEngineLock lock];
        
        if(engineState == ENGINE_STATE_CLOSING || pEngine->FinishedExecution())
        {
            break;
        }
        else
        {
            engineState = ENGINE_STATE_ACTIVE;
            
            //CPerfTimer engine_timer("Engine Run Time", true);
            pEngine->Run();
            //engine_timer.PrintTimer();
        }
        
        [mutexEngineLock unlock];
    }
    
    pEngine->Shutdown();
    
    // Now release the interface pointer
    GetInterfaceRegistration()->ReleaseInterfacePointer(ENGINE_INTERFACE_NAME, pEngine);
    
    // Release any un-released interfaces (they will be reported)
    GetInterfaceRegistration()->ReleaseAllInterfacePointers();
    
    dlclose(pEngineDLL);
    
    engineState = ENGINE_STATE_INACTIVE;
    
    [mutexEngineLock unlock];
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
-(NSOpenGLPixelFormat*)CreateFullScreenPixelFormat:(const graphics::context_info &) info
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
-(NSOpenGLPixelFormat*)CreateWindowedPixelFormat:(const graphics::context_info &) info
{
    //setup the window gl context
	NSOpenGLPixelFormatAttribute attribs[] =
	{
		NSOpenGLPFANoRecovery,
		NSOpenGLPFAAccelerated,
		NSOpenGLPFADoubleBuffer,
        NSOpenGLPFAWindow,
		NSOpenGLPFAColorSize,
		(NSOpenGLPixelFormatAttribute) info.colorBufferSize,
		NSOpenGLPFADepthSize,
		(NSOpenGLPixelFormatAttribute) info.depthBufferSize,
		NSOpenGLPFAStencilSize,
		(NSOpenGLPixelFormatAttribute) info.stencilBufferSize,
		NSOpenGLPFAAccumSize,
		(NSOpenGLPixelFormatAttribute) info.accumulationBufferSize,
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
- (Boolean)CreateGraphicsContext:(const graphics::context_info &) info
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
        //[m_pCtxFullScreen makeCurrentContext];
        
        // TODO: We need proper cursor control.
        //[NSCursor hide];
        
        m_bFullscreen = true;
    }
    else
    {        
        if(info.highResBackingMode)
        {
            [m_pGLView setWantsBestResolutionOpenGLSurface:YES];
            [m_pGLView convertRectToBacking:[m_pGLView bounds]];
        }
        
        //[self setContentView: m_pGLView];
        [m_pCtxWindowed setView:m_pGLView];
        [m_pGLView setOpenGLContext:m_pCtxWindowed];
        [m_pGLView setPixelFormat:m_pWindowedPixelFmt];
        
        //[ m_pCtxWindowed copyAttributesFromContext:m_pCtxFullScreen withMask:GL_ALL_ATTRIB_BITS ];
        //[m_pCtxWindowed makeCurrentContext];
        m_bFullscreen = false;
    }
    
    [NSOpenGLContext clearCurrentContext];

    return true;
}

//------------------------------------------------------------------------------
/**
 * Sets the name of the window.
 */
-(void) SetWindowName: (NSString *) str
{    
    m_pWindowName = str;
}

- (NSString *) GetWindowName
{
    return m_pWindowName;
}

//------------------------------------------------------------------------------
/**
 * Creates the GL view for the window.
 */
- (void)CreateGLView
{
    ASSERTION(m_pGLView == nil, "GLView already created for this window!");
    
    if(m_pGLView == nil)
    {
        NSSize myNSWindowSize = [[self contentView]frame].size;
        m_pGLView = [[NSOpenGLView alloc]initWithFrame:NSMakeRect(0,
                                                                  0,
                                                                  myNSWindowSize.width,
                                                                  myNSWindowSize.height)];
        
        ASSERTION(m_pGLView != nil, "Could not create GLView!");
        
        [self setContentView: m_pGLView];
    }
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
        
        //CGLLockContext((CGLContextObj)[m_pCtxWindowed CGLContextObj]);
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
    // Create a new mutex for engine locking so we can hault the engine if
    // needed.
    mutexEngineLock = [[NSLock alloc] init];
    
    // Initialize the memory pool for the application.
    // All systems designed around the engine use the memory pool for all
    // allocations. This is done to help with fragmentation, but most of all, it
    // is done to ensure all allocations are accounted for, and in debug situations,
    // allows the developer to understand exactly what is allocated at any one
    // time, and what is not being de-allocated when it should.
    GetMemoryPool()->Initialize();
    
    // We create our platform class here and pass it to the engine. Any operating
    // system specific functions should be put in the platform and setup for all
    // platforms in the manner they require.
    g_platform.Initialize();
    
    for(int i = 0; i < Foundation::MAX_PLATFORM_WINDOWS; ++i)
    {
        m_windows[i] = NULL;
    }
    
    // Set the application pointer for C++ access
    pCocoaApp = self;
    
    // Create Application Windows
    Utility::Keyvalues kvRoot;
    
    FileHandle fileref = GetPlatform()->FileOpen("./configuration/windows.kv", FILE_READ_BINARY);
    if(!fileref || !kvRoot.PopulateWithFile(fileref, "windows.kv"))
    {
        ASSERTION(fileref, "Could not open windows.kv, no application windows were created!");
        Logging::Error("Unable to load windows file");
        return;
    }
    
    Utility::Keyvalues *pkvWindows = kvRoot.GetKey("windows");
    if(!pkvWindows)
    {
        Logging::Error("Invalid windows file");
        return;
    }
    
    for(const Utility::Keyvalues *pCurKey = pkvWindows->GetFirstChild();
                        pCurKey != NULL; pCurKey = pCurKey->GetNextChild())
    {
        // Should always have children...
        if(pCurKey->HasChildren())
        {
            window_info info;
            
            info.width = pCurKey->GetInt("min_width", 0);
            info.height = pCurKey->GetInt("min_height", 0);
            info.x = pCurKey->GetInt("pos_x", 0);
            info.y = pCurKey->GetInt("pos_y", 0);
            info.centered = pCurKey->GetInt("centered", 0);
            info.maxWidth = pCurKey->GetInt("max_width", 0);
            info.maxHeight = pCurKey->GetInt("max_height", 0);
            info.windowTitle = pCurKey->GetName();
            
            // Create the actual window
            int wind = [self CreateContentWindow:info];
            [self SetActiveWindow:wind];
            
            // Create the rendering context
            graphics::context_info settings;
            
            settings.windowed = true;
            settings.fullscreen = false;
            
            settings.colorBufferSize = pCurKey->GetInt("color_buffer_size", 0);
            settings.depthBufferSize = pCurKey->GetInt("depth_buffer_size", 0);
            settings.stencilBufferSize = pCurKey->GetInt("stencil_buffer_size", 0);
            settings.accumulationBufferSize = pCurKey->GetInt("accum_buffer_size", 0);
            
            settings.defaultFullscreen = false;
            
            settings.vsync = true;
#ifdef _MAC
            settings.multiThreadServer = true;
            // TODO: Need to figure out if high res is supported before turning this on.
            settings.highResBackingMode = true;
#else
            settings.multiThreadServer = false;
            settings.highResBackingMode = false;
#endif
            if(settings.colorBufferSize != 0)
            {
                [[self m_activeWindow] CreateGraphicsContext:settings];
            }
        }
    }

    [[self m_activeWindow] ActivateGraphicsContext];
    
    unsigned int width, height;
    [m_activeWindow GetWindowSize:width GetHeight:height];
    
#ifdef ENABLE_VSYNC
    const GLint setVal = 0;
    [g_curContext setValues:setVal forParameter:NSOpenGLCPSwapInterval];
#endif // ENABLE_VSYNC
    
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
    [mutexEngineLock lock];

    // No engine running? Just quit now.
    if(engineState == ENGINE_STATE_INACTIVE)
    {
        [mutexEngineLock unlock];
        [NSApp terminate:self];
        return;
    }
    
    engineState = ENGINE_STATE_CLOSING;
    [mutexEngineLock unlock];
    
    // Wait a bit for the engine, it might finish before we check again.
    usleep(1000);
    
    // Wait for the engine to be properly shutdown
    while(true)
    {
        [mutexEngineLock lock];
        
        // Is the engine shutoff yet?
        if(engineState == ENGINE_STATE_INACTIVE)
        {
            [mutexEngineLock unlock];
            break;
        }
        
        [mutexEngineLock unlock];
        usleep(1000); // Wait before trying again
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
            
            if(info.windowTitle != NULL)
            {
                NSString *windowString = [NSString stringWithUTF8String:info.windowTitle];
                
                [window SetWindowName:windowString];
                [window setTitle: windowString];
            }
            else
            {
                [window setTitle: @"untitled"];
                [window SetWindowName:@"untitled"];
            }
            
            

            if(info.centered)
            {
                [window center];
            }
            
            NSSize maxSize;
            maxSize.width = info.maxWidth;
            maxSize.height = info.maxHeight;
            
            if(maxSize.width != 0 && maxSize.height != 0)
            {
                [m_activeWindow setMaxSize:maxSize];
            }
            
            [window makeKeyAndOrderFront:nil];
            [window setBackgroundColor:[NSColor blackColor]];
            [window CreateGLView];
            
            m_windows[i] = window;
            return i;
        }
    }
    
    ASSERTION(false, "Tried to create a content window, but ran out of windows!");
    
    return -1;
}

-(int)GetWindowHandleByName: (NSString *) str
{
    for(int i = 0; i < Foundation::MAX_PLATFORM_WINDOWS; ++i)
    {
        if(m_windows[i] != NULL)
        {
            if([str compare:[m_windows[i] GetWindowName]] == NSOrderedSame)
            {
                return i;
            }
        }
    }
    
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
