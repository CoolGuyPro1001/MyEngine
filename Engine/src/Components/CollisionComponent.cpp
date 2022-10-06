#include "CollisionComponent.h"

#include "Level.h"

CCollision::CCollision()
{
}

void CCollision::AttachToLevel(Level& lvl)
{
    lvl.collision_components.push_back(shared_from_this());
}

CCollision::CCollision(float depth, float height, float width) : depth(depth), height(height), width(width)
{
}

/*void Collision::Print()
{
    Log("Colliding\n");
}*/

/*CollisionTri::CollisionTri()
{
    p0 = Vector3();
    p1 = Vector3();
    p2 = Vector3();
    normal = Vector3();
}

CollisionTri::CollisionTri(Vector3 p0, Vector3 p1, Vector3 p2) : p0(p0), p1(p1), p2(p2)
{
}

CollisionTri::CollisionTri(const CollisionTri& other_col)
{
    p0 = other_col.p0;
    p1 = other_col.p1;
    p2 = other_col.p2;
    normal = other_col.normal;
}

CollisionQuad::CollisionQuad(Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3) : p0(p0), p1(p1), p2(p2), p3(p3)
{
}

void CollisionBox::Print()
{
    Log("Box Colliding\n");
}

void CollisionSphere::Print()
{
    Log("Ball Colliding\n");
}

void SetFlatCollisionNormals(std::vector<CollisionTri>& collisions)
{
    for(CollisionTri& col : collisions)
    {
        Vector3 u = col.p1 - col.p0; 
        Vector3 v = col.p2 - col.p0; 
        col.normal = CrossProduct(u, v);
        CriticalErrorArgs(ENGINE_ERROR, "%f %f %f\n", col.normal.x, col.normal.y, col.normal.z);
    }
}*/

