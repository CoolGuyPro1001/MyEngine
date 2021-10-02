#include "Log.h"

static FILE* log_file;
bool InitLog()
{
    log_file = fopen("log.txt", "w");
    if(!log_file)
        printf("Can't Log: %s\n", strerror(errno));
    return log_file != nullptr;
}

bool CloseLog()
{
    if(log_file)
        return (bool) fclose(log_file);
    return false;
}

void Log(const char* s, ...)
{
    if(log_file == nullptr)
        InitLog();

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
                    fputs(std::to_string(i).c_str(), stdout);
                    break;
                }
                case 'f':
                {
                    double d = va_arg(args, double);
                    fputs(std::to_string(d).c_str(), stdout);
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
                    fputs(s, stdout);
                    break;
                }
            }
            s++;
        }
        else
        {
            fputc(*s, stdout);
        }
        s++;
    }
}