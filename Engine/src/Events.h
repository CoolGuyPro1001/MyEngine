#ifndef EVENTS_H
#define EVENTS_H

#include "Controller.h"

class Controller;

struct Event
{
    bool handled;

    virtual std::string ToString() = 0;
};

struct EventArgs
{

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

void PollEvents(std::vector<Shared<Controller>>& controllers);

#endif