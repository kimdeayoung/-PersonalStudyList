#pragma once
#include "CEntity.h"
#include "CGameObject.h"

#define GET_COMPONENT(Type) C##Type* Type() { return m_owner->Type();}

class CComponent :
    public CEntity
{
private:
    CGameObject* m_owner;
    const COMPONENT_TYPE m_componentType;

public:
    COMPONENT_TYPE GetComponentType() { return m_componentType; }
    CGameObject* GetOwner() { return m_owner; }

    GET_COMPONENT(Transform);
    GET_COMPONENT(MeshRender);
    GET_COMPONENT(Camera);
    GET_COMPONENT(Collider2D);

public:
    virtual void Start() {}
    virtual void Update() {}
    virtual void FinalUpdate() = 0;

public:
    CComponent(COMPONENT_TYPE componentType);
    ~CComponent();

    friend class CGameObject;
};

