#ifndef ERROR_H
#define ERROR_H

#include "Common/Log.h"
#include "Common/Console.h"

/*
Fatal Errors Will Stop The Program Log() To log.txt
Critical Errors Will Let Program Continue And Use printf();
*/

//Error Types
#define ENGINE_ERROR 0
#define OPENGL_ERROR 1
#define GLSL_ERROR 2
#define GUI_ERROR 3
#define FREETYPE_ERROR 4
#define SDL_ERROR 5

//Macros
#define FatalError(t, msg) Error::Fatal(t, msg, __FILE__, __LINE__);
#define FatalErrorArgs(t, msg, ...) Error::Fatal(t, msg, __FILE__, __LINE__, __VA_ARGS__);
#define CriticalError(t, msg) Error::Critical(t, msg, __FILE__, __LINE__);
#define CriticalErrorArgs(t, msg, ...) Error::Critical(t, msg, __FILE__, __LINE__, __VA_ARGS__);

namespace Error
{
    template<typename... Args>
    void Fatal(uint type, const char* msg, const char* file, int line, Args... args)
    {
        switch(type)
        {
            case ENGINE_ERROR: Log("[Engine Error] %s:%d: ", file, line); break;
            case OPENGL_ERROR: Log("[OpenGL Error] %s:%d: ", file, line); break;
            case GLSL_ERROR: Log("[GLSL Error] %s:%d: ", file, line); break;
            case GUI_ERROR: Log("[GUI Error] %s:%d: ", file, line); break;
            case FREETYPE_ERROR: Log("[FreeType Error] %s:%d: ", file, line); break;
        }

        
        Log(msg, args...);
        CloseLog();
        exit(EXIT_FAILURE);
    }

    template<typename... Args>
    void Critical(uint type, const char* msg, const char* file, int line, Args... args)
    {
        InitConsole();

        switch(type)
        {
            case ENGINE_ERROR: printf("[Engine Error] %s:%d: ", file, line); break;
            case OPENGL_ERROR: printf("[OpenGL Error] %s:%d: ", file, line); break;
            case GLSL_ERROR: printf("[GLSL Error] %s:%d: ", file, line); break;
            case GUI_ERROR: printf("[GUI Error] %s:%d: ", file, line); break;
            case FREETYPE_ERROR: printf("[FreeType Error] %s:%d: ", file, line); break;
        }

        printf(msg, args...);
    }
}
#endif