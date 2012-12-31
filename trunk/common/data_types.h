//
//  data_types.h
//  server
//
//  Created by Ryan Sheffer on 2012-12-31.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef DATA_TYPES_H
#define DATA_TYPES_H

//************
// The types of data allowed in data maps ( network maps, save / restore )
//************
enum data_map_types
{
	DATA_VOID = 0,
	DATA_FLOAT,
	DATA_INTEGER,
	DATA_BOOLEAN,
	DATA_SHORT,
	DATA_CHARACTER,		// Note: Used for char arrays
	DATA_VECTOR3,		// 3D Vector
    
	DATA_COUNT,			// Number of Data Types that are mapable.
};

// Sizeof types
#define FLOAT_SIZE		 sizeof( float )
#define INT_SIZE		 sizeof( int )
#define BOOL_SIZE		 sizeof( bool )
#define SHORT_SIZE		 sizeof( short )
#define CHAR_SIZE		 sizeof( char )
#define VECTOR3_SIZE	 sizeof( Vector3 )

inline size_t GetDataSize(data_map_types obj)
{
    switch(obj)
	{
		case DATA_VOID:
			return 0;
		case DATA_FLOAT:
			return FLOAT_SIZE;
		case DATA_INTEGER:
			return INT_SIZE;
		case DATA_BOOLEAN:
			return BOOL_SIZE;
		case DATA_SHORT:
			return SHORT_SIZE;
		case DATA_CHARACTER:
			return CHAR_SIZE;
		case DATA_VECTOR3:
			return VECTOR3_SIZE;
		default:
			return 0;
	};
}

#endif // DATA_TYPES_H
