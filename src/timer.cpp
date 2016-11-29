#include "timer.hpp"
#include <iostream>

void Timer::startTimer() { ftime(&startTime); }

void Timer::stopTimer() { ftime(&endTime); }

void Timer::printTime() {
    std::cout << "Runing time:";
    std::cout << ((endTime.time - startTime.time) * 1000.0 +
                  (endTime.millitm - startTime.millitm)) /
                     1000.0;
    std::cout << " s" << std::endl;
}
