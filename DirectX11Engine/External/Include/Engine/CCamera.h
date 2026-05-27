#pragma once
#include "CComponent.h"
class CCamera :
    public CComponent
{
private:
    PROJECTION_TYPE m_projectionType;

    Matrix m_matView;
    Matrix m_matProj;

    float m_fov;

    float m_aspectRatio;
    float m_orthograhpicScale;

    int m_camPriority; // 렌더 매니저에 등록시 카메라의 우선 순위
    float m_farPlane;

    UINT m_layerMask;
public:
    int GetCamPriority() { return m_camPriority; }
    void SetCamPriority(int priority);

    float GetFar() { return m_farPlane; }
    void SetFar(float farDistance) { m_farPlane = farDistance; }

    float GetFov() { return m_fov; }
    void SetFov(float fov) { m_fov = fov; }

    void SetAspectRatio(Vector2 screenSize);

    PROJECTION_TYPE GetProjectionType() { return m_projectionType; }
    void SetProjectionType(PROJECTION_TYPE type) { m_projectionType = type; }

    float GetOrthograhpicScale() { return m_orthograhpicScale; }
    void SetOrthograhpicScale(float scale) { m_orthograhpicScale = scale; }

public:
    void SetLayerNone() { m_layerMask = 0; }
    void SetLayerEverything() { m_layerMask = 0xffffffff; }
    void ToggleLayerEnable(int layerIndex);

    virtual void FinalUpdate() override;

    void Render();

public:
    CCamera();
    ~CCamera();
};

