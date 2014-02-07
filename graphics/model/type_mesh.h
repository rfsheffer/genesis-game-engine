//
//  mesh.h
//  A class designed to hold a mesh ( Verts, Normals, UV, Tangents )
//
//  Created by Ryan Sheffer on 2012-10-27.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef TYPE_MESH_H
#define TYPE_MESH_H

#ifdef _WIN
#pragma once
#endif

// This is a base mesh type which contains verticies, normals, and UV coordinates
// for a mesh.
struct mesh_t
{
    Container::Vector<Vector3> m_verticies;
    Container::Vector<Vector3> m_normals;
    Container::Vector<Vector2> m_uvs;
    
    Container::Vector<unsigned int>     m_indicies;
    
    inline unsigned int    AddVertex(const Vector3 &vertex)
    {
        return m_verticies.AddElementToBack(vertex);
    }
    
    inline unsigned int    AddNormal(const Vector3 &normal)
    {
        return m_normals.AddElementToBack(normal);
    }
    
    inline unsigned int    AddUV(const Vector2 &uv)
    {
        return m_uvs.AddElementToBack(uv);
    }
    
    inline unsigned int    AddIndex(const unsigned int index)
    {
        return m_indicies.AddElementToBack(index);
    }
    
    bool        IsValid(void)
    {
        // Check that all containers have the same number of elements.       
        if((m_verticies.Count() + m_normals.Count() + m_uvs.Count()) /
                                        3.0f != m_verticies.Count())
        {
            return false;
        }
        
        // Indicies needs to be divisible by 3
        if(m_indicies.Count() % 3 != 0)
        {
            return false;
        }
        
        return true;
    }
};

#endif // TYPE_MESH_H
