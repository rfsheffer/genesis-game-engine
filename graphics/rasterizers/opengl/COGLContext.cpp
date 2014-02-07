//
//  COGLContext.cpp
//  genesis
//
//  Created by Ryan Sheffer on 2012-12-09.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#include "COGLContext.h"
#include "camera.h"

// TEMP: Global camera for testing
CCamera g_camera;

//------------------------------------------------------------------------------
// Purpose: Initialization of the graphics device
//------------------------------------------------------------------------------
void COGLRender::Init(void)
{
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
	glClearDepth(1.0f);
    glClearStencil(1);
    
    glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
  
    // This isn't on by default, so we can always assume we are trying to turn
    // it on.
    if(ENABLE_MACGL_MULTI_THREAD)
    {
        ASSERTION(SetAppleGLThreadedCalls(true), "Could not enable Apple GL Threaded Calls!");
    }
    
    if(ENABLE_VSYNC)
    {
        ASSERTION(SetVerticalSync(true), "Could not enable Vertical Sync");
    }
    else
    {
        ASSERTION(SetVerticalSync(false), "Could not disable Vertical Sync");
    }
    
    // Initial camera pos
	g_camera.m_pos.Init(0.0f, 0.0f, 0.0f);
	g_camera.m_ang.Init(0.0f, 0.0f, 0.0f);
    
    CreateWorldBox();
    
    CreateAxesLines();
}

//------------------------------------------------------------------------------
// Purpose: Initialization of the graphics device
//------------------------------------------------------------------------------
void COGLRender::FrameUpdate(void)
{
    // Setup the projection frustum
    SetupProjection();
    
    // Setup the model view matrix
    SetupModelView();
    
    // Clear all the buffers
    // TODO: Call this function sparingly. Profiling it shows it is pretty slow.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    for(int i = 0; i < 6; ++i)
    {
        // Draw the world box
        DrawMeshGL(m_WorldBox[i], Vector3(0, 200, 0));
    }
    
    // Draw Axes
    DrawMeshGL(m_XAxis, Vector3Origin);
    DrawMeshGL(m_YAxis, Vector3Origin);
    DrawMeshGL(m_ZAxis, Vector3Origin);
}