//
//  data_mappable.h
//  A class which is mappable, serializable, and networkable
//
//  Created by Ryan Sheffer on 2/5/2014.
//  Copyright (c) 2014 Ryan Sheffer. All rights reserved.
//

#ifndef DATA_MAPPABLE_H
#define DATA_MAPPABLE_H

#ifdef _WIN
#pragma once
#endif

#include "data_mapping.h"

//------------------------------------------------------------------------------
/**
 * Derive from this class to have it mappable
 */
class CDataMappable
{
public:
    DECLARE_CLASS_NO_BASE(CDataMappable);
    DECLARE_DATAMAP();
    
    virtual const char      *GetClassname(void) const = 0;
};

#endif // DATA_MAPPABLE_H
