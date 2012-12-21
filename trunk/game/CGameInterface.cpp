//
//  gameinterface.cpp
//  Purpose: This is where the game is controlled. Everything starts and ends
//  here for the game.
//
//  Created by Ryan Sheffer on 2012-10-27.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#include "CGameInterface.h"
#include "COGLContext.h"
#include "file_smd.h"
#include "util_time.h"

using namespace FileTypes;

static CTime        s_gameTime;

// TODO: Going to setup a cleaner way for systems to talk
extern COGLRender *g_pOGLRenderContext;

// TEMP
static Vector3 camPos;
static Angle camAng;

//------------------------------------------------------------------------------
// Purpose: Initializes the main game
//------------------------------------------------------------------------------
void CGameInterface::Init(void)
{
    // Initilize the game timer
    s_gameTime.Init();
    
    // Load up some vertex data to test with
    //CSMDFile smd;
    
    //smd.ParseSMD("genesis.app/Contents/Resources/zenlil_ext_ref.SMD");
    
    camPos.Init(0, 0, 0);
    camAng.Init(0, 0, 0);
    
    m_MouseXDelta = 0;
    m_MouseYDelta = 0;
}

//------------------------------------------------------------------------------
// Purpose: Called when the game should shutdown.
//------------------------------------------------------------------------------
void CGameInterface::Shutdown(void)
{
    
}

#define MAX_CAMERA_SPEED        100 // 40 units / second

//------------------------------------------------------------------------------
// Purpose: Called per game frame
//------------------------------------------------------------------------------
void CGameInterface::GameFrame(void)
{
    // Update the timer so we have valid elapsed time for deltas and such
    s_gameTime.Update();
    
    // Get the delta time in seconds. All our movement is (distance)/(second)
    double delta = ConvertToSeconds(s_gameTime.GetPerfElapsedTime());
    
    /*unsigned int screenWidth;
    unsigned int screenHeight;
    
    if(g_pOGLRenderContext)
    {
        screenWidth = g_pOGLRenderContext->GetWidth();
        screenHeight = g_pOGLRenderContext->GetHeight();
    }
    else
    {
        screenWidth = 800;
        screenHeight = 600;
    }*/
    
    // Set the pitch and yaw
    // Note: Flipping here to convert screen vectors to angles
    // HACK: * 3 is for speed. Once we throttle the game frame rate to the
    // graphics frame rate, this will no longer be a problem.
    camAng[PITCH] -= m_MouseYDelta * delta * 4;
    camAng[YAW] -= m_MouseXDelta * delta * 4;
    
    // Reset the mouse movement deltas
    m_MouseXDelta = m_MouseYDelta = 0;
    
    // Clamp the camera pitch so we can't roll over
    if(camAng[PITCH] > (M_PI / 2))
    {
        camAng[PITCH] = (M_PI / 2);
    }
    else if(camAng[PITCH] < -(M_PI / 2))
    {
        camAng[PITCH] = -(M_PI / 2);
    }
    
    // Fix the YAW
    if(camAng[YAW] > M_PI)
    {
        camAng[YAW] -= (M_PI * 2);
    }
    else if(camAng[YAW] < -M_PI)
    {
        camAng[YAW] += (M_PI * 2);
    }
    
    
    Vector3 left, up, forward;
    
    // TODO: Figure this out, it should work!
    /*matrix4x4 mat_worldView; mat_worldView.Identity();
    
    matrix4x4 rotx, roty, rotz;
    rotx.SetRotationX(camAng.x); // PITCH
    roty.SetRotationY(camAng.y); // YAW
    rotz.SetRotationZ(camAng.z); // ROLL
    
    matrix4x4 temp;
    MatrixMultiply(rotz, roty, temp); // Z * Y
    MatrixMultiply(temp, rotx, mat_worldView); // (Z * Y) * X
    
    mat_worldView.GetBasisVectors(left, up, forward);*/
    
    forward.Init((cos(camAng[PITCH]) * sin(camAng[YAW])),
                 -sin(camAng[PITCH]),
                 (cos(camAng[PITCH]) * cos(camAng[YAW])));
    
    left.Init(sin(camAng[YAW] + 3.14f/2.0f),
              0,
              cos(camAng[YAW] + 3.14f/2.0f));
    
    CrossProduct(left, forward, up);
    
    //printf("forward %f, %f, %f\n", forward.x, forward.y, forward.z);
    
    // Strafing
    if(GetKeyState('a'))
    {
        Vector3Multiply(left, -(MAX_CAMERA_SPEED * delta), left);
    }
    else if(GetKeyState('d'))
    {
        Vector3Multiply(left, (MAX_CAMERA_SPEED * delta), left);
    }
    else
    {
        left.Zero();
    }
    
    // Forward backward
    if(GetKeyState('w'))
    {
        Vector3Multiply(forward, -(MAX_CAMERA_SPEED * delta), forward);
    }
    else if(GetKeyState('s'))
    {
        Vector3Multiply(forward, (MAX_CAMERA_SPEED * delta), forward);
    }
    else
    {
        forward.Zero();
    }
    
    camPos += forward;
    camPos += left;
    
    // Update the view
    if(g_pOGLRenderContext)
    {
        g_pOGLRenderContext->SetCamera(camPos, camAng);
    }
    
    //printf("Camera Pos: X %f, Y %f, Z %f\nCamera Rot: PITCH %f, YAW %f, ROLL %f\n",
    //       camPos.x, camPos.y, camPos.z, RAD2DEG(camAng.x), RAD2DEG(camAng.y), RAD2DEG(camAng.z));
}

//------------------------------------------------------------------------------
// Purpose: Called when a key is pressed
//------------------------------------------------------------------------------
void CGameInterface::KeyPressed(char character)
{
    if(character >= 255)
        return;
    
    m_keys[character] = true;
}

//------------------------------------------------------------------------------
// Purpose: Called when a key is released
//------------------------------------------------------------------------------
void CGameInterface::KeyReleased(char character)
{
    if(character >= 255)
        return;
    
    m_keys[character] = false;
}

//------------------------------------------------------------------------------
// Purpose: Gets the state of a key
//------------------------------------------------------------------------------
bool CGameInterface::GetKeyState(char character) const
{
    if(character >= 255)
        return false;
    
    return m_keys[character];
}

//------------------------------------------------------------------------------
// Purpose: Mouse Pressed Event
//------------------------------------------------------------------------------
void CGameInterface::MousePressed(bool right)
{
    
}

//------------------------------------------------------------------------------
// Purpose: Mouse Released Event
//------------------------------------------------------------------------------
void CGameInterface::MouseReleased(bool right)
{
    
}

//------------------------------------------------------------------------------
// Purpose: Accumulates the current mouse movement for view control
//------------------------------------------------------------------------------
void CGameInterface::MouseMoved(float deltaX, float deltaY)
{
    m_MouseXDelta += deltaX;
    m_MouseYDelta += deltaY;
}