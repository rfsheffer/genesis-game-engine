//========= Copyright © 2012, Ryan Sheffer, All rights reserved. ============//
//
// Purpose: Entity Class
//
//==========================================================================//

#ifndef TEST_ENTITY_H
#define TEST_ENTITY_H

//-----------------------------------------------------------------------------
// Base Entity Class
//-----------------------------------------------------------------------------
class CTestEntity : public CEntity
{
public:

	virtual void CreateComponents(void)
	{
		AddComponent("component_position");
		AddComponent("component_ai");
	}
};

#endif // TEST_ENTITY_H