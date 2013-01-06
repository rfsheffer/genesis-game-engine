//
//  data_structure.h
//  Methods for setting up a class with a map for reflection.
//  Usages: Changing data via variable names, saving and restoring data
//
//  Created by Ryan Sheffer on 10-07-10.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef DATA_MAPPING_H
#define DATA_MAPPING_H

#include "data_types.h"

// Easy way of getting basename, classname.
#define DECLARE_CLASS( className, baseClassName ) \
typedef className ThisClass; \
typedef baseClassName BaseClass;

#define DECLARE_CLASS_NO_BASE( className ) \
typedef className ThisClass;

//************
// Flags
//************
#define MAPOBJ_SAVED		1<<0		// Saved / Restored Object
#define MAPOBJ_NETWORKED    1<<1        // Networked SERVER->CLIENT object

//************
// Base Items
//************
#define _MAPOBJ( var_name, obj_type, count, flags ) \
{   obj_type, \
    #var_name, \
    offsetof(classNameTypedef, var_name), \
    count, \
    sizeof(((classNameTypedef *)NULL)->var_name), \
    flags, \
    0 \
}

//************
// Item Types
//************
// NULLOBJ : Blank object, no data.
#define DEFINE_NULLOBJ()  { DATA_VOID, 0, 0, 0, 0, 0, 0 },

// MAPOBJ ( Name of Variable, Object Type, Flags )
#define DEFINE_MAPOBJ( var_name, obj_type, flags ) \
                                _MAPOBJ( var_name, obj_type, 1, flags )

// MAPOBJ ARRAY ( Name of Variable, Object Type, Object Count, Flags )
#define DEFINE_MAPOBJ_ARRAY( var_name, obj_type, count, flags )	\
                                _MAPOBJ( var_name, obj_type, count, flags )

struct datamap_t;
struct objdesc_t;

//-----------------------------------------------------------------------------
// Purpose: Stored Objects description
// Note: Update _MAPOBJ etc if you change this.
//-----------------------------------------------------------------------------
struct objdesc_t
{
	// Object Information
	data_map_types		objType;			// Type of Data Stored.
	const char			*objname;			// Name of Stored Variable Offset
	size_t				objoffset;			// Offset to Object in Class or Struct
	size_t              numobjs;			// Number of Objects ( ex. Array of chars )
	size_t				objSize;			// Size of object in bytes.
	short				flags;				// Object Settings ( Saved, etc... )

	// Other Data
	datamap_t			*td;				// Owner
};


//-----------------------------------------------------------------------------
// Purpose: Stores of list of Objects ( Variable Mapping )
//-----------------------------------------------------------------------------
struct datamap_t
{
	objdesc_t			*objList;			// Objects and Descriptions.
	size_t				NumObjs;			// Number of Stored Objects.
	char const			*dataClassName;		// Class that is being mapped by this.
	datamap_t			*baseMap;			// Next Class in line, NULL if not a derived class.
};

//-----------------------------------------------------------------------------
// Macros used to implement data maps
//-----------------------------------------------------------------------------
#define	DECLARE_DATAMAP() \
	static datamap_t m_DataMap; \
	template <typename T> friend void DataMapAccess(T *ignored, datamap_t **p); \
	template <typename T> friend datamap_t *DataMapInit(T *); \
	virtual datamap_t *GetDataMap( void ){ return &m_DataMap; } \
	static datamap_t *GetBaseMap();

#define BEGIN_DATA_MAP( className ) \
	datamap_t *className::GetBaseMap() \
    { datamap_t *pResult; DataMapAccess((BaseClass *)NULL, &pResult); return pResult; } \
	DATA_MAP_CREATE( className )

#define BEGIN_DATA_MAP_NO_BASE( className ) \
	datamap_t *className::GetBaseMap(){ return NULL; } \
	DATA_MAP_CREATE( className )

#define DATA_MAP_CREATE( className ) \
	datamap_t className::m_DataMap = { 0, 0, #className, NULL }; \
	template <typename T> datamap_t *DataMapInit(T *); \
	template <> datamap_t *DataMapInit<className>(className *); \
	namespace className##_DataMapInit \
	{ \
		datamap_t *g_DataMapHolder = DataMapInit( (className *)NULL ); /*Create Data Map*/ \
	} \
	\
	template <> datamap_t *DataMapInit<className>(className *) \
	{ \
		typedef className classNameTypedef; \
		classNameTypedef::m_DataMap.baseMap = classNameTypedef::GetBaseMap(); \
		static objdesc_t objList[] = \
		{ \
		DEFINE_NULLOBJ() /*Create a null object so this list can exist without other members*/

#define END_DATA_MAP() \
		}; \
		\
		if ( sizeof( objList ) > sizeof( objList[0] ) ) \
		{ \
			classNameTypedef::m_DataMap.NumObjs = _ARRAYSIZE( objList ) - 1; \
			classNameTypedef::m_DataMap.objList 	  = &objList[1]; \
		} \
		else \
		{ \
			classNameTypedef::m_DataMap.NumObjs = 1; \
			classNameTypedef::m_DataMap.objList 	  = objList; \
		} \
		return &classNameTypedef::m_DataMap; \
	}

// Used to gain access to a datamap in private class space.
template <typename T> 
inline void DataMapAccess(T *ignored, datamap_t **p)
{
	*p = &T::m_DataMap;
}

// returns number of objects with a saved flag.
inline int num_saved_obj( datamap_t *p )
{
	if( !p )
		return 0;

	int num_saved = 0;
	for( int i = 0; i < p->NumObjs; i++ )
	{
		if( (p->objList[i].flags & MAPOBJ_SAVED) == MAPOBJ_SAVED )
			num_saved++;
	}
	return num_saved;
}

#endif // DATA_MAPPING_H