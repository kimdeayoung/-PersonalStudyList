#include "pch.h"
#include "CDevice.h"
#include "CConstBuffer.h"

CDevice::CDevice()
	: m_hwnd(nullptr)
	, m_renderResoulution{}
	, m_constantBuffer{}
	, m_samplerState{}
{
}

CDevice::~CDevice()
{
	Safe_Del_Array(m_constantBuffer);
}

int CDevice::Init(HWND hwnd, Vector2 resolution)
{
	m_hwnd = hwnd;
	m_renderResoulution = resolution;

	UINT deviceFlag = 0;
#ifdef _DEBUG
	deviceFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL level = D3D_FEATURE_LEVEL_11_0;

	// D3DX11 Device 코드는 d3d11.dll에 존재함
	// DLL 함수 등을 사용해서 어떤 인스턴스를 생성했으면 해당 DLL에서 제공하는 Release를 써야 함

	D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, deviceFlag, nullptr, 0, D3D11_SDK_VERSION, m_device.GetAddressOf(), &level, m_context.GetAddressOf());

	if (FAILED(CreateSwapChain()))
	{
		return E_FAIL;
	}

	if (FAILED(CreateView()))
	{
		return E_FAIL;
	}

	//ViewPort 설정: SwapChain이 Present시 윈도우 상 어느 위치에서 그려지는지 설정
	//렌더 타겟에 그림을 그린 후 해당 그림의 그려진 렌더 타겟 텍스쳐는 SwapChain
	//SwapChain에서 이미 타겟 윈도우를 알고 있고, ViewPort 설정으로 타겟 윈도우의 어느 지점에 그려야할지 지정

	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;

	viewport.Width = (float)m_renderResoulution.x;
	viewport.Height = (float)m_renderResoulution.y;

	// 깊이 텍스쳐에 저장되는 깊이 Min, Max 지정
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;

	// ViewPort 정보 세팅
	m_context->RSSetViewports(1, &viewport);

	if (FAILED(CreateConstBuffer()))
	{
		return E_FAIL;
	}

	if (FAILED(CreateSamplerState()))
	{
		return E_FAIL;
	}

	if (FAILED(CreateRasterizerState()))
	{
		return E_FAIL;
	}

	if (FAILED(CreateDepthStencilState()))
	{
		return E_FAIL;
	}

	if (FAILED(CreateBlendState()))
	{
		return E_FAIL;
	}

	return S_OK;
}

int CDevice::CreateSwapChain()
{
	DXGI_SWAP_CHAIN_DESC desc = {};//swapchain 생성 시 필요한 관련 옵션 구조체

	//SwapChain이 만들어질때 버퍼 옵션
	desc.BufferCount = 1;
	desc.BufferDesc.Width = (UINT)m_renderResoulution.x;
	desc.BufferDesc.Height = (UINT)m_renderResoulution.y;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// DISCARD의 경우 화면 출력 이후 해당 버퍼의 데이터를 버림, SEQUENTIAL은 해당 버퍼의 데이터를 남겨둠
	// 비트 블록 전송 모델 - DXGI_SWAP_EFFECT_DISCARD, DXGI_SWAP_EFFECT_SEQUENTIAL(현재 버퍼를 가능한 즉시 그리려함)
	// 대칭 이동 프레젠테이션 모델 - DXGI_SWAP_EFFECT_FLIP_DISCARD, DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL(드로우용 버퍼, 출력용 버퍼의 주소값만 바꿔가면서 드로우, 출력 스왑)
	// 위에 대한 자세한 설명은 https://learn.microsoft.com/ko-kr/windows/win32/direct3ddxgi/dxgi-flip-model 참조
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// SwapChain이 화면을 게시(Present) 할때 출력 목적지 윈도우
	desc.OutputWindow = m_hwnd;
	desc.Windowed = true;

	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;

	ComPtr<IDXGIDevice> device;
	ComPtr<IDXGIAdapter> adapter;
	ComPtr<IDXGIFactory> factory;

	m_device->QueryInterface(__uuidof(IDXGIDevice), (void**)device.GetAddressOf());
	device->GetParent(__uuidof(IDXGIAdapter), (void**)adapter.GetAddressOf());
	adapter->GetParent(__uuidof(IDXGIFactory), (void**)factory.GetAddressOf());

	if (FAILED(factory->CreateSwapChain(m_device.Get(), &desc, m_swapChain.GetAddressOf())))
	{
		return E_FAIL;
	}

	return S_OK;
}

