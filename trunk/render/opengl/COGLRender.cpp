//
//  COGLRender.cpp
//  Methods for dealing specifically for the rendering of objects using OpenGL
//
//  Created by Ryan Sheffer on 2012-09-30.
//  Copyright (c) 2012 Ryanware. All rights reserved.
//
//  TODO: Manage OGL states instead of using glPushAttrib. glPushAttrib is very slow.

#include "COGLContext.h"
#include "type_mesh.h"
#include "camera.h"

extern CCamera g_camera;

//------------------------------------------------------------------------------
// Purpose: Initialization of the graphics device
//------------------------------------------------------------------------------
void COGLRender::SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{
    m_uiWidthPixels = width;
    m_uiHeightPixels = height;
    
    glViewport(x, y, width, height);
}

//------------------------------------------------------------------------------
// Purpose: Sets up a frustum for OpenGL
//------------------------------------------------------------------------------
void FrustumGL(float l, float r, float b, float t, float n, float f)
{
    matrix4x4 mat; mat.Identity();
    
    mat[0]  = 2 * n / (r - l);
    mat[2]  = (r + l) / (r - l);
    mat[5]  = 2 * n / (t - b);
    mat[6]  = (t + b) / (t - b);
    mat[10] = -(f + n) / (f - n);
    mat[11] = -(2 * f * n) / (f - n);
    mat[14] = -1;
    mat[15] = 0;
    
    // TODO: Get rid of this!
    mat.Transpose();
    
    glLoadMatrixf(&mat[0]);
}

void FrustumGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
	const GLdouble DEG2RAD = M_PI / 180.0;
    
	GLdouble tangent = tan(fovY/2 * DEG2RAD);		// tangent of half fovY
	GLdouble height = zNear * tangent;				// half height of near plane
	GLdouble width = height * aspect;				// half width of near plane
    
    FrustumGL(-width, width, -height, height, zNear, zFar);
}

//------------------------------------------------------------------------------
// Purpose: Sets up the camera perspective, and the camera frustum
//------------------------------------------------------------------------------
void COGLRender::SetupProjection(void)
{
	glMatrixMode(GL_PROJECTION);
    
	// Setup the view frustum
	FrustumGL(90.0, 800.0/600.0, 1, 2000);
}

//------------------------------------------------------------------------------
// Purpose: Sets up the model view
//------------------------------------------------------------------------------
void COGLRender::SetupModelView(void)
{
    glMatrixMode(GL_MODELVIEW);

    // NOTE: The angles and translation are inverted for the camera position
    // to the world.
    matrix4x4 mat_worldView; mat_worldView.Identity();
    
    matrix4x4 rotx, roty, rotz;
    rotx.SetRotationX(-g_camera.m_ang.x); // PITCH
    roty.SetRotationY(-g_camera.m_ang.y); // YAW
    rotz.SetRotationZ(-g_camera.m_ang.z); // ROLL
    
    matrix4x4 temp, temp2;
    MatrixMultiply(rotz, roty, temp); // Z * Y
    MatrixMultiply(temp, rotx, temp2); // (Z * Y) * X
    
    // Translation
    matrix4x4 cam_trans; cam_trans.Identity();
    cam_trans.SetTranslation(-g_camera.m_pos.x, -g_camera.m_pos.y, -g_camera.m_pos.z);
    MatrixMultiply(cam_trans, temp2, mat_worldView);
    
    glLoadMatrixf(&mat_worldView[0]);
}

//------------------------------------------------------------------------------
// Purpose: Sets the camera position and angle
//------------------------------------------------------------------------------
void COGLRender::SetCamera(Vector3 &position, Angle &angle)
{
    g_camera.m_pos = position;
    g_camera.m_ang = angle;
}

//------------------------------------------------------------------------------
// Purpose: Draws a buffered mesh
//------------------------------------------------------------------------------
void COGLRender::DrawMeshGL(const ogl_mesh_t &mesh, const Vector3 &origin)
{
    if(mesh.vertexBuffer == 0 || mesh.indexBuffer == 0)
        return;
    
	//glPushAttrib(GL_CURRENT_BIT  | GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	
	// Turn on some GL states
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_INDEX_ARRAY);
    
	// Push stack for unique matrix
	glPushMatrix();
    
	// Add Translation
	glTranslatef(origin.x, origin.y, origin.z);
    
	// Add rotation
	//glRotatef( pAngle->x, 1.0f, 0.0f, 0.0f );
	//glRotatef( pAngle->y, 0.0f, 1.0f, 0.0f );
	//glRotatef( pAngle->z, 0.0f, 0.0f, 1.0f );
    
    // Color Override, entire mesh!
    glColor3ub((GLubyte)mesh.meshColorR,
               (GLubyte)mesh.meshColorG,
               (GLubyte)mesh.meshColorB);
    
    // Setup Pointers, this describes the objects
    glBindBufferARB(GL_ARRAY_BUFFER, mesh.vertexBuffer);
    glVertexPointer( 3, GL_FLOAT, 0, NULL );
    
    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, mesh.indexBuffer);
    glIndexPointer( GL_INT, 0, NULL );
    
    glDrawElements(mesh.meshType, mesh.numIndicies, GL_UNSIGNED_INT, 0);
    
	// Pop back to World
	glPopMatrix();
    
	// Turn them off
	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_INDEX_ARRAY );
    
	// Disable buffers
	glBindBufferARB(GL_ARRAY_BUFFER, 0);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, 0);
    
	//glPopAttrib();
}

