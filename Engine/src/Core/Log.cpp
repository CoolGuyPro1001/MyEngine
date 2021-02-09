#include "Log.h"

namespace Engine
{
    static FILE* log_file;
    bool InitLog()
    {
        log_file = fopen("log.txt", "w");
        return log_file != nullptr;
    }

    bool CloseLog()
    {
        fclose(log_file);
    }

    void Log(const char* s, ...)
    {
        va_list args;
        va_start(args, s);

        while(*s != '\0')
        {
            if(*s == '%')
            {
                switch(*(s + 1))
                {
                    case 'd':
                    {
                        int i = va_arg(args, int);
                        fputs(std::to_string(i).c_str(), log_file);
                        break;
                    }
                    case 'f':
                    {
                        double d = va_arg(args, double);
                        fputs(std::to_string(d).c_str(), log_file);
                        break;
                    }
                    /*case 'c':
                    {
                        char c = va_arg(args, int);
                        fputs(&c, log_file);
                        break;
                    }*/
                    case 's':
                    {
                        const char* s = va_arg(args, const char*);
                        fputc(*s, log_file);
                        break;
                    }
                }
                s++;
            }
            else
            {
                fputc(*s, log_file);
            }
            s++;
        }
    }
}