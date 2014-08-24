//
//  data_types.h
//  Base types defined
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
#define FLOAT_SIZE          sizeof(float)
#define INTEGER_SIZE        sizeof(int)
#define BOOLEAN_SIZE        sizeof(bool)
#define SHORT_SIZE          sizeof(short)
#define CHARACTER_SIZE      sizeof(char)


//--------------------------------------------------------------------------
/**
 * These are base data types
 */
enum data_types
{
    DATA_VOID = 0,
    DATA_FLOAT,
    DATA_INTEGER,
    DATA_BOOLEAN,
    DATA_SHORT,
    DATA_CHARACTER,
    DATA_STRING,
    
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
    return INTEGER_SIZE;
}

//--------------------------------------------------------------------------
template<> inline size_t DataType<DATA_BOOLEAN>::GetDataSize(void)
{
    return BOOLEAN_SIZE;
}

//--------------------------------------------------------------------------
template<> inline size_t DataType<DATA_SHORT>::GetDataSize(void)
{
    return SHORT_SIZE;
}

//--------------------------------------------------------------------------
template<> inline size_t DataType<DATA_CHARACTER>::GetDataSize(void)
{
    return CHARACTER_SIZE;
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
            return INTEGER_SIZE;
        case DATA_BOOLEAN:
            return BOOLEAN_SIZE;
        case DATA_SHORT:
            return SHORT_SIZE;
        case DATA_CHARACTER:
            return CHARACTER_SIZE;
        default:
            return 0;
    }
}

#endif // DATA_TYPES_H
