#include "Events.h"

std::priority_queue<Event*, std::vector<Event*>, decltype(compare)>& EventQueue()
{
    static std::priority_queue<Event*, std::vector<Event*>, decltype(compare)> event_queue(compare);
    return event_queue;
}

void AddToEventQueue(Event* event)
{
    EventQueue().push(event);
}

void ProcessEvents()
{
    while(!EventQueue().empty())
    {
        EventQueue().top()->Process();
        EventQueue().pop();
    }
}

//These Functions Are Redundant, But I Don't Know Any Fixes

Event::Event()
{
    time = TIME_NOW;
}

void Event::Announce()
{
    time = TIME_NOW;
}
