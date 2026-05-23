#pragma once
#include "CRenderComponent.h"
class CMeshRenderComponent :
    public CRenderComponent
{
public:
    virtual void FinalUpdate() override;
    virtual void Render() override;

public:
    CMeshRenderComponent();
    ~CMeshRenderComponent();
};

