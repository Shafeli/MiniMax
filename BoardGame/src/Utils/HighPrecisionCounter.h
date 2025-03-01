// HighPrecisionCounter.h
#pragma once

#include <chrono>

class HighPrecisionCounter
{
    using HighResolutionClock = std::chrono::high_resolution_clock;

    using TimePoint = HighResolutionClock::time_point;

    TimePoint m_startTime;

public:
    void StartCounter();
    double GetDeltaFromStart();
};
