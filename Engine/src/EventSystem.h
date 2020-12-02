#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

#include "Events.h"


namespace EventSystem
{
    void Subscribe(Channel&, std::function<void(Event e)> function);
    void UnSubscribe(Channel&, std::function<void(Event e)> function);

    template<typanem T>
    void Publish(Event<T> e);
}
#endif