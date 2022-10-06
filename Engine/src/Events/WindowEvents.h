#ifndef WINDOWEVENTS_H
#define WINDOWEVENTS_H

#include "Events.h"
#include "Common/Vector2.h"

template<typename RetValue, typename... Args>
struct Delegate;

struct EWindowResized : public Event
{
    EWindowResized();
    void AddListener(Shared<Delegate<void, EWindowResized*>> func);
    void Announce();
    void Process();

    Vector2 original_position; //Bottom Left Corner
    Vector2 original_size;
    Vector2 new_position;
    Vector2 new_size;
    bool max_screen;
    bool minimized;

private:
    std::vector<Shared<Delegate<void, EWindowResized*>>> m_listeners;
};


/*struct EWindowClose : public Event
{
    EWindowClose();
    void AddListener(Shared<Delegate<void, EWindowClose*>> func);
    void Announce();
    void Process();

private:
    std::vector<Shared<Delegate<void, EWindowClose*>>> listeners;
};*/

#endif
