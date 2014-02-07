//
//  data_networkunpack.cpp
//  Used to unpack a network buffer
//
//  Created by Ryan Sheffer on 2013-02-16.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#include "data_networkunpack.h"
//#include "entity_dictionary.h"

namespace DataPacking
{
    //--------------------------------------------------------------------------
    /**
     * Unpacks this network package to an entity list
     * @param pEntities The entities which should be updated.
     * @param numEntities The number of entities to be updated.
     */
    void NetworkUnpackage::UnpackToMappables(CDataMappable *pMappables[],
                                                unsigned int numMappables)
    {
        ASSERTION(m_pDataBuffer, "Trying to unpack NULL network package!");
        
        ASSERTION(m_pDataBuffer->m_iNum_Blocks == numMappables,
                  "Network package incompatible with unpack mappables!");
        
        for(int i = 0; i < numMappables; ++i)
        {
            WriteToMappable(&pMappables[i], i);
        }
    }
    
    //--------------------------------------------------------------------------
    /**
     * Write data buffer block to entity.
     */
    void NetworkUnpackage::WriteToMappable(CDataMappable **ppBaseClass, unsigned int blockIndex)
    {
        //DataBuffer::data_block &CurBlock = m_pDataBuffer->m_pBlocks[blockIndex];
        
        // TODO: Create a block reader class for reading back specific data from
        // blocks.
        
        unsigned int curBlockOffset = 0;
        
        int netFlags = *(int*)m_pDataBuffer->ReadFromBlock(blockIndex, curBlockOffset);
        curBlockOffset += 4;
        if(netFlags & NET_FLAG_DEAD)
        {
            if(*ppBaseClass != NULL)
            {
                // TODO: REMOVE!
            }
            return;
        }
        
        int iStrLen = *(int*)m_pDataBuffer->ReadFromBlock(blockIndex, curBlockOffset);
        curBlockOffset += 4;
        //const char *pszClassName = (const char *)m_pDataBuffer->ReadFromBlock(blockIndex, curBlockOffset);
        curBlockOffset += iStrLen;
        
        if(*ppBaseClass == NULL)
        {
            //*ppBaseClass =
            //EntityFactoryDictionary()->Create(pszClassName, false, false);
        }
    }
}