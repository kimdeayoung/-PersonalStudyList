#include "pch.h"
#include "CLevelManager.h"
#include "CLevel.h"

#include "CGameObject.h"
#include "components.h"
#include "func.h"

#include "CCameraMoveScipt.h"
#include "CPlayerScript.h"

CLevelManager::CLevelManager()
	: m_currentLevel(nullptr)
{

}

CLevelManager::~CLevelManager()
{
	if (m_currentLevel != nullptr)
	{
		delete m_currentLevel;
	}
}

void CLevelManager::Init()
{
	m_currentLevel = new CLevel;

	{
		CGameObject* pObject = new CGameObject;
		pObject->SetName(L"MainCamera");
		pObject->AddComponent(new CTransform);
		pObject->AddComponent(new CCamera);
		pObject->AddComponent(new CCameraMoveScipt);
		pObject->Camera()->SetCamPriority(0);
		pObject->Camera()->SetProjectionType(PROJECTION_TYPE::ORTHOGRAPHIC);
		pObject->Camera()->SetLayerEverything();

		m_currentLevel->AddObject(0, pObject);
	}

	{
		CGameObject* pObject = new CGameObject;
		pObject->SetName(L"Player");
		pObject->AddComponent(new CTransform);
		pObject->AddComponent(new CMeshRender);
		pObject->AddComponent(new CPlayerScript);
		pObject->AddComponent(new CCollider2D);
	
		pObject->Transform()->SetRelativePos(Vector3(0.f, 0.0f, 1.1f));
		pObject->Transform()->SetRelativeScale(Vector3(50.f, 50.0f, 1.1f));
		pObject->MeshRender()->SetMesh(CAssetManager::GetInstance()->FindAsset<CMesh>(L"RectMesh"));
		pObject->MeshRender()->SetMaterial(CAssetManager::GetInstance()->FindAsset<CMaterial>(L"StdMat"));
		pObject->MeshRender()->GetMaterial()->SetTexture(TEX_0, CAssetManager::GetInstance()->FindAsset<CTexture>(L"background"));

		pObject->Collider2D()->SetOffset(Vector3(0.f, 0.0f, 0.0f));
		pObject->Collider2D()->SetScale(Vector3(1.f, 1.f, 1.f));
		m_currentLevel->AddObject(1, pObject);
	}
}

void CLevelManager::Update()
{
	if (m_currentLevel != nullptr)
	{
		m_currentLevel->Update();
		m_currentLevel->FinalUpdate();
	}
}
