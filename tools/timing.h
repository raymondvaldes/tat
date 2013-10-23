#ifndef TIMING_H
#define TIMING_H

class stopwatch
{
private:
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point stopTime;
    std::chrono::high_resolution_clock::time_point currentTime;
    std::chrono::high_resolution_clock::time_point tdel;

    std::chrono::duration<double> clockSpan;
    std::chrono::high_resolution_clock::time_point checktime(void);

public:
    stopwatch(void);
    void start(void);
    void stop(void);
    double returnTime(void);
    void displayTime(void);

};

#endif // TIMING_H
