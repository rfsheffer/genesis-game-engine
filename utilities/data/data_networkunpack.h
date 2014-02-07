//
//  data_networkunpack.h
//  Used to unpack a network buffer
//
//  Created by Ryan Sheffer on 2013-02-16.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef DATA_NETWORK_UNPACK_H
#define DATA_NETWORK_UNPACK_H

#ifdef _WIN32
#pragma once
#endif

#include "data_mappable.h"
#include "data_pack.h"
#include "data_network_helpers.h"

namespace DataPacking
{
    //--------------------------------------------------------------------------
    /** Networking unpacking */
    class NetworkUnpackage
    {
    public:
        
        NetworkUnpackage(DataBuffer *pBuffer) : m_pDataBuffer(pBuffer) {}
        
        void        UnpackToMappables(CDataMappable *pMappables[],
                                           unsigned int numMappables);
        
        void        WriteToMappable(CDataMappable **ppBaseClass, unsigned int blockIndex);
        
        /** This is the buffer that is currently being worked on. */
        DataBuffer *m_pDataBuffer;
    };
}

#endif // DATA_NETWORK_UNPACK_H
