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
    class NetworkPackage : public DataBuffer
    {
    public:
        
        /**
         * Constructor
         * @param numEntities The number of entities which can be packed.
         */
        NetworkPackage(unsigned int numEntities) : DataBuffer(0, numEntities){}
        
        bool        PackageEntities(CEntityBase *pEntities[],
                                            unsigned int numEntities);
        
        void        WriteDataMaps(CEntityBase *pBaseClass);
        void        WriteObject(CEntityBase *pBaseClass, objdesc_t *pObject);
        void        WriteTypeFromClass(CEntityBase *pBaseClass,
                                       objdesc_t *pObject, char *pBuffer);
        
        struct networked_entity_header_t
        {
            //char entityname[MAX_ENTITY_NAME];
            //char classname[MAX_CLASS_NAME];		// Classname.
            bool topclass;						// Is this the top most class in the class hierarchy?
            short num_objs;						// Number of Saved Objects.
        };
    };
    
}


#endif // DATA_NETWORK_PACK_H
