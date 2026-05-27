#pragma once
#include "CEntity.h"

class CGameObject;

class CLayer :
    public CEntity
{
private:
    std::vector<CGameObject*> m_gameObjects;
    std::vector<CGameObject*> m_renderObjects;

public:
    void Start();
    void Update();
    void FinalUpdate();
    void Render();

public:
    void AddObject(CGameObject* object);
    void RemoveObject(CGameObject* object);

    void RegisterRenderObject(CGameObject* object);
    void UnRegisterRenderObject(CGameObject* object);

public:
    CLayer();
    ~CLayer();
};