//------------------------------------------------------------------------------
// Purpose: Buffers a number of meshes to VRAM using OGL calls
//------------------------------------------------------------------------------
void COGLRender::BufferMeshesGL(mesh_t meshes[],
                                ogl_mesh_t oglmeshes[],
                                unsigned int numMeshes)
{
    for(unsigned int i = 0; i < numMeshes; ++i)
    {
        // Generate new buffers
        glGenBuffersARB(1, &oglmeshes[i].vertexBuffer);
        glGenBuffersARB(1, &oglmeshes[i].indexBuffer);
        
        // Set current buffer
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, oglmeshes[i].vertexBuffer);
        
        // Write to Buffer
        glBufferDataARB(GL_ARRAY_BUFFER_ARB,
                        (sizeof(Vector3) * meshes[i].m_verticies.Count()),
                        meshes[i].m_verticies.Base(),
                        GL_STATIC_DRAW_ARB);
        
        // Set index buffer
        glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, oglmeshes[i].indexBuffer);
        
        // write indices
        glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB,
                        (sizeof(unsigned int) * meshes[i].m_indicies.Count()),
                        meshes[i].m_indicies.Base(),
                        GL_STATIC_DRAW_ARB);
    }
    
    // unbind the current buffers
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
}

//------------------------------------------------------------------------------
// Purpose: Creates the Axes Line meshes
//------------------------------------------------------------------------------
void COGLRender::CreateAxesLines(void)
{
    // Create Axes Lines
    mesh_t axesLines;
    
    // X
    axesLines.AddVertex(Vector3(10, 0, 0));
    axesLines.AddVertex(Vector3(-10, 0, 0));
    
    axesLines.AddIndex(0);
    axesLines.AddIndex(1);
    
    m_XAxis.numIndicies = 2;
    m_XAxis.meshType = GL_LINES;
    m_XAxis.meshColorR = 255;
    m_XAxis.meshColorG = 80;
    m_XAxis.meshColorB = 80;
    
    BufferMeshesGL(&axesLines, &m_XAxis, 1);
    
    // Y
    axesLines.m_verticies[0].Init(0, 10, 0);
    axesLines.m_verticies[1].Init(0, -10, 0);
    
    m_YAxis.numIndicies = 2;
    m_YAxis.meshType = GL_LINES;
    m_YAxis.meshColorR = 0;
    m_YAxis.meshColorG = 255;
    m_YAxis.meshColorB = 0;
    
    BufferMeshesGL(&axesLines, &m_YAxis, 1);
    
    // Z
    axesLines.m_verticies[0].Init(0, 0, 10);
    axesLines.m_verticies[1].Init(0, 0, -10);
    
    m_ZAxis.numIndicies = 2;
    m_ZAxis.meshType = GL_LINES;
    m_ZAxis.meshColorR = 0;
    m_ZAxis.meshColorG = 0;
    m_ZAxis.meshColorB = 255;
    
    BufferMeshesGL(&axesLines, &m_ZAxis, 1);
}

#define WORLD_BOX_SIZE      512.0f

