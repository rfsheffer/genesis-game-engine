//
//  util_mempool.cpp
//  An object for storing raw memory.
//
//  Created by Ryan Sheffer on 2012-12-20.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#include "util_mempool.h"

using namespace MemPool;

namespace MemPool
{
	MemoryPool g_memoryPool;
}

// This macro is only for in MemoryPool methods!
#define IS_IN_POOL(pMem) ((((byte *)pMem - sizeof(unsigned int)) >= m_Pool) && (pMem < ((byte*)m_Pool + m_numBytes)))

//-----------------------------------------------------------------------------
// Purpose: Sets up the Pool
//-----------------------------------------------------------------------------
MemoryPool::MemoryPool()
{
	// Determine the number of bytes to alloc for the whole pool
	m_numBytes = 0;
	m_Pool = NULL;

	// Create the general memory pool first
	CreatePool(GENERAL_POOL_NAME, GENERAL_POOL_SIZE);
}

//-----------------------------------------------------------------------------
// Purpose: De-allocates the pools memory, house keeping
//-----------------------------------------------------------------------------
MemoryPool::~MemoryPool()
{
	// In debug, print how many bytes were not freed
#ifdef _DEBUG

	unsigned int curDebugInfo = 0;
	for(unsigned int i = 0; i < m_PoolInfo.size(); i++)
	{
		mem_pool_info &PoolInfo = m_PoolInfo[i];

		if(PoolInfo.m_debugInfo.size() == 0)
			continue;

		byte *pChunk = (byte *)m_Pool + PoolInfo.m_iPoolStart;
		//byte *poolEnd = (byte *)m_PoolStarts[i] + g_pool_sizes[i];

		while(curDebugInfo < PoolInfo.m_debugInfo.size())
		{
			unsigned int *pInfo = (unsigned int *)pChunk;
			unsigned int bytes = *pInfo >> NUM_MEM_INFO_BITS;

			if((*pInfo & MEM_INFO_INUSE_BIT))
			{
				char buf[256];

				sprintf(buf, "Memory Not Freed: Pool %d, alloc of %d bytes in %s at %d!\n",
                          i + 1,
                          bytes,
                          PoolInfo.m_debugInfo[curDebugInfo].file,
                          PoolInfo.m_debugInfo[curDebugInfo].line);
                
				//OutputDebugString(buf);
			}

			unsigned int movement = (bytes + sizeof(unsigned int));

			pChunk += movement;

			curDebugInfo++;
		}

		curDebugInfo = 0;
	}
#endif

	free(m_Pool);
}

//-----------------------------------------------------------------------------
// Purpose: Creates a new pool on the end of the master pool
// Return: The index of the pool
// NOTE: This is expensive and should only be called at load time
//-----------------------------------------------------------------------------
unsigned int MemoryPool::CreatePool(const char *pName, unsigned int size)
{
	// See if the pool already exists
	unsigned int searchIndex = PoolIndexByName(pName);
	if(searchIndex < m_PoolInfo.size())
		return searchIndex;

	// Create a new pool
	m_PoolInfo.push_back(mem_pool_info());

	mem_pool_info &newPool = m_PoolInfo[m_PoolInfo.size() - 1];

	// General Setup
	strncpy( newPool.m_szPoolName, pName, MAX_POOL_NAME );
	newPool.m_numBytes = size;
	newPool.m_iCurWritePos = 0;

	// Resize the master
	void *pNewPool = realloc(m_Pool, m_numBytes + size);
	if(pNewPool == NULL)
	{
		m_PoolInfo.pop_back();
		return -1;
	}

	// Set the pool to the new memory block
	m_Pool = pNewPool;

	// Setup the start position for the new block in the pool
	newPool.m_iPoolStart = m_numBytes;

#ifdef _DEBUG
	// In debug clear out the new bytes
	memset((byte *)m_Pool + newPool.m_iPoolStart, 0, newPool.m_numBytes);
#endif

	// Increment the master pool byte count
	m_numBytes += size;

	return (unsigned int)m_PoolInfo.size() - 1;
}

//-----------------------------------------------------------------------------
// Purpose: Clear a pool of all memory
//-----------------------------------------------------------------------------
void MemoryPool::ClearPool(unsigned int pool)
{
	if(pool >= m_PoolInfo.size())
		return;

	m_PoolInfo[pool].m_iCurWritePos = 0;

#ifdef _DEBUG
	// Pool is cleared completely in debug
	memset((byte *)m_Pool + m_PoolInfo[pool].m_iPoolStart, 0, m_PoolInfo[pool].m_numBytes);
	m_PoolInfo[pool].m_debugInfo.clear();
#endif
}

//-----------------------------------------------------------------------------
// Purpose: Finds a pool by name and returns its pool index
//-----------------------------------------------------------------------------
unsigned int MemoryPool::PoolIndexByName(const char *pName)
{
	if(!pName)
		return -1;

	for(unsigned int i = 0; i < m_PoolInfo.size(); i++)
	{
		if(!strncmp(m_PoolInfo[i].m_szPoolName, pName, MAX_POOL_NAME))
			return i;
	}

	return -1;
}

