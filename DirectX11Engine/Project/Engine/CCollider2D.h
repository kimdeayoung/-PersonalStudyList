#pragma once
#include "CComponent.h"
class CCollider2D :
    public CComponent
{
private:
    Vector3 m_offset;
    Vector3 m_computePosition;

    Vector3 m_scale;
    bool m_absolute; // true인 경우 오브젝트의 크기에 영향을 받지 않는 절대(고정) 크기로 계산

    Matrix m_colliderMatrix;
public:
    Vector3 GetOffset() { return m_offset; }
    void SetOffset(Vector3 offset) { m_offset = offset; }

    Vector3 GetComputePosition() { return m_computePosition; }

    Vector3 GetScale() { return m_scale; }
    void SetScale(Vector3 scale) { m_scale = scale; }

    bool IsAbsolute() { return m_absolute; }
    void SetAbsolute(bool absolute) { m_absolute = absolute; }

public:
    virtual void FinalUpdate() override;

public:
    CCollider2D();
    ~CCollider2D();
};

