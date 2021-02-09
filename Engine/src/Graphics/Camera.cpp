#include "Camera.h"
#include "Core/Log.h"

namespace Graphics
{
    Camera::Camera(float focal_distance, bool enable_logging, int log_delay)
    {
        position = Vector3(0, 0, 0);
        this->focal_distance = focal_distance;
        looking_at = Vector3(0, 0, focal_distance);
        rotation = Vector3(0, 0, 0);
        position_velocity = Vector3(0, 0, 0);
        relative_position_velocity = Vector3(0, 0, 0); 
        rotation_velocity = Vector3(0, 0, 0);
        rod_rotation = Vector3(0, 0, 0);
        rod_rotation_velocity = Vector3(0, 0, 0);
        up = Vector3(0, 1.0f, 0);
        
        log_on_tick = enable_logging;
        if(log_on_tick) this->log_delay = log_delay;
    }

    void Camera::Tick()
    {
        if(attached_actor)
        {
            Vector3 actor_pos = attached_actor->position;

            //Rotate Rod
            AddToOrientation(rod_rotation.pitch, rod_rotation_velocity.pitch, false);
            AddToOrientation(rod_rotation.yaw, rod_rotation_velocity.yaw, true);
            AddToOrientation(rod_rotation.roll, rod_rotation_velocity.roll, true);

            position.x = sin(rod_rotation.yaw) * (cos(rod_rotation.pitch) * rod_length) + actor_pos.x;
            position.y = sin(rod_rotation.pitch) * rod_length + actor_pos.y;
            position.z = cos(rod_rotation.yaw) * (cos(rod_rotation.pitch) * rod_length) + actor_pos.z;
        }

        if(rod_lock && attached_actor)
        {
            looking_at = attached_actor->position;
        }
        else
        {
            //Rotate Camera
            AddToOrientation(rotation.pitch, rotation_velocity.pitch, false);
            AddToOrientation(rotation.yaw, rotation_velocity.yaw, true);
            AddToOrientation(rotation.roll, rotation_velocity.roll, true);

            looking_at.x = sin(rotation.yaw) * (cos(rotation.pitch) * focal_distance) + position.x;
            looking_at.y = sin(rotation.pitch) * focal_distance + position.y;
            looking_at.z = cos(rotation.yaw) * (cos(rotation.pitch) * focal_distance) + position.z;
            
            up.x = sin(rotation.yaw) * (sin(rotation.roll));
            up.y = cos(rotation.roll);
            up.z = cos(rotation.yaw) * (sin(rotation.roll));
        }

        if(!attached_actor)
        {
            //Move Camera
            position_velocity.x = sin(rotation.yaw) * (cos(rotation.pitch) * relative_position_velocity.direct) + sin(rotation.yaw - PI / 2.0f) * relative_position_velocity.side;
            position_velocity.y = sin(rotation.pitch) * relative_position_velocity.direct + relative_position_velocity.vertical;
            position_velocity.z = cos(rotation.yaw) * (cos(rotation.pitch) * relative_position_velocity.direct) + cos(rotation.yaw - PI / 2.0f) * relative_position_velocity.side;

            position += position_velocity;
            looking_at += position_velocity;
        }

        if(--log_delay == 0 && log_on_tick)
        {
            PrintLocation();
            log_delay = 500;
        }
    }
    
    void Camera::AddToOrientation(float& axis, float deg, bool full_circle)
    {
        axis += deg;

        float half = PI / 2.0f;
        float b = cos(half);

        if(full_circle)
        {
            if(axis > PI)
            {
                axis = axis - 2.0f * PI;
            }
            else if(axis < -1 * PI)
            {
                axis = axis + 2.0f * PI;
            }
        }
        else
        {
            if(axis > PI / 2.0f)
            {
                axis = PI / 2.0f;
            }
            else if(axis < -1 * PI / 2.0f)
            {
                axis = -1 * PI / 2;
            }
        }  
    }

    void Camera::PrintLocation()
    {
        Engine::Log("At| X: %f Y: %f Z: %f\n", position.x, position.y, position.z);
        Engine::Log("Looking At| X: %f Y: %f Z: %f\n", looking_at.x, looking_at.y, looking_at.z);
        Engine::Log("Orientation| P: %f Y: %f R: %f\n", rotation.pitch, rotation.yaw, rotation.roll);
        Engine::Log("Up| X: %f Y: %f Z; %f\n\n", up.x, up.y, up.z);
    }