int CDevice::CreateView()
{
	// RenderTarget Texture를 스왑체인으로부터 가져오기
	m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)m_renderTarget.GetAddressOf());

	m_device->CreateRenderTargetView(m_renderTarget.Get(), nullptr, m_renderTargetView.GetAddressOf());

	D3D11_TEXTURE2D_DESC stencilTexDesc = {};
	stencilTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;// DXGI Format Depth 24bit, stenccil 8bit
	// 렌더 타겟과 깊이 텍스쳐의 해상도가 정확하게 일치해야 함
	stencilTexDesc.Width = (UINT)m_renderResoulution.x;
	stencilTexDesc.Height = (UINT)m_renderResoulution.y;
	stencilTexDesc.ArraySize = 1;

	stencilTexDesc.CPUAccessFlags = 0;
	stencilTexDesc.Usage = D3D11_USAGE_DEFAULT;
	stencilTexDesc.MipLevels = 1;
	stencilTexDesc.SampleDesc.Count = 1;
	stencilTexDesc.SampleDesc.Quality = 0;
	stencilTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	m_device->CreateTexture2D(&stencilTexDesc, nullptr, m_depthStencilTexture.GetAddressOf());

	m_device->CreateDepthStencilView(m_depthStencilTexture.Get(), nullptr, m_depthStencilView.GetAddressOf());

	m_context->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());

	return S_OK;
}

int CDevice::CreateConstBuffer()
{
	m_constantBuffer[(UINT)CONST_BUFFER_TYPE::TRANSFORM] = new CConstBuffer;
	m_constantBuffer[(UINT)CONST_BUFFER_TYPE::TRANSFORM]->Create(sizeof(Transform), CONST_BUFFER_TYPE::TRANSFORM);

	m_constantBuffer[(UINT)CONST_BUFFER_TYPE::MATERIAL] = new CConstBuffer;
	m_constantBuffer[(UINT)CONST_BUFFER_TYPE::MATERIAL]->Create(sizeof(MaterialConst), CONST_BUFFER_TYPE::MATERIAL);

	return S_OK;
}

int CDevice::CreateSamplerState()
{
	D3D11_SAMPLER_DESC desc[2] = {};

	desc[0].AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc[0].AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc[0].AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	desc[0].Filter = D3D11_FILTER_ANISOTROPIC;

	m_device->CreateSamplerState(desc, m_samplerState[0].GetAddressOf());
	m_context->PSSetSamplers(0, 1, m_samplerState[0].GetAddressOf());

	desc[1].AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc[1].AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc[1].AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	desc[1].Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;

	m_device->CreateSamplerState(desc + 1, m_samplerState[1].GetAddressOf());
	m_context->PSSetSamplers(1, 1, m_samplerState[1].GetAddressOf());

	return S_OK;
}

int CDevice::CreateRasterizerState()
{
	// CULL_BACK은 DX11 Rasteriazer의 Default State로 되어있음(별도로 제작할 필요가 없음)
	// 별도로 커스텀된 데이터를 날려버림으로 간단하게 CULL_BACK State를 사용할 수 있음
	m_rasterizerState[(UINT)RASTERIZER_STATE_TYPE::CULL_BACK] = nullptr;

	{
		D3D11_RASTERIZER_DESC desc = {};
		desc.CullMode = D3D11_CULL_FRONT;
		desc.FillMode = D3D11_FILL_SOLID;

		m_device->CreateRasterizerState(&desc, m_rasterizerState[(UINT)RASTERIZER_STATE_TYPE::CULL_FRONT].GetAddressOf());
	}

	{
		D3D11_RASTERIZER_DESC desc = {};
		desc.CullMode = D3D11_CULL_NONE;
		desc.FillMode = D3D11_FILL_SOLID;

		m_device->CreateRasterizerState(&desc, m_rasterizerState[(UINT)RASTERIZER_STATE_TYPE::CULL_NONE].GetAddressOf());
	}

	{
		D3D11_RASTERIZER_DESC desc = {};
		desc.CullMode = D3D11_CULL_NONE;
		desc.FillMode = D3D11_FILL_WIREFRAME;

		m_device->CreateRasterizerState(&desc, m_rasterizerState[(UINT)RASTERIZER_STATE_TYPE::WIRE_FRAME].GetAddressOf());
	}

	return S_OK;
}

