#ifndef RUNTIME_H
#define RUNTIME_H

#include "Controller.h"
#include "Collision.h"
#include "Actor.h"

namespace Engine
{
    extern std::chrono::duration<double, std::milli> delay;

    float Normalize(int num, int low, int high);
    void PollEvents(std::vector<Controller>& controllers);
    void DoCollision(Shared<Actor> actor, std::vector<Shared<Actor>> other_actors);
    double Delay();
}
#endif