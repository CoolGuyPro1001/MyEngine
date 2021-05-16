#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Events.h"

struct ButtonAction
{
    std::vector<std::function<void()>> down_functions;
    std::vector<std::function<void()>> up_functions;

    SDL_KeyCode key;
    SDL_GameControllerButton button;
    Uint8 mouse_button;
};

struct StickAction
{
    std::vector<std::function<void(StickXEvent)>> x_functions;
    std::vector<std::function<void(StickYEvent)>> y_functions;

    SDL_KeyCode up_key;
    SDL_KeyCode down_key;
    SDL_KeyCode right_key;
    SDL_KeyCode left_key;

    SDL_GameControllerAxis x_axis;
    SDL_GameControllerAxis y_axis;
};


SDL_KeyCode GetKeyCode(std::string key);

template<class PuppetType, class F, class... Args>
void BindButtonPress(ButtonAction& action, PuppetType& puppet, F&& button_press_function, Args... args)
{
    action.down_functions.push_back(std::bind(button_press_function, puppet, args...));
};

template<class F, class... Args>
void BindButtonPress(ButtonAction& action, F&& button_press_function, Args... args)
{
    action.down_functions.push_back(std::bind(button_press_function, args...));
}

template<class PuppetType, class F, class... Args>
void BindButtonRelease(ButtonAction& action, PuppetType& puppet, F&& button_release_function, Args... args)
{
    action.up_functions.push_back(std::bind(button_release_function, puppet, args...));
};

template<class F, class... Args>
void BindButtonRelease(ButtonAction& action, F&& button_release_function, Args... args)
{
    action.up_functions.push_back(std::bind(button_release_function, args...));
}

template<class PuppetType, class F, class... Args>
void BindStickX(StickAction& action, PuppetType& puppet, F&& stick_x_function, Args... args)
{
    action.x_functions.push_back(std::bind(stick_x_function, puppet, std::placeholders::_1, args...));
};

template<class F, class... Args>
void BindStickX(StickAction& action, F&& stick_x_function, Args... args)
{
    action.x_functions.push_back(std::bind(stick_x_function, std::placeholders::_1, args...));
};

template<class PuppetType, class F, class... Args>
void BindStickY(StickAction& action, PuppetType& puppet, F&& stick_y_function, Args... args)
{
    action.y_functions.push_back(std::bind(stick_y_function, puppet, std::placeholders::_1, args...));
};

template<class F, class... Args>
void BindStickY(StickAction& action, F&& stick_y_function, Args... args)
{
    action.y_functions.push_back(std::bind(stick_y_function, std::placeholders::_1, args...));
};

struct Controller
{
public:
    Controller();
    
    void AddButtonAction(ButtonAction action);
    void AddStickAction(StickAction action);

    std::vector<ButtonAction> button_actions;
    std::vector<StickAction> stick_actions;

    bool enabled;
};

#endif