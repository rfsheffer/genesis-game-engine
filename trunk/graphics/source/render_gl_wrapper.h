//
//  render_gl_wrapper.h
//  Wraps all used GL calls. We are doing this because we will definitely
//  set up the renderer to use multiple cores, and we want to buffer our calls
//  for that.
//
//  Created by Ryan Sheffer on 2013-04-19.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

/*
 NOTES:
 
 We are wrapping all these gl functions so that later on we can buffer
 them up so multiple cores can work on graphics tasks. Then we will offload all
 calls in one go at the end. We will also be able to detect redundant gl calls
 as well. This will be a major peformance gain to any graphics program once it
 is finished.
 
 The only code that should go here are inlined functions for IContext!
 */

inline void glClear (GLbitfield mask)
{
    ::glClear(mask);
}
inline void glClearAccum (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
    ::glClearAccum(red, green, blue, alpha);
}
inline void glClearColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
    ::glClearColor(red, green, blue, alpha);
}
inline void glClearDepth (GLclampd depth)
{
    ::glClearDepth(depth);
}
inline void glClearIndex (GLfloat c)
{
    ::glClearIndex(c);
}
inline void glClearStencil (GLint s)
{
    ::glClearStencil(s);
}
inline void glEnable (GLenum cap)
{
    ::glEnable(cap);
}

inline void glCullFace (GLenum mode)
{
    ::glCullFace(mode);
}

inline void glViewport (GLint x, GLint y, GLsizei width, GLsizei height)
{
    ::glViewport(x, y, width, height);
}

inline void glMatrixMode (GLenum mode)
{
    ::glMatrixMode(mode);
}

inline void glLoadIdentity (void)
{
    ::glLoadIdentity();
}
inline void glLoadMatrixd (const GLdouble *m)
{
    ::glLoadMatrixd(m);
}
inline void glLoadMatrixf (const GLfloat *m)
{
    ::glLoadMatrixf(m);
}

//--------------------------------------------------------------------------
/**
 * Purpose: Sets the vertical sync state
 */
inline bool glSetVerticalSync(bool enable)
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

//--------------------------------------------------------------------------
/**
 * Purpose: Sets the state of the Apple OpenGL threading
 */
inline bool glSetAppleGLThreadedCalls(bool enable)
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