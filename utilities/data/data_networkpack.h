//
//  data_networkpack.h
//  Network package for entities
//
//  Created by Ryan Sheffer on 2013-02-04.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef DATA_NETWORK_PACK_H
#define DATA_NETWORK_PACK_H

#ifdef _WIN32
#pragma once
#endif

#include "data_mappable.h"
#include "data_pack.h"
#include "data_network_helpers.h"

namespace DataPacking
{
    //--------------------------------------------------------------------------
    /** Networking packaging */
    class UTILITIES_CLASS NetworkPackage
    {
    public:
        
        NetworkPackage() : m_pDataBuffer(NULL) {}
        
        ~NetworkPackage()
        {
            if(m_pDataBuffer)
            {
                delete m_pDataBuffer;
            }
        }
        
        DataBuffer        *PackageMappables(CDataMappable *pMappables[],
                                            unsigned int numMappables);
        
        void        WriteDataMaps(CDataMappable *pBaseClass);
        void        WriteObject(CDataMappable *pBaseClass, objdesc_t *pObject);
        void        WriteTypeFromClass(CDataMappable *pBaseClass,
                                       objdesc_t *pObject, byte *pBuffer);
        
        /** This is the buffer that is currently being worked on. */
        DataBuffer *m_pDataBuffer;
    };
}


#endif // DATA_NETWORK_PACK_H
