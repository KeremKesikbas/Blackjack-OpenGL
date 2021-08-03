#ifndef FRAMETIMER_HPP
#define FRAMETIMER_HPP

#include "stats.hpp"

#include <chrono>

using namespace std;

class FrameTimer {
public:
	FrameTimer(int fps);

	void WaitUntilNext();

	double getCurrentTime();
    double getTotalTime();

	void SetFrameLimit(int fps);
	void calculateNext();
    void destroy();

    void countFPS();
    int getFPS();

    void setWaiting(bool condition);

    bool isRunning = true;
	
private:
    chrono::steady_clock::time_point time;
	chrono::steady_clock::time_point startingTime;
	chrono::steady_clock::duration targetDuration;

    double remainingTime = 0;
    int secondCounter = 0;
    int fps = 0;
    int frameCounter = 0;

    bool waiting = true;
};

#endif