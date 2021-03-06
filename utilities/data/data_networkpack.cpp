//
//  data_networkpack.cpp
//  Packager for networking the server <-> client
//
//  Created by Ryan Sheffer on 2013-02-04.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include "utilhead.h"
#include "data_networkpack.h"

namespace DataPacking
{
    //--------------------------------------------------------------------------
    /**
     * Packages a list of entities up for sending.
     * @param pEntities The entities which should be packed.
     * @param numEntities The number of entities being passed in for packing.
     * @return The data buffer containing the entities packed for networking.
     */
    DataBuffer *NetworkPackage::PackageMappables(CDataMappable *pMappables[],
                                         unsigned int numMappables)
    {
        ASSERTION(!m_pDataBuffer, "Trying to package a new buffer,"
                  "but the old buffer hasn't been destroyed yet!");
        
        m_pDataBuffer = new DataBuffer(0 ,numMappables);
        m_pDataBuffer->SetBlockGrowth(10);
        
        for(unsigned int i = 0; i < numMappables; ++i)
        {
            WriteDataMaps(pMappables[i]);
        }
        
        return m_pDataBuffer;
    }
    
    //--------------------------------------------------------------------------
    /**
     * Write data mapped variables with the network flag to buffer.
     */
    void NetworkPackage::WriteDataMaps(CDataMappable *pBaseClass)
    {        
        m_pDataBuffer->StartWritting("NET_ENTITY_BLOCK"); // Write an entity block.
        networked_entity_header_t net_ent_header;
        //bool first_class = true;
        
        if(!pBaseClass)
        {
            /*unsigned int uiStrLen = strlen("empty");
            m_pDataBuffer->WriteBuffer((char*)&uiStrLen, sizeof(uiStrLen));
            m_pDataBuffer->WriteBuffer("empty", strlen("empty"));
            
            // Write an empty block and stop here if there is no entity.
            net_ent_header.flags = networked_entity_header_t::NET_FLAG_DEAD;
            net_ent_header.num_objs = 0;
            
            m_pDataBuffer->WriteBuffer((char*)&net_ent_header, sizeof(net_ent_header));*/
            
            int netFlags = NET_FLAG_DEAD;
            m_pDataBuffer->WriteBuffer((byte*)&netFlags, sizeof(netFlags));
            
            m_pDataBuffer->EndWritting();
            return;
        }
        
        int netFlags = NET_FLAG_UPDATE;
        m_pDataBuffer->WriteBuffer((byte*)&netFlags, sizeof(netFlags));
        
        int iStrLen = (int)strlen(pBaseClass->GetClassname());
        m_pDataBuffer->WriteBuffer((byte*)&iStrLen, sizeof(iStrLen));
        m_pDataBuffer->WriteBuffer((byte*)pBaseClass->GetClassname(),
                                  (unsigned int)strlen(pBaseClass->GetClassname()));
        
        // OPTIMIZATION: Only package an update for an entity if something actually
        // changed...
        
        datamap_t *pCurDataMap = pBaseClass->GetDataMap();
        while( pCurDataMap )
        {
            //net_ent_header.flags = networked_entity_header_t::NET_FLAG_UPDATE;
            int numNetworkedObjs = num_networked_obj(pCurDataMap);
            ASSERTION(numNetworkedObjs <= SHRT_MAX, "Exceeded short type, change to int");
            net_ent_header.num_objs = (short)numNetworkedObjs;
            
            //Write entity save header first.
//            net_ent_header.flags |=
//                first_class?networked_entity_header_t::NET_FLAG_TOPCLASS:0;
            
            m_pDataBuffer->WriteBuffer((byte*)&net_ent_header, sizeof(net_ent_header));

            // Write Objects
            for(int i = 0; i < pCurDataMap->NumObjs; i++)
            {
                objdesc_t *pobject = &pCurDataMap->objList[i];
                if(pobject->flags & MAPOBJ_NETWORKED)
                {
                    WriteObject(pBaseClass, pobject);
                }
            }
            
            //first_class = false;
            pCurDataMap = pCurDataMap->baseMap;
        }
        
        m_pDataBuffer->EndWritting();
    }
    
    #pragma warning( disable : 4127 ) // conditional expression is constant
    //--------------------------------------------------------------------------
    /**
     * Writes a mapped object to the buffer
     * @param pBaseClass The Entity owner of this class.
     * @param pObject The Object being written.
     */
    void NetworkPackage::WriteObject(CDataMappable *pBaseClass, objdesc_t *pObject)
    {
        if(!pBaseClass || !pObject)
            return;
        
        // First determine the size of this obj_block
        size_t obj_name_len = strlen( pObject->objname );
        size_t obj_block_size = (SHORT_SIZE +
                                        CHARACTER_SIZE +
                                        obj_name_len +
                                        SHORT_SIZE +
                                        SHORT_SIZE +
                                        (GetDataSize(pObject->objType) * pObject->numobjs));

        ASSERTION(obj_block_size <= SHRT_MAX, "Exceeded short type, change to int");
        ASSERTION(DATA_COUNT <= SHRT_MAX, "Exceeded short type, change to int");
        ASSERTION(pObject->numobjs <= SHRT_MAX, "Exceeded short type, change to int");
        
        // Request a buffer
        byte *pBuffer = m_pDataBuffer->CreateBuffer((unsigned int)obj_block_size);
        if( pBuffer )
        {
            // Size of this block of data.
            *((short*)pBuffer) = (short)obj_block_size; pBuffer += SHORT_SIZE;
            // Name Length
            pBuffer[0] = (char)obj_name_len; pBuffer += 1;
            // Name
            memcpy( pBuffer, pObject->objname, obj_name_len ); pBuffer += obj_name_len;
            // Type
            *((short*)pBuffer) = (short)pObject->objType; pBuffer += SHORT_SIZE;
            // num items
            *((short*)pBuffer) = (short)pObject->numobjs; pBuffer += SHORT_SIZE;
            
            // Objects
            WriteTypeFromClass( pBaseClass, pObject, pBuffer );
        }
    }
    
    //--------------------------------------------------------------------------
    /**
     * Writes the object type from the class
     * @param pBaseClass The class who owns this type
     * @param pObject The object to write from
     * @param pBuffer The buffer to write to
     */
    void NetworkPackage::WriteTypeFromClass(CDataMappable *pBaseClass,
                                            objdesc_t *pObject, byte *pBuffer)
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