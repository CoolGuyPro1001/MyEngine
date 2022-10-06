#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

#include "Common/Delegate.h"

struct EButtonInput;
struct EAnalogInput;

enum InputDeviceType
{
    GAMEPAD_DEVICE, KEYBOARD_DEVICE, MOUSE_DEVICE
};

/*An Abstract Device For Input That Receives It's Data From A Input Backend
 * Buttons Are Digital Inputs, Like Keys And Gamepad Buttons
 * Analogs Are Variable Inputs, Like Mouse Position And Gamepad Sticks
 * States, Changes, And Events Match And Are In Order
 * Key Codes, Mouse Codes, Gamepad Buttons Codes, Etc. Can Be Found In Core/Media/InputValues.h
 */

class InputDevice
{
public:

    //Instead Of Derived Classes, Each Input Device Has A Number Of Buttons And Analogs
    //Port 0 Is For Global Devices (Keyboard, Mouse)
    InputDevice(uint type, uint port, uint button_amount, uint analog_amount);
    ~InputDevice();

    void Handle();

    // Also Called By Other Functions
    bool HasButton(uint button_id);
    bool HasAnalog(uint analog_id);

    //The Return Value Is Error (0 = Error, 1 = Success)
    bool GetButtonState(uint button_id, bool& state);
    bool GetButtonChange(uint button_id, uint& change);

    bool GetAnalogValue(uint analog_id, float& value);
    bool GetAnalogChange(uint analog_id, bool& change);

    bool GetButtonEvent(uint button_id, EButtonInput*& event);
    bool GetAnalogEvent(uint analog_id, EAnalogInput*& event);

    //For Binding Functions To Button (Pressed And Released) Or Analog Events
    bool BindButton(uint button_id, Shared<Delegate<void, EButtonInput*>> button_function);
    bool BindAnalog(uint analog_id, Shared<Delegate<void, EAnalogInput*>> analog_function);


    //Binding Functions With No Delegate Argument Needed
    template<typename RetType, typename... Args>
    bool BindButton(uint button_id, RetType (*button_function)(Args...));

    template<class ObjType, typename RetType, typename... Args>
    bool BindButton(uint button_id, ObjType* object, RetType(ObjType::*button_function)(Args...));

    template<class ObjType, typename RetType, typename... Args>
    bool BindButton(uint button_id, Shared<ObjType> object, RetType(ObjType::*button_function)(Args...));


    template<typename RetType, typename... Args>
    bool BindAnalog(uint analog_id, RetType (*analog_function)(Args...));

    template<class ObjType, typename RetType, typename... Args>
    bool BindAnalog(uint analog_id, ObjType* object, RetType (ObjType::*analog_function)(Args...));

    template<class ObjType, typename RetType, typename... Args>
    bool BindAnalog(uint analog_id, Shared<ObjType> object, RetType(ObjType::*analog_function)(Args...));

    float deadzone_radius;

    friend class MInput;
    friend class SDLInput;
    friend class XInput;

private:
    uint m_port;
    uint m_type;

    std::vector<bool> m_button_states; //Index Is The Input Code
    std::vector<uint> m_button_changes; //Query. Cleared On Every Handle()

    std::vector<float> m_analog_values; //Index Is The Input Code
    std::vector<uint> m_analog_changes; //Query. Cleared On Every Handle()
    std::vector<bool> m_in_deadzone;

    std::vector<EButtonInput*> m_button_events;
    std::vector<EAnalogInput*> m_analog_events;
};

template<typename RetType, typename... Args>
bool InputDevice::BindButton(uint button_id, RetType (*button_function)(Args...))
{
    Shared<Delegate<void, EButtonInput*>> button_delegate = CreateShared<Delegate<void, EButtonInput*>>();
    button_delegate->Bind(button_function);

    return BindButton(button_id, button_delegate);
}

template<class ObjType, typename RetType, typename... Args>
bool InputDevice::BindButton(uint button_id, ObjType* object, RetType(ObjType::*button_function)(Args...))
{
    Shared<Delegate<void, EButtonInput*>> button_delegate = CreateShared<Delegate<void, EButtonInput*>>();
    button_delegate->Bind(object, button_function);

    return BindButton(button_id, button_delegate);
}

template<class ObjType, typename RetType, typename... Args>
bool InputDevice::BindButton(uint button_id, Shared<ObjType> object, RetType(ObjType::*button_function)(Args...))
{
    Shared<Delegate<void, EButtonInput*>> button_delegate = CreateShared<Delegate<void, EButtonInput*>>();
    button_delegate->Bind(object, button_function);

    return BindButton(button_id, button_delegate);
}





template<typename RetType, typename... Args>
bool InputDevice::BindAnalog(uint analog_id, RetType (*analog_function)(Args...))
{
    Shared<Delegate<void, EAnalogInput*>> analog_delegate = CreateShared<Delegate<void, EAnalogInput*>>();
    analog_delegate->Bind(analog_function);

    return BindAnalog(analog_id, analog_delegate);
}

template<class ObjType, typename RetType, typename... Args>
bool InputDevice::BindAnalog(uint analog_id, ObjType* object, RetType (ObjType::*analog_function)(Args...))
{
    Shared<Delegate<void, EAnalogInput*>> analog_delegate = CreateShared<Delegate<void, EAnalogInput*>>();
    analog_delegate->Bind(object, analog_function);

    return BindAnalog(analog_id, analog_delegate);
}

template<class ObjType, typename RetType, typename... Args>
bool InputDevice::BindAnalog(uint analog_id, Shared<ObjType> object, RetType(ObjType::*analog_function)(Args...))
{
    Shared<Delegate<void, EAnalogInput*>> analog_delegate = CreateShared<Delegate<void, EAnalogInput*>>();
    analog_delegate->Bind(object, analog_function);

    return BindAnalog(analog_id, analog_delegate);
}
#endif
