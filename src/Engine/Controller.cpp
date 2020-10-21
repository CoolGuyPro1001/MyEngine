#include "Controller.h"

Controller::Controller()
{
    button_actions = std::vector<ButtonAction>();
    stick_actions = std::vector<StickAction>();
}

void Controller::BindButtonPress(std::string name, std::function<void()> button_press_function)
{
    button_actions[name].down_function = button_press_function;
}

void Controller::BindButtonRelease(std::string name, std::function<void()> button_release_function)
{
    button_actions[name].up_function = button_release_function;
}

void Controller::BindStickX(std::string name, std::function<void(StickEventX)> stick_x_function)
{
    button_actions[name].x_function = stick_x_function;
}

void Controller::BindStickY(std::string name, std::function<void(StickEventY)> stick_y_function)
{
    button_actions[name].y_function = stick_y_function;
}

void Controller::SetButtonKeyboard(std::string name, SDL_KeyCode key)
{
    button_actions[name].key = key;
}

void Controller::SetButtonController(std::string name, SDL_GameControllerButton button)
{
    button_actions[name].button = button;
}

void Controller::SetStickKeyboard(std::string name, SDL_KeyCode up_key, SDL_KeyCode down_key, SDL_KeyCode right_key, SDL_KeyCode left_key);
{
    stick_actions[name].up_key = up_key;
    stick_actions[name].down_key = down_key;
    stick_actions[name].right_key = right_key;
    stick_actions[name].left_key = left_key;
}

void Controller::SetStickController(std::string name, bool right_stick)
{
    stick_actions[name].x_axis = (right_stick) ? SDL_CONTROLLER_AXIS_RIGHTX : SDL_CONTROLLER_AXIS_LEFTX;
    stick_actions[name].y_axis = (right_stick) ? SDL_CONTROLLER_AXIS_RIGHTY : SDL_CONTROLLER_AXIS_LEFTY;
}

void Controller::PollEvents()
{
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
            StickAction action = stick_actions[i];
            switch(event.type)
            {
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == action.second.right_key)
                    {
                        action.second.x_function(StickEventX(SHRT_MAX));
                        return;
                    }
                    else if(event.key.keysym.sym == action.second.left_key)
                    {
                        action.second.x_function(StickEventX(SHRT_MIN));
                        return;
                    }
                    else if(event.key.keysym.sym == action.second.down_key)
                    {
                        action.second.y_function(StickEventY(SHRT_MAX));
                        return;
                    }
                    else if(event.key.keysym.sym == action.second.up_key)
                    {
                        action.second.y_function(StickEventY(SHRT_MIN));
                        return;
                    }
                    break;
                case SDL_KEYUP:
                    if(event.key.keysym.sym == action.second.up_key || event.key.keysym.sym == action.second.down_key)
                    {
                        action.second.x_function(StickEventX(0));
                        return;
                    }
                    else if(event.key.keysym.sym == action.second.up_key || event.key.keysym.sym == action.second.down_key)
                    {
                        action.second.y_function(StickEventY(0));
                        return;
                    }
                    
                    break;
                case SDL_CONTROLLERAXISMOTION:
                    if(event.caxis.axis == action.second.x_axis)
                    {
                        action.second.x_function(StickEventX(event.caxis.value));
                        return;
                    }
                    else if(event.caxis.axis == action.second.y_axis)
                    {
                        action.second.y_function(StickEventY(event.caxis.value));
                        return;
                    }
                    break;
            }
        }
    }
}