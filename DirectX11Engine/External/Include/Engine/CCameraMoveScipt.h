#pragma once
#include "CScript.h"
class CCameraMoveScipt :
    public CScript
{
private:
    float m_speed;

public:
    virtual void Update() override;

private:
    void MoveByPerspective();
    void MoveByOrthographic();

public:
    CCameraMoveScipt();
    ~CCameraMoveScipt();
};

