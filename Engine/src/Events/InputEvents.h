#ifndef INPUTEVENTS_H
#define INPUTEVENTS_H

#include "Events.h"

template<typename RetValue, typename... Args>
struct Delegate;

struct EButtonInput : public Event
{
    EButtonInput();
    void AddListener(Shared<Delegate<void, EButtonInput*>> func);
    void Announce();
    void Process();

    bool pressed;

private:
    std::vector<Shared<Delegate<void, EButtonInput*>>> m_listeners;
};

struct EAnalogInput : public Event
{
    void Process();
    void Announce();
    void AddListener(Shared<Delegate<void, EAnalogInput*>> func);

    float value; //-1.0 to 1.0

private:
    std::vector<Shared<Delegate<void, EAnalogInput*>>> m_listeners;
};

struct EDeviceDetected : public Event
{
    void Process();
    void Announce();
    void AddListener(Shared<Delegate<void, EDeviceDetected*>> func);

    uint port;

private:
    std::vector<Shared<Delegate<void, EDeviceDetected*>>> m_listeners;
};

#endif
