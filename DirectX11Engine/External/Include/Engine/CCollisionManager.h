#pragma once
#include "Singleton.h"
class CCollisionManager :
    public CSingleton<CCollisionManager>
{
private:
    UINT m_matrix[(UINT)MAX_LAYER]; // unity의 Layer Collision Matrix와 동일

public:
    void Update();

public:
    void ToggleLayerEnable(UINT lhs, UINT rhs);

public:
    Singleton(CCollisionManager)
};

