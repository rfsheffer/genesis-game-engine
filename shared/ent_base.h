//
//  ent_base.h
//  client
//
//  Created by Ryan Sheffer on 2012-12-31.
//  Copyright (c) 2012 Ryan Sheffer. All rights reserved.
//

#ifndef ENT_BASE_H
#define ENT_BASE_H

// TODO: Make this a value taken from the master.cfg
#define MAX_NUM_ENTITIES        256

/** The lowest level entity class, understood by the client and the server */
class CEntityBase
{
public:
    DECLARE_CLASS_NO_BASE(CEntityBase);
    DECLARE_DATAMAP();
    
    /** Constructor */
    CEntityBase();
    
    /**
     * A method designed to initialize a created entity. Should only be called
     * by a factory.
     */
    int             GetEntityIndex(void) const { return m_iEntIndex; }
    
    /**
     * A method designed to initialize a created entity. Should only be called
     * by a factory.
     */
//    void            _InitBaseEntity(unsigned int index)
//    {
//        m_iEntIndex = index;
//    }
    
    const char      *GetClassname(void) const
    {
        return m_pszClassName;
    }
    
protected:
    
    /** The position of this entity in world space. */
    Vector3         m_vecOrigin;
    
    /** The angle of this entity. */
    Angle           m_angAngle;
    
private:
    
    friend class IEntityFactory;
    
    /**
     * The entity index assigned to this entity.
     * Will be set to -1 if this entity is not networked.
     */
    int             m_iEntIndex;
    
    /**
     * The name of this entity
     */
    const char      *m_pszClassName;
};


#endif // ENT_BASE_H
