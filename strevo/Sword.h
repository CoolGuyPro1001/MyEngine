#ifndef SWORD_H
#define SWORD_H

#include <Actor.h>

class Sword : public Actor
{
public:
    Sword();
    void Tick() override;
};

#endif
