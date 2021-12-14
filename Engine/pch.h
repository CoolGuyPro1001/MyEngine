#ifndef PCH_H
#define PCH_H

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <memory>
#include <functional>
#include <map>
#include <limits.h>
#include <cmath>
#include <chrono>
#include <climits>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <utility>
#include <unordered_map>
#include <typeindex>

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_gamecontroller.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_video.h>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#if _WIN32
#include <windows.h>
#endif

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned long ulong;
typedef uint8_t u8;

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

constexpr float PI = 3.14159250;
constexpr double EPSILON = 1.0e-323;

template<typename T>
T ToBigEndian(T x)
{
    u8* bytes;
    bytes = (u8*)&x;
    
    u8 flip[sizeof(T)];
    long move_by = sizeof(T) - 1;

    for(size_t i = 0; i < sizeof(T); i++)
    {
        flip[i + move_by] = bytes[i];
        move_by -= 2;
    }
}
#endif
