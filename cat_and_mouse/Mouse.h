#ifndef MOUSE_H
#define MOUSE_H

#include <Actor.h>

class Mouse : public Actor
{
public:
    Mouse(Shared<Model> model);
    void Tick();
};
#endif