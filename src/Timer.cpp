#include "Timer.hpp"

#include <map>

using namespace std;

map<timer::ID, chrono::steady_clock::time_point> timerMap;

timer::ID timer::createTimer() {
    chrono::steady_clock::time_point timer;

    auto id = timerMap.size() + 1;

    timerMap.insert(pair<timer::ID, chrono::steady_clock::time_point>(id, timer));

    timer = chrono::steady_clock::now();

    return id;
}

double timer::updateTimer(timer::ID id) {
    auto it = timerMap.find(id);

    chrono::steady_clock::time_point now = chrono::steady_clock::now();

	auto diff = chrono::duration_cast<chrono::nanoseconds>(now - it->second).count() * .000000001;

    it->second = now;

    return diff;
}