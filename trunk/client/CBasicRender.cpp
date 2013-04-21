//
//  CBasicRender.cpp
//  A basic rendering pipeline
//
//  Created by Ryan Sheffer on 2013-04-19.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include "CBasicRender.h"
#include "CClient.h"

//------------------------------------------------------------------------------
/**
 * Setup before drawing
 */
void CBasicRender::Setup(render::CContext *pContext)
{
    pContext->ActivateContext();
    
    pContext->glClearColor(0.4f, 0.0f, 0.0f, 1.0f);
    pContext->glClearDepth(1.0f);
    pContext->glClearStencil(1);
    
    pContext->glEnable(GL_CULL_FACE);
    pContext->glCullFace(GL_BACK);
    
    m_camAng.Init();
    m_camPos.Init();
}

//------------------------------------------------------------------------------
/**
 * Draw
 */
void CBasicRender::Draw(render::CContext *pContext)
{
    pContext->ActivateContext();
    
    SetupProjection(pContext);
    SetupModelView(pContext);
    
    pContext->glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    pContext->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    // Draw stuff!
}

//------------------------------------------------------------------------------
/**
 * Gets a perspective projection matrix from some frustum variables
 * @param out The matrix to setup
 * @param l Left maximum ( along x )
 * @param r Right maximum ( along x )
 * @param b Bottom Maximum ( along y )
 * @param t Top Maximum ( along y )
 * @param n Near ( along Z )
 * @param f Far ( along Z )
 */
void GetPerspectiveProjectionMatrix(matrix4x4 &out, float l, float r, float b, float t, float n, float f)
{
    out.Identity();
    out[0]  = 2.0f * n / (r - l);
    out[5]  = 2.0f * n / (t - b);
    out[8]  = (r + l) / (r - l);
    out[9]  = (t + b) / (t - b);
    out[10] = -(f + n) / (f - n);
    out[11] = -1.0f;
    out[14] = -(2.0f * f * n) / (f - n);
    out[15] = 0.0f;
}

//------------------------------------------------------------------------------
/**
 * Sets up a perspective camera
 */
void CBasicRender::SetupProjection(render::CContext *pContext)
{
	pContext->glMatrixMode(GL_PROJECTION);
    
    unsigned int viewwidth, viewheight;
    pContext->GetViewportSize(viewwidth, viewheight);
    
    const double FOVY = 90.0;
          double ASPECT = viewwidth / viewheight;
    const double NEAR = 1.0;
    const double FAR = 2000.0;
    const double DEG2RAD = M_PI / 180.0;
    
	GLdouble tangent = tan(FOVY / 2.0 * DEG2RAD);	// tangent of half fovY
	GLdouble height = NEAR * tangent;				// half height of near plane
	GLdouble width = height * ASPECT;				// half width of near plane
    
    matrix4x4 Mper;
    GetPerspectiveProjectionMatrix(Mper, -width, width, -height, height, NEAR, FAR);
    pContext->glLoadMatrixf(&Mper[0]);
}

//------------------------------------------------------------------------------
/**
 * Sets up the model view matrix ( the cameras position )
 */
void CBasicRender::SetupModelView(render::CContext *pContext)
{
    pContext->glMatrixMode(GL_MODELVIEW);
    
    // NOTE: The angles and translation are inverted for the camera position
    // to the world.
    matrix4x4 mat_worldView; mat_worldView.Identity();
    
    matrix4x4 rotx, roty, rotz;
    rotx.SetRotationX(-m_camAng.x); // PITCH
    roty.SetRotationY(-m_camAng.y); // YAW
    rotz.SetRotationZ(-m_camAng.z); // ROLL
    
    matrix4x4 temp, temp2;
    MatrixMultiply(rotz, roty, temp); // Z * Y
    MatrixMultiply(temp, rotx, temp2); // (Z * Y) * X
    
    // Translation
    matrix4x4 cam_trans; cam_trans.Identity();
    cam_trans.SetTranslation(-m_camPos.x, -m_camPos.y, -m_camPos.z);
    MatrixMultiply(cam_trans, temp2, mat_worldView);
    
    pContext->glLoadMatrixf(&mat_worldView[0]);
}

