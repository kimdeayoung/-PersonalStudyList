#pragma once

class CEngineBase
	: public CSingleton<CEngineBase>
{
public:
	int Init(HWND hwnd, Vector2 resolution);

	void Update();

	HWND GetMainHwnd() { return m_hwnd; }
private:
	HWND m_hwnd;
	Vector2 m_resolution;

	Singleton(CEngineBase)
};

