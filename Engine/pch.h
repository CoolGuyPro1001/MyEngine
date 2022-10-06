#ifndef PCH_H
#define PCH_H

#include <iostream>
#include <vector>
#include <array>
#include <memory>
#include <map>
#include <chrono>
#include <climits>
#include <algorithm>
#include <utility>
#include <unordered_map>
#include <typeindex>
#include <queue>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned long ulong;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;


template<typename T>
using Unique = std::unique_ptr<T>;

template<typename T, typename ... Args>
constexpr Unique<T> CreateUnique(Args&& ... args)
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


constexpr float PI = 3.14159250;
constexpr double EPSILON = 1.0e-323;
#endif


