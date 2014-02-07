//
//  OGL_Types.h
//  genesis
//
//  Created by Ryan Sheffer on 2012-11-18.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef genesis_OGL_Types_h
#define genesis_OGL_Types_h

// This is the information for a buffered mesh.
struct ogl_mesh_t
{
    // The vertex buffer index
    GLuint  vertexBuffer;
    
    // The index buffer index
    GLuint  indexBuffer;
    
    // Number of indicies
    GLuint  numIndicies;
    
    // The type of mesh ( GL_POINTS, GL_LINES, GL_LINE_LOOP,
    //                    GL_LINE_STRIP, GL_TRIANGLES, GL_TRIANGLE_STRIP,
    //                    GL_TRIANGLE_FAN, GL_QUADS, GL_QUAD_STRIP, GL_POLYGON )
    GLuint  meshType;
    
    // Color
    GLuint  meshColorR;
    GLuint  meshColorG;
    GLuint  meshColorB;
    
};


#endif
