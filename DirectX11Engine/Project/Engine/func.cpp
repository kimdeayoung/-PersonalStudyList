#include "pch.h"

#include "CDebugRenderManager.h"

void DrawDebugRect(const Vector3& position, const Vector3& rotation, const Vector3& scale, float durtaion, const Vector4& color)
{
	DebugShapeInfo shapeInfo = { };
	shapeInfo.ShapeType = DEBUG_SHAPE::RECT;

	Matrix matScale = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
	Matrix matRotation = DirectX::XMMatrixRotationX(rotation.x) * DirectX::XMMatrixRotationY(rotation.y) * DirectX::XMMatrixRotationZ(rotation.z);
	Matrix matPosition = DirectX::XMMatrixTranslation(position.x, position.y, position.z);
	shapeInfo.matWorld = matScale * matRotation * matPosition;

	shapeInfo.age = 0;
	shapeInfo.duration = durtaion;
	shapeInfo.color = color;

	CDebugRenderManager::GetInstance()->AddDebugShapeInfo(shapeInfo);
}

void DrawDebugRect(const Matrix& matWorld, float durtaion, const Vector4& color)
{
	DebugShapeInfo shapeInfo = { };
	shapeInfo.ShapeType = DEBUG_SHAPE::RECT;

	shapeInfo.matWorld = matWorld;

	shapeInfo.age = 0;
	shapeInfo.duration = durtaion;
	shapeInfo.color = color;

	CDebugRenderManager::GetInstance()->AddDebugShapeInfo(shapeInfo);
}

void DrawDebugCircle()
{
}

void DrawDebugLine()
{
}
