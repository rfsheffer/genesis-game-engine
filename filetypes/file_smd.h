//
//  file_smd.h
//  genesis
//
//  Created by Ryan Sheffer on 2012-10-27.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef FILE_SMD_H
#define FILE_SMD_H

#ifdef _WIN
#pragma once
#endif

#include "type_mesh.h"

namespace FileTypes
{
    
// Purpose: Used for Parsing SMD text files
class CSMDFile
{
public:
    void ParseSMD(const char *pFileName);
    
private:
    int FindVertex(Vector3 &vert);
    bool ParseTriangleBlock(FILE *pFile);
    
    // Read in contents
    mesh_t m_meshData;
};
    
}

#endif // FILE_SMD_H
