#include "pch.h"
#include "CEngineBase.h"

#include "CDevice.h"
#include "CTimeManager.h"
#include "CPathManager.h"
#include "CKeyManager.h"
#include "CAssetManager.h"
#include "CLevelManager.h"
#include "CRenderManager.h"
#include "CDebugRenderManager.h"
#include "CCollisionManager.h"

CEngineBase::CEngineBase()
	: m_hwnd(nullptr)
	, m_resolution{}
{
}

CEngineBase::~CEngineBase()
{
}

int CEngineBase::Init(HWND hwnd, Vector2 resolution)
{
	m_hwnd = hwnd;
	m_resolution = resolution;

	RECT rt = { 0, 0, m_resolution.x, m_resolution.y };

	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);// 윈도우 해상도가 우리가 원하는 윈도우 크기가 아니기에 윈도우 크기 계산 필요
	SetWindowPos(m_hwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);

	// DirectX11 Device 생성
	if (FAILED(CDevice::GetInstance()->Init(hwnd, resolution)))
	{
		MessageBox(nullptr, L"엔진 초기화 실패", L"엔진 초기화 실패", MB_OK);
		return E_FAIL;
	}

	CTimeManager::GetInstance()->Init();
	CKeyManager::GetInstance()->Init();
	CPathManager::GetInstance()->Init();
	CAssetManager::GetInstance()->Init();
	CLevelManager::GetInstance()->Init();

	return S_OK;
}

void CEngineBase::Update()
{
	CTimeManager::GetInstance()->Update();
	CKeyManager::GetInstance()->Update();
	
	CLevelManager::GetInstance()->Update();
	CCollisionManager::GetInstance()->Update();

	CDevice::GetInstance()->ClearTarget();
	
	CRenderManager::GetInstance()->Render();
	CDebugRenderManager::GetInstance()->Render();

	CDevice::GetInstance()->Present();
}
