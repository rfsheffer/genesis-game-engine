//
//  ent_base.h
//  client
//
//  Created by Ryan Sheffer on 2012-12-31.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef ENT_BASE_H
#define ENT_BASE_H

//#include "network_base.h"

class CEntityBase
{
    DECLARE_CLASS_NO_BASE(CEntityBase);
public:
    
    CEntityBase();
    
    //DECLARE_NETWORK_TABLE();
    DECLARE_DATAMAP();
    
    Vector3     m_vecOrigin;
    Angle       m_angAngle;
    
    int         m_iEntIndex;
};


#endif // ENT_BASE_H
