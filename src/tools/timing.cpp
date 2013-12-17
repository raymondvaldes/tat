#include "../Header.h"
//#include <boost/filesystem.hpp>

std::chrono::high_resolution_clock::time_point stopwatch::checktime(void)
{
    return std::chrono::high_resolution_clock::now();
}

stopwatch::stopwatch(void)
{
    start();
}

void stopwatch::start(void)
{
    startTime = checktime();
}

void stopwatch::stop(void)
{
    stopTime = checktime();
    clockSpan = std::chrono::duration_cast
            <std::chrono::duration<double>>(stopTime- startTime);
}

double stopwatch::returnTime(void)
{
    stop();
    return clockSpan.count();
}

void stopwatch::displayTime(void)
{
    std::cout << "\nStopwatch: " << returnTime() <<" sec.\n\n";
}
