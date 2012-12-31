//
//  entity_dictionary.h
//  Used for mapping names to class names for entity creation
//
//  Created by Ryan Sheffer on 2012-12-31.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef ENTITY_DICTIONARY_H
#define ENTITY_DICTIONARY_H

#ifdef _WIN
#pragma once
#endif

#include "ent_base.h"

// Easy way of getting basename, classname.
#define DECLARE_CLASS( className, baseClassName ) \
typedef className ThisClass; \
typedef baseClassName BaseClass;

#define DECLARE_CLASS_NO_BASE( className ) \
typedef className ThisClass;

class CEntityFactoryDictionary;
CEntityFactoryDictionary *EntityFactoryDictionary();

//-----------------------------------------------------------------------------
// Entity factory
//-----------------------------------------------------------------------------
class IEntityFactory
{
public:
	virtual baseentity *Create( void ) = 0;
	virtual size_t GetEntitySize() = 0;
};

template <class T>
class CEntityFactory : public IEntityFactory
{
public:
    
	CEntityFactory( const char *pEntityName )
	{
		EntityFactoryDictionary()->InstallFactory( this, pEntityName );
	}
    
	T *Create( void )
	{
        // TODO: Get memory from the memory pools
		T* pEnt = new T;
		return pEnt;
	}
    
	virtual size_t GetEntitySize()
	{
		return sizeof(T);
	}
};

#define LINK_ENTITY_TO_CLASS( EntityName, ClassName ) \
static CEntityFactory<ClassName> EntityName##_Factory( #EntityName );

#define CREATE_ENTITY_BY_NAME( ClassName ) EntityFactoryDictionary()->Create( ClassName );

//-----------------------------------------------------------------------------
// Entity creation factory
//-----------------------------------------------------------------------------
class CEntityFactoryDictionary
{
public:
	CEntityFactoryDictionary(){}
    
	~CEntityFactoryDictionary()
	{
		// Clear out the chars we alloced for the names.
		map<char*, IEntityFactory*>::iterator it;
		it = m_Factories.begin();
		while( it != m_Factories.end() )
		{
			free( (*it).first );
			it = m_Factories.erase( it );
		}
        
		m_Factories.clear();
	}
    
	void InstallFactory( IEntityFactory *pFactory, const char *pClassName )
	{
		if( pFactory && pClassName )
		{
			int classname_len = strlen( pClassName );
			char *pClassNameCpy = (char*)malloc(classname_len+1); pClassNameCpy[classname_len] = 0;
			strncpy( pClassNameCpy, pClassName, classname_len );
			m_Factories.insert( pair<char*, IEntityFactory*>(pClassNameCpy, pFactory) );
		}
	}
    
	IEntityFactory *FindFactory( const char *pClassName )
	{
		map<char*, IEntityFactory*>::iterator it;
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
		return NULL;
	}
    
	virtual CEntityBase *Create( const char *pClassName )
	{
		IEntityFactory *pFactory = FindFactory( pClassName );
		if( pFactory )
			return pFactory->Create();
		
		return NULL;
	}
    
private:
    
	map<char*, IEntityFactory*> m_Factories;
};

//-----------------------------------------------------------------------------
// Singleton accessor
//-----------------------------------------------------------------------------
inline CEntityFactoryDictionary *EntityFactoryDictionary()
{
	static CEntityFactoryDictionary s_EntityFactory;
	return &s_EntityFactory;
}

#endif // ENTITY_DICTIONARY_H
