#pragma once

#include <chrono>

class Timer
{
    std::chrono::time_point<std::chrono::high_resolution_clock> m_lastTick;
    std::chrono::duration<double, std::ratio<1, 1>> m_interval;

  public:
    explicit Timer(double interval);

    bool Tick();
};