#pragma once

#define GLCall(x) ClearErrors();\
    x;\
    LogCall(#x, __FILE__, __LINE__)
    
#define GLCallAssign(x, y) ClearErrors();\
    LogCall(#x, __FILE__, __LINE__)\
    y = x;

bool LogCall(const char* function, const char* file, int line);
void ClearErrors();