int CDevice::CreateDepthStencilState()
{
	m_depthStencilState[(UINT)DEPTHSTENCIL_STATE_TYPE::LESS] = nullptr;

	{
		D3D11_DEPTH_STENCIL_DESC desc = {};
		desc.DepthEnable = true; // 깊이 비교 기능 사용
		desc.StencilEnable = false; // 스텐실 기능 비활성화
		desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL; // 먼저 기록된 픽셀의 뎁스보다 작거나 같은 경우 통과
		desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; // 뎁스 테스트 성공 시, 깊이 기록

		m_device->CreateDepthStencilState(&desc, m_depthStencilState[(UINT)DEPTHSTENCIL_STATE_TYPE::LESS_EQUAL].GetAddressOf());
	}

	{
		D3D11_DEPTH_STENCIL_DESC desc = {};
		desc.DepthEnable = true; // 깊이 비교 기능 사용
		desc.StencilEnable = false; // 스텐실 기능 비활성화
		desc.DepthFunc = D3D11_COMPARISON_GREATER; // 먼저 기록된 픽셀의 뎁스보다 작거나 같은 경우 통과
		desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; // 뎁스 테스트 성공 시, 깊이 기록

		m_device->CreateDepthStencilState(&desc, m_depthStencilState[(UINT)DEPTHSTENCIL_STATE_TYPE::GRATER].GetAddressOf());
	}

	{
		D3D11_DEPTH_STENCIL_DESC desc = {};
		desc.DepthEnable = true; // 깊이 비교 기능 사용
		desc.StencilEnable = false; // 스텐실 기능 비활성화
		desc.DepthFunc = D3D11_COMPARISON_ALWAYS; // 먼저 기록된 픽셀의 뎁스보다 작거나 같은 경우 통과
		desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; // 뎁스 테스트 성공 시, 깊이 기록

		m_device->CreateDepthStencilState(&desc, m_depthStencilState[(UINT)DEPTHSTENCIL_STATE_TYPE::NO_TEST].GetAddressOf());
	}

	{
		D3D11_DEPTH_STENCIL_DESC desc = {};
		desc.DepthEnable = false; // 깊이 비교 기능 사용
		desc.StencilEnable = false; // 스텐실 기능 비활성화
		desc.DepthFunc = D3D11_COMPARISON_ALWAYS; // 먼저 기록된 픽셀의 뎁스보다 작거나 같은 경우 통과
		desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO; // 뎁스 테스트 성공 시, 깊이 기록

		m_device->CreateDepthStencilState(&desc, m_depthStencilState[(UINT)DEPTHSTENCIL_STATE_TYPE::NO_TEST_NO_WRITE].GetAddressOf());
	}

	return S_OK;
}

int CDevice::CreateBlendState()
{
	m_blendState[(UINT)BLEND_STATE_TYPE::DEFAULT] = nullptr;

	{
		D3D11_BLEND_DESC desc = {};
		desc.AlphaToCoverageEnable = false;
		desc.IndependentBlendEnable = false;

		desc.RenderTarget[0].BlendEnable = true;

		// 블랜딩 방식
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;

		// 블랜딩 계수
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		// 알파끼리의 혼합식
		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;

		m_device->CreateBlendState(&desc, m_blendState[(UINT)BLEND_STATE_TYPE::ALPHA_BLEND].GetAddressOf());
	}

	{
		D3D11_BLEND_DESC desc = {};
		desc.AlphaToCoverageEnable = true;
		desc.IndependentBlendEnable = false;

		desc.RenderTarget[0].BlendEnable = true;

		// 블랜딩 방식
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;

		// 블랜딩 계수
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		// 알파끼리의 혼합식
		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;

		m_device->CreateBlendState(&desc, m_blendState[(UINT)BLEND_STATE_TYPE::ALPHA_BLEND].GetAddressOf());
	}

	return S_OK;
}

void CDevice::ClearTarget()
{
	float clearColor[4] = { 0.0f,0.0f,1.0f,1.0f };
	m_context->ClearRenderTargetView(m_renderTargetView.Get(), clearColor);

	//Depth가 0f이면 어떠한 것도 그려지지 않음(기준값이 0이라서 0보다 작은 물체는 존재할 수 없음) 따라서 1로 초기화
	m_context->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
}

void CDevice::Present()
{
	m_swapChain->Present(0, 0);
}
