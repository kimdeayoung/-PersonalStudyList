#include "pch.h"
#include "CPlayerScript.h"

CPlayerScript::CPlayerScript()
	: m_speed(1.f)
{
}

CPlayerScript::~CPlayerScript()
{
}

void CPlayerScript::Update()
{
	CTransform* transform = GetOwner()->Transform();
	Vector3 pos = transform->GetRelativePos();

	float deltaTime = DT

	if (KEY_PRESSED(KEY::UP))
	{
		pos.y += deltaTime * m_speed;
	}

	if (KEY_PRESSED(KEY::DOWN))
	{
		pos.y -= deltaTime * m_speed;
	}

	if (KEY_PRESSED(KEY::LEFT))
	{
		pos.x -= deltaTime * m_speed;
	}

	if (KEY_PRESSED(KEY::RIGHT))
	{
		pos.x += deltaTime * m_speed;
	}

	if (KEY_PRESSED(KEY::Z))
	{
		Vector3 vRot = GetOwner()->Transform()->GetRelativeRotation();
		vRot.z += deltaTime * DirectX::XM_PI;
		GetOwner()->Transform()->SetRelativeRotation(vRot);
	}

	transform->SetRelativePos(pos);
}