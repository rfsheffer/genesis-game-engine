//========= Copyright © 2012, Ryan Sheffer, All rights reserved. ============//
//
// Purpose: Component Factory
//
//==========================================================================//

#ifndef COMPONENT_FACTORY_H
#define COMPONENT_FACTORY_H

#include <map>

class CComponentFactoryDictionary;
CComponentFactoryDictionary *ComponentFactoryDictionary();

using namespace std;

//-----------------------------------------------------------------------------
// Component factory
//-----------------------------------------------------------------------------
class IComponentFactory
{
public:
	virtual CComponent *Create(void) = 0;
	virtual size_t GetComponentSize() = 0;

	virtual void SetComponentMemoryPool(unsigned int pool) = 0;
};

template <class T>
class CComponentFactory : public IComponentFactory
{
public:

	CComponentFactory( const char *pComponentName )
	{
		ComponentFactoryDictionary()->InstallFactory( this, pComponentName );
		m_uiMemoryPoolIndex = -1;
	}

	T *Create( void )
	{
		T* pComponent = MemPool::ALLOC_TYPE_POOL_MEM(T, m_uiMemoryPoolIndex);
		return pComponent;
	}

	virtual size_t GetComponentSize()
	{
		return sizeof(T);
	}

	virtual void SetComponentMemoryPool(unsigned int pool)
	{
		m_uiMemoryPoolIndex = pool;
	}

	// This is the index of the memory pool for fast lookup.
	unsigned int		m_uiMemoryPoolIndex;
};

#define LINK_COMPONENT_TO_CLASS( ComponentName, ClassName ) \
	static CComponentFactory<ClassName> ComponentName##_Factory( #ComponentName );

#define CREATE_COMPONENT_BY_NAME( ClassName ) ComponentFactoryDictionary()->Create( ClassName );
#define DESTROY_COMPONENT( pComponent ) ComponentFactoryDictionary()->Destroy( pComponent )

//-----------------------------------------------------------------------------
// Component creation factory
//-----------------------------------------------------------------------------
class CComponentFactoryDictionary
{
public:
	CComponentFactoryDictionary(){}

	~CComponentFactoryDictionary()
	{
		// Clear out the chars we alloced for the names.
		map<char*, IComponentFactory*>::iterator it;
		it = m_Factories.begin();
		while( it != m_Factories.end() )
		{
			free( (*it).first );
			it = m_Factories.erase( it );
		}

		m_Factories.clear();
	}

	void InstallFactory( IComponentFactory *pFactory, const char *pClassName ) 
	{ 
		if( pFactory && pClassName )
		{
			int classname_len = strlen( pClassName );
			char *pClassNameCpy = (char*)malloc(classname_len+1); pClassNameCpy[classname_len] = 0;
			strncpy_s( pClassNameCpy, classname_len+1, pClassName, classname_len );
			m_Factories.insert( pair<char*, IComponentFactory*>(pClassNameCpy, pFactory) );
		}
	}

	IComponentFactory *FindFactory( const char *pClassName )
	{
		map<char*, IComponentFactory*>::iterator it;
		it = m_Factories.begin();
		while( it != m_Factories.end() )
		{
			if( (*it).first )
			{
				if( !_strnicmp( (*it).first, pClassName, strlen( (*it).first ) ) )
				{
					return (*it).second;
				}
			}
			it++;
		}

		// Doesn't work :(
		/*it = m_Factories.find(pClassName);
		if(it != m_Factories.end())
		{
			return (*it).second;
		}*/

		return NULL;
	}

	virtual CComponent *Create( const char *pClassName )
	{
		IComponentFactory *pFactory = FindFactory( pClassName );
		if( pFactory )
		{
			CComponent *pComponent = pFactory->Create();
			if(pComponent)
			{
				strncpy_s(pComponent->m_szName, MAX_COMPONENT_NAME, pClassName, MAX_COMPONENT_NAME - 1);
				return pComponent;
			}
		}

		return NULL;
	}

	virtual void Destroy(CComponent *pComponent)
	{
		if(pComponent)
			MemPool::FREE_TYPE_ALLOC(CComponent, pComponent);
	}

	virtual void SetupComponentMemoryPools(void)
	{
		map<char*, IComponentFactory*>::iterator it;
		it = m_Factories.begin();
		while( it != m_Factories.end() )
		{
			if( (*it).first )
			{
				(*it).second->SetComponentMemoryPool(MemPool::g_memoryPool.CreatePool((*it).first, 2048));
			}
			it++;
		}
	}

private:

	map<char*, IComponentFactory*> m_Factories;
};

//-----------------------------------------------------------------------------
// Singleton accessor
//-----------------------------------------------------------------------------
inline CComponentFactoryDictionary *ComponentFactoryDictionary()
{
	static CComponentFactoryDictionary s_ComponentFactory;
	return &s_ComponentFactory;
}

#endif // COMPONENT_FACTORY_H