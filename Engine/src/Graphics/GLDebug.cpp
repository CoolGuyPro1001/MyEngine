#include "GLDebug.h"
#include <iostream>

void ClearErrors()
{
    while(glGetError() != GL_NO_ERROR)
    {

    }
}

bool LogCall(const char* function, const char* file, int line)
{
    std::string error_message;
    while(GLenum error = glGetError())
    {
        switch(error)
        {
            case GL_INVALID_ENUM:
                error_message = "Invalid Enum";
                break;
            case GL_INVALID_VALUE:
                error_message = "Invalid Value";
                break;
            case GL_STACK_OVERFLOW:
                error_message = "Stack Overflow";
                break;
            case GL_STACK_UNDERFLOW:
                error_message = "Stack Underflow";
                break;
            case GL_OUT_OF_MEMORY:
                error_message = "Out Of Memory";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                error_message = "Invalid Framebuffer Operation";
                break;
            case GL_CONTEXT_LOST:
                error_message = "Context Lost";
                break;
            case GL_TABLE_TOO_LARGE:
                error_message = "Table Too Large";
                break;
            case GL_INVALID_OPERATION:
                error_message = "Invalid Operation";
                break;
        }

        std::cout << "[OpenGL Error] " << file << ":" << line << ": " << error_message << "\n";
        std::cout << function << std::endl;
        return false;
    }

    return true; 
}