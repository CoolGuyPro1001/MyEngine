#include "Enviroment.h"
#include "Graphics/Graphics.h"

namespace Engine
{
    float Normalize(int num, int low, int high)
    {
        if(num < low || num > high)
        {
            return 0;
        }

        return (num - low) / (high - low);
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
                        case SDL_WINDOWEVENT_ENTER:
                            std::cout << "Mouse has entered window\n";
                            break;
                        case SDL_WINDOWEVENT_LEAVE:
                            std::cout << "Mouse has exited window\n";
                            break;
                        case SDL_WINDOWEVENT_RESIZED:
                            int window_width, window_height;
                            SDL_GetWindowSize(Graphics::window, &window_width, &window_height);
                            glViewport(0, 0, window_width, window_height);
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
}