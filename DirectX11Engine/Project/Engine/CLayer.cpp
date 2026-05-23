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
	for (UINT i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->Render();
	}
}

void CLayer::AddObject(CGameObject* object)
{
	m_gameObjects.push_back(object);
}