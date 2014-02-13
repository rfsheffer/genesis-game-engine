//
//  data_types.h
//  Types of data allowed in the mapping system.
//  TODO:
//
//  Created by Ryan Sheffer on 2012-12-31.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#ifdef _WIN
#pragma once
#endif

// Sizeof types
#define FLOAT_SIZE		 sizeof( float )
#define INT_SIZE		 sizeof( int )
#define BOOL_SIZE		 sizeof( bool )
#define SHORT_SIZE		 sizeof( short )
#define CHAR_SIZE		 sizeof( char )

#ifdef MATHLIB
#define VECTOR3_SIZE	 sizeof( Vector3 )
#define ANGLE_SIZE       sizeof( Angle )
#endif // MATHLIB


//--------------------------------------------------------------------------
/**
 * The types of data allowed in data maps ( network maps, save / restore )
 */
enum data_types
{
    DATA_VOID = 0,
    DATA_FLOAT,
    DATA_INTEGER,
    DATA_BOOLEAN,
    DATA_SHORT,
    DATA_CHARACTER,		// Note: Used for char arrays
    
    // TODO: Need to create a CUSTOM type for vector and angle
    DATA_VECTOR3,		// 3D Vector
    DATA_ANGLE,
    
    DATA_COUNT			// Number of Data Types that are mapable.
};

//--------------------------------------------------------------------------
/**
 * A class type which will return the data size based on special templates.
 */
template<data_types T>
class DataType
{
public:
    inline size_t GetDataSize(void) { return 0; }
};

//--------------------------------------------------------------------------
template<> inline size_t DataType<DATA_VOID>::GetDataSize(void)
{
    return 0;
}

//--------------------------------------------------------------------------
template<> inline size_t DataType<DATA_FLOAT>::GetDataSize(void)
{
    return FLOAT_SIZE;
}

//--------------------------------------------------------------------------
template<> inline size_t DataType<DATA_INTEGER>::GetDataSize(void)
{
    return INT_SIZE;
}

//--------------------------------------------------------------------------
template<> inline size_t DataType<DATA_BOOLEAN>::GetDataSize(void)
{
    return BOOL_SIZE;
}

//--------------------------------------------------------------------------
template<> inline size_t DataType<DATA_SHORT>::GetDataSize(void)
{
    return SHORT_SIZE;
}

//--------------------------------------------------------------------------
template<> inline size_t DataType<DATA_CHARACTER>::GetDataSize(void)
{
    return CHAR_SIZE;
}

//--------------------------------------------------------------------------
/**
 * With a data type, returns the size of that type
 */
inline size_t GetDataSize(data_types obj)
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
#ifdef MATHLIB
        case DATA_VECTOR3:
            return VECTOR3_SIZE;
        case DATA_ANGLE:
            return ANGLE_SIZE;
#endif // MATHLIB
        default:
            return 0;
    }
}

#endif // DATA_TYPES_H
