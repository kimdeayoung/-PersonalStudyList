#pragma once
#include "CComponent.h"
class CScript :
    public CComponent
{
public:
    virtual void Update() = 0;
    virtual void FinalUpdate() final {}

public:
    CScript();
    ~CScript();
};

