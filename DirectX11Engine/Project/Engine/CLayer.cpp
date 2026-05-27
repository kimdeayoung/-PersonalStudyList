#include "pch.h"
#include "CLayer.h"

#include "CGameObject.h"

CLayer::CLayer()
	: m_gameObjects{}
{
}

CLayer::~CLayer()
{
	Safe_Del_Vector(m_gameObjects);
}

void CLayer::Start()
{
	for (UINT i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->Start();
	}
}

void CLayer::Update()
{
	for (UINT i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->Update();
	}
}

void CLayer::FinalUpdate()
{
	for (UINT i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->FinalUpdate();
	}
}

void CLayer::Render()
{
	for (UINT i = 0; i < m_renderObjects.size(); ++i)
	{
		m_renderObjects[i]->Render();
	}
}

void CLayer::AddObject(CGameObject* object)
{
	m_gameObjects.push_back(object);
}

void CLayer::RemoveObject(CGameObject* object)
{
	std::vector<CGameObject*>::iterator iter = m_gameObjects.begin();
	while (iter != m_gameObjects.end())
	{
		if (*iter == object)
		{
			m_gameObjects.erase(iter);
			break;
		}
		++iter;
	}
}

void CLayer::RegisterRenderObject(CGameObject* object)
{
	m_renderObjects.push_back(object);
}

void CLayer::UnRegisterRenderObject(CGameObject* object)
{
	std::vector<CGameObject*>::iterator iter = m_renderObjects.begin();
	while (iter != m_renderObjects.end())
	{
		if (*iter == object)
		{
			m_renderObjects.erase(iter);
			break;
		}
		++iter;
	}
}
