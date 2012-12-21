//========= Copyright © 2012, Ryan Sheffer, All rights reserved. ============//
//
// Purpose: Entity Class
//
//==========================================================================//

#ifndef ENTITY_H
#define ENTITY_H

//-----------------------------------------------------------------------------
// Base Entity Class
//-----------------------------------------------------------------------------
class CEntity
{
public:
	CEntity()
	{
		//CreateComponents();
	}
	~CEntity()
	{
		//DestroyComponents();
	}

	vector<CComponent *>	m_components;

	void	AddComponent(const char *pComponentName)
	{
		CComponent *pComponent = CREATE_COMPONENT_BY_NAME(pComponentName);
		if(pComponent)
			m_components.push_back(pComponent);
	}

	void	DestroyComponents(void)
	{
		for(unsigned int i = 0; i < m_components.size(); i++)
		{
			DESTROY_COMPONENT(m_components[i]);
		}

		m_components.clear();
	}

	// Implement these

	// This function is used to create all needed components. Call AddComponent("name")
	virtual void CreateComponents(void)
	{
		OutputDebugString("In Base Ent Comp!\n");
	}
};

#endif // ENTITY_H