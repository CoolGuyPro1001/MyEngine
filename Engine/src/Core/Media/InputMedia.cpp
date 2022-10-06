#include "InputMedia.h"

#include "Core/MediaDevices/InputDevice.h"
#include "Common/Delegate.h"

MInput::MInput()
{
    m_devices = std::vector<Shared<InputDevice>>(); //MInput Interface Has No Devices
    m_devices.reserve(4); //Reserve vector capacity to hold at least four devices before reallocating

    m_device_connect_event = new EDeviceDetected;
    m_device_disconnect_event = new EDeviceDetected;

    max_mouse_velocity = 1.0f;
    max_mouse_wheel_velocity = 1.0f;
}

MInput::~MInput()
{
    m_devices.clear();
    delete m_device_connect_event;
    delete m_device_disconnect_event;
}

void MInput::HandleDevices()
{
    for(Shared<InputDevice>& d : m_devices)
        d->Handle();
}

void MInput::BindDeviceConnect(Shared<Delegate<void, EDeviceDetected*>> func)
{
    m_device_connect_event->AddListener(func);
}

void MInput::BindDeviceDisconnect(Shared<Delegate<void, EDeviceDetected*>> func)
{
    m_device_disconnect_event->AddListener(func);
}

Shared<InputDevice> MInput::GetInputDevice(uint type, uint port)
{
    for(Shared<InputDevice> d: m_devices)
    {
        if(d->m_type == type && d->m_port == port)
            return d;
    }
    return nullptr;
}

void MInput::AddDevice(uint type, uint port, uint num_buttons, uint num_analogs)
{
    m_devices.push_back(CreateShared<InputDevice>(type, port, num_buttons, num_analogs));
}

void MInput::RemoveDevice(uint type, uint port)
{
    //Removal code
    //auto it = devices.begin() + port_number;
    //devices.erase(it);
}
