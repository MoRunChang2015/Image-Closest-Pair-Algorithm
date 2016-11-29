#ifndef TIME_HPP
#define TIMER_HPP
#include <sys/timeb.h>

class Timer {
   public:
    void startTimer();
    void stopTimer();
    void printTime();

   private:
    struct timeb startTime, endTime;
};
#endif