//-----------------------------------------------------------------------------
// Purpose: Allocates new memory
//-----------------------------------------------------------------------------
void *MemoryPool::MemAlloc(unsigned int bytes, unsigned int pool, const char *file, int line)
{
	if(bytes == 0 || pool >= m_PoolInfo.size())
		return NULL;

	unsigned int alloc_size = bytes + sizeof(unsigned int);

	mem_pool_info &PoolInfo = m_PoolInfo[pool];

	// See if we have enough space
	if((PoolInfo.m_iCurWritePos + alloc_size) >= PoolInfo.m_numBytes)
		return NULL;

	unsigned int *pAlloc = (unsigned int *)((byte *)m_Pool + PoolInfo.m_iPoolStart + PoolInfo.m_iCurWritePos);
	*pAlloc = (bytes << NUM_MEM_INFO_BITS) | MEM_INFO_INUSE_BIT; // Squish in the size and the info bits

	PoolInfo.m_iCurWritePos += alloc_size;

#ifdef _DEBUG
	// Extended information is saved off in debug mode for leak detection
	debug_alloc_info debuginfo;
	strncpy(debuginfo.file, file, MAX_DEBUG_FILE_NAME);
	debuginfo.line = line;
	PoolInfo.m_debugInfo.push_back(debuginfo);
#endif

	return ((byte *)pAlloc) + sizeof(unsigned int);
}

//-----------------------------------------------------------------------------
// Purpose: Free memory stored in the pool
//-----------------------------------------------------------------------------
bool MemoryPool::FreeAlloc(void *pMem)
{
	if(!IS_IN_POOL(pMem))
		return false;

	unsigned int *pInfo = (unsigned int *)((byte *)pMem - sizeof(unsigned int));

	// Don't allow locked memory to be freed
	if(*pInfo & MEM_INFO_LOCKED_BIT)
		return false;

	*pInfo = *pInfo & ~MEM_INFO_INUSE_BIT;

#ifdef _DEBUG
	// In debug memory is zero'd
	unsigned int size = (*pInfo >> NUM_MEM_INFO_BITS);

	byte *pMemory = (byte *)pMem;
	for(unsigned int i = 0; i < size; i++)
	{
		pMemory[i] = 0;
	}
#endif

	return true;
}

//-----------------------------------------------------------------------------
// Purpose: Returns true if this memory is within the memory pool
//-----------------------------------------------------------------------------
bool MemoryPool::IsPoolAlloc(void *pMem)
{
	if(!IS_IN_POOL(pMem))
		return false;

	// If the memory is freed already return false
	unsigned int *pInfo = (unsigned int *)((byte *)pMem - sizeof(unsigned int));
	if(!(*pInfo & MEM_INFO_INUSE_BIT))
		return false;

	return true;
}

//-----------------------------------------------------------------------------
// Purpose: Locks an allocation
//-----------------------------------------------------------------------------
void MemoryPool::LockAlloc(void *pMem)
{
	if(!IS_IN_POOL(pMem))
		return;

	unsigned int *pInfo = (unsigned int *)((byte *)pMem - sizeof(unsigned int));

	*pInfo = (*pInfo | MEM_INFO_LOCKED_BIT);
}

//-----------------------------------------------------------------------------
// Purpose: Unlocks an allocation
//-----------------------------------------------------------------------------
void MemoryPool::UnlockAlloc(void *pMem)
{
	if(!IS_IN_POOL(pMem))
		return;

	unsigned int *pInfo = (unsigned int *)((byte *)pMem - sizeof(unsigned int));

	*pInfo = *pInfo & ~MEM_INFO_LOCKED_BIT;
}

//-----------------------------------------------------------------------------
// Purpose: Locks an allocation
//-----------------------------------------------------------------------------
bool MemoryPool::IsAllocLocked(void *pMem)
{
	if(!IS_IN_POOL(pMem))
		return false;

	unsigned int *pInfo = (unsigned int *)((byte *)pMem - sizeof(unsigned int));

	return (*pInfo & MEM_INFO_LOCKED_BIT)?true:false;
}

//-----------------------------------------------------------------------------
// Purpose: Dumps all memory to a file
//-----------------------------------------------------------------------------
void MemoryPool::DumpMemory(void)
{
    // TODO: Run this through the file system
	FILE *pFile = NULL;
#if _MAC
    pFile = fopen("memdump.txt", "wb");
#else
    fopen_s(&pFile, "memdump.txt", "wb");
#endif
	if(!pFile)
		return;

	for(unsigned int i = 0; i < m_PoolInfo.size(); i++)
	{
		byte *pMemory = (byte *)m_Pool + m_PoolInfo[i].m_iPoolStart;
		fprintf(pFile, "\nMemory Pool %d\n", i);
		for(unsigned int j = 0; j < m_PoolInfo[i].m_numBytes; j++)
		{
			fprintf(pFile, "%c", *pMemory);
			++pMemory;
		}
	}

	fclose(pFile);
}