#include "Enviroment.h"

namespace Engine
{
    void Tick(std::vector<std::function<void()>> tick_functions)
    {
        for(std::function<void()> ticks : tick_functions)
        {
            ticks;
        }
    }
}