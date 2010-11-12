#include "htTimer.h"

using namespace hooktail;

// static initialization
double  htTimer::s_frequency;
double  htTimer::s_frequencyInv;
BOOL    htTimer::s_isFrequencySet;


htTimer::htTimer()
    : m_startTime()
    , m_stopTime()
    , m_running(false)
    , m_elapsedTime()
{
    if(!s_isFrequencySet)
    {
        LARGE_INTEGER temp;

        QueryPerformanceFrequency((LARGE_INTEGER*) &temp);

        s_frequency         = static_cast<double>(temp.QuadPart) / 1000.0;
        s_frequencyInv      = 1 / s_frequency;
        s_isFrequencySet    = true;
    }
}

