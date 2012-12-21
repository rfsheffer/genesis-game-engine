//
//  smd.cpp
//  Purpose: Parses an SMD file and produces mesh data.
//
//  Created by Ryan Sheffer on 2012-10-27.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#include "file_smd.h"

namespace FileTypes
{
    
#define MAX_FILE_LINE_LEN       2048
    
    static char szFileLine[MAX_FILE_LINE_LEN];
    
    //------------------------------------------------------------
    // Purpose: Parses an SMD text file
    //------------------------------------------------------------
    void CSMDFile::ParseSMD(const char *pFileName)
    {
        // Load up the file
        FILE *pFile = NULL;
        pFile = fopen(pFileName, "r");
        printf("Opening file %s\n", pFileName);
        if(!pFile)
        {
            perror ("ParseSMD: The following error occurred");
            return;
        }
        
        // Start parsing the files block headers
        while(fgets(szFileLine, MAX_FILE_LINE_LEN, pFile))
        {
            if(strnstr(szFileLine, "triangles", 9))
            {
                // Get triangle data next
                ParseTriangleBlock(pFile);
            }
        }
        
        fclose(pFile);
    }
    
    //------------------------------------------------------------
    // A simple comparison can be used here because we read in exactly
    // the same for all verticies. If there is a slight change,
    // then maybe the SMD exporter being used is farked...
    //------------------------------------------------------------
    int CSMDFile::FindVertex(Vector3 &vert)
    {
        if(m_meshData.m_verticies.Count() == 0)
            return -1;
        
        for(unsigned int i = 0; i < m_meshData.m_verticies.Count(); ++i)
        {
            if(vert == m_meshData.m_verticies[i])
                return i;
        }
        
        return -1;
    }
    
    //------------------------------------------------------------
    // Purpose: Parses an SMD text file
    //------------------------------------------------------------
    bool CSMDFile::ParseTriangleBlock(FILE *pFile)
    {
        int boneIndex;      // We will use this in the future...
        Vector3 vertex;
        Vector3 normal;
        Vector2 uv;
        
        int scanIn;
        int index;
        
        // Start parsing the files block headers
        while(fgets(szFileLine, MAX_FILE_LINE_LEN, pFile))
        {
            if(strnstr(szFileLine, "end", 4))
            {
                // End of the block, break!
                break;
            }
            
            // Scan in the three verticies
            for(int i = 0; i < 3; ++i)
            {
                if(!fgets(szFileLine, MAX_FILE_LINE_LEN, pFile))
                {
                    printf("Warning: Could not get vertex line from SMD file!\n");
                    return false;
                }
                
                scanIn = sscanf(szFileLine, "%d %f %f %f %f %f %f %f %f", &boneIndex,
                                &vertex.x, &vertex.y, &vertex.z,
                                &normal.x, &normal.y, &normal.z,
                                &uv.x, &uv.y);
                
                // Add the new verts to the list
                if(scanIn == 9)
                {
                    index = FindVertex(vertex);
                    if(index == -1)
                    {
                        // New Vertex! Add it to the master list.
                        index = m_meshData.AddVertex(vertex);
                        m_meshData.AddNormal(normal);
                        m_meshData.AddUV(uv);
                    }
                    
                    // The index needs to be added to the indicies array
                    m_meshData.AddIndex(index);
                }
                else
                {
                    printf("SMD Syntax Error: Not enough parameters!\n");
                    return false;
                }
            }
        }
        
        if(m_meshData.IsValid())
            return true;
        else
            return false;
    }
    
}