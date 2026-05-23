#pragma once
#include "CEntity.h"
#include "CGameObject.h"

class CComponent :
    public CEntity
{
private:
    CGameObject* m_owner;
    const COMPONENT_TYPE m_componentType;

public:
    COMPONENT_TYPE GetComponentType() { return m_componentType; }
    CGameObject* GetOwner() { return m_owner; }

    CTransform* Transform() { return GetOwner()->Transform(); }
    CMeshRenderComponent* MeshRenderer() { return GetOwner()->MeshRenderer(); }
    CCamera* Camera() { return GetOwner()->Camera(); }

public:
    virtual void Start() {}
    virtual void Update() {}
    virtual void FinalUpdate() = 0;

public:
    CComponent(COMPONENT_TYPE componentType);
    ~CComponent();

    friend class CGameObject;
};

