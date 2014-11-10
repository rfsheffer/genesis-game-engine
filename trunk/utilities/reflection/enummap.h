//
//  enummap.h
//  utilities
//
//  Created by Ryan Sheffer on 2014-11-09.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#ifndef utilities_enummap_h
#define utilities_enummap_h

#include "string/util_string_allocation.h"
#include "container/util_vector.h"

/**
 * An enumerator mapping can be created here to allow for serialization of
 * enumerators via enumerator row naming instead of value. This allows for
 * enumerator structure changes that will not stomp old enumerator serialization.
 * Mapping an enumerator requires an enumerator name, its namespace (to prevent
 * collisions with like enumerator names elsewhere) and a list of rows by name and
 * thier current (at the time of compile) value.
 */
class EnumMapping
{
public:
    EnumMapping(const char *pszEnumName, const char *pszNamespaceName)
    {
        // TODO: Save the string off like this.
        //m_enumName = (pszNamespaceName + '::' + pszEnumName);
    }
    
    /** A structure defining a row in an enumerator */
    struct EnumRow
    {
        /** The name of the enumerator row */
        Utility::CString    m_rowName;
        
        /** The value of that row (changes when entries are added) */
        unsigned int        m_val;
    };
    
    /** Adds a row to this enumerator mapping */
    void AddRow(const char *pszRowName, unsigned int value)
    {
        EnumRow row;
        //row.m_rowName = pszRowName;
        row.m_val = value;
        m_enumList.AddElementToBack(row);
    }
    
    /** Finds a row name based on the rows value */
    const char *FindRowName(unsigned int value)
    {
        return NULL;
    }
    
    /** Finds a row value based on the rows name */
    unsigned int FindRowValue(const char *pszRowName)
    {
        return 0;
    }
    
private:
    
    /** A list of enumerator rows */
    Utility::Vector<EnumRow>     m_enumList;

    /** The name of the enumerator */
    Utility::CString        m_enumName;
};

/** Static helper calls for creating and getting enumeration mappings */
class EnumMap
{
public:
    static EnumMapping *AddMapping(const char *pszEnumNamespace, const char *pszEnumName);
    static EnumMapping *FindMapping(const char *pszEnumNamespace, const char *pszEnumName);
};

#endif
