#ifndef SDLINPUT_H
#define SDLINPUT_H

#include "Core/Media/InputMedia.h"
#include "Core/Media/InputCodes.h"

struct AnalogFlag
{
    uint device_type;
    uint port;
    uint analog;
    bool event_happened;
};

class SDLInput : public MInput
{
public:
    SDLInput();

    void CollectEvents();
    void HandleEvents();
    std::vector<Shared<InputDevice>> CurrentDevices();

private:
    void MapGamepadButtons();
    void MapKeyboardButtons();
    void MapMouseButtons();

    void MapGamepadAnalogs();

    bool GamepadDetected(uint& port);
    bool KeyboardDetected(int* num_keys);
    bool MouseDetected();

    int m_num_keys;
    bool m_mouse_moving;
    bool m_mouse_scrolling;

    std::vector<uint> m_gamepad_button_codes;
    std::vector<uint> m_gamepad_analog_codes;
    std::vector<uint> m_key_codes;
    std::vector<uint> m_mouse_button_codes;
};
#endif
