#include "timer.hpp"
#include <chrono>

Timer::Timer(double interval) : m_interval(interval), m_lastTick(std::chrono::high_resolution_clock::now())
{
}

bool Timer::Tick()
{
    auto now = std::chrono::high_resolution_clock::now();
    if (now - m_lastTick > m_interval)
    {
        m_lastTick = now;
        return true;
    }

    return false;
}