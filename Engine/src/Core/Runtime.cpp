#include "Runtime.h"
#include "Graphics/Graphics.h"
#include "Entry.h"
#include "Log.h"
#include "Common/Mathematics.h"

namespace Engine
{
    std::chrono::duration<double, std::milli> delay;

    float Normalize(int num, int low, int high)
    {
        if(num < low || num > high)
        {
            return 0;
        }

        return (num - low) / (high - low);
    }

    double Delay()
    {
        return delay.count();
    }

    void PollEvents(std::vector<Controller>& controllers)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    exit(EXIT_SUCCESS);
                    break;
                case SDL_WINDOWEVENT:
                    switch(event.window.event)
                    {
                        case SDL_WINDOWEVENT_CLOSE:
                            Close();
                            break;
                        case SDL_WINDOWEVENT_ENTER:
                            break;
                        case SDL_WINDOWEVENT_LEAVE:
                            break;
                        case SDL_WINDOWEVENT_RESIZED:
                            SDL_GetWindowSize(Graphics::window, &Graphics::window_width, &Graphics::window_height);
                            glViewport(0, 0, Graphics::window_width, Graphics::window_height);
                    }
                    break;
                case SDL_KEYDOWN:
                {
                    for(Controller controller : controllers)
                    {
                        for(ButtonAction action : controller.button_actions)
                        {
                            if(event.key.keysym.sym == action.key)
                            {
                                action.down_function();
                                return;
                            }
                        }
                        
                        for(StickAction action : controller.stick_actions)
                        {
                            if(event.key.keysym.sym == action.right_key)
                            {
                                action.x_function(StickXEvent(SHRT_MAX));
                                return;
                            }
                            
                            if(event.key.keysym.sym == action.left_key)
                            {
                                action.x_function(StickXEvent(SHRT_MIN));
                                return;
                            }
                            
                            if(event.key.keysym.sym == action.down_key)
                            {
                                action.y_function(StickYEvent(SHRT_MIN));
                                return;
                            }
                            
                            if(event.key.keysym.sym == action.up_key)
                            {
                                action.y_function(StickYEvent(SHRT_MAX));
                                return;
                            }
                        }
                    }
                    break;
                }
                case SDL_KEYUP:
                {
                    for(Controller controller : controllers)
                    {
                        for(ButtonAction action : controller.button_actions)
                        {
                            if(event.key.keysym.sym == action.key)
                            {
                                action.up_function();
                                return;
                            }
                        }
                        
                        for(StickAction action : controller.stick_actions)
                        {
                            if(event.key.keysym.sym == action.right_key || event.key.keysym.sym == action.left_key)
                            {
                                action.x_function(StickXEvent(0));
                                return;
                            }
                            
                            if(event.key.keysym.sym == action.up_key || event.key.keysym.sym == action.down_key)
                            {
                                action.y_function(StickYEvent(0));
                                return;
                            }
                        }
                    }
                    break;
                }
                case SDL_CONTROLLERBUTTONDOWN:
                {
                    Controller controller = controllers[event.cbutton.which];
                    for(ButtonAction action : controller.button_actions)
                    {
                        if(event.cbutton.button == action.button)
                        {
                            action.down_function();
                            return;
                        }
                    }
                    break;
                }
                case SDL_CONTROLLERBUTTONUP:
                {
                    Controller controller = controllers[event.cbutton.which];
                    for(ButtonAction action : controller.button_actions)
                    {
                        if(event.cbutton.button == action.button)
                        {
                            action.up_function();
                            return;
                        }
                    }
                    break;
                }
                case SDL_CONTROLLERAXISMOTION:
                {
                    Controller controller = controllers[event.caxis.which];
                    for(StickAction action : controller.stick_actions)
                    {
                        if(event.caxis.axis == action.x_axis)
                        {
                            action.x_function(StickXEvent(event.caxis.value));
                            return;
                        }
                        
                        if(event.caxis.axis == action.y_axis)
                        {
                            action.y_function(StickYEvent(event.caxis.value));
                            return;
                        }
                    }
                    break;
                }
                case SDL_MOUSEBUTTONDOWN:
                {
                    for(Controller controller : controllers)
                    {
                        for(ButtonAction action : controller.button_actions)
                        {
                            if(event.button.button == action.mouse_button)
                            {
                                action.down_function();
                                return;
                            }
                        }
                    }
                    break;
                }
                case SDL_MOUSEBUTTONUP:
                {
                    for(Controller controller : controllers)
                    {
                        for(ButtonAction action : controller.button_actions)
                        {
                            if(event.button.button == action.mouse_button)
                            {
                                action.up_function();
                                return;
                            }
                        }
                    }
                    break;
                }/*
                case SDL_MOUSEMOTION:
                {
                    for(Controller controller : controllers)
                    {
                        for(StickAction action : controller.stick_actions)
                        {
                            action.x_function(StickXEvent(event.motion.xrel));
                            action.y_function(StickYEvent(event.motion.yrel));
                        }
                    }
                    break;
                }*/
            }
        }
    }

    void SetFlatCollisionNormals(std::vector<CollisionTri>& collisions)
    {
        for(CollisionTri& col : collisions)
        {
            Vector3 u = col.p1 - col.p0; 
            Vector3 v = col.p2 - col.p0; 
            col.normal = CrossProduct(u, v);
        }
    }

    void DoCollision(std::vector<Shared<Actor>> all_actors, std::vector<CollisionTri> flat_collisions)
    {
        for(Shared<Actor> actor : all_actors)
        {
            Vector3& velocity = actor->position_velocity;

            if(velocity == Vector3(0, 0, 0))
                continue;

            Vector3& position = actor->position;
            Vector3 position_before = actor->position - velocity;

            if(CollisionBox* actor_box = dynamic_cast<CollisionBox*>(actor->collision))
            {
                float actor_d = actor_box->depth / 2;
                float actor_h = actor_box->height / 2;
                float actor_w = actor_box->width / 2;

                //Four Corners
                Vector3 actor_a = position + Vector3(actor_d, actor_h, actor_w);
                Vector3 actor_b = position - Vector3(actor_d, actor_h, actor_w);

                //Detect Collision With Other Actors
                for(Shared<Actor> a : all_actors)
                {
                    if(a->collision == actor_box)
                        continue;

                    if(CollisionBox* box = dynamic_cast<CollisionBox*>(a->collision))
                    {
                        float other_d = actor_box->depth / 2;
                        float other_h = actor_box->height / 2;
                        float other_w = actor_box->width / 2;

                        Vector3 other_a = a->position + Vector3(other_d, other_h, other_w);
                        Vector3 other_b = a->position - Vector3(other_d, other_h, other_w);

                        if(actor_a >= other_b && actor_b <= other_a)
                        {
                            position = position_before;
                            velocity = Vector3(0, 0, 0);
                        }
                    }
                }

                if(velocity == Vector3(0, 0, 0))
                    continue;

                Vector3 origin_pos = position_before + Vector3(actor_d, actor_h, actor_w);
                Vector3 origin_neg = position_before - Vector3(actor_d, actor_h, actor_w);

                Vector3 depth = origin_neg + Vector3(actor_d, 0, 0);
                Vector3 height = origin_neg + Vector3(0, actor_h, 0);
                Vector3 width = origin_neg + Vector3(0, 0, actor_w);
                Vector3 depth_n = origin_pos - Vector3(actor_d, 0, 0);
                Vector3 height_n = origin_pos - Vector3(0, actor_h, 0);
                Vector3 width_n = origin_pos - Vector3(0, 0, actor_w);

                Vector3 dir = NormalizeVector3(velocity);
                Vector3 intersect_pos;
                Vector3 intersect_neg;
                float m_pos;
                float m_neg;

                //Detect Collision With Flat Collisions
                for(CollisionTri col : flat_collisions)
                {   
                    //X Collision
                    if(velocity.x > 0)
                    {
                        if(IntersectParallelpipedTriangle(origin_pos, dir, depth_n, height_n, 
                            col.p0, col.p1, col.p2, col.normal, intersect_pos, m_pos))
                        {
                           if(DotProduct(Vector3(1, 0, 0), col.normal) != 0 && velocity.x >= intersect_pos.x - origin_pos.x)
                           {
                               position.x = intersect_pos.x - actor_d;
                               velocity.x = 0;
                           }
                        }
                    }
                    else if(velocity.x < 0)
                    {
                        if(IntersectParallelpipedTriangle(origin_neg, dir, width, height, 
                            col.p0, col.p1, col.p2, col.normal, intersect_neg, m_neg))
                        {
                            if(DotProduct(Vector3(-1, 0, 0), col.normal) != 0 && -velocity.x >= origin_neg.x - intersect_neg.x)
                            {
                                position.x = intersect_neg.x + actor_d;
                                velocity.x = 0;
                            }
                        }
                    }

                    //Y Collision
                    if(velocity.y > 0)
                    {
                        if(IntersectParallelpipedTriangle(origin_pos, dir, width_n, depth_n, 
                            col.p0, col.p1, col.p2, col.normal, intersect_pos, m_pos))
                        {
                           if(DotProduct(Vector3(0, 1, 0), col.normal) != 0 && velocity.y >= intersect_pos.y - origin_pos.y)
                           {
                               position.y = intersect_pos.y - actor_h;
                               velocity.y = 0;
                           }
                        }
                    }
                    else if(velocity.y < 0)
                    {
                        if(IntersectParallelpipedTriangle(origin_neg, dir, width, depth, 
                            col.p0, col.p1, col.p2, col.normal, intersect_neg, m_neg))
                        {
                            if(DotProduct(Vector3(0, -1, 0), col.normal) != 0 && -velocity.y >= origin_neg.y - intersect_neg.y)
                            {
                                position.y = intersect_neg.y + actor_h;
                                velocity.y = 0;
                            }
                        }
                    }

                    //Z Collision
                    if(velocity.z > 0)
                    {
                        if(IntersectParallelpipedTriangle(origin_pos, dir, depth_n, height_n, 
                            col.p0, col.p1, col.p2, col.normal, intersect_pos, m_pos))
                        {
                           if(DotProduct(Vector3(0, 0, 1), col.normal) != 0 && velocity.z >= intersect_pos.z - origin_pos.z)
                           {
                               position.z = intersect_pos.z - actor_w;
                               velocity.z = 0;
                           }
                        }
                    }
                    else if(velocity.z < 0)
                    {
                        if(IntersectParallelpipedTriangle(origin_neg, dir, depth, height, 
                            col.p0, col.p1, col.p2, col.normal, intersect_neg, m_neg))
                        {
                            if(DotProduct(Vector3(0, 0, -1), col.normal) != 0 && -velocity.z >= origin_neg.z - intersect_neg.z)
                            {
                                position.z = intersect_neg.z + actor_w;
                                velocity.z = 0;
                            }
                        }
                    }
                }
            }
        }
    }
}