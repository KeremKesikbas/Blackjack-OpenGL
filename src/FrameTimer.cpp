#include "FrameTimer.hpp"

#include "stats.hpp"

#include <thread>

using namespace std;

FrameTimer::FrameTimer(int targetFPS) {

    SetFrameLimit(targetFPS);

	time = chrono::steady_clock::now();
    startingTime = chrono::steady_clock::now();

	calculateNext();
}

void FrameTimer::WaitUntilNext() {
	if (!waiting) {
		return;
	}

	chrono::steady_clock::time_point now = chrono::steady_clock::now();

	if (now < time) {
		if(now + targetDuration < time) time = now + targetDuration;
		
		this_thread::sleep_until(time);
	}
	
	calculateNext();
}

double FrameTimer::getCurrentTime() {
	chrono::steady_clock::time_point now = chrono::steady_clock::now();

	return chrono::duration_cast<chrono::nanoseconds>(now - time).count() * .000000001;
}

double FrameTimer::getTotalTime() {
    chrono::steady_clock::time_point now = chrono::steady_clock::now();

	return chrono::duration_cast<chrono::nanoseconds>(now - startingTime).count() * .000000001;
}

void FrameTimer::countFPS() {
	if (getTotalTime() > (double)secondCounter + remainingTime + 1.0) {
		secondCounter++;
		fps = frameCounter;
		frameCounter = 0;

		remainingTime = getTotalTime() - (double)secondCounter;
	}

	else {
		frameCounter++;
	}
}

int FrameTimer::getFPS() {
	return fps;
}

void FrameTimer::destroy() {
	isRunning = false;
}

void FrameTimer::SetFrameLimit(int fps) {
	targetDuration = chrono::nanoseconds(NANOSECOND / fps);
}

void FrameTimer::calculateNext() {
	time += targetDuration;
}

void FrameTimer::setWaiting(bool condition) {
	waiting = condition;
}