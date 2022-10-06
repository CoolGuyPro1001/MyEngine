#include "SDLInput.h"
#include "SDLEvents.h"

#include "Core/MediaDevices/InputDevice.h"

#include "Common/Mathematics.h"
#include "Common/Error.h"

SDLInput::SDLInput()
{
    if(SDL_InitSubSystem(SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER) != 0)
        FatalErrorArgs(SDL_ERROR, "Unable To Initialize SDL Input: %s", SDL_GetError());

    SDL_GameControllerEventState(SDL_ENABLE);

    m_devices = CurrentDevices(); //Detects Input Devices Already Plugged In
    m_mouse_moving = false;
    m_mouse_scrolling = false;
}

void SDLInput::CollectEvents()
{
    Shared<InputDevice> device;

    auto update_device_button = [&](uint device_type, uint port, uint button_index, bool press)
    {
        device = GetInputDevice(device_type, port);
        device->m_button_states[button_index] = press;
        device->m_button_changes.push_back(button_index);
    };

    auto update_device_analog = [&](uint device_type, uint port, uint analog_index, float value)
    {
        device = GetInputDevice(device_type, port);
        device->m_analog_values[analog_index] = value;
        device->m_analog_changes.push_back(analog_index);
    };

    std::vector<SDL_Event> input_events = RetrieveSDLEvents(SDL_KEYDOWN, SDL_CONTROLLERDEVICEREMOVED);

    int analog_index;
    int button_index;

    for(SDL_Event& event : input_events)
    {
        switch(event.type)
        {
            case SDL_CONTROLLERDEVICEADDED:
            {
                SDL_GameControllerOpen(event.cdevice.which);

                MapGamepadButtons();
                MapGamepadAnalogs();
                break;
            }
            case SDL_CONTROLLERDEVICEREMOVED:
            {
                SDL_GameControllerClose(SDL_GameControllerFromInstanceID(event.cdevice.which));
                break;
            }

            case SDL_CONTROLLERAXISMOTION:
            {
                if(event.caxis.axis == -1)
                    continue;

                analog_index = m_gamepad_analog_codes[event.caxis.axis];
                float normalized_value = Normalize(event.caxis.value, -32768, 32767) * 2 - 1;

                //SDL Sets The Y Axis Values Of Each Stick To Be From Top To Bottom. Flip It!
                if(analog_index == LEFT_STICK_Y || analog_index == RIGHT_STICK_Y)
                    normalized_value *= -1;

                update_device_analog(GAMEPAD_DEVICE, event.caxis.which + 1, analog_index, normalized_value);
                break;
            }
            case SDL_MOUSEMOTION:
            {
                float normalized_x = Normalize(event.motion.xrel, -max_mouse_velocity, max_mouse_velocity) * 2 - 1;
                float normalized_y = Normalize(event.motion.yrel, -max_mouse_velocity, max_mouse_velocity) * 2 - 1;

                update_device_analog(MOUSE_DEVICE, 0, MOUSE_X, normalized_x);
                update_device_analog(MOUSE_DEVICE, 0, MOUSE_Y, normalized_y);

                m_mouse_moving = true;

                break;
            }
            case SDL_MOUSEWHEEL:
            {
                float normalized_value = Normalize(event.wheel.y, -max_mouse_wheel_velocity, max_mouse_wheel_velocity) * 2 - 1;
                int flip = (event.wheel.direction == SDL_MOUSEWHEEL_FLIPPED) ? -1 : 1;

                update_device_analog(MOUSE_DEVICE, 0, MOUSE_WHEEL, flip * normalized_value);

                m_mouse_scrolling = true;
                break;
            }
        }

        if(event.type == SDL_CONTROLLERBUTTONDOWN || event.type == SDL_CONTROLLERBUTTONUP)
        {
            if(event.cbutton.button == -1)
                continue;

            button_index = m_gamepad_button_codes[event.cbutton.button];
            update_device_button(GAMEPAD_DEVICE, event.cbutton.which + 1, button_index, event.cbutton.state);
        }
        else if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
        {
            //Skip Key Repeats
            if(event.key.repeat == 1)
                continue;

            button_index = m_key_codes[event.key.keysym.scancode];
            update_device_button(KEYBOARD_DEVICE, 0, button_index, event.key.state);
        }
        else if(event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
        {
            button_index = m_mouse_button_codes[event.button.button];
            update_device_button(MOUSE_DEVICE, 0, button_index, event.button.state);
        }
    }

    //Prevent Mouse Drifting
    if(!m_mouse_moving)
    {
        update_device_analog(MOUSE_DEVICE, 0, MOUSE_X, 0);
        update_device_analog(MOUSE_DEVICE, 0, MOUSE_Y, 0);
    }

    //Prevent Mouse Wheel Drifting
    if(!m_mouse_scrolling)
        update_device_analog(MOUSE_DEVICE, 0, MOUSE_WHEEL, 0);

    m_mouse_moving = false;
    m_mouse_scrolling = false;
    return;
}

void SDLInput::HandleEvents()
{
    for(Shared<InputDevice>& d : m_devices)
        d->Handle();
}

bool SDLInput::GamepadDetected(uint& port)
{
    for (int i = 0; i < SDL_NumJoysticks(); i++)
    {
        if (SDL_IsGameController(i))
        {
            SDL_GameControllerOpen(i);
            port = i + 1;
            return true;
        }
    }
    return false;
}

bool SDLInput::KeyboardDetected(int* num_keys)
{
    SDL_GetKeyboardState(num_keys);

    if(!num_keys)
        FatalError(SDL_ERROR, "Can't Get The Keyboard State");

    //Non-NULL num_keyboard_keys Means There Is A Keyboard Detected
    if(num_keys)
        return true;
    return false;
}

bool SDLInput::MouseDetected()
{
    int* mouse_x;
    int* mouse_y;
    SDL_GetMouseState(mouse_x, mouse_y);

    //Non-NULL mouse_x And mouse_y Means There Is A Mouse Detected
    if(mouse_x && mouse_y)
        return true;
    return false;
}

std::vector<Shared<InputDevice>> SDLInput::CurrentDevices()
{
    std::vector<Shared<InputDevice>> current_devices;

    uint port;
    if(GamepadDetected(port))
    {
        MapGamepadButtons();
        MapGamepadAnalogs();

        current_devices.push_back(CreateShared<InputDevice>(GAMEPAD_DEVICE, port, BUTTON_BACK + 1, RIGHT_STICK_Y + 1));
    }

    if(KeyboardDetected(&m_num_keys))
    {
        MapKeyboardButtons();
        current_devices.push_back(CreateShared<InputDevice>(KEYBOARD_DEVICE, 0, KEY_EQUALS + 1, 0));
    }

    //For Now, A Mouse Has Three Buttons (Left, Middle, Right) And Three Axis (X, Y)
    if(MouseDetected())
    {
        MapMouseButtons();
        current_devices.push_back(CreateShared<InputDevice>(MOUSE_DEVICE, 0, MOUSE_MIDDLE_BUTTON + 1, MOUSE_Y + 1));
    }

    return current_devices;
}

//Mapping Functions

void SDLInput::MapGamepadButtons()
{
    m_gamepad_button_codes = std::vector<uint>(SDL_CONTROLLER_BUTTON_DPAD_RIGHT + 1);

    std::array<uint, NUM_GAMEPAD_BUTTON_CODES> sdl_gamepad_buttons =
    {
        SDL_CONTROLLER_BUTTON_A, SDL_CONTROLLER_BUTTON_B, SDL_CONTROLLER_BUTTON_X, SDL_CONTROLLER_BUTTON_Y,
        SDL_CONTROLLER_BUTTON_DPAD_UP, SDL_CONTROLLER_BUTTON_DPAD_DOWN, SDL_CONTROLLER_BUTTON_DPAD_LEFT, SDL_CONTROLLER_BUTTON_DPAD_RIGHT,
        SDL_CONTROLLER_BUTTON_LEFTSTICK, SDL_CONTROLLER_BUTTON_RIGHTSTICK, SDL_CONTROLLER_BUTTON_LEFTSHOULDER, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,
        SDL_CONTROLLER_BUTTON_START, SDL_CONTROLLER_BUTTON_BACK
    };

    for(int i = 0; i < NUM_GAMEPAD_BUTTON_CODES; i++)
        m_gamepad_button_codes[sdl_gamepad_buttons[i]] = i;
}

void SDLInput::MapKeyboardButtons()
{
    m_key_codes = std::vector<uint>(m_num_keys);

    std::array<uint, NUM_KEY_CODES> sdl_keys =
    {
        SDL_SCANCODE_LALT, SDL_SCANCODE_RALT, SDL_SCANCODE_BACKSPACE, SDL_SCANCODE_CAPSLOCK, SDL_SCANCODE_LCTRL, SDL_SCANCODE_RCTRL,
        SDL_SCANCODE_RETURN, SDL_SCANCODE_ESCAPE, SDL_SCANCODE_SPACE, SDL_SCANCODE_TAB, SDL_SCANCODE_LSHIFT, SDL_SCANCODE_RSHIFT,
        SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_INSERT, SDL_SCANCODE_DELETE,
        SDL_SCANCODE_HOME, SDL_SCANCODE_END, SDL_SCANCODE_PAGEUP, SDL_SCANCODE_PAGEDOWN, SDL_SCANCODE_PRINTSCREEN,

        SDL_SCANCODE_0, SDL_SCANCODE_1, SDL_SCANCODE_2, SDL_SCANCODE_3, SDL_SCANCODE_4, SDL_SCANCODE_5, SDL_SCANCODE_6,
        SDL_SCANCODE_7, SDL_SCANCODE_8, SDL_SCANCODE_9,

        SDL_SCANCODE_A, SDL_SCANCODE_B, SDL_SCANCODE_C, SDL_SCANCODE_D, SDL_SCANCODE_E, SDL_SCANCODE_F, SDL_SCANCODE_G,
        SDL_SCANCODE_H, SDL_SCANCODE_I, SDL_SCANCODE_J, SDL_SCANCODE_K, SDL_SCANCODE_L, SDL_SCANCODE_M, SDL_SCANCODE_N, SDL_SCANCODE_O,
        SDL_SCANCODE_P, SDL_SCANCODE_Q, SDL_SCANCODE_R, SDL_SCANCODE_S, SDL_SCANCODE_T, SDL_SCANCODE_U, SDL_SCANCODE_V, SDL_SCANCODE_W,
        SDL_SCANCODE_X, SDL_SCANCODE_Y, SDL_SCANCODE_Z,

        SDL_SCANCODE_KP_0, SDL_SCANCODE_KP_1, SDL_SCANCODE_KP_2, SDL_SCANCODE_KP_3, SDL_SCANCODE_KP_4, SDL_SCANCODE_KP_5,
        SDL_SCANCODE_KP_6, SDL_SCANCODE_KP_7, SDL_SCANCODE_KP_8, SDL_SCANCODE_KP_9, SDL_SCANCODE_KP_PERIOD, SDL_SCANCODE_KP_ENTER,
        SDL_SCANCODE_KP_PLUS, SDL_SCANCODE_KP_MINUS, SDL_SCANCODE_KP_MULTIPLY, SDL_SCANCODE_KP_DIVIDE,

        SDL_SCANCODE_F1, SDL_SCANCODE_F2, SDL_SCANCODE_F3, SDL_SCANCODE_F4, SDL_SCANCODE_F5, SDL_SCANCODE_F6, SDL_SCANCODE_F7, SDL_SCANCODE_F8,
        SDL_SCANCODE_F9, SDL_SCANCODE_F10, SDL_SCANCODE_F11, SDL_SCANCODE_F12,

        SDL_SCANCODE_COMMA, SDL_SCANCODE_PERIOD, SDL_SCANCODE_SLASH, SDL_SCANCODE_SEMICOLON, SDL_SCANCODE_APOSTROPHE, SDL_SCANCODE_LEFTBRACKET,
        SDL_SCANCODE_RIGHTBRACKET, SDL_SCANCODE_BACKSLASH, SDL_SCANCODE_GRAVE, SDL_SCANCODE_MINUS, SDL_SCANCODE_EQUALS
    };

    for(int i = 0; i < NUM_KEY_CODES; i++)
    {
        /*
         * Example: SDL_SCANCODE_A = 10
         * i = 34, Which Is KEY_A
         * sdl_scancode = 10
         * keyboard_state_indexes[10] = 34
         * keyboard_sate_indexes[SDL_SCANCODE_A] = KEY_A
         */

        uint sdl_scancode = sdl_keys[i];
        m_key_codes[sdl_scancode] = i;
    }
}

void SDLInput::MapMouseButtons()
{
    m_mouse_button_codes = std::vector<uint>(SDL_BUTTON_RIGHT + 1);

    std::array<uint, NUM_MOUSE_BUTTON_CODES> sdl_mouse_buttons =
    {
        SDL_BUTTON_LEFT, SDL_BUTTON_RIGHT, SDL_BUTTON_MIDDLE
    };

    for(int i = 0; i < NUM_MOUSE_BUTTON_CODES; i++)
        m_mouse_button_codes[sdl_mouse_buttons[i]] = i;
}

void SDLInput::MapGamepadAnalogs()
{
    m_gamepad_analog_codes = std::vector<uint>(SDL_CONTROLLER_AXIS_TRIGGERLEFT + 1);

    std::array<uint, NUM_GAMEPAD_ANALOG_CODES> sdl_gamepad_analogs =
    {
        SDL_CONTROLLER_AXIS_TRIGGERLEFT, SDL_CONTROLLER_AXIS_TRIGGERRIGHT,
        SDL_CONTROLLER_AXIS_LEFTX, SDL_CONTROLLER_AXIS_LEFTY,
        SDL_CONTROLLER_AXIS_RIGHTX, SDL_CONTROLLER_AXIS_RIGHTY
    };

    for(int i = 0; i < NUM_GAMEPAD_ANALOG_CODES; i++)
        m_gamepad_analog_codes[sdl_gamepad_analogs[i]] = i;
}
