#include "Controller.h"

Controller::Controller()
{
    button_actions = std::map<std::string, ButtonAction>();
    stick_actions = std::map<std::string, StickAction>();
}

void Controller::SetButtonKeyboard(std::string action_name, SDL_KeyCode key)
{
    button_actions[action_name].key = key;
}

void Controller::SetButtonController(std::string action_name, SDL_GameControllerButton button)
{
    button_actions[action_name].button = button;
}

void Controller::SetStickKeyboard(std::string action_name, SDL_KeyCode up_key, SDL_KeyCode down_key, SDL_KeyCode right_key, SDL_KeyCode left_key)
{
    stick_actions[action_name].up_key = up_key;
    stick_actions[action_name].down_key = down_key;
    stick_actions[action_name].right_key = right_key;
    stick_actions[action_name].left_key = left_key;
}

void Controller::SetStickController(std::string action_name, bool use_right_stick)
{
    stick_actions[action_name].x_axis = (use_right_stick) ? SDL_CONTROLLER_AXIS_RIGHTX : SDL_CONTROLLER_AXIS_LEFTX;
    stick_actions[action_name].y_axis = (use_right_stick) ? SDL_CONTROLLER_AXIS_RIGHTY : SDL_CONTROLLER_AXIS_LEFTY;
}

void Controller::PollEvents()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        for(std::pair<std::string, ButtonAction> action : button_actions)
        {
            ButtonAction button_action = action.second;
            switch(event.type)
            {
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == button_action.key)
                    {
                        button_action.down_function();
                        return;
                    }
                    break;
                case SDL_KEYUP:
                    if(event.key.keysym.sym == button_action.key)
                    {
                        button_action.up_function();
                        return;
                    }
                    break;
                case SDL_CONTROLLERBUTTONDOWN:
                    if(event.cbutton.button == button_action.button)
                    {
                        button_action.down_function();
                        return;
                    }
                    break;
                case SDL_CONTROLLERBUTTONUP:
                    if(event.cbutton.button == button_action.button)
                    {
                        button_action.up_function();
                        return;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if(event.button.button == button_action.mouse_button)
                    {
                        button_action.down_function();
                        return;
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if(event.button.button == button_action.mouse_button)
                    {
                        button_action.up_function();
                        return;
                    }
                    break;
            }
        }
        

        for(std::pair<std::string, StickAction> action : stick_actions)
        {
            StickAction stick_action = action.second;
            switch(event.type)
            {
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == stick_action.right_key)
                    {
                        stick_action.x_function(StickXEvent(SHRT_MAX));
                        return;
                    }
                    
                    if(event.key.keysym.sym == stick_action.left_key)
                    {
                        stick_action.x_function(StickXEvent(SHRT_MIN));
                        return;
                    }
                    
                    if(event.key.keysym.sym == stick_action.down_key)
                    {
                        stick_action.y_function(StickYEvent(SHRT_MAX));
                        return;
                    }
                    
                    if(event.key.keysym.sym == stick_action.up_key)
                    {
                        stick_action.y_function(StickYEvent(SHRT_MIN));
                        return;
                    }
                    break;
                case SDL_KEYUP:
                    if(event.key.keysym.sym == stick_action.up_key || event.key.keysym.sym == stick_action.down_key)
                    {
                        stick_action.x_function(StickXEvent(0));
                        return;
                    }
                    
                    if(event.key.keysym.sym == stick_action.up_key || event.key.keysym.sym == stick_action.down_key)
                    {
                        stick_action.y_function(StickYEvent(0));
                        return;
                    }
                    
                    break;
                case SDL_CONTROLLERAXISMOTION:
                    if(event.caxis.axis == stick_action.x_axis)
                    {
                        stick_action.x_function(StickXEvent(event.caxis.value));
                        return;
                    }
                    
                    if(event.caxis.axis == stick_action.y_axis)
                    {
                        stick_action.y_function(StickYEvent(event.caxis.value));
                        return;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    stick_action.x_function(StickXEvent(event.motion.xrel));
                    stick_action.y_function(StickYEvent(event.motion.yrel));
                    return;
            }
        }
    }
}