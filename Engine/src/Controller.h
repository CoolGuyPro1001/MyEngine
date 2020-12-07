#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Events.h"


struct ButtonAction
{
    std::function<void()> down_function;
    std::function<void()> up_function;

    SDL_KeyCode key;
    SDL_GameControllerButton button;
    Uint8 mouse_button;
};

struct StickAction
{
    std::function<void(StickXEvent)> x_function;
    std::function<void(StickYEvent)> y_function;

    SDL_KeyCode up_key;
    SDL_KeyCode down_key;
    SDL_KeyCode right_key;
    SDL_KeyCode left_key;

    SDL_GameControllerAxis x_axis;
    SDL_GameControllerAxis y_axis;
};


class Controller
{
public:
    Controller();
    
    template<class PuppetType, class F>
    void BindButtonPress(ButtonAction action, PuppetType& puppet, F&& button_press_function)
    {
        button_actions.push_back(action);
        action.down_function = std::bind(button_press_function, &puppet);
    };

    template<class PuppetType, class F>
    void BindButtonRelease(ButtonAction action, PuppetType& puppet, F&& button_release_function)
    {
        button_actions.push_back(action);
        action.up_function = std::bind(button_release_function, &puppet);
    };

    template<class PuppetType, class F>
    void BindStickX(StickAction action, PuppetType& puppet, F&& stick_x_function)
    {
        stick_actions.push_back(action);
        action.x_function = std::bind(stick_x_function, &puppet, std::placeholders::_1);
    };

    template<class PuppetType, class F>
    void BindStickY(StickAction action, PuppetType& puppet, F&& stick_y_function)
    {
        stick_actions.push_back(action);
        action.y_function = std::bind(stick_y_function, &puppet, std::placeholders::_1);
    };

    std::vector<ButtonAction> button_actions = std::vector<ButtonAction>();
    std::vector<StickAction> stick_actions = std::vector<StickAction>();
};

#endif