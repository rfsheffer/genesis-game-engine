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
    
    // little-endian "GECF" (Genesis Engine Chunk File)
#define BUFFER_HEADER			(('F'<<24)+('C'<<16)+('E'<<8)+'G')
    
    // Version for chunk pools saved in files
#define BUFFER_FILE_VERSION		1
    
    // Max name for data blocks
#define MAX_DATA_BLOCK_NAME		16
    
    struct data_block
    {
        char name[MAX_DATA_BLOCK_NAME];
        int size;
        int offset;
    };
    
    // Used for file saving.
    struct buffer_header_t
    {
        int id;
        short version;
        int Num_Blocks;
        int	BufferSize;
    };
    
    enum buffer_error
    {
        OKAY = 0,
        INIT_ERROR
    };
    
    
    class DataBuffer
    {
    public:
        
        DataBuffer(unsigned int buffer_size = 0, unsigned int num_blocks = 0);
        DataBuffer();
        
        /** Sets the rate of block growth when new blocks are needed. */
        inline void SetBlockGrowth(unsigned int size)
        {
            if(size > 1)
                m_iBlockGrowSize = size;
        }
        
        bool        WriteBlock(const char *pName, const char *pBuffer, unsigned int size);
        bool        StartWritting(const char *pName);
        bool        WriteBuffer(const char *pBuffer, unsigned int size);
        char        *CreateBuffer(unsigned int size);
        void        EndWritting(void);
        bool        ResizeBlockData(unsigned int newsize);
        bool        ResizeBufferData(unsigned int newsize);
        bool        SetBufferPos(unsigned int position);
        
        /** A pointer to the start of the block data */
        data_block  *m_pBlocks;
        
        /** The number of blocks currently created */
        int         m_iNum_Blocks;
        
        /** The current block we are allowed to work with */
        int         m_iCurrent_Block;
        
        /** Pointer to start of data buffer. */
        char        *m_pBaseData;
        
        /** Pointer to current position in data buffer. */
        char		*m_pCurrentData;
        
        /** Distance in bytes to current position, also the buffers
         current size( m_iBufferSize - m_iCurrentPos ). */
        int			 m_iCurrentPos;
        
        /** Total allocated memory for this buffer in bytes. */
        int			 m_iBufferSize;
        
        /** Gets the current error level set by the buffer */
        int GetError(void)
        {
            int error = m_iError;
            m_iError = 0;
            return error;
        }
        
    private:
        
        /** The error level */
        int m_iError;
        
        data_block *CreateBlock(const char *pName, unsigned int size = 0);
        
        /** Block grow size */
        int m_iBlockGrowSize;
        
        // Used durring the writting process.
        bool m_bWritting;		// Writting.
        int m_iAmountWritten;	// In bytes written.
        int m_pWrittingblock;	// Current block being written to.
    };
    
} // DataPacking

#endif