#include "Controller.h"

ButtonAction::ButtonAction()
{
    key = SDLK_UNKNOWN;
    button = SDL_CONTROLLER_BUTTON_INVALID;
    mouse_button = 0;
}

StickAction::StickAction()
{
    up_key = SDLK_UNKNOWN;
    down_key = SDLK_UNKNOWN;
    right_key = SDLK_UNKNOWN;
    left_key = SDLK_UNKNOWN;

    x_axis = SDL_CONTROLLER_AXIS_INVALID;
    y_axis = SDL_CONTROLLER_AXIS_INVALID;

    up_button = SDL_CONTROLLER_BUTTON_INVALID;
    down_button = SDL_CONTROLLER_BUTTON_INVALID;
    right_button = SDL_CONTROLLER_BUTTON_INVALID;
    left_button = SDL_CONTROLLER_BUTTON_INVALID;

    state = 0;
}

Controller::Controller()
{
    button_actions = std::vector<ButtonAction>();
    stick_actions = std::vector<StickAction>();
    enabled = true;
    id = -1;
};

void Controller::AddButtonAction(ButtonAction action)
{
    button_actions.push_back(action);
}

void Controller::AddStickAction(StickAction action)
{
    stick_actions.push_back(action);
}