#include "pch.h"
#include "CCameraMoveScipt.h"

#include "CTransform.h"
#include "CTimeManager.h"
#include "CKeyManager.h"
#include "CCamera.h"

CCameraMoveScipt::CCameraMoveScipt()
	: m_speed(10)
{
}

CCameraMoveScipt::~CCameraMoveScipt()
{
}

void CCameraMoveScipt::Update()
{
	if (KEY_TAB(KEY::P))
	{
		PROJECTION_TYPE type = Camera()->GetProjectionType();

		switch (type)
		{
		case PROJECTION_TYPE::ORTHOGRAPHIC:
			Camera()->SetProjectionType(PROJECTION_TYPE::PERSPECTIVE);
			break;
		case PROJECTION_TYPE::PERSPECTIVE:
			Camera()->SetProjectionType(PROJECTION_TYPE::ORTHOGRAPHIC);
			{
				//Perspective 모드에서 자유 카메라 이동 중 OrthoGraphic으로 바꿨을때 z축을 바라보지 않을 수 있기에 언제나 z축을 바라보도록 초기화
				CTransform* transform = Transform();
				Vector3 position = transform->GetRelativePos();
				transform->SetRelativePos(Vector3(position.x, position.y, 0));
				transform->SetRelativeRotation(Vector3(0, 0, 0));
			}
			break;
		}
	}

	switch (Camera()->GetProjectionType())
	{
	case PROJECTION_TYPE::ORTHOGRAPHIC:
		MoveByOrthographic();
		break;
	case PROJECTION_TYPE::PERSPECTIVE:
		MoveByPerspective();
		break;
	}
}

void CCameraMoveScipt::MoveByPerspective()
{
	CTransform* transform = Transform();
	Vector3 pos = transform->GetRelativePos();
	Vector3 frontDir = transform->GetRelativeDirection(DIR_TYPE::FRONT);
	Vector3 rightDir = transform->GetRelativeDirection(DIR_TYPE::RIGHT);

	float deltaTime = DT;
	float speed = m_speed;
	if (KEY_PRESSED(KEY::LSHILFT))
	{
		speed *= 4.0f;
	}

	if (KEY_PRESSED(KEY::W))
	{
		pos += frontDir * speed * deltaTime;
	}

	if (KEY_PRESSED(KEY::S))
	{
		pos -= frontDir * speed * deltaTime;
	}

	if (KEY_PRESSED(KEY::A))
	{
		pos -= rightDir * speed * deltaTime;
	}

	if (KEY_PRESSED(KEY::D))
	{
		pos += rightDir * speed * deltaTime;
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

void CCameraMoveScipt::MoveByOrthographic()
{
	CTransform* transform = Transform();
	Vector3 pos = transform->GetRelativePos();
	Vector3 frontDir = transform->GetRelativeDirection(DIR_TYPE::FRONT);
	Vector3 rightDir = transform->GetRelativeDirection(DIR_TYPE::RIGHT);

	float deltaTime = DT;

	float speed = m_speed;
	if (KEY_PRESSED(KEY::LSHILFT))
	{
		speed *= 4.0f;
	}

	if (KEY_PRESSED(KEY::W))
	{
		pos.y += speed * deltaTime;
	}

	if (KEY_PRESSED(KEY::S))
	{
		pos.y -= speed * deltaTime;
	}

	if (KEY_PRESSED(KEY::A))
	{
		pos.x -= speed * deltaTime;
	}

	if (KEY_PRESSED(KEY::D))
	{
		pos.x += speed * deltaTime;
	}

	if (KEY_PRESSED(KEY::NUM1))
	{
		float scale = Camera()->GetOrthograhpicScale();
		scale -= deltaTime;
		if (scale < 0.01f)
		{
			scale = 0.01f;
		}

		Camera()->SetOrthograhpicScale(scale);
	}

	if (KEY_PRESSED(KEY::NUM2))
	{
		float scale = Camera()->GetOrthograhpicScale();
		scale += deltaTime;
		Camera()->SetOrthograhpicScale(scale);
	}

	transform->SetRelativePos(pos);
}