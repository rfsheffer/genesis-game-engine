//========= Copyright © 2012, Ryan Sheffer, All rights reserved. ============//
//
// Purpose: AI Component
//
//==========================================================================//

#ifndef COMPONENT_AI_H
#define COMPONENT_AI_H

//-----------------------------------------------------------------------------
// Component Class
//-----------------------------------------------------------------------------
class CComponentAI : public CComponent
{
public:
	CComponentAI()
	{
		OutputDebugString("component_ai created!\n");
	}

	~CComponentAI()
	{
		OutputDebugString("component_ai destroyed!\n");
	}

	virtual void Run(void);
};

#endif // COMPONENT_AI_H