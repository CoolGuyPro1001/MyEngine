#ifndef CONTROLLER_H
#define CONTROLLER_H

struct StickXEvent;
struct StickYEvent;

struct ButtonAction
{
    ButtonAction();
    std::vector<std::function<void()>> down_functions;
    std::vector<std::function<void()>> up_functions;

    SDL_KeyCode key;
    SDL_GameControllerButton button;
    Uint8 mouse_button;
};

//Bitwise Masks For StickAction State
constexpr u16 up_key_mask = 1 << 0;
constexpr u16 down_key_mask = 1 << 1;
constexpr u16 right_key_mask = 1 << 2;
constexpr u16 left_key_mask = 1 << 3;
constexpr u16 up_button_mask = 1 << 4;
constexpr u16 down_button_mask = 1 << 5;
constexpr u16 right_button_mask = 1 << 6;
constexpr u16 left_button_mask = 1 << 7;
constexpr u16 x_axis_mask = 1 << 8;
constexpr u16 y_axis_mask = 1 << 9;
constexpr u16 mouse_x_mask = 1 << 10;
constexpr u16 mouse_y_mask = 1 << 11;

struct StickAction
{
    StickAction();

    std::vector<std::function<void(StickXEvent)>> x_functions;
    std::vector<std::function<void(StickYEvent)>> y_functions;

    SDL_KeyCode up_key;
    SDL_KeyCode down_key;
    SDL_KeyCode right_key;
    SDL_KeyCode left_key;

    SDL_GameControllerAxis x_axis;
    SDL_GameControllerAxis y_axis;

    SDL_GameControllerButton up_button;
    SDL_GameControllerButton down_button;
    SDL_GameControllerButton right_button;
    SDL_GameControllerButton left_button;

    u16 state;
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
    int id;
};

#endif
