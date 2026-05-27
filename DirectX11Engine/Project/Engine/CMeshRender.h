#pragma once
#include "CRenderComponent.h"
class CMeshRender :
    public CRenderComponent
{
public:
    virtual void FinalUpdate() override;
    virtual void Render() override;

public:
    CMeshRender();
    ~CMeshRender();
};

