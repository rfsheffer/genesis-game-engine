//
//  data_networkpack.h
//  Network package for entities
//
//  Created by Ryan Sheffer on 2013-02-04.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef DATA_NETWORK_PACK_H
#define DATA_NETWORK_PACK_H

#include "ent_base.h"
#include "data_pack.h"

namespace DataPacking
{
    /** Networking packaging */
    class NetworkPackage
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
        
        DataBuffer        *PackageEntities(CEntityBase *pEntities[],
                                            unsigned int numEntities);
        
        void        WriteDataMaps(CEntityBase *pBaseClass);
        void        WriteObject(CEntityBase *pBaseClass, objdesc_t *pObject);
        void        WriteTypeFromClass(CEntityBase *pBaseClass,
                                       objdesc_t *pObject, char *pBuffer);
        
        /** The heading structure before an entities data map */
        struct networked_entity_header_t
        {
            /** Network flag sent with each entity datamap */
            enum net_ent_flags
            {
                /** Specifies an empty entity slot, will also destory any
                 entity currently in the client slot. */
                NET_FLAG_DEAD       =   0,
                
                /** Specifies that this data map is at the top class. */
                NET_FLAG_TOPCLASS   =   0x01,
                
                /** Specifies that the entity is new. */
                NET_FLAG_CREATE     =   0x02,
                
                /** Specifies that this data is an update for an old entity. */
                NET_FLAG_UPDATE     =   0x04
            };
            
            /** Number of Saved Objects. */
            short num_objs;
            
            /** 
             * Network flags
             * @see net_ent_flags
             */
            short flags;
        };
        
        /** This is the buffer that is currently being worked on. */
        DataBuffer *m_pDataBuffer;
    };
}


#endif // DATA_NETWORK_PACK_H
