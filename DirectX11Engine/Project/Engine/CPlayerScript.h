#pragma once
#include "CScript.h"

#include "CTimeManager.h"
#include "CKeyManager.h"
#include "CAssetManager.h"

#include "CTransform.h"

class CPlayerScript :
    public CScript
{
private:
    float m_speed;

public:
    virtual void Update() override;

public:
    CPlayerScript();
    ~CPlayerScript();
};

