#include "Clock.h"

TIME_DURATION delay = TIME_DURATION(0);
double Delay()
{
    return delay.count();
}