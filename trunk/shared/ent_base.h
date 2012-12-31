//
//  ent_base.h
//  client
//
//  Created by Ryan Sheffer on 2012-12-31.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef ENT_BASE_H
#define ENT_BASE_H

#include "network_base.h"

class CEntityBase
{
public:
    CEntityBase();
    
    //DECLARE_NETWORK_TABLE();
    
    
    
    Vector3     m_vecOrigin;
    Angle       m_angAngle;
};


#endif // ENT_BASE_H
