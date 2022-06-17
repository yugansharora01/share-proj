#pragma once

class Timer
{
public:
    Timer();
    float Mark();
    float Peek() const noexcept;
private:
    std::chrono::steady_clock::time_point last;
};