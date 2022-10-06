#include "InputDevice.h"

#include "Events/InputEvents.h"
#include "Common/Error.h"
#include "Common/Delegate.h"


InputDevice::InputDevice(uint type, uint port, uint button_amount, uint analog_amount)
{
    m_button_changes = std::vector<uint>();
    m_analog_changes = std::vector<uint>(analog_amount);
    m_button_states = std::vector<bool>(button_amount);
    m_analog_values = std::vector<float>(analog_amount);
    m_in_deadzone = std::vector<bool>(analog_amount, true);

    m_button_events = std::vector<EButtonInput*>(button_amount);
    m_analog_events = std::vector<EAnalogInput*>(analog_amount);

    m_port = port;
    m_type = type;

    deadzone_radius = 0;
}

InputDevice::~InputDevice()
{
    for(EButtonInput*& button_event : m_button_events)
    {
        if(button_event)
            delete button_event;
    }

    for(EAnalogInput*& analog_event : m_analog_events)
    {
        if(analog_event)
            delete analog_event;
    }
}

bool InputDevice::HasButton(uint button_id)
{
    if(button_id > m_button_states.size())
    {
        CriticalError(INPUT_ERROR, "Parameter button_id Exceeds The Number Of Buttons For This Device. Returning False\n" \
            "This Error Can Be Triggered By Other Functions. Double Check Any Function Calls Relating To Buttons\n"
        );
        return false;
    };
    return true;
}

bool InputDevice::HasAnalog(uint analog_id)
{
    if(analog_id > m_analog_values.size())
    {
        CriticalError(INPUT_ERROR, "Parameter analog_id Exceeds The Number Of Analog Inputs For This Device. Returning False\n" \
            "Examples Of Analog Inputs: Gamepad Thumbsticks (Has Two For Both Vertical And Horizontal), Mouse Scroll Wheel, Gamepad Triggers\n" \
            "This Error Can Be Triggered By Other Functions. Double Check Any Function Calls Relating To Analog\n"
        );
        return false;
    };
    return true;
}

bool InputDevice::GetButtonState(uint button_id, bool& state)
{
    bool has_button = HasButton(button_id);

    /* If has_button Is False (0), 0 x button_id = 0
     * Or If has_button Is True (1), 1 x button_id = button_id
     * This Works For ButtonChange(), AnalogValues(), and AnalogChange()
     */

    state = m_button_states[has_button * button_id];
    return has_button;
};

bool InputDevice::GetButtonChange(uint button_id, uint& change)
{
    bool has_button = HasButton(button_id);
    change = m_button_changes[has_button * button_id];
    return has_button;
}

bool InputDevice::GetAnalogValue(uint analog_id, float& value)
{
    bool has_analog = HasAnalog(analog_id);
    value = m_analog_values[has_analog * analog_id];
    return has_analog;
}

bool InputDevice::GetAnalogChange(uint analog_id, bool& change)
{
    bool has_analog = HasAnalog(analog_id);
    change = m_analog_changes[has_analog * analog_id];
    return has_analog;
}

bool InputDevice::GetButtonEvent(uint button_id, EButtonInput*& event)
{
    if(!HasButton(button_id))
        return false;

    event = m_button_events[button_id];
    if(event)
        return true;
    return false;
}

bool InputDevice::GetAnalogEvent(uint analog_id, EAnalogInput*& event)
{
    if(!HasAnalog(analog_id))
        return false;

    event = m_analog_events[analog_id];
    if(event)
        return true;
    return false;
}

bool InputDevice:: BindButton(uint button_id, Shared<Delegate<void, EButtonInput*>> button_function)
{
    if(!HasButton(button_id))
        return false;

    EButtonInput*& button_event = m_button_events[button_id];

    if(!button_event)
        button_event = new EButtonInput;

    button_event->AddListener(button_function);
    return true;
}

bool InputDevice::BindAnalog(uint analog_id, Shared<Delegate<void, EAnalogInput*>> analog_function)
{
    if(!HasAnalog(analog_id))
        return false;

    EAnalogInput*& analog_event = m_analog_events[analog_id];

    if(!analog_event)
        analog_event = new EAnalogInput;

    analog_event->AddListener(analog_function);

    return true;
}

void InputDevice::Handle()
{
    for(uint b_change : m_button_changes)
    {
        EButtonInput* e;
        if(GetButtonEvent(b_change, e))
        {
            e->pressed = m_button_states[b_change];
            e->Announce();
        }
    }

    for(uint a_change : m_analog_changes)
    {
        EAnalogInput* e;
        if(GetAnalogEvent(a_change, e))
        {
            float analog_value = m_analog_values[a_change];
            bool in_deadzone = m_in_deadzone[a_change];

            if(abs(analog_value) >= deadzone_radius)
            {
                e->value = analog_value;
                m_in_deadzone[a_change] = false;
                e->Announce();
            }
            else
            {
                if(in_deadzone)
                    continue;

                m_in_deadzone[a_change] = true;
                e->value = 0;
                e->Announce();
            }
        }
    }

    m_button_changes.clear();
    m_analog_changes.clear();
}

