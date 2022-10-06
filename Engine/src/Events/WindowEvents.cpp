#include "WindowEvents.h"
#include "Common/Delegate.h"

EWindowResized::EWindowResized()
{
    m_listeners = std::vector<Shared<Delegate<void, EWindowResized*>>>();
}

void EWindowResized::AddListener(Shared<Delegate<void, EWindowResized*>> func)
{
    m_listeners.push_back(func);
}

void EWindowResized::Announce()
{
    Event* e = this;
    AddToEventQueue(e);
}

void EWindowResized::Process()
{
    for(Shared<Delegate<void, EWindowResized*>> f : m_listeners)
        f->Execute(this);
}
