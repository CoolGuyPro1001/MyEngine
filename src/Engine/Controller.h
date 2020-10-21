#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Common/Units.h"
#include "Events.h"

#include <functional>
#include <climits>
#include <map>

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_gamecontroller.h>
#include <SDL2/SDL_scancode.h>

struct ButtonAction

    std::function<void()> down_function;
    std::function<void()> up_function;

    SDL_KeyCode key;
    SDL_GameControllerButton button;
};

struct StickAction
{
    std::function<void(StickEventX)> x_function;
    std::function<void(StickEventY)> y_function;

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
    
    void BindButtonPress(std::string name, std::function<void()> button_press_function);
    void BindButtonRelease(std::string name, std::function<void()> button_release_function);
    void BindStickX(std::string name, std::function<void(StickEventX)> stick_x_function);
    void BindStickY(std::string name, std::function<void(StickEventY)> stick_y_function);

    void SetButtonKeyboard(std::string name, SDL_KeyCode key);
    void SetButtonController(std::string name, SDL_GameControllerButton button);
    void SetStickKeyboard(std::string name, SDL_KeyCode up_key, SDL_KeyCode down_key, SDL_KeyCode right_key, SDL_KeyCode left_key);
    void SetStickController(std::string name, bool right_stick);
    
    void PollEvents();

private:
    std::map<std::string, ButtonAction> button_actions;
    std::map<std::string, StickAction> stick_actions;
};
#endif