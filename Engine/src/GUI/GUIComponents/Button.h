#ifndef BUTTONCOMPONENT_H
#define BUTTONCOMPONENT_H

#include "GUI/GUIComponent.h"

class GButton : public GUIComponent
{
    virtual void OnPress() = 0;
    virtual void OnRelease() = 0;
    virtual void OnHover() = 0;
    virtual void OnUnHover() = 0;
};
#endif
