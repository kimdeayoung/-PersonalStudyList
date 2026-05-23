#pragma once

struct Vertex
{
	Vector3 position;
	Vector4 color;
	Vector2 uv;
};

// 상수 버퍼 관련 구조체
struct Transform
{
	Matrix matWorld;
	Matrix matView;
	Matrix matProj;
};

struct MaterialConst
{
	int intValue[4];
	float floatValue[4];
	Vector2 vec2Value[4];
	Vector4 vec4Value[4];
	Matrix matrixValue[4];
};

struct DebugShapeInfo
{
	DEBUG_SHAPE ShapeType;

	Vector3 position;
	Vector3 scale;
	Vector3 rotation;
	Matrix matWorld;

	Vector4 color;

	float duration;
	float age;
};

extern Transform g_transform;

extern Vector3 g_xAxis;
extern Vector3 g_yAxis;
extern Vector3 g_zAxis;