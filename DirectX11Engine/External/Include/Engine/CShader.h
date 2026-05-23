#pragma once
#include "CAsset.h"
class CShader :
    public CAsset
{
protected:
    ComPtr<ID3DBlob> m_errorBlob; // 컴파일 실패한 로그를 저장

public:
    virtual void Binding() = 0;

private:
    virtual int Load(const std::wstring& path) { return S_OK; }
    virtual int Save(const std::wstring& path) { return S_OK; }

public:
    CShader(ASSET_TYPE type);
    ~CShader();
};

