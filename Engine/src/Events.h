#ifndef EVENTS_H
#define EVENTS_H

enum class MouseCodes
{
    LEFT_CLICK,
    RIGHT_CLICK
};

struct Event
{
    bool handled;
    virtual std::string ToString() = 0;
};

struct MouseEvent : Event
{
    int x;
    int y;
    MouseCodes button;
};

struct StickXEvent
{
    int value;
    StickXEvent(int val);
};

struct StickYEvent
{
    int value;
    StickYEvent(int val);
};

#endif