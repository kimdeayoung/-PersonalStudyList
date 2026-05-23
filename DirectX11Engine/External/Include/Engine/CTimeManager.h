#pragma once
#include "Singleton.h"
class CTimeManager :
    public CSingleton<CTimeManager>
{
private:
    LARGE_INTEGER m_llFrequency; // 초당 카운트 수
    LARGE_INTEGER m_llCurCount; // 현재 카운트 수
    LARGE_INTEGER m_llPrevCount; // 이전 프레임 카운트 수

    float m_deltaTime; // DeltaTime : 1 프레임 동작하는데 걸린 시간
    float m_Time; // 프로세스 실행 이후의 누적 시간

    float m_accTime; // 1초 체크 위한 시간 누적 변수

public:
    void Init();
    void Update();

public:
    float GetDeltaTime() { return m_deltaTime; }

    Singleton(CTimeManager)
};

