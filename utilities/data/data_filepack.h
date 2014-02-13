//
//  data_filepack.h
//  For putting a standard data buffer into a file.
//
//  Created by Ryan Sheffer on 2013-02-11.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef DATA_FILE_H
#define DATA_FILE_H

#ifdef _WIN
#pragma once
#endif

namespace DataPacking
{
    // little-endian "GECF" (Genesis Engine Chunk File)
#define BUFFER_HEADER			(('F'<<24)+('C'<<16)+('E'<<8)+'G')
    
    // Version for chunk pools saved in files
#define BUFFER_FILE_VERSION		1
    
    class FilePackage
    {
        /** Used for file saving. */
        struct buffer_header_t
        {
            int         id;
            short       version;
            int         numBlocks;
            int         bufferSize;
        };
    };
}


#endif // DATA_FILE_H
