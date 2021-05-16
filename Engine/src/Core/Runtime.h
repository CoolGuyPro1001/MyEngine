#ifndef RUNTIME_H
#define RUNTIME_H

#include "Controller.h"
#include "Collision.h"
#include "Actor.h"

namespace Engine
{
    extern std::chrono::duration<double, std::milli> delay;

    float Normalize(int num, int low, int high);
    void PollEvents(std::vector<Shared<Controller>>& controllers);
    void SetFlatCollisionNormals(std::vector<CollisionTri>& flat_collisions);
    void DoCollision(std::vector<Shared<Actor>> all_actors, std::vector<CollisionTri> flat_collisions);
    double Delay();
}
#endif