#include "Console.h"

static bool console = false;

void InitConsole()
{
    if(!console)
    {
    #if _WIN32
        AllocConsole();
        freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
        printf("Debug Console Window\n");
    #endif
        console = true;
    }
}

void CloseConsole()
{
    if(console)
    {
    #if _WIN32
        FreeConsole();
    #endif
    }
}