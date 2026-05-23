#pragma once
#include "CAsset.h"
class CMesh :
    public CAsset
{
private:
    ComPtr<ID3D11Buffer> m_vertexBuffer;
    D3D11_BUFFER_DESC m_vertexBufferDesc;

    UINT m_vertexCount;
    Vertex* m_vertexSysMem;

    ComPtr<ID3D11Buffer> m_indexBuffer;
    D3D11_BUFFER_DESC m_indexBufferDesc;
    UINT m_indexCount;
    UINT* m_indexSysMem;

private:
    void Binding();

    virtual int Load(const std::wstring& path) { return S_OK; }
    virtual int Save(const std::wstring& path) { return S_OK; }

public:
    int Create(Vertex* vertexSysMem, size_t vertexCount, UINT* indexSysMem, size_t indexCount);

    void Render();
public:
    CMesh();
    ~CMesh();
};

