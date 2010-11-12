#pragma once

#include <windows.h>


namespace hooktail
{
class htTimer
{
public:
                                htTimer();
                                ~htTimer() {};

    VOID                        Start();
    VOID                        Stop();
    VOID                        Reset();

    const double                GetElapsedTime() const;
    const UINT64                GetElapsedTimeNanoseconds() const;

private:
    LARGE_INTEGER               m_startTime;
    LARGE_INTEGER               m_stopTime;
    LARGE_INTEGER               m_elapsedTime;

    BOOL                        m_running;

    static double               s_frequency;
    static double               s_frequencyInv;
    static BOOL                 s_isFrequencySet;
};

inline VOID
htTimer::Start()
{
    QueryPerformanceCounter((LARGE_INTEGER*) &m_startTime);
    m_running = true;
}

inline VOID
htTimer::Stop()
{
    QueryPerformanceCounter((LARGE_INTEGER*) &m_stopTime);
    m_running = false;
}

inline VOID
htTimer::Reset()
{
    m_running                   = false;
    m_elapsedTime.LowPart       = 0;
    m_elapsedTime.HighPart      = 0;
}

/*
inline VOID
htTimer::Lap()
{
    LARGE_INTEGER lapTime();

    if (m_running)
    {
        QueryPerformanceCounter((LARGE_INTEGER*) &lapTime);
        m_elapsedTime       += lapTime;
    }
}
*/

inline const double
htTimer::GetElapsedTime() const
{
    double retVal;

    if (m_running) 
    {
        LARGE_INTEGER temp;
        QueryPerformanceCounter((LARGE_INTEGER*) &temp);
        retVal = static_cast<double>(temp.QuadPart - m_startTime.QuadPart) * s_frequencyInv;
    }
    else
    {
        retVal = static_cast<double>(m_stopTime.QuadPart - m_startTime.QuadPart) * s_frequencyInv;
    }

    return retVal;
}

inline const UINT64
htTimer::GetElapsedTimeNanoseconds() const
{
    return static_cast<UINT>(GetElapsedTime() * 1000000);
}


} // namespace hooktail
