//
//  data_pack.cpp
//  A Buffer for storing any data.
//
//  Created by Ryan Sheffer on 17-07-10.
//  Copyright 2010 Ryan Sheffer. All rights reserved.
//

#include "data_pack.h"

namespace DataPacking
{
    /**
     * Constructor
     * @param pToCopy The buffer to copy to this buffer.
     */
    DataBuffer::DataBuffer(const DataBuffer *pToCopy)
    {
        memset( this, 0, sizeof( *this ) );
        
        m_iBlockGrowSize = pToCopy->GetBlockGrowth();
        
        if(!ResizeBufferData(pToCopy->m_iBufferSize))
        {
            m_iError = BUFFER_INIT_ERROR;
            ASSERTION(false, "Buffer initialization error!");
        }
        
        if(!ResizeBlockData(pToCopy->m_iNum_Blocks))
        {
            m_iError = BUFFER_INIT_ERROR;
            ASSERTION(false, "Buffer initialization error!");
        }
        
        m_iBufferSize = pToCopy->m_iBufferSize;
        m_iNum_Blocks = pToCopy->m_iNum_Blocks;
        m_iCurrentPos = pToCopy->m_iCurrentPos;
        m_iCurrent_Block = pToCopy->m_iCurrent_Block;
        
        memcpy(m_pBlocks, pToCopy->m_pBlocks, sizeof(data_block) * m_iNum_Blocks);
        memcpy(m_pBaseData, pToCopy->m_pBaseData, pToCopy->m_iBufferSize);
        
        m_pCurrentData = m_pBaseData + m_iCurrentPos;
    }
    
    /**
     * Constructor
     * @param buffer_size The size of the buffer to create.
     * @param num_blocks The number of blocks to start with.
     */
    DataBuffer::DataBuffer(unsigned int buffer_size, unsigned int num_blocks)
    {
        memset( this, 0, sizeof( *this ) );
        m_iBlockGrowSize = 1;
        
        if( buffer_size && !ResizeBufferData( buffer_size ) )
        {
            m_iError = BUFFER_INIT_ERROR;
        }
        
        if( num_blocks && !ResizeBlockData( num_blocks ) )
        {
            m_iError = BUFFER_INIT_ERROR;
        }
    }
    
    /**
     * Destructor
     */
    DataBuffer::~DataBuffer()
    {
        if( m_pBaseData )
        {
            free( m_pBaseData );
            m_pBaseData = NULL;
        }
        
        if( m_pBlocks )
        {
            free( m_pBlocks );
            m_pBlocks = NULL;
        }
    }
    
    /**
     * Allows this data buffer to take on the data of another buffer.
     */
    DataBuffer& DataBuffer::operator= (const DataBuffer &cSource)
    {
        m_iBlockGrowSize = cSource.GetBlockGrowth();
        
        ResizeBufferData(cSource.m_iBufferSize);
        ResizeBlockData(cSource.m_iNum_Blocks);
        
        m_iBufferSize = cSource.m_iBufferSize;
        m_iNum_Blocks = cSource.m_iNum_Blocks;
        m_iCurrentPos = cSource.m_iCurrentPos;
        m_iCurrent_Block = cSource.m_iCurrent_Block;
        
        memcpy(m_pBlocks, cSource.m_pBlocks, sizeof(data_block) * m_iNum_Blocks);
        memcpy(m_pBaseData, cSource.m_pBaseData, cSource.m_iBufferSize);
        
        m_pCurrentData = m_pBaseData + m_iCurrentPos;
        
        m_bWritting = false;
        m_iAmountWritten = 0;
        
        return *this;
    }
    
    /**
     * Used to add more blocks to the current availible blocks
     * @param newsize The new number of blocks.
     */
    bool DataBuffer::ResizeBlockData(unsigned int newsize)
    {
        if( newsize <= m_iNum_Blocks )
            return false;
        
        if( !m_pBlocks )
        {
            m_pBlocks = (data_block*)malloc( sizeof( data_block ) * newsize );
            if( m_pBlocks )
            {
                m_iNum_Blocks = newsize;
                return true;
            }
            return false;
        }
        else
        {
            // Need to resize the current block buffer.
            data_block *ptemp = (data_block*)realloc( m_pBlocks, newsize );
            if( !ptemp )
                return false;
            
            m_pBlocks = ptemp;
            return true;
        }
        
        return false;
    }
    
