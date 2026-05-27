#include "pch.h"
#include "CTransform.h"
#include "CConstBuffer.h"
#include "CDevice.h"

CTransform::CTransform()
	: CComponent(COMPONENT_TYPE::TRANSFORM)
	, m_relativeScale(Vector3(1.f,1.f,1.f))
{
}

CTransform::~CTransform()
{
}

void CTransform::FinalUpdate()
{
	Matrix matScale = DirectX::XMMatrixScaling(m_relativeScale.x, m_relativeScale.y, m_relativeScale.z);
	Matrix matRotation = DirectX::XMMatrixRotationX(m_relativeRotation.x) * DirectX::XMMatrixRotationY(m_relativeRotation.y) * DirectX::XMMatrixRotationZ(m_relativeRotation.z);
	Matrix matPosition = DirectX::XMMatrixTranslation(m_relativePos.x, m_relativePos.y,m_relativePos.z);

	m_matWorld = matScale * matRotation * matPosition;

	//오브젝트의 방향 정보 계산
	for (int i = 0; i < (UINT)DIR_TYPE::LENGTH; ++i)
	{
		m_relativeDir[i] = DirectX::XMVector3TransformNormal(m_worldDir[i], m_matWorld);
		m_relativeDir[i].Normalize();
	}

	CGameObject* parent = GetOwner()->GetParent();
	if (parent != nullptr)
	{
		m_matWorld *= parent->Transform()->GetWorldMatrix();

		for (int i = 0; i < (UINT)DIR_TYPE::LENGTH; ++i)
		{
			m_worldDir[i] = DirectX::XMVector3TransformNormal(m_worldDir[i], m_matWorld);
			m_worldDir[i].Normalize();
		}
	}
	else
	{
		for (int i = 0; i < (UINT)DIR_TYPE::LENGTH; ++i)
		{
			m_worldDir[i] = m_relativeDir[i];
		}
	}
}

void CTransform::Binding()
{
	CConstBuffer* buffer = CDevice::GetInstance()->GetConstBuffer(CONST_BUFFER_TYPE::TRANSFORM);
	
	g_transform.matWorld = m_matWorld;

	buffer->SetData(&g_transform);
	buffer->Binding();
}
