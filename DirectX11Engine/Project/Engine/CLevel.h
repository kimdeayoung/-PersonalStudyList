#pragma once
#include "CEntity.h"

class CLayer;
class CGameObject;

class CLevel :
    public CEntity
{
private:
    CLayer* m_layers[MAX_LAYER];

public:
    void Start();
    void Update();
    void FinalUpdate();

public:
    void AddObject(UINT layerIndex, CGameObject* object);
    void RemoveObject(CGameObject* object);

    CLayer* GetLayer(int layerIndex) { return m_layers[layerIndex]; }

//public:
//    virtual CLevel* Clone() { return new CLevel(*this); }

public:
    CLevel();
    ~CLevel();
};

