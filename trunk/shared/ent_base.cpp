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
    DEFINE_MAPOBJ(m_vecOrigin, DATA_VECTOR3, MAPOBJ_SAVED|MAPOBJ_NETWORKED),
    DEFINE_MAPOBJ(m_angAngle, DATA_ANGLE, MAPOBJ_SAVED|MAPOBJ_NETWORKED),
END_DATA_MAP();

//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
CEntityBase::CEntityBase()
{

}