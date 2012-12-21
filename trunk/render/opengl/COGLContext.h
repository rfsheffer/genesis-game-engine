//
//  CGLRender.h
//  render_gl
//
//  Created by Ryan Sheffer on 2012-09-30.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef COGLRENDER_H
#define COGLRENDER_H

#include "IGraphicsContext.h"
#include "OGL_Types.h"

// Forward declarations
struct mesh_t;

// OGL version of the graphics Device
class COGLRender : public IGraphicsContext
{
public:
    
    //-----------------------------------------------------------------------
    // General Interface Methods
    //-----------------------------------------------------------------------
    virtual void Init(void);
    virtual void FrameUpdate(void);
    virtual void Shutdown(void) {}
    
    //-----------------------------------------------------------------------
    // Render Controls
    //-----------------------------------------------------------------------
    virtual void SetViewport(unsigned int x,
                             unsigned int y,
                             unsigned int width,
                             unsigned int height);
    
    virtual void SetupProjection(void);
    
    virtual void SetupModelView(void);
    
    virtual void SetCamera(Vector3 &position, Angle &angle);

    void DrawMeshGL(const ogl_mesh_t &mesh, const Vector3 &origin);
    void BufferMeshesGL(mesh_t meshes[],
                        ogl_mesh_t oglmeshes[],
                        unsigned int numMeshes);
    
    void CreateAxesLines(void);
    void CreateWorldBox(void);
    
    unsigned int GetWidth(void)
    {
        return m_uiWidthPixels;
    }
    
    unsigned int GetHeight(void)
    {
        return m_uiHeightPixels;
    }
    
    //-----------------------------------------------------------------------
    // Device Controls
    //-----------------------------------------------------------------------
    bool SetVerticalSync(bool enable);
    bool SetAppleGLThreadedCalls(bool enable);
    
private:
    
    // This is the pixel width and height of this render context
    unsigned int m_uiWidthPixels;
    unsigned int m_uiHeightPixels;
    
    // Floor
    ogl_mesh_t      m_WorldBox[6];
    
    // Axes Hints
    ogl_mesh_t      m_XAxis;
    ogl_mesh_t      m_YAxis;
    ogl_mesh_t      m_ZAxis;
};

#endif // COGLRENDER_H
