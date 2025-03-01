// HighPrecisionCounter.cpp
#include "HighPrecisionCounter.h"

using namespace std::chrono;

void HighPrecisionCounter::StartCounter()
{
    m_startTime = HighResolutionClock::now();
}

double HighPrecisionCounter::GetDeltaFromStart()
{
    TimePoint endTime = HighResolutionClock::now();
    duration<double> timeSpan = duration_cast<duration<double>>(endTime - m_startTime);
    return timeSpan.count() * 1000.0;  // convert to milliseconds before returning
}
