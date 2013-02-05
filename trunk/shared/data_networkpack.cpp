//
//  data_networkpack.cpp
//  Packager for network the server -> client
//
//  Created by Ryan Sheffer on 2013-02-04.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include "data_networkpack.h"

namespace DataPacking
{
    /**
     * Packages a list of entities up for sending.
     * @param pEntities The entities which should be packed.
     * @param numEntities The number of entities being passed in for packing.
     */
    bool NetworkPackage::PackageEntities(CEntityBase *pEntities[],
                                         unsigned int numEntities)
    {
        SetBlockGrowth(10);
        
        for(int i = 0; i < numEntities; ++i)
        {
            WriteDataMaps(pEntities[i]);
        }
        
        return true;
    }
    
    /**
     * Write data mapped variables with the network flag to buffer.
     */
    void NetworkPackage::WriteDataMaps(CEntityBase *pBaseClass)
    {
        if(!pBaseClass)
        {
            // TODO: Writting an empty block for this index
            return;
        }
        
        StartWritting("NET_ENTITY_BLOCK"); // Write an entity save block.
        networked_entity_header_t net_ent_header;
        bool first_class = true;
        
        datamap_t *pCurDataMap = pBaseClass->GetDataMap();;
        while( pCurDataMap )
        {
            //Write entity save header first.
            //strncpy( save_ent_header.entityname, ent_name->c_str(), MAX_ENTITY_NAME );
            //strncpy( save_ent_header.classname, pCurDataMap->dataClassName, MAX_CLASS_NAME );
            net_ent_header.topclass = first_class;
            net_ent_header.num_objs = 0;
            
            WriteBuffer((char*)&net_ent_header, sizeof(net_ent_header));

            // Write Objects
            for(int i = 0; i < pCurDataMap->NumObjs; i++)
            {
                objdesc_t *pobject = &pCurDataMap->objList[i];
                if(pobject->flags & MAPOBJ_NETWORKED)
                {
                    WriteObject(pBaseClass, pobject);
                    ++net_ent_header.num_objs;
                }
            }
            
            first_class = false;
            pCurDataMap = pCurDataMap->baseMap;
        }
        
        EndWritting();
    }
    
    /**
     * Writes a mapped object to the buffer
     * @param pBaseClass The Entity owner of this class.
     * @param pObject The Object being written.
     */
    void NetworkPackage::WriteObject(CEntityBase *pBaseClass, objdesc_t *pObject)
    {
        if(!pBaseClass || !pObject)
            return;
        
        // First determine the size of this obj_block
        size_t obj_name_len = strlen( pObject->objname );
        short obj_block_size = (SHORT_SIZE +
                                BYTE_SIZE +
                                obj_name_len +
                                SHORT_SIZE +
                                SHORT_SIZE +
                                (GetDataSize(pObject->objType) * pObject->numobjs));
        
        // Request a buffer
        char *pBuffer = CreateBuffer( obj_block_size );
        if( pBuffer )
        {
            // Size of this block of data.
            *((short*)pBuffer) = obj_block_size; pBuffer += SHORT_SIZE;
            // Name Length
            pBuffer[0] = (char)obj_name_len; pBuffer += 1;
            // Name
            memcpy( pBuffer, pObject->objname, obj_name_len ); pBuffer += obj_name_len;
            // Type
            *((short*)pBuffer) = pObject->objType; pBuffer += SHORT_SIZE;
            // num items
            *((short*)pBuffer) = pObject->numobjs; pBuffer += SHORT_SIZE;
            
            // Objects
            WriteTypeFromClass( pBaseClass, pObject, pBuffer );
        }
    }
    
    /**
     * Writes the object type from the class
     * @param pBaseClass The class who owns this type
     * @param pObject The object to write from
     * @param pBuffer The buffer to write to
     */
    void NetworkPackage::WriteTypeFromClass(CEntityBase *pBaseClass,
                                            objdesc_t *pObject, char *pBuffer)
    {
        if( !pBaseClass || !pObject || !pBuffer )
            return;
        
        size_t objectsize = GetDataSize( pObject->objType );
        
        for( int i = 0; i < pObject->numobjs; i++ )
        {
            // Get pointer to REAL object so we can copy it.
            char *pVar = ((char *)pBaseClass + pObject->objoffset + ( objectsize * i ));
            memcpy( pBuffer, pVar, objectsize ); pBuffer += objectsize;
        }
    }
}