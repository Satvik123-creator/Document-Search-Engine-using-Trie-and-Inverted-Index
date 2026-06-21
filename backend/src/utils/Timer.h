#ifndef TIMER_H
#define TIMER_H

#include <chrono>

using namespace std;

class Timer {
public:
    Timer();

    void start();
    void stop();
    void reset();

    double elapsedMilliseconds() const;
    double elapsedSeconds() const;

private:
    chrono::high_resolution_clock::time_point startTime;
    chrono::high_resolution_clock::time_point endTime;
    bool running;
};

#endif
