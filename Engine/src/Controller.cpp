#include "Controller.h"

Controller::Controller()
{
    button_actions = std::vector<ButtonAction>();
    stick_actions = std::vector<StickAction>();
};

void Controller::AddButtonAction(ButtonAction action)
{
    button_actions.push_back(action);
}

void Controller::AddStickAction(StickAction action)
{
    stick_actions.push_back(action);
}