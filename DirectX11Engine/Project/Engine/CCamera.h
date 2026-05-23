#pragma once
#include "CComponent.h"
class CCamera :
    public CComponent
{
private:
    Matrix m_matView;
    Matrix m_matProj;

    int m_camPriority; // 렌더 매니저에 등록시 카메라의 우선 순위
    float m_farPlane;
public:
    int GetCamPriority() { return m_camPriority; }
    void SetCamPriority(int priority);

public:
    virtual void FinalUpdate() override;

    void Render();

public:
    CCamera();
    ~CCamera();
};

