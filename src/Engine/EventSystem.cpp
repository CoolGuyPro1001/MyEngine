#include "EventSystem.h"

namespace EventSystem
{
    void Publish(Event e)
    {
        if(e.sender == NULL)
        {
            return;
        }

        for(int i = 0; i < channels.size(); i++)
        {
            if(channels.)
        }
    }

}