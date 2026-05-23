#include "pch.h"
#include "CTexture.h"
#include "CDevice.h"

CTexture::CTexture()
	:CAsset(ASSET_TYPE::TEXTURE)
{
}

CTexture::~CTexture()
{
}

int CTexture::Load(const std::wstring& path)
{
	wchar_t ext[50];
	_wsplitpath_s(path.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, ext, 50);

	std::wstring extString = ext;

	HRESULT hr = E_FAIL;
	if (extString == L".dds" || extString == L".DDS")
	{
		hr = DirectX::LoadFromDDSFile(path.c_str(), DirectX::DDS_FLAGS::DDS_FLAGS_NONE, nullptr, m_image);
	}
	else if (extString == L".tga" || extString == L".TGA")
	{
		hr = DirectX::LoadFromTGAFile(path.c_str(), nullptr, m_image);
	}
	else
	{
		hr = DirectX::LoadFromWICFile(path.c_str(), DirectX::WIC_FLAGS::WIC_FLAGS_NONE, nullptr, m_image);
	}

	if (FAILED(hr))
	{
		MessageBox(nullptr, L"텍스쳐 로딩 실패", L"텍스쳐 로딩 실패", MB_OK);
		return E_FAIL;
	}

	// Texture2D Description 작성해서 Texture2D 개체 생성
	// Texture2D 개체를 이ㅣ용해서 ShaderResourceView 생성
	ID3D11Device* device = CDevice::GetInstance()->GetDevice();
	hr = DirectX::CreateShaderResourceView(device, m_image.GetImages(), m_image.GetImageCount(), m_image.GetMetadata(), m_resourceView.GetAddressOf());

	if (FAILED(hr))
	{
		MessageBox(nullptr, L"ShaderResourceView 생성 실패", L"ShaderResourceView 생성 실패", MB_OK);
		return E_FAIL;
	}

	m_resourceView->GetResource((ID3D11Resource**)m_tex2D.GetAddressOf());

	return hr;
}

int CTexture::Save(const std::wstring& path)
{
	return 0;
}

void CTexture::Binding(int registerNum)
{
	ID3D11DeviceContext* context = CDevice::GetInstance()->GetDeviceContext();
	context->PSSetShaderResources(registerNum, 1, m_resourceView.GetAddressOf());
}

void CTexture::Clear(int registerNum)
{
	ID3D11DeviceContext* context = CDevice::GetInstance()->GetDeviceContext();

	ID3D11ShaderResourceView* resource = nullptr;
	context->PSSetShaderResources(registerNum, 1, &resource);
}
