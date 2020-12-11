#ifndef PCH_H
#define PCH_H

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <functional>
#include <map>
#include <limits.h>
#include <cmath>
#include <chrono>
#include <climits>
#include <math.h>

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_gamecontroller.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_video.h>

#include <GL/glew.h>

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned long ulong;

#if UINT_MAX == 4294967295
typedef ulong u64;
typedef uint u32;
typedef ushort u16;
#elif UINT_MAX == 65535
typedef ulong u32;
typedef uint u16;
#error Unexpected UINT_MAX
#endif

#if INT_MAX == 2147483647
typedef long s64;
typedef int s32;
typedef short s16;
#elif INT_MAX == 32767
typedef long s32;
typedef int s16;
#error Unexpected INT_MAX
#endif

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