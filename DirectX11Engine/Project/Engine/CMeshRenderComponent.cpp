#include "pch.h"
#include "CMeshRenderComponent.h"
#include "CTransform.h"

#include "CMaterial.h"

CMeshRenderComponent::CMeshRenderComponent()
	:CRenderComponent(COMPONENT_TYPE::MESHRENDER)
{
}

CMeshRenderComponent::~CMeshRenderComponent()
{
}

void CMeshRenderComponent::FinalUpdate()
{
}

void CMeshRenderComponent::Render()
{
	GetOwner()->Transform()->Binding();

	GetMaterial()->Binding();

	GetMesh()->Render();
}
