#include "Controller.h"

Controller::Controller()
{
    button_actions = std::map<std::string, ButtonAction>();
    stick_actions = std::map<std::string, StickAction>();
}

void Controller::SetButtonKeyboard(std::string name, SDL_KeyCode key)
{
    button_actions[name].key = key;
}

void Controller::SetButtonController(std::string name, SDL_GameControllerButton button)
{
    button_actions[name].button = button;
}

void Controller::SetStickKeyboard(std::string name, SDL_KeyCode up_key, SDL_KeyCode down_key, SDL_KeyCode right_key, SDL_KeyCode left_key)
{
    stick_actions[name].up_key = up_key;
    stick_actions[name].down_key = down_key;
    stick_actions[name].right_key = right_key;
    stick_actions[name].left_key = left_key;
}

void Controller::SetStickController(std::string name, bool use_right_stick)
{
    stick_actions[name].x_axis = (use_right_stick) ? SDL_CONTROLLER_AXIS_RIGHTX : SDL_CONTROLLER_AXIS_LEFTX;
    stick_actions[name].y_axis = (use_right_stick) ? SDL_CONTROLLER_AXIS_RIGHTY : SDL_CONTROLLER_AXIS_LEFTY;
}

void Controller::PollEvents()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        for(std::pair<std::string, ButtonAction> action : button_actions)
        {
            switch(event.type)
            {
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == action.second.key)
                    {
                        action.second.down_function();
                        return;
                    }
                    break;
                case SDL_KEYUP:
                    if(event.key.keysym.sym == action.second.key)
                    {
                        action.second.up_function();
                        return;
                    }
                    break;
                case SDL_CONTROLLERBUTTONDOWN:
                    if(event.cbutton.button == action.second.button)
                    {
                        action.second.down_function();
                        return;
                    }
                    break;
                case SDL_CONTROLLERBUTTONUP:
                    if(event.cbutton.button == action.second.button)
                    {
                        action.second.up_function();
                        return;
                    }
                    break;
            }
        }

        for(std::pair<std::string, StickAction> action : stick_actions)
        {
            switch(event.type)
            {
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == action.second.right_key)
                    {
                        action.second.x_function(StickXEvent(SHRT_MAX));
                        return;
                    }
                    else if(event.key.keysym.sym == action.second.left_key)
                    {
                        action.second.x_function(StickXEvent(SHRT_MIN));
                        return;
                    }
                    else if(event.key.keysym.sym == action.second.down_key)
                    {
                        action.second.y_function(StickYEvent(SHRT_MAX));
                        return;
                    }
                    else if(event.key.keysym.sym == action.second.up_key)
                    {
                        action.second.y_function(StickYEvent(SHRT_MIN));
                        return;
                    }
                    break;
                case SDL_KEYUP:
                    if(event.key.keysym.sym == action.second.up_key || event.key.keysym.sym == action.second.down_key)
                    {
                        action.second.x_function(StickXEvent(0));
                        return;
                    }
                    else if(event.key.keysym.sym == action.second.up_key || event.key.keysym.sym == action.second.down_key)
                    {
                        action.second.y_function(StickYEvent(0));
                        return;
                    }
                    
                    break;
                case SDL_CONTROLLERAXISMOTION:
                    if(event.caxis.axis == action.second.x_axis)
                    {
                        action.second.x_function(StickXEvent(event.caxis.value));
                        return;
                    }
                    else if(event.caxis.axis == action.second.y_axis)
                    {
                        action.second.y_function(StickYEvent(event.caxis.value));
                        return;
                    }
                    break;
            }
        }
    }
}