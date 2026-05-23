#include "pch.h"
#include "CLevelManager.h"
#include "CLevel.h"

#include "CGameObject.h"
#include "components.h"
#include "func.h"

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

		m_currentLevel->AddObject(0, pObject);
	}

	{
		CGameObject* pObject = new CGameObject;
		pObject->SetName(L"Player");
		pObject->AddComponent(new CTransform);
		pObject->AddComponent(new CMeshRenderComponent);
		pObject->AddComponent(new CPlayerScript);
	
		pObject->Transform()->SetRelativePos(Vector3(0.f, 0.0f, 1.1f));
		pObject->Transform()->SetRelativeScale(Vector3(1.f, 1.0f, 1.1f));
		pObject->MeshRenderer()->SetMesh(CAssetManager::GetInstance()->FindAsset<CMesh>(L"RectMesh"));
		pObject->MeshRenderer()->SetMaterial(CAssetManager::GetInstance()->FindAsset<CMaterial>(L"StdMat"));
		pObject->MeshRenderer()->GetMaterial()->SetTexture(TEX_0, CAssetManager::GetInstance()->FindAsset<CTexture>(L"background"));
		m_currentLevel->AddObject(0, pObject);
	}

	DrawDebugRect(Vector3(0.f, 0.f, 500.f), Vector3(0.f, 0.f, 0.f), Vector3(100.f, 100.f, 100.f), 1100.f, Vector4(0.f, 1.f, 0.f, 1.f));
}

void CLevelManager::Update()
{
	if (m_currentLevel != nullptr)
	{
		m_currentLevel->Update();
		m_currentLevel->FinalUpdate();
	}
}

void CLevelManager::Render()
{
	if (m_currentLevel != nullptr)
	{
		m_currentLevel->Render();
	}
}
