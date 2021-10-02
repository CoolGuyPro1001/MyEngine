#ifndef SWORD_H
#define SWORD_H

#include <Component.h>

class Sword : public Component
{
public:
    Sword(Shared<Model> model, Shared<Actor> actor);
};

#endif