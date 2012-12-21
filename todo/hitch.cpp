#include "stdafx.h"

#include "test_entity.h"

/*HANDLE hMutex;

int num = 0;

void Thread( void* pParams )
{
	while(1)
	{
		WaitForSingleObject( hMutex, INFINITE );
		num++;
		ReleaseMutex( hMutex );
	}
}

int main( void )
{
	hMutex = CreateMutex( NULL, FALSE, NULL );
	_beginthread( Thread, 0, NULL );

	while(1)
	{
		WaitForSingleObject( hMutex, INFINITE );
		printf("%d\n", num);
		ReleaseMutex( hMutex );
	}

	return 0;
}*/

class holyTest
{
public:
	short a;
	int b;
	long c;

	holyTest()
	{
		OutputDebugString("holyTest created!\n");
	}

	~holyTest()
	{
		OutputDebugString("holyTest destroyed!\n");
	}

	void testtest()
	{
		c = b = a = 20;
	}
};

#define ENTITY_POOL_SIZE	16777216 // 16mb	

int main(void)
{
	// Setup Entity Memory Pool
	MemPool::g_memoryPool.CreatePool("Entities", ENTITY_POOL_SIZE);

	// Setup Component Memory Pools
	ComponentFactoryDictionary()->SetupComponentMemoryPools();

	// Create test entity
	CTestEntity *pTestEntity = MemPool::ALLOC_TYPE_POOL_MEM(CTestEntity, MemPool::g_memoryPool.PoolIndexByName("Entities"));
	if(!pTestEntity)
		return 1;

	pTestEntity->CreateComponents();

	// TODO: Setup component threads

	// Run Components

	pTestEntity->DestroyComponents();

	MemPool::FREE_TYPE_ALLOC(CTestEntity, pTestEntity);

	return 0;
}