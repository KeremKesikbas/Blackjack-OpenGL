#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

namespace timer {
    typedef unsigned int ID;

    ID createTimer(); // creates and starts timer

    double updateTimer(ID id); // returns time diff and restarts timer.

    double getTime(ID id);
};

#endif