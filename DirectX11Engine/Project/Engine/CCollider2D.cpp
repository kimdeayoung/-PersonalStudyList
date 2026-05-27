#include "pch.h"
#include "CCollider2D.h"

#include "components.h"

CCollider2D::CCollider2D()
	: CComponent(COMPONENT_TYPE::COLLIDER2D)
	, m_absolute(false)
	, m_scale(1,1,1)
{
}

CCollider2D::~CCollider2D()
{
}

void CCollider2D::FinalUpdate()
{
	CTransform* transform = Transform();
	m_computePosition = transform->GetRelativePos() + m_offset;

	if (m_absolute)
	{
		Matrix matScale = DirectX::XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
		Matrix matTranslation = DirectX::XMMatrixTranslation(m_offset.x, m_offset.y, m_offset.z);


		Vector3 objectScale = transform->GetRelativeScale();
		Matrix matScaleInverse = DirectX::XMMatrixScaling(objectScale.x, objectScale.y, objectScale.z);
		matScaleInverse = DirectX::XMMatrixInverse(nullptr, matScaleInverse);

		m_colliderMatrix = matScale * matTranslation * matScaleInverse * transform->GetWorldMatrix();
	}
	else
	{
		Matrix matScale = DirectX::XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
		Matrix matTranslation = DirectX::XMMatrixTranslation(m_offset.x, m_offset.y, m_offset.z);

		m_colliderMatrix = matScale * matTranslation * transform->GetWorldMatrix();
	}
	DrawDebugRect(m_colliderMatrix, 0.0f, Vector4(0.0f, 1.0f, 0.0f, 1.0f));
}