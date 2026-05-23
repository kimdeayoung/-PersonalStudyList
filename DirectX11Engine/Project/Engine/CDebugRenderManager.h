#pragma once
#include "Singleton.h"

class CGameObject;

class CDebugRenderManager :
    public CSingleton<CDebugRenderManager>
{
    Singleton(CDebugRenderManager);

private:
    std::list<DebugShapeInfo> m_shapeInfo;

    CGameObject* m_debugRenderObject;
public:
    void AddDebugShapeInfo(const DebugShapeInfo& info) { m_shapeInfo.push_back(info); }

public:
    void Render();
};

