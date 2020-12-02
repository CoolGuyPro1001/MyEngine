#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Events.h"

#include <climits>

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_gamecontroller.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_mouse.h>


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
    void BindButtonPress(std::string name, PuppetType& puppet, F&& button_press_function)
    {
        button_actions[name].down_function = std::bind(button_press_function, &puppet);
    };

    template<class PuppetType, class F>
    void BindButtonRelease(std::string name, PuppetType& puppet, F&& button_release_function)
    {
        button_actions[name].up_function = std::bind(button_release_function, &puppet);
    };

    template<class PuppetType, class F>
    void BindStickX(std::string name, PuppetType& puppet, F&& stick_x_function)
    {
        stick_actions[name].x_function = std::bind(stick_x_function, &puppet, std::placeholders::_1);
    };

    template<class PuppetType, class F>
    void BindStickY(std::string name, PuppetType& puppet, F&& stick_y_function)
    {
        stick_actions[name].y_function = std::bind(stick_y_function, &puppet, std::placeholders::_1);
    };

    void SetButtonKeyboard(std::string action_name, SDL_KeyCode key);
    void SetButtonController(std::string action_name, SDL_GameControllerButton button);
    void SetStickKeyboard(std::string action_name, SDL_KeyCode up_key, SDL_KeyCode down_key, SDL_KeyCode right_key, SDL_KeyCode left_key);
    void SetStickController(std::string action_name, bool use_right_stick);
    void SetStickMouse(std::string action_name);
    
    void PollEvents();

private:
    std::map<std::string, ButtonAction> button_actions;
    std::map<std::string, StickAction> stick_actions;
};

#endif