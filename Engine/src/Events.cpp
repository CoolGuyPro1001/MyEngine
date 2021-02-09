#include "Events.h"

ButtonEvent::ButtonEvent()
{
    value = SHRT_MAX;
}

ButtonEvent::ButtonEvent(ushort val)
{
    value = val;
}

StickXEvent::StickXEvent(short val) : value(val)
{
}

StickYEvent::StickYEvent(short val) : value(val)
{
}