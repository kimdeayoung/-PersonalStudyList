#include "pch.h"
#include "CGameObject.h"

#include "CComponent.h"
#include "CRenderComponent.h"

#include "CScript.h"

CGameObject::CGameObject()
	: m_components{}
	, m_renderComponent(nullptr)
{
}

CGameObject::~CGameObject()
{
	Safe_Del_Array(m_components);
}

void CGameObject::Start()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::LENGTH; ++i)
	{
		if (m_components[i] != nullptr)
		{
			m_components[i]->Start();
		}
	}

	for (UINT i = 0; i < m_scripts.size(); ++i)
	{
		m_scripts[i]->Start();
	}
}

void CGameObject::Update()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::LENGTH; ++i)
	{
		if (m_components[i] != nullptr)
		{
			m_components[i]->Update();
		}
	}

	for (UINT i = 0; i < m_scripts.size(); ++i)
	{
		m_scripts[i]->Update();
	}
}

void CGameObject::FinalUpdate()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::LENGTH; ++i)
	{
		if (m_components[i] != nullptr)
		{
			m_components[i]->FinalUpdate();
		}
	}
}

void CGameObject::Render()
{
	if (m_renderComponent != nullptr)
	{
		m_renderComponent->Render();
	}
}

void CGameObject::AddComponent(CComponent* component)
{
	assert(component);
	COMPONENT_TYPE type = component->GetComponentType();

	if (type == COMPONENT_TYPE::SCRIPT)
	{
		m_scripts.push_back((CScript*)component);
	}
	else
	{
		assert(!m_components[(UINT)type]);

		CRenderComponent* renderComponent = dynamic_cast<CRenderComponent*>(component);
		if (renderComponent != nullptr)
		{
			assert(!m_renderComponent);
			m_renderComponent = renderComponent;
		}

		m_components[(UINT)type] = component;
	}
	component->m_owner = this;
}
