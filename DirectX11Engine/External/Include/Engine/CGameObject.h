#pragma once

#include "CEntity.h"

class CComponent;
class CScript;
class CRenderComponent;

#define GET_COMPONENT(Type, TYPE) class C##Type* Type() { return (C##Type*)m_components[(UINT)COMPONENT_TYPE::TYPE]; }

class CGameObject :
	public CEntity
{
private:
	CComponent* m_components[(UINT)COMPONENT_TYPE::LENGTH];
	CRenderComponent* m_renderComponent;

	std::vector<CScript*> m_scripts;

	CGameObject* m_parent;
	std::vector<CGameObject*> m_childs;

	int m_layer;

public:
	void Start();
	void Update();
	void FinalUpdate();
	void Render();

public:
	void AddComponent(CComponent* component);
	CComponent* GetComponent(COMPONENT_TYPE type) { return m_components[(UINT)type]; }

	GET_COMPONENT(Transform, TRANSFORM);
	GET_COMPONENT(MeshRender, MESHRENDER);
	GET_COMPONENT(Camera, CAMERA);
	GET_COMPONENT(Collider2D, COLLIDER2D);

	void SetParent(CGameObject* parent);

	const std::vector<CGameObject*>& GetChilds() { return m_childs; }
	CGameObject* GetParent() { return m_parent; }

	int GetLayer() { return m_layer; }
	void SetLayer(int layer);

public:
	CGameObject();
	~CGameObject();
};

