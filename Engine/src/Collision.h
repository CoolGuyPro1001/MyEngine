#ifndef COLLISION_H
#define COLLISION_H

#include "Actor.h"

#include "Common/Vector3.h"

class Actor;

struct Collision
{
    Collision();
    Collision(Vector3 position);
    virtual void Print();
    Vector3 position;
};


struct CollisionTri
{
    CollisionTri();
    CollisionTri(Vector3 p0, Vector3 p1, Vector3 p2);
    CollisionTri(const CollisionTri& other_col);
    
    Vector3 p0, p1, p2;
    Vector3 normal;
};

struct CollisionQuad
{
    CollisionQuad(Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3);
    Vector3 p0, p1, p2, p3;
};

struct CollisionBox : public Collision
{
    CollisionBox();
    CollisionBox(Vector3 position, float depth, float height, float width);
    void Print() override;
    float width; //z
    float height; //y
    float depth; //x
};

struct CollisionSphere : public Collision
{
    CollisionSphere();
    CollisionSphere(Vector3 position, float radius);
    void Print() override;
    float radius;
};

void SetFlatCollisionNormals(std::vector<CollisionTri>& flat_collisions);
void DoCollision(std::vector<Shared<Actor>>& all_actors, std::vector<CollisionTri>& flat_collisions);
#endif