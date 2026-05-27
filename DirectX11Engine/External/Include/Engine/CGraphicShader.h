#pragma once
#include "CShader.h"
class CGraphicShader :
    public CShader
{
private:
    ComPtr<ID3DBlob> m_vertexBlob; // 컴파일한 쉐이더 코드를 저장
    ComPtr<ID3D11VertexShader> m_vertexShader;

    // Pixel Shader
    ComPtr<ID3DBlob> m_pixelBlob; // 컴파일한 쉐이더 코드를 저장
    ComPtr<ID3D11PixelShader> m_pixelShader;

    ComPtr<ID3D11InputLayout> m_inputLayout;
    D3D11_PRIMITIVE_TOPOLOGY m_topologyType;

    RASTERIZER_STATE_TYPE m_rasterizerType;
    DEPTHSTENCIL_STATE_TYPE m_depthStencilType;
    BLEND_STATE_TYPE m_blendStateType;
public:
    int CreateVertexShader(const std::wstring& path, const std::string& funcName);
    int CreatePixelShader(const std::wstring& path, const std::string& funcName);

    void SetTopologyType(D3D11_PRIMITIVE_TOPOLOGY type) { m_topologyType = type; }
    void SetRasterizerType(RASTERIZER_STATE_TYPE type) { m_rasterizerType = type; }
    void SetDepthStencilType(DEPTHSTENCIL_STATE_TYPE type) { m_depthStencilType = type; }
    void SetBlendType(BLEND_STATE_TYPE type) { m_blendStateType = type; }

    virtual void Binding() override;

public:
    CGraphicShader();
    ~CGraphicShader();
};

