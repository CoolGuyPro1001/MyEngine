#pragma once

#include <GL/glew.h>

#define ASSERT(x) if(!(x)) __builtin_trap();
#define GLCall(x) ClearErrors();\
    x;\
    ASSERT(LogCall(#x, __FILE__, __LINE__))

bool LogCall(const char* function, const char* file, int line);
void ClearErrors();