    void Camera::MoveSideways(StickXEvent e)
    {
        relative_position_velocity.side = e.value * sideways_throttle;
    }

    void Camera::MoveDirectly(StickYEvent e)
    {
        relative_position_velocity.direct = e.value * forward_throttle;
    }

    void Camera::MoveVertical(StickYEvent e)
    {
        relative_position_velocity.vertical = e.value * vertical_throttle;
    }

    void Camera::MoveUpwards(ButtonEvent e)
    {
        relative_position_velocity.vertical = e.value * vertical_throttle;
    }

    void Camera::MoveDownwards(ButtonEvent e)
    {
        relative_position_velocity.vertical = -1 * e.value * vertical_throttle;
    }

    void Camera::MoveRight(ButtonEvent e)
    {
        relative_position_velocity.side = e.value * sideways_throttle;
    }

    void Camera::MoveLeft(ButtonEvent e)
    {
        relative_position_velocity.side = -1 * e.value * sideways_throttle;
    }

    void Camera::MoveForwards(ButtonEvent e)
    {
        relative_position_velocity.direct = e.value * forward_throttle;
    }

    void Camera::MoveBackwards(ButtonEvent e)
    {
        relative_position_velocity.direct = -1 * e.value * forward_throttle;
    }

    void Camera::Pitch(StickYEvent e)
    {
        rotation_velocity.pitch = e.value * pitch_throttle;
    }

    void Camera::PitchUp(ButtonEvent e)
    {
        rotation_velocity.pitch = e.value * pitch_throttle;
    }

    void Camera::PitchDown(ButtonEvent e)
    {
        rotation_velocity.pitch = -1 * e.value * pitch_throttle;
    }

    void Camera::Yaw(StickXEvent e)
    {
        rotation_velocity.yaw = -1 * e.value * yaw_throttle;
    }

    void Camera::YawRight(ButtonEvent e)
    {
        rotation_velocity.yaw = -1* e.value * yaw_throttle;
    }

    void Camera::YawLeft(ButtonEvent e)
    {
        rotation_velocity.yaw = e.value * yaw_throttle;;
    }

    void Camera::Roll(StickXEvent e)
    {
        rotation_velocity.roll = e.value * yaw_throttle;
    }

    void Camera::RollRight(ButtonEvent e)
    {
        rotation_velocity.roll = e.value * yaw_throttle;
    }

    void Camera::RollLeft(ButtonEvent e)
    {
        rotation_velocity.roll = -1 * e.value * yaw_throttle;
    }

    void Camera::AttachRod(Shared<Actor> actor, float length, bool lock_on_actor)
    {
        attached_actor = actor;
        rod_length = length;
        looking_at = attached_actor->position;
        rod_lock = lock_on_actor;
    }

    void Camera::RodPitch(StickYEvent e)
    {
        float deg = e.value * rod_pitch_throttle;
        rod_rotation_velocity.pitch = deg;
    }

    void Camera::RodPitchUp(ButtonEvent e)
    {
        rod_rotation_velocity.pitch = e.value * rod_pitch_throttle;
    }

    void Camera::RodPitchDown(ButtonEvent e)
    {
        rod_rotation_velocity.pitch = -1 * e.value * rod_pitch_throttle;
    }

    void Camera::RodYaw(StickXEvent e)
    {
        rod_rotation_velocity.yaw = e.value * rod_yaw_throttle;
    }

    void Camera::RodYawRight(ButtonEvent e)
    {
        rod_rotation_velocity.yaw = e.value * rod_yaw_throttle;
    }

    void Camera::RodYawLeft(ButtonEvent e)
    {
        rod_rotation_velocity.yaw = -1 * e.value * rod_yaw_throttle;
    }

    void Camera::RodRoll(StickXEvent e)
    {
        rod_rotation_velocity.roll = e.value * rod_roll_throttle;
    }

    void Camera::RodRollRight(ButtonEvent e)
    {
        rod_rotation_velocity.roll = e.value * rod_roll_throttle;
    }

    void Camera::RodRollLeft(ButtonEvent e)
    {
        rod_rotation_velocity.roll = -1 * e.value * rod_roll_throttle;
    }
}