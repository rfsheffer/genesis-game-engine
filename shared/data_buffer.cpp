//
//  data_buffer.cpp
//  A Buffer for storing any data.
//
//  Created by Ryan Sheffer on 17-07-10.
//  Copyright 2010 Ryan Sheffer. All rights reserved.
//

#include "data_buffer.h"

//===================================================================
// Purpose: Data Buffer
//===================================================================
data_buffer::data_buffer( int buffer_size, int num_blocks )
{
	memset( this, 0, sizeof( *this ) );
	m_iBlockGrowSize = 1;

	if( buffer_size && !ResizeBufferData( buffer_size ) )
	{
		m_iError = 1;
	}

	if( num_blocks && !ResizeBlockData( num_blocks ) )
	{
		m_iError = 1;
	}
}

data_buffer::~data_buffer()
{
	if( m_pBaseData )
		free( m_pBaseData );

	if( m_pBlocks )
		free( m_pBlocks );
}

//===================================================================
// Purpose: Resize the BlockData
//===================================================================
bool data_buffer::ResizeBlockData( int newsize )
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

//===================================================================
// Purpose: Resize the Buffer
//===================================================================
bool data_buffer::ResizeBufferData( int newsize )
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

bool data_buffer::SetBufferPos( int position )
{
	if( position > m_iBufferSize )
		return false;

	m_pCurrentData = m_pBaseData + position;
	m_iCurrentPos = position;
	return true;
}

//===================================================================
// Purpose: Write a block and buffer combo!
//===================================================================
bool data_buffer::WriteBlock( const char *pBuffer, const char *pName, int size )
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

//===================================================================
// Purpose:
//===================================================================
bool data_buffer::StartWritting( const char *pName )
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

//===================================================================
// Purpose:
//===================================================================
bool data_buffer::WriteBuffer( const char *pBuffer, int size )
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

char *data_buffer::CreateBuffer( int size )
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

//===================================================================
// Purpose:
//===================================================================
void data_buffer::EndWritting( void )
{
	if( m_bWritting == true )
	{
		m_pBlocks[m_iCurrent_Block].size = m_iAmountWritten;
		m_iAmountWritten = 0;
		m_bWritting = false;
		m_iCurrent_Block++;
	}
}

//===================================================================
// Purpose:
//===================================================================
data_block *data_buffer::CreateBlock( const char *pName, int size )
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