void COGLRender::CreateWorldBox(void)
{
    // Create a test floor
    mesh_t boxSides[6];
    
    float halfsize = WORLD_BOX_SIZE / 2;
    
    // BOTTOM
    boxSides[0].AddVertex(Vector3(halfsize, -halfsize, -halfsize));
    boxSides[0].AddVertex(Vector3(-halfsize, -halfsize, -halfsize));
    boxSides[0].AddVertex(Vector3(-halfsize, -halfsize, halfsize));
    boxSides[0].AddVertex(Vector3(halfsize, -halfsize, halfsize));
    
    boxSides[0].AddIndex(0);
    boxSides[0].AddIndex(1);
    boxSides[0].AddIndex(2);
    boxSides[0].AddIndex(3);
    
    m_WorldBox[0].numIndicies = 4;
    m_WorldBox[0].meshType = GL_TRIANGLE_FAN;
    m_WorldBox[0].meshColorR = 0;
    m_WorldBox[0].meshColorG = 201;
    m_WorldBox[0].meshColorB = 19;
    
    // TOP
    boxSides[1].AddVertex(Vector3(halfsize, halfsize, halfsize));
    boxSides[1].AddVertex(Vector3(-halfsize, halfsize, halfsize));
    boxSides[1].AddVertex(Vector3(-halfsize, halfsize, -halfsize));
    boxSides[1].AddVertex(Vector3(halfsize, halfsize, -halfsize));
    
    boxSides[1].AddIndex(0);
    boxSides[1].AddIndex(1);
    boxSides[1].AddIndex(2);
    boxSides[1].AddIndex(3);
    
    m_WorldBox[1].numIndicies = 4;
    m_WorldBox[1].meshType = GL_TRIANGLE_FAN;
    m_WorldBox[1].meshColorR = 0;
    m_WorldBox[1].meshColorG = 157;
    m_WorldBox[1].meshColorB = 230;
    
    // BACK
    boxSides[2].AddVertex(Vector3(halfsize, halfsize, -halfsize));
    boxSides[2].AddVertex(Vector3(-halfsize, halfsize, -halfsize));
    boxSides[2].AddVertex(Vector3(-halfsize, -halfsize, -halfsize));
    boxSides[2].AddVertex(Vector3(halfsize, -halfsize, -halfsize));
    
    boxSides[2].AddIndex(0);
    boxSides[2].AddIndex(1);
    boxSides[2].AddIndex(2);
    boxSides[2].AddIndex(3);
    
    m_WorldBox[2].numIndicies = 4;
    m_WorldBox[2].meshType = GL_TRIANGLE_FAN;
    m_WorldBox[2].meshColorR = 0;
    m_WorldBox[2].meshColorG = 157;
    m_WorldBox[2].meshColorB = 230;
    
    // FRONT
    boxSides[3].AddVertex(Vector3(halfsize, -halfsize, halfsize));
    boxSides[3].AddVertex(Vector3(-halfsize, -halfsize, halfsize));
    boxSides[3].AddVertex(Vector3(-halfsize, halfsize, halfsize));
    boxSides[3].AddVertex(Vector3(halfsize, halfsize, halfsize));
    
    boxSides[3].AddIndex(0);
    boxSides[3].AddIndex(1);
    boxSides[3].AddIndex(2);
    boxSides[3].AddIndex(3);
    
    m_WorldBox[3].numIndicies = 4;
    m_WorldBox[3].meshType = GL_TRIANGLE_FAN;
    m_WorldBox[3].meshColorR = 0;
    m_WorldBox[3].meshColorG = 157;
    m_WorldBox[3].meshColorB = 230;
    
    // RIGHT
    boxSides[4].AddVertex(Vector3(halfsize, halfsize, halfsize));
    boxSides[4].AddVertex(Vector3(halfsize, halfsize, -halfsize));
    boxSides[4].AddVertex(Vector3(halfsize, -halfsize, -halfsize));
    boxSides[4].AddVertex(Vector3(halfsize, -halfsize, halfsize));
    
    boxSides[4].AddIndex(0);
    boxSides[4].AddIndex(1);
    boxSides[4].AddIndex(2);
    boxSides[4].AddIndex(3);
    
    m_WorldBox[4].numIndicies = 4;
    m_WorldBox[4].meshType = GL_TRIANGLE_FAN;
    m_WorldBox[4].meshColorR = 0;
    m_WorldBox[4].meshColorG = 157;
    m_WorldBox[4].meshColorB = 230;
    
    // LEFT
    boxSides[5].AddVertex(Vector3(-halfsize, halfsize, -halfsize));
    boxSides[5].AddVertex(Vector3(-halfsize, halfsize, halfsize));
    boxSides[5].AddVertex(Vector3(-halfsize, -halfsize, halfsize));
    boxSides[5].AddVertex(Vector3(-halfsize, -halfsize, -halfsize));
    
    boxSides[5].AddIndex(0);
    boxSides[5].AddIndex(1);
    boxSides[5].AddIndex(2);
    boxSides[5].AddIndex(3);
    
    m_WorldBox[5].numIndicies = 4;
    m_WorldBox[5].meshType = GL_TRIANGLE_FAN;
    m_WorldBox[5].meshColorR = 0;
    m_WorldBox[5].meshColorG = 157;
    m_WorldBox[5].meshColorB = 230;
    
    // Now setup the meshes with OGL
    BufferMeshesGL(boxSides, m_WorldBox, 6);
}
















