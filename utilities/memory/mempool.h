//
//  util_mempool.h
//  An object for storing raw memory.
//
//  Created by Ryan Sheffer on 2012-12-20.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef UTIL_MEMPOOL_H
#define UTIL_MEMPOOL_H

// Namespace encompassing the memory pool system
namespace Memory
{
    
    // This is the size of the general pool which is created at the start.
#define GENERAL_POOL_SIZE	134217728 // 2^27 = approx 128mb
#define GENERAL_POOL_INDEX	0 // Don't change this, it's always 0...
#define GENERAL_POOL_NAME	"General Pool"
    
#define NUM_MEM_INFO_BITS		2
#define MEM_INFO_INUSE_BIT		0x01	// Set to 1 if this memory is used (has not been freed)
#define MEM_INFO_LOCKED_BIT		0x02	// Set to 1 if this memory is locked
    
#define MAX_POOL_NAME			32
#define MAX_DEBUG_FILE_NAME		256
    
    struct debug_alloc_info
    {
        int line;
        char file[MAX_DEBUG_FILE_NAME];
    };
    
    struct mem_pool_info
    {
        // The name assigned to this pool
        char			m_szPoolName[MAX_POOL_NAME];
        
        // This is the start of the memory pool in memory
        //void			*m_PoolStart;
        
        // Number of bytes in which this pool start
        unsigned int	m_iPoolStart;
        
        // This is the current position in bytes from m_PoolStart to write new memory.
        unsigned int	m_iCurWritePos;
        
        // Number total allocated bytes in this pool
        unsigned int	m_numBytes;
        
#ifdef _DEBUG
        // Debug allocation information
        std::vector<debug_alloc_info> m_debugInfo;
#endif
    };
    
    // Main memory pool class
    class MemoryPool
    {
    public:
        MemoryPool();
        ~MemoryPool();
        
        // Creation of pools
        unsigned int 	CreatePool(const char *pName, unsigned int size);
        void			ClearPool(unsigned int pool);
        unsigned int	PoolIndexByName(const char *pName) const;
        unsigned int	GetNumberOfPools(void) const
        {
            return (unsigned int)m_PoolInfo.size();
        }
        
        void		*MemAlloc(unsigned int bytes,
                              unsigned int pool,
                              const char *file,
                              int line);
        
        bool		FreeAlloc(void *pMem);
        
        bool		IsPoolAlloc(void *pMem) const;
        
        // Memory Locking
        void		LockAlloc(void *pMem);
        void		UnlockAlloc(void *pMem);
        bool		IsAllocLocked(void *pMem) const;
        
        void		DumpMemory(void) const;
        
    private:
        
        // Number total allocated bytes in this pool
        unsigned int			m_numBytes;
        
        // This is a pointer to the start of the memory pool
        void			*m_Pool;
        
        // This is the info for each pool stored in m_Pool. The order is the same as the memory order.
        std::vector<mem_pool_info> m_PoolInfo;
    };
    
    extern MemoryPool g_memoryPool;
    
    // Allocate specific pool memory
#define ALLOC_POOL_MEM(bytes, pool) g_memoryPool.MemAlloc(bytes, pool, __FILE__, __LINE__)
    
    // Allocate general memory
#define ALLOC_MEM(bytes) g_memoryPool.MemAlloc(bytes, GENERAL_POOL_INDEX, __FILE__, __LINE__)
    
    // Free a memory allocation
#define FREE_ALLOC(pAlloc) g_memoryPool.FreeAlloc(pAlloc)
    
    // Locks an allocation so it cannot be freed
#define LOCK_ALLOC(pAlloc) g_memoryPool.LockAlloc(pAlloc)
    
    // Unlocks an allocation
#define UNLOCK_ALLOC(pAlloc) g_memoryPool.UnlockAlloc(pAlloc)
    
    // Returns true if the allocation is locked
#define IS_ALLOC_LOCKED(pAlloc) g_memoryPool.IsAllocLocked(pAlloc)
    
#define IS_POOL_MEMORY(pAlloc) g_memoryPool.IsPoolAlloc(pAlloc)
    
    template<typename T>
    T *allocTypeMem(unsigned int pool, const char *file, int line)
    {
        T *pMem = (T *)g_memoryPool.MemAlloc(sizeof(T), pool, file, line);
        
        if(pMem)
        {
            new(pMem) T();
        }
        
        return pMem;
    }
    
    template<typename T>
    bool freeTypeMem(void *pMem)
    {
        if(!pMem)
            return false;
        
        T *pClass = (T *)pMem;
        pClass->~T();
        
        return g_memoryPool.FreeAlloc(pMem);
    }
    
    // Class memory pool allocation. Placement new included.
#define ALLOC_TYPE_POOL_MEM(className, pool) allocTypeMem<className>(pool, __FILE__, __LINE__)
#define ALLOC_TYPE_MEM(className) allocTypeMem<className>(GENERAL_POOL_INDEX, __FILE__, __LINE__)
    
    // Frees class and calls destructor
#define FREE_TYPE_ALLOC(className, pAlloc) freeTypeMem<className>(pAlloc)
    
} // Namespace MemPool

#endif // UTIL_MEMPOOL_H