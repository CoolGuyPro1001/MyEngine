#include "Collision.h"
#include "Core/Log.h"

Collision::Collision()
{
}

Collision::Collision(Vector3 position) : position(position)
{
}

void Collision::Print()
{
    Engine::Log("Colliding\n");
}

CollisionTri::CollisionTri(Vector3 p0, Vector3 p1, Vector3 p2) : p0(p0), p1(p1), p2(p2)
{
}

CollisionQuad::CollisionQuad(Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3) : p0(p0), p1(p1), p2(p2), p3(p3)
{
}

CollisionBox::CollisionBox()
{
}

CollisionBox::CollisionBox(Vector3 position, float depth, float height, float width) : 
    Collision(position), depth(depth), height(height), width(width)
{
}

void CollisionBox::Print()
{
    Engine::Log("Box Colliding\n");
}

CollisionSphere::CollisionSphere()
{
}

CollisionSphere::CollisionSphere(Vector3 position, float radius) : Collision(position), radius(radius)
{
}

void CollisionSphere::Print()
{
    Engine::Log("Ball Colliding\n");
}