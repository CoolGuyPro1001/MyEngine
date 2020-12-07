#include "Events.h"

StickXEvent::StickXEvent(int val) : value(val)
{

}

StickYEvent::StickYEvent(int val) : value(val)
{
    
}

void PollEvents(std::vector<Controller>& controllers, uint window_id)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_KEYDOWN:
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
                            action.y_function(StickYEvent(SHRT_MAX));
                            return;
                        }
                        
                        if(event.key.keysym.sym == action.up_key)
                        {
                            action.y_function(StickYEvent(SHRT_MIN));
                            return;
                        }
                    }
                }
                break;
            case SDL_KEYUP:
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
                    
                    for(StickAction actio : controller.stick_actions)
                    {
                        if(event.key.keysym.sym == action.up_key || event.key.keysym.sym == action.down_key)
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
            case SDL_CONTROLLERBUTTONDOWN:
                Controller controller = controllers[event.cbutton.which];
                for(ButtonAction action : controller.button_actions)
                {
                    if(event.cbutton.button == button_action.button)
                    {
                        button_action.down_function();
                        return;
                    }
                }
                break;
            case SDL_CONTROLLERBUTTONUP:
                Controller controller = controllers[event.cbutton.which];
                for(ButtonAction action : controller.button_actions)
                {
                    if(event.cbutton.button == button_action.button)
                    {
                        button_action.up_function();
                        return;
                    }
                }
                break;
            case SDL_CONTROLLERAXISMOTION:
                Controller controller = controllers[event.caxis.which];
                for(StickAction action : controller)
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
            case SDL_MOUSEBUTTONDOWN:
                for(Controller controller : controllers)
                {
                    for(ButtonAction action : controller.button_actions)
                    {
                        if(event.button.button == action.mouse_button)
                        {
                            button_action.down_function();
                            return;
                        }
                    }
                }
                
                break;
            case SDL_MOUSEBUTTONUP:
                for(Controller controller : controllers)
                {
                    for(ButtonAction action : controller.button_actions)
                    {
                        if(event.button.button == action.mouse_button)
                        {
                            button_action.up_function();
                            return;
                        }
                    }
                }
                break;
            case SDL_MOUSEMOTION:
                stick_action.x_function(StickXEvent(event.motion.xrel));
                stick_action.y_function(StickYEvent(event.motion.yrel));
        }
    }
}