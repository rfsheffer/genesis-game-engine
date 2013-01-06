//
//  ent_base.cpp
//  client
//
//  Created by Ryan Sheffer on 2012-12-31.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#include "ent_base.h"

BEGIN_DATA_MAP_NO_BASE(CEntityBase)
    DEFINE_MAPOBJ(m_iEntIndex, DATA_INTEGER, MAPOBJ_SAVED),
END_DATA_MAP();

//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
CEntityBase::CEntityBase()
{

}