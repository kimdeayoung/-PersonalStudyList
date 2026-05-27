#pragma once

class CConstBuffer;

class CDevice
	: public CSingleton<CDevice>
{
private:
	//윈도우에 따라 모델 뷰, 게임 뷰 등을 따로 보여줘야하는 케이스도 존재함(유니티에서가 대표적인 예)
	//가장 최종적으로 출력을 담당해야할 출력 대상 윈도우를 알아야 함
	HWND m_hwnd;

	//최적화 용도로 렌더 스케일이 다를 수 가 있기에 윈도우 출력용 해상도와 별개로 렌더 타겟 해상도를 별도로 설정
	Vector2 m_renderResoulution;

	//다이렉트 라이브러리 디바이스, 주요 기능: GPU 메모리 할당, DX11 개체 생성등등
	ComPtr<ID3D11Device> m_device;
	//DX11부터는 주요기능을 일부 분할, 주요 기능: GPU 렌더링 관련 명령
	ComPtr<ID3D11DeviceContext> m_context;
	//렌더 타겟 버퍼 소유, 화면에 최종 장면을 개시
	ComPtr<IDXGISwapChain> m_swapChain;

	ComPtr<ID3D11Texture2D> m_renderTarget;
	ComPtr<ID3D11RenderTargetView> m_renderTargetView;

	ComPtr<ID3D11Texture2D> m_depthStencilTexture;
	ComPtr<ID3D11DepthStencilView> m_depthStencilView;

	ComPtr<ID3D11SamplerState> m_samplerState[2];
	ComPtr<ID3D11RasterizerState> m_rasterizerState[(UINT)RASTERIZER_STATE_TYPE::LENGTH];

	ComPtr<ID3D11DepthStencilState> m_depthStencilState[(UINT)DEPTHSTENCIL_STATE_TYPE::LENGTH];
	ComPtr<ID3D11BlendState> m_blendState[(UINT)BLEND_STATE_TYPE::LENGTH];

	CConstBuffer* m_constantBuffer[(UINT)CONST_BUFFER_TYPE::LENGTH];

public:
	int Init(HWND hwnd, Vector2 resolution);
	int CreateSwapChain();
	int CreateView();
	int CreateConstBuffer();
	int CreateSamplerState();
	int CreateRasterizerState();
	int CreateDepthStencilState();
	int CreateBlendState();

	ID3D11Device* GetDevice() { return m_device.Get(); }
	ID3D11DeviceContext* GetDeviceContext() { return m_context.Get(); }

	Vector2 GetRenderResoulution() { return m_renderResoulution; }
	void SetRenderResoulution(const Vector2& resoulution) { m_renderResoulution = resoulution; }

	CConstBuffer* GetConstBuffer(CONST_BUFFER_TYPE type) { return m_constantBuffer[(UINT)type]; }

	ComPtr<ID3D11RasterizerState> GetRasterizerState(RASTERIZER_STATE_TYPE type) { return m_rasterizerState[(UINT)type]; }

	ComPtr<ID3D11DepthStencilState> GetDepthStencilState(DEPTHSTENCIL_STATE_TYPE type) { return m_depthStencilState[(UINT)type]; }
	ComPtr<ID3D11BlendState> GetBlendState(BLEND_STATE_TYPE type) { return m_blendState[(UINT)type]; }

	void ClearTarget();
	void Present();

	Singleton(CDevice)
};

