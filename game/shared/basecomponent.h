//========= Copyright © 2012, Ryan Sheffer, All rights reserved. ============//
//
// Purpose: Base Component Class
//
//==========================================================================//

#ifndef BASE_COMPONENT_H
#define BASE_COMPONENT_H

#define MAX_COMPONENT_NAME		128

//-----------------------------------------------------------------------------
// Component Class
//-----------------------------------------------------------------------------
class CComponent
{
public:
	CComponent()
	{

	}

	virtual ~CComponent()
	{

	}

	virtual void Run(void) = 0;

	char	m_szName[128];
	int		m_iIndex;
};

void InitComponents(void)
{

}

#endif // BASE_COMPONENT_H