#include "pch.h"
#include "CMeshRender.h"
#include "CTransform.h"

#include "CMaterial.h"

CMeshRender::CMeshRender()
	:CRenderComponent(COMPONENT_TYPE::MESHRENDER)
{
}

CMeshRender::~CMeshRender()
{
}

void CMeshRender::FinalUpdate()
{
}

void CMeshRender::Render()
{
	GetOwner()->Transform()->Binding();

	GetMaterial()->Binding();

	GetMesh()->Render();
}
