#pragma once
#include "Singleton.h"

class CCamera;

class CRenderManager :
    public CSingleton<CRenderManager>
{
    Singleton(CRenderManager);
private:
    std::vector<CCamera*> m_cameras;

public:
    void RegisterCamera(CCamera* cam);
    void UnRegisterCamera(CCamera* cam);

public:
    void Init();
    void Update();
    void Render();
};

