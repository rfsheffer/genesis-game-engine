//
//  data_pack.h
//  A Buffer for storing any data.
//
//  Created by Ryan Sheffer on 17-07-10.
//  Copyright 2010 Ryan Sheffer. All rights reserved.
//

#ifndef DATA_BUFFER_H
#define DATA_BUFFER_H

#ifdef _WIN32
#pragma once
#endif

namespace DataPacking
{
    /** A class used to map and buffer data. */
    class UTILITIES_CLASS DataBuffer
    {
    public:
        
        DataBuffer(const DataBuffer *pToCopy);
        DataBuffer(unsigned int buffer_size = 0, unsigned int num_blocks = 0);
        ~DataBuffer();
        
        DataBuffer& operator= (const DataBuffer &cSource);
        
        /** Sets the rate of block growth when new blocks are needed. */
        inline void SetBlockGrowth(unsigned int size)
        {
            ASSERTION(size >= 1, "Invalid block growth size!");
            if(size >= 1)
            {
                m_uiBlockGrowSize = size;
            }
        }
        
        /** Gets the block growth rate. */
        inline unsigned int GetBlockGrowth(void) const { return m_uiBlockGrowSize; }
        
        bool        WriteBlock(const char *pName, const byte *pBuffer, unsigned int size);
        bool        StartWritting(const char *pName);
        bool        WriteBuffer(const byte *pBuffer, unsigned int size);
        byte        *CreateBuffer(unsigned int size);
        void        EndWritting(void);
        bool        ResizeBlockData(unsigned int newsize);
        bool        ResizeBufferData(unsigned int newsize);
        bool        SetBufferPos(unsigned int position);
        
        byte        *ReadFromBlock(unsigned int blockIndex, unsigned int offset);
        
        // Max name for data blocks
#define MAX_DATA_BLOCK_NAME		16
        
        /** A data block header */
        struct data_block
        {
            char name[MAX_DATA_BLOCK_NAME];
            int size;
            int offset;
        };
        
        /** A pointer to the start of the block data */
        data_block  *m_pBlocks;
        
        /** The number of blocks currently created */
        unsigned int         m_uiNum_Blocks;
        
        /** The current block we are allowed to work with */
        unsigned int         m_uiCurrent_Block;
        
        /** Pointer to start of data buffer. */
        byte        *m_pBaseData;
        
        /** Pointer to current position in data buffer. */
        byte		*m_pCurrentData;
        
        /** Distance in bytes to current position, also the buffers
         current size( m_iBufferSize - m_iCurrentPos ). */
        unsigned int			 m_uiCurrentPos;
        
        /** Total allocated memory for this buffer in bytes. */
        unsigned int			 m_uiBufferSize;
        
        /** Error IDs for data buffer errors */
        enum buffer_error
        {
            BUFFER_OKAY = 0,
            BUFFER_INIT_ERROR
        };
        
        /** Gets the current error level set by the buffer */
        buffer_error GetError(void)
        {
            buffer_error error = m_iError;
            m_iError = BUFFER_OKAY;
            return error;
        }
        
    private:
        
        /** The error level */
        buffer_error m_iError;
        
        data_block *CreateBlock(const char *pName, unsigned int size = 0);
        
        /** Block grow size */
        unsigned int m_uiBlockGrowSize;
        
        // Used durring the writting process.
        bool m_bWritting;		// Writting.
        unsigned int m_uiAmountWritten;	// In bytes written.
        //int m_pWrittingblock;	// Current block being written to.
        
        // No copy constructor or assignment
        DataBuffer(const DataBuffer &pCopy) { UNREFERENCED_PARAMETER(pCopy); }
    };
    
} // DataPacking

#endif