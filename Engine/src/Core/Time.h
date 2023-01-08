#ifndef TIME_H
#define TIME_H

#define TIME std::chrono::high_resolution_clock::time_point
#define TIME_NOW std::chrono::high_resolution_clock::now()
#define TIME_DURATION std::chrono::duration<double, std::nano>

double Delay();
double FramesPerSecond(); //The FPS For That Exact Frame Called
void UpdateTime();

/**
 * Functions For Performance Benchmarking. Records The Time In Nano Seconds, Prints The Result To Console
 */
void StartTimer();
void StopTimer();

#endif
