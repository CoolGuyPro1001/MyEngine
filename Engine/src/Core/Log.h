#ifndef LOG_H
#define LOG_H

namespace Engine
{
    bool CloseLog();
    bool InitLog();
    void Log(const char* s, ...);
}
#endif