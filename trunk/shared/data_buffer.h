//
//  data_buffer.h
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

class data_buffer
{
public:

	data_buffer( int buffer_size = 0, int num_blocks = 0 );
	~data_buffer();


	void SetBlockGrowth( int size )
	{
		if( size > 1 )
			m_iBlockGrowSize = size;
	}

	// Write
	bool WriteBlock( const char *pBuffer, const char *pName, int size );	//Writes a buffer and creates a datablock.

	// On the Fly Buffering.
	bool StartWritting( const char *pName );					// Starts a data block.
	bool WriteBuffer( const char *pBuffer, int size );			// Writes to data buffer of current block.
	char *CreateBuffer( int size );								// Creates a buffer to be written too.
	void EndWritting( void );									// Ends block.

	// Block Functions
	bool ResizeBlockData( int newsize );

	// Buffer Functions
	bool ResizeBufferData( int newsize );
	bool SetBufferPos( int position );

	//---------------------------------
	// Block data
	// A list of objects from start to end, the mapping of the data stored in m_pBaseData;
	//---------------------------------
	data_block *m_pBlocks;
	int m_iNum_Blocks;
	int m_iCurrent_Block;

	//---------------------------------
	// Buffer data
	//---------------------------------
	char		*m_pBaseData;		// Pointer to start of data buffer.
	char		*m_pCurrentData;	// Pointer to current position in data buffer.
	int			 m_iCurrentPos;		// Distance in bytes to current position, also the buffers current size( m_iBufferSize - m_iCurrentPos ).
	int			 m_iBufferSize;		// Total allocated memory for this buffer in bytes.

	int GetError( void )
	{
		int error = m_iError;
		m_iError = 0;
		return error;
	}

private:

	int m_iError;

	data_block *CreateBlock( const char *pName, int size = 0 );

	int m_iBlockGrowSize;

	// Used durring the writting process.
	bool m_bWritting;		// Writting.
	int m_iAmountWritten;	// In bytes written.
	int m_pWrittingblock;	// Current block being written to.
};

#endif