//
//  enummap.cpp
//  utilities
//
//  Created by Ryan Sheffer on 2014-11-09.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#include "enummap.h"

namespace {
    // TODO: Dict of Enums
    Utility::Vector<EnumMapping>     g_enumList;
}

//------------------------------------------------------------------------------
/**
 * Adds a new enumeration mapping
 */
EnumMapping *EnumMap::AddMapping(const char *pszEnumNamespace, const char *pszEnumName)
{
    size_t elmIndex = g_enumList.AddElementToBack(EnumMapping(pszEnumNamespace, pszEnumName));
    return &g_enumList.Element(elmIndex);
}

//------------------------------------------------------------------------------
/**
 * Finds an already created enumeration mappings
 */
EnumMapping *EnumMap::FindMapping(const char *pszEnumNamespace, const char *pszEnumName)
{
    // TODO: search a dict
    return NULL;
}