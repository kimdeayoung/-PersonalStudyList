#include "pch.h"
#include "CGraphicShader.h"
#include "CDevice.h"

CGraphicShader::CGraphicShader()
	: CShader(ASSET_TYPE::GRAPHICS_SHADER)
	, m_topologyType(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
	, m_rasterizerType(RASTERIZER_STATE_TYPE::CULL_BACK)
	, m_depthStencilType(DEPTHSTENCIL_STATE_TYPE::LESS)
	, m_blendStateType(BLEND_STATE_TYPE::DEFAULT)
{
}

CGraphicShader::~CGraphicShader()
{
}

int CGraphicShader::CreateVertexShader(const std::wstring& path, const std::string& funcName)
{
	if (FAILED(D3DCompileFromFile(path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, funcName.c_str(), "vs_5_0",
		D3DCOMPILE_DEBUG, 0, m_vertexBlob.GetAddressOf(), m_errorBlob.GetAddressOf())))
	{
		if (m_errorBlob == nullptr)
		{
			MessageBox(nullptr, L"File Not Found", L"Compile Error", MB_OK);
		}
		else
		{
			MessageBoxA(nullptr, (char*)m_errorBlob->GetBufferPointer(), "Compile Error", MB_OK);
		}

		return E_FAIL;
	}

	ID3D11Device* device = CDevice::GetInstance()->GetDevice();
	if (FAILED(device->CreateVertexShader(m_vertexBlob->GetBufferPointer(), m_vertexBlob->GetBufferSize(), nullptr, m_vertexShader.GetAddressOf())))
	{
		return E_FAIL;
	}

	// 정점 레이아웃 정보 생성
	const int layoutSize = 3;
	D3D11_INPUT_ELEMENT_DESC layoutDesc[layoutSize] = {};
	UINT byteOffset = 0;
	layoutDesc[0].AlignedByteOffset = byteOffset;
	layoutDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	layoutDesc[0].InputSlot = 0;
	layoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	layoutDesc[0].SemanticName = "POSITION";
	layoutDesc[0].SemanticIndex = 0;
	byteOffset += sizeof(Vector3);

	layoutDesc[1].AlignedByteOffset = byteOffset;
	layoutDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	layoutDesc[1].InputSlot = 0;
	layoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	layoutDesc[1].SemanticName = "COLOR";
	layoutDesc[1].SemanticIndex = 0;
	byteOffset += sizeof(Vector4);

	layoutDesc[2].AlignedByteOffset = byteOffset;
	layoutDesc[2].Format = DXGI_FORMAT_R32G32_FLOAT;
	layoutDesc[2].InputSlot = 0;
	layoutDesc[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	layoutDesc[2].SemanticName = "TEXCOORD";
	layoutDesc[2].SemanticIndex = 0;

	if (FAILED(device->CreateInputLayout(layoutDesc, layoutSize, m_vertexBlob->GetBufferPointer(), m_vertexBlob->GetBufferSize(), m_inputLayout.GetAddressOf())))
	{
		return E_FAIL;
	}

	return S_OK;
}

int CGraphicShader::CreatePixelShader(const std::wstring& path, const std::string& funcName)
{
	if (FAILED(D3DCompileFromFile(path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, funcName.c_str(), "ps_5_0",
		D3DCOMPILE_DEBUG, 0, m_pixelBlob.GetAddressOf(), m_errorBlob.GetAddressOf())))
	{
		if (m_errorBlob == nullptr)
		{
			MessageBox(nullptr, L"File Not Found", L"Compile Error", MB_OK);
		}
		else
		{
			MessageBoxA(nullptr, (char*)m_errorBlob->GetBufferPointer(), "Compile Error", MB_OK);
		}
	}

	ID3D11Device* device = CDevice::GetInstance()->GetDevice();
	if (FAILED(device->CreatePixelShader(m_pixelBlob->GetBufferPointer(), m_pixelBlob->GetBufferSize(), nullptr, m_pixelShader.GetAddressOf())))
	{
		return E_FAIL;
	}

	return S_OK;
}

void CGraphicShader::Binding()
{
	ID3D11DeviceContext* context = CDevice::GetInstance()->GetDeviceContext();

	context->IASetInputLayout(m_inputLayout.Get());
	context->IASetPrimitiveTopology(m_topologyType);

	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);

	context->RSSetState(CDevice::GetInstance()->GetRasterizerState(m_rasterizerType).Get());

	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	context->OMSetDepthStencilState(CDevice::GetInstance()->GetDepthStencilState(m_depthStencilType).Get(), 0);
	context->OMSetBlendState(CDevice::GetInstance()->GetBlendState(m_blendStateType).Get(), Vector4(0.f, 0.f, 0.f, 0.f), 0xffffffff);
}