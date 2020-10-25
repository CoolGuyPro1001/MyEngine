#ifndef PCH_H
#define PCH_H

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <functional>
#include <map>

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned long ulong;

#define TIME std::chrono::high_resolution_clock::time_point

template<typename T>
using Local = std::unique_ptr<T>;

template<typename T, typename ... Args>
constexpr Local<T> CreateLocal(Args&& ... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T>
using Shared = std::shared_ptr<T>;

template<typename T, typename ... Args>
constexpr Shared<T> CreateShared(Args&& ... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}
#endif