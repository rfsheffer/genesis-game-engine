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

class CEntityFactoryDictionary;
CEntityFactoryDictionary *EntityFactoryDictionary();

/**
 * Forward declarations of important functions used in the entity creation
 * process. Create these in your entity manager.
 */
unsigned int    RegisterSharedEntity(CEntityBase *pEnt);
unsigned int    RegisterLocalEntity(CEntityBase *pEnt);

/**
 * Base Entity Factory Template
 */
class IEntityFactory
{
public:
	virtual CEntityBase *Create(void) = 0;
	virtual size_t GetEntitySize(void) = 0;
    
protected:
    
    friend class CEntityFactoryDictionary;
    
    void InitializeEntity(CEntityBase *pEnt, bool bRegister, bool bShared)
    {
        pEnt->m_pszClassName = pszClassname;
        
        if(bRegister)
        {
            if(bShared)
            {
                pEnt->m_iEntIndex = RegisterSharedEntity(pEnt);
            }
            else
            {
                pEnt->m_iEntIndex = RegisterLocalEntity(pEnt);
            }
        }
    }
    
    const char *pszClassname;
};

/**
 * The entity dictionary itself
 */
class CEntityFactoryDictionary
{
public:
    
	~CEntityFactoryDictionary()
	{
		// Clear out the chars we alloced for the names.
//		std::map<const char*, IEntityFactory*>::iterator it;
//		it = m_Factories.begin();
//		while( it != m_Factories.end() )
//		{
//			free( (*it).first );
//			it = m_Factories.erase( it );
//		}
        
		m_Factories.clear();
	}
    
    /**
     * Installs a new factory. Ensure that pClassName is a string table pointer.
     */
	void InstallFactory(IEntityFactory *pFactory, const char *pClassName)
	{
		if(pFactory && pClassName)
		{
			//size_t classname_len = strlen(pClassName);
			//char *pClassNameCpy = (char*)malloc(classname_len+1); pClassNameCpy[classname_len] = 0;
			//strncpy( pClassNameCpy, pClassName, classname_len );
            
#ifdef _DEBUG
            ASSERTION(FindFactory(pClassName) == NULL,
                      "Entity Factory: Duplicate entity entry!");
#endif
            
			m_Factories.insert( std::pair<const char*, IEntityFactory*>(pClassName, pFactory) );
		}
	}
    
    /**
     * Finds a factory by entity class name
     */
	IEntityFactory *FindFactory(const char *pClassName)
	{
		std::map<const char*, IEntityFactory*>::iterator it;
		it = m_Factories.begin();
		while(it != m_Factories.end())
		{
			if((*it).first)
			{
				if(!strncasecmp((*it).first, pClassName, strlen( (*it).first)))
				{
					return (*it).second;
				}
			}
			it++;
		}
		return NULL;
	}
    
    /**
     * Creates an entity by classname
     */
	CEntityBase *Create(const char *pClassName, bool bRegister, bool bShared)
	{
        IEntityFactory *pFactory = FindFactory(pClassName);
		if(pFactory)
		{
            CEntityBase *pNewEnt = pFactory->Create();
            if(pNewEnt)
            {
                pFactory->InitializeEntity(pNewEnt, bRegister, bShared);
                return pNewEnt;
            }
        }
		
		return NULL;
	}
    
private:
    
	std::map<const char*, IEntityFactory*> m_Factories;
    
    // Only the entity factories getter function can create us.
    friend CEntityFactoryDictionary *EntityFactoryDictionary(void);
    CEntityFactoryDictionary(){}
};

/**
 * The entity factory for creating an entity.
 */
template <class T>
class CEntityFactory : public IEntityFactory
{
public:
    
	CEntityFactory(const char *pEntityName)
	{
        pszClassname = pEntityName;
		EntityFactoryDictionary()->InstallFactory(this, pEntityName);
	}
    
    /**
     * Creates the entity from the template
     */
	T *Create(void)
	{
        // TODO: Get memory from the memory pools
		T* pEnt = new T;        
		return pEnt;
	}
    
    /**
     * Gets the size of this entity.
     */
	virtual size_t GetEntitySize(void)
	{
		return sizeof(T);
	}
};

#define LINK_ENTITY_TO_CLASS(EntityName, ClassName) \
    static CEntityFactory<ClassName> EntityName##_Factory(#EntityName);

#define CREATE_SHARED_ENTITY_BY_NAME(ClassName) \
    EntityFactoryDictionary()->Create(ClassName, true, true);

#define CREATE_LOCAL_ENTITY_BY_NAME(ClassName) \
    EntityFactoryDictionary()->Create(ClassName, true, false);

/**
 * Singleton entity factory accessor
 */
inline CEntityFactoryDictionary *EntityFactoryDictionary(void)
{
	static CEntityFactoryDictionary s_EntityFactory;
	return &s_EntityFactory;
}

#endif // ENTITY_DICTIONARY_H
