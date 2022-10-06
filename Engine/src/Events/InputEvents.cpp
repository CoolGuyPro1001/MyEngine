#include "InputEvents.h"
#include "Common/Delegate.h"

EButtonInput::EButtonInput()
{
    m_listeners = std::vector<Shared<Delegate<void, EButtonInput*>>>();
}

void EButtonInput::AddListener(Shared<Delegate<void, EButtonInput*>> func)
{
    m_listeners.push_back(func);
}

void EButtonInput::Announce()
{
    Event* e = this;
    AddToEventQueue(e);
}

void EButtonInput::Process()
{
    for(Shared<Delegate<void, EButtonInput*>> f : m_listeners)
        f->Execute(this);
}

void EAnalogInput::AddListener(Shared<Delegate<void, EAnalogInput*>> func)
{
    m_listeners.push_back(func);
}

void EAnalogInput::Announce()
{
    Event* e = this;
    AddToEventQueue(e);
}

void EAnalogInput::Process()
{
    for(Shared<Delegate<void, EAnalogInput*>> f : m_listeners)
        f->Execute(this);
}

void EDeviceDetected::AddListener(Shared<Delegate<void, EDeviceDetected*>> func)
{
    m_listeners.push_back(func);
}

void EDeviceDetected::Announce()
{
    Event* e = this;
    AddToEventQueue(e);
}

void EDeviceDetected::Process()
{
    for(Shared<Delegate<void, EDeviceDetected*>> f : m_listeners)
        f->Execute(this);
}
