#include "Time.h"

#include "Common/Log.h"

#define BILLION 1000000000.0
static TIME_DURATION delay = TIME_DURATION(0);
static TIME start_time;

double Delay()
{
    return delay.count() / BILLION;
}

double FramesPerSecond()
{
    return BILLION / delay.count();
}

void UpdateTime()
{
    static TIME last_time = TIME_NOW;

    delay = std::chrono::duration_cast<std::chrono::nanoseconds>(TIME_NOW - last_time);
    last_time = TIME_NOW;
}

void StartTimer()
{
    start_time = TIME_NOW;
}

void StopTimer()
{
    TIME_DURATION duration = std::chrono::duration_cast<std::chrono::nanoseconds>(TIME_NOW - start_time);

    Log("Duration: %f Nano Seconds\n", duration.count() / BILLION);

    start_time = TIME_NOW;
}
