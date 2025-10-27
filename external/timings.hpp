#pragma once
#include <iostream>
#include <chrono>

namespace Timings {
    // Timer Debug
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = Clock::time_point;

    TimePoint startInitializationTime, endInitializationTime, startExecutionTime, endExecutionTime;

    static double getDuration(std::chrono::high_resolution_clock::time_point start, std::chrono::high_resolution_clock::time_point end) {
        return std::chrono::duration<double>(end - start).count();
    }

    void reset() {
        startInitializationTime = endInitializationTime = startExecutionTime = endExecutionTime = TimePoint{};
    }

    void startInitializationTimer() {
        startInitializationTime = std::chrono::high_resolution_clock::now();
    }

    void endInitializationTimerAndStartExecutionTimer() {
        endInitializationTime = std::chrono::high_resolution_clock::now();
        startExecutionTime = std::chrono::high_resolution_clock::now();
    }

    void endExecutionTimer() {
        endExecutionTime = std::chrono::high_resolution_clock::now();
    }

    void debugTimings() {
        std::cout << "\n\n=================================================================\n";
        std::cout << "-> Initialization Running Time:    " << getDuration(startInitializationTime, endInitializationTime) << " seconds.\n";
        std::cout << "-> Execution Running Time:         " << getDuration(startExecutionTime, endExecutionTime) << " seconds.\n";
        std::cout << "-> Total Running Time:             " << getDuration(startInitializationTime, endExecutionTime) << " seconds.\n";
        std::cout << "=================================================================\n";
    }
}
using namespace Timings;