#include "pch.h"
#include "CDebugRenderManager.h"
#include "CTimeManager.h"

#include "CAssetManager.h"
#include "CMesh.h"
#include "CMaterial.h"

#include "CGameObject.h"
#include "CTransform.h"
#include "CMeshRender.h"

CDebugRenderManager::CDebugRenderManager()
	:m_debugRenderObject(new CGameObject)
{
	m_debugRenderObject->AddComponent(new CTransform);
	m_debugRenderObject->AddComponent(new CMeshRender);

	m_debugRenderObject->MeshRender()->SetMaterial(CAssetManager::GetInstance()->FindAsset<CMaterial>(L"DebugShapeMat"));
}

CDebugRenderManager::~CDebugRenderManager()
{
	delete m_debugRenderObject;
	m_debugRenderObject = nullptr;
}

void CDebugRenderManager::Render()
{
	std::list<DebugShapeInfo>::iterator iter = m_shapeInfo.begin();

	float deltaTime = DT;
	while (iter != m_shapeInfo.end())
	{
		m_debugRenderObject->Transform()->SetWorldMatrix(iter->matWorld);

		switch (iter->ShapeType)
		{
		case DEBUG_SHAPE::RECT:
			m_debugRenderObject->MeshRender()->SetMesh(CAssetManager::GetInstance()->FindAsset<CMesh>(L"RectMesh_Debug"));
			break;
		case DEBUG_SHAPE::CIRCLE:
			m_debugRenderObject->MeshRender()->SetMesh(CAssetManager::GetInstance()->FindAsset<CMesh>(L"CircleMesh_Debug"));
			break;
		case DEBUG_SHAPE::LINE:
			m_debugRenderObject->MeshRender()->SetMesh(CAssetManager::GetInstance()->FindAsset<CMesh>(L"LineMesh"));
			break;
		case DEBUG_SHAPE::CUBE:
			m_debugRenderObject->MeshRender()->SetMesh(CAssetManager::GetInstance()->FindAsset<CMesh>(L"CubeMesh"));
			break;
		case DEBUG_SHAPE::SPHERE:
			m_debugRenderObject->MeshRender()->SetMesh(CAssetManager::GetInstance()->FindAsset<CMesh>(L"SphereMesh"));
			break;
		}

		Ptr<CMaterial> material = m_debugRenderObject->MeshRender()->GetMaterial();
		material->SetScalarParam(VECTOR4_0, iter->color);

		m_debugRenderObject->Render();

		iter->age += deltaTime;

		if (iter->duration <= iter->age)
		{
			iter = m_shapeInfo.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}
