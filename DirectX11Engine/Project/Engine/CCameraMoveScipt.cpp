#include "pch.h"
#include "CCameraMoveScipt.h"

#include "CTransform.h"
#include "CTimeManager.h"
#include "CKeyManager.h"

CCameraMoveScipt::CCameraMoveScipt()
	: m_speed(1)
{
}

CCameraMoveScipt::~CCameraMoveScipt()
{
}

void CCameraMoveScipt::Update()
{
	CTransform* transform = Transform();
	Vector3 pos = transform->GetRelativePos();
	Vector3 frontDir = transform->GetRelativeDirection(DIR_TYPE::FRONT);
	Vector3 rightDir = transform->GetRelativeDirection(DIR_TYPE::RIGHT);

	float deltaTime = DT

	if (KEY_PRESSED(KEY::W))
	{
		pos += frontDir * m_speed * deltaTime;
	}

	if (KEY_PRESSED(KEY::S))
	{
		pos -= frontDir * m_speed * deltaTime;
	}

	if (KEY_PRESSED(KEY::A))
	{
		pos -= rightDir * m_speed * deltaTime;
	}

	if (KEY_PRESSED(KEY::D))
	{
		pos += rightDir * m_speed * deltaTime;
	}

	if (KEY_PRESSED(KEY::RB_MOUSE))
	{
		Vector2 dragDirection = CKeyManager::GetInstance()->GetDragDirection();

		Vector3 rotation = transform->GetRelativeRotation();
		rotation.x -= dragDirection.y * deltaTime * DirectX::XM_PI;
		rotation.y += dragDirection.x * deltaTime * DirectX::XM_PI;
		transform->SetRelativeRotation(rotation);
	}

	transform->SetRelativePos(pos);
}