//========= Copyright © 2012, Ryan Sheffer, All rights reserved. ============//
//
// Purpose: Component for entities which need a world space position and rotation
//
//==========================================================================//

#include "stdafx.h"

//-----------------------------------------------------------------------------
// Position Component
//-----------------------------------------------------------------------------
class CComponentPosition : public CComponent
{
public:

	CComponentPosition()
	{
		OutputDebugString("component_position created!\n");
	}

	~CComponentPosition()
	{
		OutputDebugString("component_position destroyed!\n");
	}

	virtual void Run(void)
	{

	}

private:

	float x, y, z;
	float pitch, yaw, roll;
};

LINK_COMPONENT_TO_CLASS(component_position, CComponentPosition)