#include "pch.h"

#include "CDebugRenderManager.h"

void DrawDebugRect(const Vector3& position, const Vector3& rotation, const Vector3& scale, float duration, const Vector4& color)
{
	Matrix matScale = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
	Matrix matRotation = DirectX::XMMatrixRotationX(rotation.x) * DirectX::XMMatrixRotationY(rotation.y) * DirectX::XMMatrixRotationZ(rotation.z);
	Matrix matPosition = DirectX::XMMatrixTranslation(position.x, position.y, position.z);
	Matrix matWorld = matScale * matRotation * matPosition;

	DrawDebugRect(matWorld, duration, color);
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

void DrawDebugCircle(const Vector3& position, float radius, float duration, const Vector4& color)
{
	Matrix matScale = DirectX::XMMatrixScaling(radius, radius, 1.0f);
	Matrix matPosition = DirectX::XMMatrixTranslation(position.x, position.y, position.z);
	Matrix matWorld = matScale * matPosition;

	DrawDebugCircle(matWorld, duration, color);
}

void DrawDebugCircle(const Matrix& matWorld, float durtaion, const Vector4& color)
{
	DebugShapeInfo shapeInfo = { };
	shapeInfo.ShapeType = DEBUG_SHAPE::CIRCLE;

	shapeInfo.matWorld = matWorld;

	shapeInfo.age = 0;
	shapeInfo.duration = durtaion;
	shapeInfo.color = color;

	CDebugRenderManager::GetInstance()->AddDebugShapeInfo(shapeInfo);
}

void DrawDebugLine()
{
}
