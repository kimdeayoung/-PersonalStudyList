#pragma once
#include "CEntity.h"
class CConstBuffer :
    public CEntity
{
private:
    ComPtr<ID3D11Buffer> m_constantBuffer;
    D3D11_BUFFER_DESC m_bufferDesc;

    CONST_BUFFER_TYPE m_type;

public:
    int Create(size_t bufferSize, CONST_BUFFER_TYPE type);
    void SetData(void* data);
    void Binding();

public:
    CConstBuffer();
    ~CConstBuffer();
};