/*void DoCollision(std::vector<Collision> collisions)
{
    for(Shared<Object>& object : all_objects)
    {
        Vector3 velocity = object->GetPositionVelocity();

        if(velocity == Vector3(0, 0, 0) || !object->collision)
            continue;

        Vector3 position = object->GetPosition();
        Vector3 position_before = position - velocity;

        if(CollisionBox* actor_box = dynamic_cast<CollisionBox*>(object->collision))
        {
            Vector3 new_position = position;
            Vector3 new_velocity = velocity;

            float actor_d = actor_box->depth / 2;
            float actor_h = actor_box->height / 2;
            float actor_w = actor_box->width / 2;

            //Four Corners
            Vector3 actor_a = position + Vector3(actor_d, actor_h, actor_w);
            Vector3 actor_b = position - Vector3(actor_d, actor_h, actor_w);

            //Detect Collision With Other Actors
            for(Shared<Actor>& a : all_actors)
            {
                if(a->collision == actor_box)
                    continue;

                if(CollisionBox* box = dynamic_cast<CollisionBox*>(a->collision))
                {
                    float other_d = actor_box->depth / 2;
                    float other_h = actor_box->height / 2;
                    float other_w = actor_box->width / 2;

                    Vector3 other_a = a->GetPosition() + Vector3(other_d, other_h, other_w);
                    Vector3 other_b = a->GetPosition() - Vector3(other_d, other_h, other_w);

                    if(actor_a >= other_b && actor_b <= other_a)
                    {
                        new_position = position_before;
                        new_velocity = Vector3(0, 0, 0);
                    }
                }
            }

            if(new_velocity == Vector3(0, 0, 0))
            {
                actor->SetPosition(new_position);
                actor->SetPositionVelocity(new_velocity);
                continue;
            }

            Vector3 origin_pos = position_before + Vector3(actor_d, actor_h, actor_w);
            Vector3 origin_neg = position_before - Vector3(actor_d, actor_h, actor_w);

            Vector3 depth = origin_neg + Vector3(actor_d, 0, 0);
            Vector3 height = origin_neg + Vector3(0, actor_h, 0);
            Vector3 width = origin_neg + Vector3(0, 0, actor_w);
            Vector3 depth_n = origin_pos - Vector3(actor_d, 0, 0);
            Vector3 height_n = origin_pos - Vector3(0, actor_h, 0);
            Vector3 width_n = origin_pos - Vector3(0, 0, actor_w);

            Vector3 dir = NormalizeVector3(new_velocity);
            Vector3 intersect_pos;
            Vector3 intersect_neg;
            float m_pos;
            float m_neg;

            //Detect Collision With Flat Collisions
            for(CollisionTri col : flat_collisions)
            {   
                //X Collision
                if(new_velocity.x > 0)
                {
                    if(IntersectParallelpipedTriangle(origin_pos, dir, depth_n, height_n, 
                        col.p0, col.p1, col.p2, col.normal, intersect_pos, m_pos))
                    {
                        if(DotProduct(Vector3(1, 0, 0), col.normal) != 0 && new_velocity.x >= intersect_pos.x - origin_pos.x)
                        {
                            new_position.x = intersect_pos.x - actor_d;
                            new_velocity.x = 0;
                        }
                    }
                }
                else if(new_velocity.x < 0)
                {
                    if(IntersectParallelpipedTriangle(origin_neg, dir, width, height, 
                        col.p0, col.p1, col.p2, col.normal, intersect_neg, m_neg))
                    {
                        if(DotProduct(Vector3(-1, 0, 0), col.normal) != 0 && -new_velocity.x >= origin_neg.x - intersect_neg.x)
                        {
                            new_position.x = intersect_neg.x + actor_d;
                            new_velocity.x = 0;
                        }
                    }
                }

                //Y Collision
                if(new_velocity.y > 0)
                {
                    if(IntersectParallelpipedTriangle(origin_pos, dir, width_n, depth_n, 
                        col.p0, col.p1, col.p2, col.normal, intersect_pos, m_pos))
                    {
                        if(DotProduct(Vector3(0, 1, 0), col.normal) != 0 && new_velocity.y >= intersect_pos.y - origin_pos.y)
                        {
                            new_position.y = intersect_pos.y - actor_h;
                            new_velocity.y = 0;
                        }
                    }
                }
                else if(new_velocity.y < 0)
                {
                    if(IntersectParallelpipedTriangle(origin_neg, dir, width, depth, 
                        col.p0, col.p1, col.p2, col.normal, intersect_neg, m_neg))
                    {
                        if(DotProduct(Vector3(0, -1, 0), col.normal) != 0 && -new_velocity.y >= origin_neg.y - intersect_neg.y)
                        {
                            new_position.y = intersect_neg.y + actor_h;
                            new_velocity.y = 0;
                        }
                    }
                }

                //Z Collision
                if(new_velocity.z > 0)
                {
                    if(IntersectParallelpipedTriangle(origin_pos, dir, depth_n, height_n, 
                        col.p0, col.p1, col.p2, col.normal, intersect_pos, m_pos))
                    {
                        if(DotProduct(Vector3(0, 0, 1), col.normal) != 0 && new_velocity.z >= intersect_pos.z - origin_pos.z)
                        {
                            new_position.z = intersect_pos.z - actor_w;
                            new_velocity.z = 0;
                        }
                    }
                }
                else if(new_velocity.z < 0)
                {
                    if(IntersectParallelpipedTriangle(origin_neg, dir, depth, height, 
                        col.p0, col.p1, col.p2, col.normal, intersect_neg, m_neg))
                    {
                        if(DotProduct(Vector3(0, 0, -1), col.normal) != 0 && -new_velocity.z >= origin_neg.z - intersect_neg.z)
                        {
                            new_position.z = intersect_neg.z + actor_w;
                            new_velocity.z = 0;
                        }
                    }
                }
            }
            actor->SetPosition(new_position);
            actor->SetPositionVelocity(new_velocity);
        }
    }
}*/
