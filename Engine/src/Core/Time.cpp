#include "Time.h"

static TIME_DURATION delay = TIME_DURATION(0);

double Delay()
{
    return delay.count();
}

void UpdateTime()
{
    static TIME last_time;

    delay = TIME_NOW - last_time;
    last_time = TIME_NOW;
}
