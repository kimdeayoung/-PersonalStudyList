#pragma once
#include "CEntity.h"

class CGameObject;

class CLayer :
    public CEntity
{
private:
    std::vector<CGameObject*> m_gameObjects;

public:
    void Start();
    void Update();
    void FinalUpdate();
    void Render();

public:
    void AddObject(CGameObject* object);

public:
    CLayer();
    ~CLayer();
};

