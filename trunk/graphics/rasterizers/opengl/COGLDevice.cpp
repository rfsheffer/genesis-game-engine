//
//  COGLDevice.cpp
//  Methods specifically for changing the OpenGL device state
//
//  Created by Ryan Sheffer on 2012-12-09.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#include "COGLContext.h"

//------------------------------------------------------------------------------
// Purpose: Sets the vertical sync state
//------------------------------------------------------------------------------
bool COGLRender::SetVerticalSync(bool enable)
{
#ifdef _MAC
    CGLError err = kCGLNoError;
    CGLContextObj ctx = CGLGetCurrentContext();
    
    GLint setting = enable?1:0;
    
    // Enable the multithreading
    err = CGLSetParameter(ctx, kCGLCPSwapInterval, &setting);
    
    return (err == kCGLNoError);
#else
    return false;
#endif
}

//------------------------------------------------------------------------------
// Purpose: Sets the state of the Apple OpenGL threading
//------------------------------------------------------------------------------
bool COGLRender::SetAppleGLThreadedCalls(bool enable)
{
#ifdef _MAC
    CGLError err = kCGLNoError;
    CGLContextObj ctx = CGLGetCurrentContext();
    
    // Enable the multithreading
    if(enable)
        err = CGLEnable(ctx, kCGLCEMPEngine);
    else
        err = CGLDisable(ctx, kCGLCEMPEngine);
    
    return (err == kCGLNoError);
#else
    return false;
#endif
}