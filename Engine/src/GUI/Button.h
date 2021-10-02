#ifndef BUTTON_H
#define BUTTON_H

#include "GUI/Widget.h"

class Button : public Widget
{
    virtual void OnPress() = 0;
    virtual void OnRelease() = 0;
    virtual void OnHover() = 0;
    virtual void OnUnHover() = 0;
};
#endif