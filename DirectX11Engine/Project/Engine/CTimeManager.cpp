#include "pch.h"
#include "CTimeManager.h"

#include "CEngineBase.h"

CTimeManager::CTimeManager()
	: m_llFrequency{},
	m_llCurCount{},
	m_llPrevCount{},
	m_Time(0.0f),
	m_accTime(0.0f)
{

}

CTimeManager::~CTimeManager()
{

}

void CTimeManager::Init()
{
	QueryPerformanceFrequency(&m_llFrequency);
	QueryPerformanceCounter(&m_llCurCount);
	m_llPrevCount = m_llCurCount;
}

void CTimeManager::Update()
{
	QueryPerformanceCounter(&m_llCurCount);

	m_deltaTime = (float)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (float)m_llFrequency.QuadPart;
	m_Time += m_deltaTime;

	m_accTime += m_deltaTime;
	if (1.0f <= m_accTime)
	{
		m_accTime -= 1.0f;

		HWND mainHwnd = CEngineBase::GetInstance()->GetMainHwnd();

		wchar_t szText[255];

		swprintf_s(szText, L"DeltaTime: %f", m_deltaTime);

		SetWindowText(mainHwnd, szText);
	}

	m_llPrevCount = m_llCurCount;
}
