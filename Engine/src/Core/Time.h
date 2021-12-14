#ifndef TIME_H
#define TIME_H

#define TIME std::chrono::high_resolution_clock::time_point
#define TIME_NOW std::chrono::high_resolution_clock::now()
#define TIME_DURATION std::chrono::duration<double, std::milli>

double Delay();
void UpdateTime();
#endif
