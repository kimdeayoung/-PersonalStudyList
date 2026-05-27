#include "pch.h"
#include "CCamera.h"

#include "CRenderManager.h"
#include "CLevelManager.h"
#include "CLevel.h"
#include "CLayer.h"
#include "CTransform.h"
#include "CDevice.h"

CCamera::CCamera()
	: CComponent(COMPONENT_TYPE::CAMERA)
	, m_projectionType(PROJECTION_TYPE::PERSPECTIVE)
	, m_camPriority(-1)
	, m_fov(DirectX::XM_PI / 3)
	, m_farPlane(10000)
	, m_orthograhpicScale(1)
	, m_layerMask(0)
{
	Vector2 renderResoulution = CDevice::GetInstance()->GetRenderResoulution();
	m_aspectRatio = renderResoulution.x / renderResoulution.y;
}

CCamera::~CCamera()
{
}

void CCamera::SetCamPriority(int priority)
{
	if (priority >= 0)
	{
		m_camPriority = priority;
		CRenderManager::GetInstance()->RegisterCamera(this);
	}
	else
	{
		CRenderManager::GetInstance()->UnRegisterCamera(this);
		m_camPriority = priority;
	}
}

void CCamera::SetAspectRatio(Vector2 screenSize)
{
	CDevice::GetInstance()->SetRenderResoulution(screenSize);
	m_aspectRatio = screenSize.x / screenSize.y;
}

void CCamera::ToggleLayerEnable(int layerIndex)
{
	m_layerMask ^= (1 << layerIndex);
}

void CCamera::FinalUpdate()
{
	// View 행렬 계산
	Vector3 camWorldPosition = Transform()->GetRelativePos();
	m_matView = DirectX::XMMatrixTranslation(-camWorldPosition.x, -camWorldPosition.y, -camWorldPosition.z);

	Vector3 vRight = Transform()->GetRelativeDirection(DIR_TYPE::RIGHT);
	Vector3 vUp = Transform()->GetRelativeDirection(DIR_TYPE::UP);
	Vector3 vFront = Transform()->GetRelativeDirection(DIR_TYPE::FRONT);

	Matrix matRot = DirectX::XMMatrixIdentity();
	matRot._11 = vRight.x; matRot._12 = vUp.x; matRot._13 = vFront.x;
	matRot._21 = vRight.y; matRot._22 = vUp.y; matRot._23 = vFront.y;
	matRot._31 = vRight.z; matRot._32 = vUp.z; matRot._33 = vFront.z;

	m_matView *= matRot;

	// Proj 행렬 계산
	switch (m_projectionType)
	{
	case PROJECTION_TYPE::ORTHOGRAPHIC:
	{
		Vector2 renderResoulution = CDevice::GetInstance()->GetRenderResoulution();
		m_matProj = DirectX::XMMatrixOrthographicLH(renderResoulution.x * m_orthograhpicScale, renderResoulution.y * m_orthograhpicScale, 1.f, m_farPlane);
	}
		break;
	case PROJECTION_TYPE::PERSPECTIVE:
		m_matProj = DirectX::XMMatrixPerspectiveFovLH(m_fov, m_aspectRatio, 1, m_farPlane);
		break;
	}

}

void CCamera::Render()
{
	g_transform.matView = m_matView;
	g_transform.matProj = m_matProj;

	CLevel* level = CLevelManager::GetInstance()->GetCurrentLevel();

	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		if (m_layerMask & (1 << i))
		{
			CLayer* layer = level->GetLayer(i);
			layer->Render();
		}
	}
}
