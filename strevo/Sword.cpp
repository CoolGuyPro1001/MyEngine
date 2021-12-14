#include "Sword.h"

Sword::Sword() : Actor()
{
    position = Vector3(5, 0, 0);
}

void Sword::Tick()
{
    Actor::Tick();
}
