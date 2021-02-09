#ifndef EVENTS_H
#define EVENTS_H

struct Event
{
    bool handled;

    virtual std::string ToString() = 0;
};

struct ButtonEvent
{
    ushort value;
    ButtonEvent();
    ButtonEvent(ushort val);
};

struct StickXEvent
{
    short value;
    StickXEvent(short val);
};

struct StickYEvent
{
    short value;
    StickYEvent(short val);
};

#endif