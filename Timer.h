#pragma once
#include <chrono>

class Timer 
{
public:
    Timer() 
    {
        start = std::chrono::high_resolution_clock::now();
    }

    double elapsed() 
    {
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        return duration.count();
    }

private:
    std::chrono::high_resolution_clock::time_point start;
};
