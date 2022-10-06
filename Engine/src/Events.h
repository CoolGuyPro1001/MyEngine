#ifndef EVENTS_H
#define EVENTS_H

#define TIME std::chrono::high_resolution_clock::time_point
#define TIME_NOW std::chrono::high_resolution_clock::now()

template<typename RetValue, typename... Args>
struct Delegate;

struct Event
{
    Event();
    virtual void Announce();
    virtual void Process() = 0;

    TIME time;

    //virtual std::string ToString() = 0;
};

static auto compare = [](Event* left, Event* right) { return left->time > right->time; };
static std::priority_queue<Event*, std::vector<Event*>, decltype(compare)>& EventQueue();
void ProcessEvents();

void AddToEventQueue(Event* event);

#endif
