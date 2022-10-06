#ifndef INPUTMEDIA_H
#define INPUTMEDIA_H

#include "Core/MediaDevices/InputDevice.h"
#include "Events/InputEvents.h"

class Controller;
class InputDevice;

template<typename RetValue, typename... Args>
struct Delegate;

/*
 * An Interface For Managing Input
 * Set(Device Name)StateIndexes Are For Setting An State Index Array
 * Where Each Index Corresponds To A Key Code, Mouse Code, Etc. From The Backend
 */

class MInput
{
public:
    MInput();
    ~MInput();

    virtual void CollectEvents() = 0;
    virtual void HandleEvents() = 0;
    virtual std::vector<Shared<InputDevice>> CurrentDevices() = 0;

    void BindDeviceConnect(Shared<Delegate<void, EDeviceDetected*>> func);
    void BindDeviceDisconnect(Shared<Delegate<void, EDeviceDetected*>> func);

    Shared<InputDevice> GetInputDevice(uint type, uint port = 0);

    void AddDevice(uint type, uint num_buttons, uint num_analogs, uint port = 0);
    void RemoveDevice(uint type, uint port = 0);

    void HandleDevices();

    //The Analog Value Of A Mouse Device Depends On How Fast It's Moving
    //To Normalize The Analog Value, A Maximum Speed Is Needed
    float max_mouse_velocity;
    float max_mouse_wheel_velocity;

protected:
    virtual void MapGamepadButtons() = 0;
    virtual void MapKeyboardButtons() = 0;
    virtual void MapMouseButtons() = 0;

    virtual void MapGamepadAnalogs() = 0;

    std::vector<Shared<InputDevice>> m_devices;
    EDeviceDetected* m_device_connect_event;
    EDeviceDetected* m_device_disconnect_event;
};

#endif


