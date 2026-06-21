#include "Timer.h"

using namespace std;

Timer::Timer() : running(false) {}

void Timer::start() {
    startTime = chrono::high_resolution_clock::now();
    running = true;
}

void Timer::stop() {
    endTime = chrono::high_resolution_clock::now();
    running = false;
}

void Timer::reset() {
    running = false;
}

double Timer::elapsedMilliseconds() const {
    auto end = running ? chrono::high_resolution_clock::now() : endTime;
    return chrono::duration<double, milli>(end - startTime).count();
}

double Timer::elapsedSeconds() const {
    auto end = running ? chrono::high_resolution_clock::now() : endTime;
    return chrono::duration<double>(end - startTime).count();
}
