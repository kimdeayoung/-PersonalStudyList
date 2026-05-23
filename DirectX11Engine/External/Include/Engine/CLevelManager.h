#pragma once
#include "Singleton.h"

class CLevel;

class CLevelManager :
    public CSingleton<CLevelManager>
{
    Singleton(CLevelManager)

private:
    CLevel* m_currentLevel;

public:
    CLevel* GetCurrentLevel() { return m_currentLevel; }

public:
    void Init();
    void Update();
    void Render();
};

