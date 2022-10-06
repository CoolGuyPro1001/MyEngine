#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H

#include "Component.h"

struct Level;

/*
 * AABB Collision Between Actors
 * [depth] Is Size Along X Direction
 * [height] Is Size Along Y Direction
 * [width] Is Size Along Z Direction
 * See Common/Vector3.h For More Details About Coordinates
 */

struct CCollision : public Component, public std::enable_shared_from_this<CCollision>
{
    CCollision();
    CCollision(float depth, float height, float width);
    void AttachToLevel(Level& lvl);

    float depth;
    float height;
    float width;
    //virtual void Print();
};

/*struct CollisionTri
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

void SetFlatCollisionNormals(std::vector<CollisionTri>& flat_collisions);*/
void DoCollision(std::vector<CCollision> collisions);
#endif