    /**
     * Used to resize the buffer of data.
     * @param newsize The new size of the buffer in bytes.
     */
    bool DataBuffer::ResizeBufferData(unsigned int newsize)
    {
        if( newsize <= m_iBufferSize )
            return false;
        
        if( !m_pBaseData )
        {
            m_pBaseData = m_pCurrentData = (char*)malloc( newsize );
            if( m_pBaseData )
            {
                m_iBufferSize = newsize;
                return true;
            }
            return false;
        }
        else
        {
            // Need to resize the current block buffer.
            char *ptemp = (char*)realloc( m_pBaseData, newsize );
            if( !ptemp )
                return false;
            
            m_iBufferSize = newsize;
            m_pBaseData = ptemp;
            m_pCurrentData = ptemp + m_iCurrentPos;
            return true;
        }
        
        return false;
    }
    
    /**
     * Sets the position in the buffer where the head should be.
     * @param position The position to move the head to.
     */
    bool DataBuffer::SetBufferPos(unsigned int position)
    {
        if( position > m_iBufferSize )
            return false;
        
        m_pCurrentData = m_pBaseData + position;
        m_iCurrentPos = position;
        return true;
    }
    
    /**
     * Creates a new block by name, adds the data buffer to it
     * @param pName The name of the new block.
     * @param pBuffer The buffer to be added to the block.
     * @param size The size of the buffer being passed in.
     */
    bool DataBuffer::WriteBlock(const char *pName,
                                const char *pBuffer,
                                unsigned int size)
    {
        if( !pBuffer || !pName || !size )
            return false;
        
        if( !StartWritting( pName ) )
            return false;
        
        if( !WriteBuffer( pBuffer, size ) )
            return false;
        
        EndWritting();
        return true;
    }
    
    /**
     * Starts a new block to start writting data to.
     */
    bool DataBuffer::StartWritting(const char *pName)
    {
        if( !pName )
            return false;
        
        data_block *pBlock = CreateBlock( pName );
        
        if( !pBlock )
            return false;
        
        m_bWritting = true;
        m_iAmountWritten = 0;
        return true;
    }
    
    /**
     * Writes a buffer to the currently open block.
     */
    bool DataBuffer::WriteBuffer(const char *pBuffer, unsigned int size)
    {
        if( m_bWritting == false )
            return false;
        
        // Check if we need to resize.
        if( m_iBufferSize < (m_iBufferSize+size) )
        {
            // We need to resize the buffer.
            if( !ResizeBufferData( m_iBufferSize + size ) )
                return false;
        }
        
        // Write to buffer.
        if( m_pCurrentData )
        {
            memcpy( m_pCurrentData, pBuffer, size );
            m_pCurrentData = m_pCurrentData + size;
            m_iAmountWritten += size;
            m_iCurrentPos += size;
            return true;
        }
        else
            return false;
    }
    
    /**
     * Creates a new buffer of N bytes in the currently open block, and
     * returns a pointer to it.
     * @param size The size of buffer to create.
     */
    char *DataBuffer::CreateBuffer(unsigned int size)
    {
        if( m_bWritting == false )
            return NULL;
        
        // Check if we need to resize.
        if( m_iBufferSize < (m_iBufferSize+size) )
        {
            // We need to resize the buffer.
            if( !ResizeBufferData( m_iBufferSize + size ) )
                return NULL;
        }
        
        if( m_pCurrentData )
        {
            char *newbuffer = m_pCurrentData;
            m_pCurrentData = m_pCurrentData + size;
            m_iAmountWritten += size;
            m_iCurrentPos += size;
            return newbuffer;
        }
        else
            return NULL;
        
    }
    
    /**
     * Closes the currently open block/
     */
    void DataBuffer::EndWritting(void)
    {
        if( m_bWritting == true )
        {
            m_pBlocks[m_iCurrent_Block].size = m_iAmountWritten;
            m_iAmountWritten = 0;
            m_bWritting = false;
            m_iCurrent_Block++;
        }
    }
    
    /**
     * Creates a new block by name, returns a pointer to it.
     * @param pName The name of the block to create.
     * @param size The size to assign to the block.
     */
    DataBuffer::data_block *DataBuffer::CreateBlock(const char *pName,
                                                    unsigned int size)
    {
        // Alloc more space if needed.
        if( !m_pBlocks || ( m_iNum_Blocks == m_iCurrent_Block ) )
        {
            if( !ResizeBlockData( (m_iNum_Blocks + m_iBlockGrowSize) ) )
                return NULL;
        }
        
        // Create Block for Data Mapping.
        data_block block;
        strncpy( block.name, pName, MAX_DATA_BLOCK_NAME );
        block.offset = m_iCurrentPos;
        block.size = size;
        memcpy( &m_pBlocks[m_iCurrent_Block], &block, sizeof( data_block ) );
        
        return &m_pBlocks[m_iCurrent_Block];
    }
    
} // DataPacking