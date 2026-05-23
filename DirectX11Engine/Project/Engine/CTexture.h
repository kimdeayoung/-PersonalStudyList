#pragma once
#include "CAsset.h"

class CTexture :
    public CAsset
{
private:
    // 시스템 메모리에 로딩된 이미지 관리
    DirectX::ScratchImage m_image;
    // 시스템 메모리에 로딩된 이미지를 GPU 쪽으로 보내기 위한 개체
    // 텍스쳐는 로딩된 후 시스템 메모리, GPU 메모리 두 곳에 존재함
    ComPtr<ID3D11Texture2D> m_tex2D;
    // GPU 메모리에 할당된 Texture를 직접적으로 렌더링에 사용하지 않고 ShaderResourceView를 활용하여 리소스 데이터 바인딩
    ComPtr<ID3D11ShaderResourceView> m_resourceView;
private:
    virtual int Load(const std::wstring& path) override;
    virtual int Save(const std::wstring& path) override;

public:
    void Binding(int registerNum);
    static void Clear(int registerNum);

public:
    CTexture();
    ~CTexture();
};

