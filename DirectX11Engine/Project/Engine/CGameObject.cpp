#include "pch.h"
#include "CGameObject.h"

#include "CComponent.h"
#include "CRenderComponent.h"

#include "CScript.h"

#include "CLevelManager.h"
#include "CLevel.h"
#include "CLayer.h"

CGameObject::CGameObject()
	: m_components{}
	, m_renderComponent(nullptr)
	, m_parent(nullptr)
	, m_layer(-1)
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

	for (UINT i = 0; i < m_childs.size(); ++i)
	{
		m_childs[i]->Start();
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

	for (UINT i = 0; i < m_childs.size(); ++i)
	{
		m_childs[i]->Update();
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

	for (UINT i = 0; i < m_childs.size(); ++i)
	{
		m_childs[i]->FinalUpdate();
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

void CGameObject::SetParent(CGameObject* parent)
{
	if (m_parent != nullptr)
	{
		std::vector<CGameObject*> childs = m_parent->m_childs;

		std::vector<CGameObject*>::iterator iter = childs.begin();
		while (iter != childs.end())
		{
			if (*iter == this)
			{
				childs.erase(iter);
				break;
			}
		}
	}

	m_parent = parent;
	m_parent->m_childs.push_back(this);

	CLevel* level = CLevelManager::GetInstance()->GetCurrentLevel();
	level->RemoveObject(this);
}

void CGameObject::SetLayer(int layer)
{
	CLevel* level = CLevelManager::GetInstance()->GetCurrentLevel();
	if (m_layer >= 0)
	{
		level->GetLayer(m_layer)->UnRegisterRenderObject(this);
	}
	
	m_layer = layer;
	level->GetLayer(m_layer)->RegisterRenderObject(this);
}