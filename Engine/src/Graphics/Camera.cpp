#include "Camera.h"
#include "Core/Log.h"
#include "Core/Runtime.h"

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
        fov = 70.0f;
        
        log_on_tick = enable_logging;
        if(log_on_tick) this->log_delay = log_delay;
    }

    void Camera::Tick()
    {
        float sin_yaw;
        float sin_pitch;
        float cos_yaw;
        float cos_pitch;
        float sin_yaw_half;
        float cos_yaw_half;

        if(attached_actor)
        {
            Vector3 actor_pos = attached_actor->position;
            float pitch_velocity = rod_rotation_velocity.pitch * Engine::Delay();
            float yaw_velocity = rod_rotation_velocity.yaw * Engine::Delay();
            float roll_velocity = rod_rotation_velocity.roll * Engine::Delay();

            //Rotate Rod
            AddToOrientation(rod_rotation.pitch, pitch_velocity, false);
            AddToOrientation(rod_rotation.yaw, yaw_velocity, true);
            AddToOrientation(rod_rotation.roll, roll_velocity, true);

            float rod_sin_yaw = sin(rod_rotation.yaw);
            float rod_sin_pitch = sin(rod_rotation.pitch);
            float rod_cos_yaw = cos(rod_rotation.yaw);
            float rod_cos_pitch = cos(rod_rotation.pitch);

            position.x = rod_sin_yaw * rod_cos_pitch * rod_length + actor_pos.x;
            position.y = rod_sin_pitch * rod_length + actor_pos.y;
            position.z = rod_cos_yaw * rod_cos_pitch * rod_length + actor_pos.z;
        }

        if(rod_lock && attached_actor)
        {
            looking_at = attached_actor->position;
        }
        else
        {
            //Rotate Camera
            float pitch_velocity = rotation_velocity.pitch * Engine::Delay();
            float yaw_velocity = rotation_velocity.yaw * Engine::Delay();
            float roll_velocity = rotation_velocity.roll * Engine::Delay();

            AddToOrientation(rotation.pitch, pitch_velocity, false);
            AddToOrientation(rotation.yaw, yaw_velocity, true);
            AddToOrientation(rotation.roll, roll_velocity, true);

            sin_yaw = sin(rotation.yaw);
            sin_pitch = sin(rotation.pitch);
            cos_yaw = cos(rotation.yaw);
            cos_pitch = cos(rotation.pitch);
            sin_yaw_half = sin(rotation.yaw - PI / 2.0f);
            cos_yaw_half = cos(rotation.yaw - PI / 2.0f);

            float sin_roll = sin(rotation.roll);
            float cos_roll = cos(rotation.roll);

            looking_at.x = sin_yaw * (cos_pitch * focal_distance) + position.x;
            looking_at.y = sin_pitch * focal_distance + position.y;
            looking_at.z = cos_yaw * (cos_pitch * focal_distance) + position.z;
            
            up.x = sin_yaw * sin_roll;
            up.y = cos_roll;
            up.z = cos_yaw * sin_roll;
        }

        if(!attached_actor)
        {
            //Move Camera
            float direct = relative_position_velocity.direct * Engine::Delay();
            float side = relative_position_velocity.side * Engine::Delay();
            float vertical = relative_position_velocity.vertical * Engine::Delay();

            position_velocity.x = sin_yaw * cos_pitch * direct + sin_yaw_half * side;
            position_velocity.y = sin_pitch * direct + vertical;
            position_velocity.z = cos_yaw * cos_pitch * direct + cos_yaw_half * side;

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

        if(full_circle)
        {
            if(axis > PI)
            {
                axis = axis - 2.0f * PI;
            }
            else if(axis < -PI)
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
            else if(axis < -PI / 2.0f)
            {
                axis = -PI / 2;
            }
        }  
    }

    void Camera::PrintLocation()
    {
        Engine::Log("At| X: %f Y: %f Z: %f\n", position.x, position.y, position.z);
        Engine::Log("Looking At| X: %f Y: %f Z: %f\n", looking_at.x, looking_at.y, looking_at.z);
        Engine::Log("Orientation| P: %f Y: %f R: %f\n", rotation.pitch, rotation.yaw, rotation.roll);
        Engine::Log("Rod Orientation| P: %f Y: %f R: %f\n", rod_rotation.pitch, rod_rotation.yaw, rod_rotation.roll);
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
        relative_position_velocity.vertical = -e.value * vertical_throttle;
    }

    void Camera::MoveRight(ButtonEvent e)
    {
        relative_position_velocity.side = e.value * sideways_throttle;
    }

    void Camera::MoveLeft(ButtonEvent e)
    {
        relative_position_velocity.side = -e.value * sideways_throttle;
    }

    void Camera::MoveForwards(ButtonEvent e)
    {
        relative_position_velocity.direct = e.value * forward_throttle;
    }

    void Camera::MoveBackwards(ButtonEvent e)
    {
        relative_position_velocity.direct = -e.value * forward_throttle;
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
        rotation_velocity.pitch = -e.value * pitch_throttle;
    }

    void Camera::Yaw(StickXEvent e)
    {
        rotation_velocity.yaw = -e.value * yaw_throttle;
    }

    void Camera::YawRight(ButtonEvent e)
    {
        rotation_velocity.yaw = -e.value * yaw_throttle;
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
        rotation_velocity.roll = -e.value * yaw_throttle;
    }

    void Camera::AttachRod(Shared<Actor> actor, float length, Vector3 rotation, bool lock_on_actor)
    {
        attached_actor = actor;
        rod_length = length;
        rod_rotation = rotation;
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
        rod_rotation_velocity.pitch = -e.value * rod_pitch_throttle;
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
        rod_rotation_velocity.yaw = -e.value * rod_yaw_throttle;
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
        rod_rotation_velocity.roll = -e.value * rod_roll_throttle;
    }
}