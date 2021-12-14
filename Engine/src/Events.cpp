#include "Events.h"
#include "Common/Log.h"
#include "Core/Entry.h"
#include "Core/Graphics/Graphics.h"
#include "Core/Graphics/GLDebug.h"
#include "Controller.h"

ButtonEvent::ButtonEvent()
{
    value = SHRT_MAX;
}

ButtonEvent::ButtonEvent(ushort val)
{
    value = val;
}

StickXEvent::StickXEvent(short val) : value(val)
{
}

StickYEvent::StickYEvent(short val) : value(val)
{
}

void PollEvents(std::vector<Shared<Controller>>& controllers)
{
    bool mouse_moved = false;
    std::vector<SDL_Event> event_list = std::vector<SDL_Event>();

    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        event_list.push_back(event);
    }
    for(SDL_Event event : event_list)
    {
        //no_event = false;
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
                        SDL_GetWindowSize(Graphics::g_window, &Graphics::g_window_width, &Graphics::g_window_height);
                        GLCall(glViewport(0, 0, Graphics::g_window_width, Graphics::g_window_height));
                }
                break;
            case SDL_CONTROLLERDEVICEADDED:
            {
                SDL_GameControllerOpen(event.cdevice.which);
                break;
            }
            case SDL_CONTROLLERDEVICEREMOVED:
            {
                SDL_GameControllerClose(SDL_GameControllerFromInstanceID(event.cdevice.which));
                break;
            }
            case SDL_KEYDOWN:
            {
                for(const Shared<Controller>& controller : controllers)
                {
                    if(!controller->enabled)
                        continue;

                    for(ButtonAction action : controller->button_actions)
                    {
                        if(event.key.keysym.sym == action.key)
                        {
                            for(std::function<void()> function : action.down_functions)
                                function();

                            break;
                        }
                    }
                    
                    for(StickAction action : controller->stick_actions)
                    {
                        if(event.key.keysym.sym == action.right_key)
                        {
                            for(std::function<void(StickXEvent)> function : action.x_functions)
                                function(StickXEvent(SHRT_MAX));
                            
                            action.state |= right_key_mask;
                            break;
                        }
                        
                        if(event.key.keysym.sym == action.left_key)
                        {
                            for(std::function<void(StickXEvent)> function : action.x_functions)
                                function(StickXEvent(SHRT_MIN));

                            action.state |= left_key_mask;
                            break;
                        }
                        
                        if(event.key.keysym.sym == action.down_key)
                        {
                            for(std::function<void(StickYEvent)> function : action.y_functions)
                                function(StickYEvent(SHRT_MIN));

                            action.state |= down_key_mask;
                            break;
                        }
                        
                        if(event.key.keysym.sym == action.up_key)
                        {
                            for(std::function<void(StickYEvent)> function : action.y_functions)
                                function(StickYEvent(SHRT_MAX));
                            
                            action.state = up_key_mask;
                            break;
                        }
                    }
                }
                break;
            }
            case SDL_KEYUP:
            {
                for(const Shared<Controller>& controller : controllers)
                {
                    if(!controller->enabled)
                        continue;

                    for(ButtonAction action : controller->button_actions)
                    {
                        if(event.key.keysym.sym == action.key)
                        {
                            for(std::function<void()> function : action.up_functions)
                                function();

                            break;
                        }
                    }
                    
                    for(StickAction action : controller->stick_actions)
                    {
                        if(event.key.keysym.sym == action.right_key || event.key.keysym.sym == action.left_key)
                        {
                            for(std::function<void(StickXEvent)> x_function : action.x_functions)
                                x_function(StickXEvent(0));

                            action.state &= ~(right_key_mask | left_key_mask);
                            break;
                        }
                        
                        if(event.key.keysym.sym == action.up_key || event.key.keysym.sym == action.down_key)
                        {
                            for(std::function<void(StickYEvent)> y_function : action.y_functions)
                                y_function(StickYEvent(0));

                            action.state &= ~(up_key_mask | down_key_mask);
                            break;
                        }
                    }
                }
                break;
            }
            case SDL_CONTROLLERBUTTONDOWN:
            {
                for(const Shared<Controller>& controller : controllers)
                {
                    if(!controller->enabled || controller->id != event.cbutton.which)
                        continue;

                    for(ButtonAction action : controller->button_actions)
                    {
                        if(event.cbutton.button == action.button)
                        {
                            for(std::function<void()> function : action.down_functions)
                                function();

                            goto NextEvent;
                        }
                    }

                    for(StickAction action : controller->stick_actions)
                    {
                        if(event.cbutton.button == action.right_button)
                        {
                            for(std::function<void(StickXEvent)> function : action.x_functions)
                                function(StickXEvent(SHRT_MAX));
                            
                            action.state |= right_button_mask;
                            break;
                        }
                        
                        if(event.cbutton.button == action.left_button)
                        {
                            for(std::function<void(StickXEvent)> function : action.x_functions)
                                function(StickXEvent(SHRT_MIN));

                            action.state |= left_button_mask;
                            break;
                        }
                        
                        if(event.cbutton.button== action.down_button)
                        {
                            for(std::function<void(StickYEvent)> function : action.y_functions)
                                function(StickYEvent(SHRT_MIN));

                            action.state |= down_button_mask;
                            break;
                        }
                        
                        if(event.cbutton.button == action.up_button)
                        {
                            for(std::function<void(StickYEvent)> function : action.y_functions)
                                function(StickYEvent(SHRT_MAX));
                            
                            action.state = up_button_mask;
                            break;
                        }
                    }
                }
                break;
            }
            case SDL_CONTROLLERBUTTONUP:
            {
                for(const Shared<Controller>& controller : controllers)
                {
                    if(!controller->enabled || controller->id != event.cbutton.which)
                        continue;

                    for(ButtonAction action : controller->button_actions)
                    {
                        if(event.cbutton.button == action.button)
                        {
                            for(std::function<void()> function : action.up_functions)
                                function();

                            break;
                        }
                    }

                    for(StickAction action : controller->stick_actions)
                    {
                        if(event.cbutton.button == action.right_button || event.cbutton.button == action.left_button)
                        {
                            for(std::function<void(StickXEvent)> x_function : action.x_functions)
                                x_function(StickXEvent(0));

                            action.state &= ~(right_button_mask | left_button_mask);
                            break;
                        }
                        
                        if(event.cbutton.button == action.up_button || event.cbutton.button == action.down_button)
                        {
                            for(std::function<void(StickYEvent)> y_function : action.y_functions)
                                y_function(StickYEvent(0));

                            action.state &= ~(up_button_mask | down_button_mask);
                            break;
                        }
                    }
                }
                break;
            }
            case SDL_CONTROLLERAXISMOTION:
            {
                for(const Shared<Controller>& controller : controllers)
                {
                    if(!controller->enabled || controller->id != event.caxis.which)
                        continue;

                    for(StickAction action : controller->stick_actions)
                    {
                        
                        if(event.caxis.axis == action.x_axis)
                        {
                            if(event.caxis.value < 10000 && event.caxis.value > -10000)
                            {
                                for(std::function<void(StickXEvent)> function : action.x_functions)
                                    function(StickXEvent(0));
                                action.state &= ~x_axis_mask;
                            }
                            else
                            {
                                for(std::function<void(StickXEvent)> function : action.x_functions)
                                    function(StickXEvent(event.caxis.value));
                                action.state |= x_axis_mask;
                            }

                            break;
                        }
                        
                        if(event.caxis.axis == action.y_axis)
                        {
                            if(event.caxis.value < 10000 && event.caxis.value > -10000)
                            {
                                for(std::function<void(StickYEvent)> function : action.y_functions)
                                    function(StickYEvent(0));
                                action.state &= ~y_axis_mask;
                            }
                            else
                            {
                                for(std::function<void(StickYEvent)> function : action.y_functions)
                                    function(StickYEvent(-event.caxis.value));
                                action.state |= y_axis_mask;
                            }

                            break;
                        }
                        
                    }
                }
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                for(const Shared<Controller>& controller : controllers)
                {
                    if(!controller->enabled)
                        continue;

                    for(ButtonAction action : controller->button_actions)
                    {
                        if(event.button.button == action.mouse_button)
                        {
                            for(std::function<void()> function : action.down_functions)
                                function();

                            break;
                        }
                    }
                }
                break;
            }
            case SDL_MOUSEBUTTONUP:
            {
                for(const Shared<Controller>& controller : controllers)
                {
                    if(!controller->enabled)
                        continue;
                        
                    for(ButtonAction action : controller->button_actions)
                    {
                        if(event.button.button == action.mouse_button)
                        {
                            for(std::function<void()> function : action.up_functions)
                                function();

                            break;
                        }
                    }
                }
                break;
            }
            /*case SDL_MOUSEMOTION:
            {
                for(Shared<Controller> controller : controllers)
                {
                    for(StickAction action : controller->stick_actions)
                    {
                        Log("X:%d, Y:%d\n", event.motion.xrel, event.motion.yrel);
                        for(std::function<void(StickXEvent)> x_function : action.x_functions)
                            x_function(StickXEvent(event.motion.xrel));
                        
                        for(std::function<void(StickYEvent)> y_function : action.y_functions)
                            y_function(StickYEvent(event.motion.yrel));

                        if(event.motion.xrel == 0)
                            action.state &= ~mouse_x_mask;
                        else
                            action.state |= mouse_x_mask;

                        if(event.motion.yrel == 0)
                            action.state &= ~mouse_y_mask;
                        else
                            action.state |= mouse_y_mask;
                        
                        mouse_moved = true;
                    }
                }
                break;
            }*/
        }
        NextEvent:
        float a = 5;
    }

    /*if(no_event)
    {
        for(Shared<Controller> controller : controllers)
        {
            for(StickAction action : controller->stick_actions) 
            {
                if(!action.x_key_active && !action.x_axis_active)
                {
                    for(std::function<void(StickXEvent)> x_function : action.x_functions)
                        x_function(StickXEvent(0));
                }
                
                if(!action.y_key_active && !action.y_axis_active)
                {
                    for(std::function<void(StickYEvent)> y_function : action.y_functions)
                        y_function(StickYEvent(0));
                }
            }
        }
    }*/
}
