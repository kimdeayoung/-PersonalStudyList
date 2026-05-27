#include "pch.h"
#include "CLevel.h"

#include "CLayer.h"
#include "CGameObject.h"

CLevel::CLevel()
	: m_layers{}
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_layers[i] = new CLayer;
	}
}

CLevel::~CLevel()
{
	Safe_Del_Array(m_layers);
}

void CLevel::Start()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_layers[i]->Start();
	}
}

void CLevel::Update()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_layers[i]->Update();
	}
}

void CLevel::FinalUpdate()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		m_layers[i]->FinalUpdate();
	}
}

void CLevel::AddObject(UINT layerIndex, CGameObject* object)
{
	m_layers[layerIndex]->AddObject(object);
	object->SetLayer(layerIndex);
}

void CLevel::RemoveObject(CGameObject* object)
{
	m_layers[object->GetLayer()]->RemoveObject(object);
}
