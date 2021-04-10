#include "Runtime.h"
#include "Graphics/Graphics.h"
#include "Entry.h"
#include "Log.h"

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

    void DoCollision(Shared<Actor> actor, std::vector<Shared<Actor>> all_actors)
    {
        Vector3& velocity = actor->position_velocity;
        Vector3& position = actor->position;
        Vector3 position_before = actor->position - velocity;

        if(CollisionBox* actor_box = dynamic_cast<CollisionBox*>(actor->collision))
        {
            float actor_d = actor_box->depth / 2;
            float actor_h = actor_box->height / 2;
            float actor_w = actor_box->width / 2;

            Vector3 actor_a = position + Vector3(actor_d, actor_h, actor_w);
            Vector3 actor_b = position - Vector3(actor_d, actor_h, actor_w);

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
                        actor_box->Print();
                    }
                }
            }
        }
    }

    /*void ContinousCollision(Shared<Actor> actor, std::vector<Shared<Collision>> all_hitboxes)
    {
        Vector3 velocity = actor->position_velocity;
        Vector3 position = actor->position;
        Vector3 position_before = actor->position - velocity;
        
        CollisionBox* collision_box = dynamic_cast<CollisionBox*>(actor->model->collision.get());

        float xy_slope = velocity.y / velocity.x;
        float zx_slope = velocity.x / velocity.z;
        float zy_slope = velocity.y / velocity.z;

        float xy_b = xy_slope * position.x + position.y;
        float zx_b = zx_slope * position.z + position.x;
        float zy_b = zy_slope * position.z + position.y;

        //Detect
        for(Shared<Collision> hitbox : all_hitboxes)
        {
            if(hitbox.get() == collision_box)
                continue;

            if(CollisionBox* box = dynamic_cast<CollisionBox*>(hitbox.get()))
            {
                if(box->position.
            }
        }
        /*
        XYZ
            xy: b = xy_slope * (pos.x + depth) + pos.y + height
            zx: b = zx_slope * (pos.z + width) + pos.x + depth
            zy: b = zy_slope * (pos.z + width) + pos.y + height
        /*

        y - y1 = m(x-x1)
        y = m(x-(pos.x+d) + (pos.y+h)
        y = mx - m(pos.x+d) + pos.y + h
        y = mx - 
    }*/
}