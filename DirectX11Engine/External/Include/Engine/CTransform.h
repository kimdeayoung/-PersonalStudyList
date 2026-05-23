#pragma once
#include "CComponent.h"
class CTransform :
	public CComponent
{
private:
	Vector3 m_relativePos;
	Vector3 m_relativeScale;
	Vector3 m_relativeRotation;

	Vector3 m_relativeDir[(UINT)DIR_TYPE::LENGTH];

	Matrix m_matWorld;
public:
	virtual void FinalUpdate() override;

	void Binding();

public:
	Vector3 GetRelativePos() { return m_relativePos; }
	Vector3 GetRelativeScale() { return m_relativeScale; }
	Vector3 GetRelativeRotation() { return m_relativeRotation; }

	Vector3 GetRelativeDirection(DIR_TYPE type) { return m_relativeDir[(UINT)type]; }

	void SetRelativePos(const Vector3& pos) { m_relativePos = pos; }
	void SetRelativeScale(const Vector3& scale) { m_relativeScale = scale; }
	void SetRelativeRotation(const Vector3& rotation) { m_relativeRotation = rotation; }

	void SetRelativePos(float x, float y, float z) { m_relativePos = Vector3(x, y, z); }
	void SetRelativeScale(float x, float y, float z) { m_relativeScale = Vector3(x, y, z); }
	void SetRelativeRotation(float x, float y, float z) { m_relativeRotation = Vector3(x, y, z); }

	void SetWorldMatrix(const Matrix& matrix) { m_matWorld = matrix; }

public:
	CTransform();
	~CTransform();
};

