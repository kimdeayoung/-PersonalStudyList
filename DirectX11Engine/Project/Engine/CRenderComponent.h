#pragma once
#include "CComponent.h"

#include "assets.h"

class CRenderComponent :
    public CComponent
{
private:
    Ptr<CMesh> m_mesh;
    Ptr<CMaterial> m_material;

public:
    virtual void Render() = 0;

    Ptr<CMesh> GetMesh() { return m_mesh; }
    void SetMesh(Ptr<CMesh> mesh) { m_mesh = mesh; }

    Ptr<CMaterial> GetMaterial() { return m_material; }
    void SetMaterial(Ptr<CMaterial> material) { m_material = material; }
    
public:
    CRenderComponent(COMPONENT_TYPE componentType);
    ~CRenderComponent();
};

