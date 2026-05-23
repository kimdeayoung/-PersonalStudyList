#include "pch.h"
#include "CRenderManager.h"

#include "CDevice.h"
#include "CCamera.h"

CRenderManager::CRenderManager()
{

}

CRenderManager::~CRenderManager()
{

}

void CRenderManager::RegisterCamera(CCamera* cam)
{
	for (size_t i = 0; i < m_cameras.size(); ++i)
	{
		if (m_cameras[i] == cam)
		{
			m_cameras[i] = nullptr;
			break;
		}
	}

	int priority = cam->GetCamPriority();

	if (m_cameras.size() <= priority)
	{
		m_cameras.resize(priority + 1);
	}

	m_cameras[priority] = cam;
}

void CRenderManager::UnRegisterCamera(CCamera* cam)
{
}

void CRenderManager::Init()
{
}

void CRenderManager::Update()
{
}

void CRenderManager::Render()
{
	for (size_t i = 0; i < m_cameras.size(); ++i)
	{
		m_cameras[i]->Render();
	}
}
