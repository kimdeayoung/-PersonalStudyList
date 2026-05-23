#pragma once

#include "CEntity.h"

class CComponent;
class CScript;

class CTransform;

class CRenderComponent;
class CMeshRenderComponent;
class CCamera;

class CGameObject :
	public CEntity
{
private:
	CComponent* m_components[(UINT)COMPONENT_TYPE::LENGTH];
	CRenderComponent* m_renderComponent;

	std::vector<CScript*> m_scripts;

public:
	void Start();
	void Update();
	void FinalUpdate();
	void Render();

public:
	void AddComponent(CComponent* component);
	CComponent* GetComponent(COMPONENT_TYPE type) { return m_components[(UINT)type]; }

	CTransform* Transform() { return (CTransform*)m_components[(UINT)COMPONENT_TYPE::TRANSFORM]; }
	CMeshRenderComponent* MeshRenderer() { return (CMeshRenderComponent*)m_components[(UINT)COMPONENT_TYPE::MESHRENDER]; }
	CCamera* Camera() { return (CCamera*)m_components[(UINT)COMPONENT_TYPE::CAMERA]; }

public:
	CGameObject();
	~CGameObject();
};

