#include "CameraComponent.h"

#include "Level.h"
#include "Actor.h"

#include "Common/Log.h"
#include "Common/Mathematics.h"

#include "Core/Time.h"

#include "Events/InputEvents.h"

#define FULL_ROTATION 360
#define HALF_ROTATION 180
#define QUARTER_ROTATION 90

CCamera::CCamera(float focal_distance, bool enable_logging, int log_delay)
{
    position = Vector3(0, 0, 0);
    looking_at = Vector3(0, 0, 0);
    rotation = Vector3(0, 0, 0);
    position_velocity = Vector3(0, 0, 0);
    relative_position_velocity = Vector3(0, 0, 0);
    rotation_velocity = Vector3(0, 0, 0);
    rod_rotation = Vector3(0, 0, 0);
    rod_rotation_velocity = Vector3(0, 0, 0);
    up = Vector3(0, 1.0f, 0);
    zoom_velocity = 0;
    view_velocity = 0;
    rod_length_velocity = 0;
    fov = 70.0f;
    free_cam = true;
    rod_length = 0;
    this->focal_distance = focal_distance;

    m_log_on_tick = enable_logging;
    m_log_delay = log_delay;
    m_log_cooldown = 0;
}

CCamera::CCamera(const CCamera& c)
{
    position = c.position;
    focal_distance = c.focal_distance;
    looking_at = c.looking_at;
    rotation = c.rotation;
    position_velocity = c.position_velocity;
    relative_position_velocity = c.relative_position_velocity;
    rotation_velocity = c.rotation_velocity;
    rod_rotation = c.rod_rotation;
    rod_rotation_velocity = c.rod_rotation_velocity;
    up = c.up;
    zoom_velocity = c.zoom_velocity;
    view_velocity = c.view_velocity;
    rod_length_velocity = c.rod_length_velocity;
    fov = c.fov;
    free_cam = c.free_cam;
    rod_length = c.rod_length;

    m_log_on_tick = c.m_log_on_tick;
    if(m_log_on_tick) m_log_delay = c.m_log_delay;
}

void CCamera::Tick()
{
    float sin_yaw;
    float sin_pitch;
    float cos_yaw;
    float cos_pitch;
    float sin_yaw_half;
    float cos_yaw_half;

    if(attached_actor && !free_cam)
    {
        Vector3 actor_pos = attached_actor->position;

        float rod_pitch_velocity = rod_rotation_velocity.pitch * Delay();
        float rod_yaw_velocity = rod_rotation_velocity.yaw * Delay();
        float rod_roll_velocity = rod_rotation_velocity.roll * Delay();

        //Rotate Rod
        AddToRotation(rod_rotation.pitch, rod_pitch_velocity, false);
        AddToRotation(rod_rotation.yaw, rod_yaw_velocity, true);
        AddToRotation(rod_rotation.roll, rod_roll_velocity, true);

        float rod_pitch_radians = DegreesToRadians(rod_rotation.pitch);
        float rod_yaw_radians = DegreesToRadians(rod_rotation.yaw);

        float rod_sin_yaw = sin(rod_yaw_radians);
        float rod_sin_pitch = sin(rod_pitch_radians);
        float rod_cos_yaw = cos(rod_yaw_radians);
        float rod_cos_pitch = cos(rod_pitch_radians);

        //Move Camera With Rod
        position.x = rod_sin_yaw * rod_cos_pitch * rod_length + actor_pos.x;
        position.y = rod_sin_pitch * rod_length + actor_pos.y;
        position.z = rod_cos_yaw * rod_cos_pitch * rod_length + actor_pos.z;
    }

    //Update Camera's Rotation
    if(rod_lock && attached_actor && !free_cam)
    {
        //Lock Camera To Face Actor
        looking_at = attached_actor->position;

        float& pitch = rod_rotation.pitch;
        float& yaw = rod_rotation.yaw;
        float& roll = rod_rotation.roll;

        //Update Camera Rotation
        rotation.pitch = (pitch >= 0 && pitch <= HALF_ROTATION) ? pitch - HALF_ROTATION : pitch + HALF_ROTATION;
        rotation.yaw = (yaw >= 0 && yaw <= HALF_ROTATION) ? yaw - HALF_ROTATION : yaw + HALF_ROTATION;

        //Update Camera Rotation view_velocity
        rotation_velocity.pitch = -rod_rotation_velocity.pitch * Delay();
        rotation_velocity.yaw = -rod_rotation_velocity.yaw * Delay();
        rotation_velocity.roll = rod_rotation_velocity.roll * Delay();
    }
    else
    {
        //Rotate Camera
        float pitch_velocity = rotation_velocity.pitch * Delay();
        float yaw_velocity = rotation_velocity.yaw * Delay();
        float roll_velocity = rotation_velocity.roll * Delay();

        AddToRotation(rotation.pitch, pitch_velocity, false);
        AddToRotation(rotation.yaw, yaw_velocity, true);
        AddToRotation(rotation.roll, roll_velocity, true);

        float pitch_radians = DegreesToRadians(rotation.pitch);
        float yaw_radians = DegreesToRadians(rotation.yaw);
        float roll_radians = DegreesToRadians(rotation.roll);

        sin_yaw = sin(yaw_radians);
        sin_pitch = sin(pitch_radians);
        cos_yaw = cos(yaw_radians);
        cos_pitch = cos(pitch_radians);
        sin_yaw_half = sin(yaw_radians - PI / 2.0f);
        cos_yaw_half = cos(yaw_radians - PI / 2.0f);

        float sin_roll = sin(rotation.roll);
        float cos_roll = cos(rotation.roll);

        //Calculate The Point Camera Is Looking At Based On Rotation And Focal Distance
        looking_at.x = sin_yaw * (cos_pitch * focal_distance) + position.x;
        looking_at.y = sin_pitch * focal_distance + position.y;
        looking_at.z = cos_yaw * (cos_pitch * focal_distance) + position.z;

        up.x = sin_yaw * sin_roll;
        up.y = cos_roll;
        up.z = cos_yaw * sin_roll;
    }

    if(!attached_actor || free_cam)
    {
        //Move Camera
        float direct = relative_position_velocity.direct * Delay();
        float vertical = relative_position_velocity.vertical * Delay();
        float side = relative_position_velocity.side * Delay();

        position_velocity.x = sin_yaw * cos_pitch * direct + sin_yaw_half * side;
        position_velocity.y = sin_pitch * direct + vertical;
        position_velocity.z = cos_yaw * cos_pitch * direct + cos_yaw_half * side;

        position += position_velocity;
        looking_at += position_velocity;
    }

    focal_distance += zoom_velocity;
    fov += view_velocity;
    if(fov > 180) fov = 180;
    if(fov < 0) fov = 0;
    rod_length += rod_length_velocity;

    ++m_log_cooldown;
    if(m_log_on_tick && m_log_cooldown == m_log_delay)
    {
        PrintInformation();
        m_log_cooldown = 0;
    }
}

void CCamera::AddToRotation(float& axis, float deg, bool full_circle)
{
    axis += deg;

    if(full_circle)
    {
        if(axis > HALF_ROTATION)
        {
            axis = axis - FULL_ROTATION;
        }
        else if(axis < -HALF_ROTATION)
        {
            axis = axis + FULL_ROTATION;
        }
    }
    else
    {
        if(axis > QUARTER_ROTATION)
        {
            axis = QUARTER_ROTATION;
        }
        else if(axis < -QUARTER_ROTATION)
        {
            axis = -QUARTER_ROTATION;
        }
    }
}

void CCamera::PrintInformation()
{
    Log("Position At| X: %f Y: %f Z: %f\n", position.x, position.y, position.z);
    Log("Looking At| X: %f Y: %f Z: %f\n", looking_at.x, looking_at.y, looking_at.z);
    Log("Orientation| P: %f Y: %f R: %f\n", rotation.pitch, rotation.yaw, rotation.roll);
    Log("Rod Orientation| P: %f Y: %f R: %f\n", rod_rotation.pitch, rod_rotation.yaw, rod_rotation.roll);
    Log("Up| X: %f Y: %f Z; %f\n\n", up.x, up.y, up.z);
}


void CCamera::MoveSideways(EAnalogInput* e)
{
    relative_position_velocity.side = e->value * sideways_throttle;
}

void CCamera::MoveDirectly(EAnalogInput* e)
{
    relative_position_velocity.direct = e->value * forward_throttle;
}

void CCamera::MoveVertical(EAnalogInput* e)
{
    relative_position_velocity.vertical = e->value * vertical_throttle;
}

void CCamera::MoveUpwards(EButtonInput* e)
{
    relative_position_velocity.vertical = vertical_throttle;
}

void CCamera::MoveDownwards(EButtonInput* e)
{
    relative_position_velocity.vertical = e->pressed * -vertical_throttle;
}

void CCamera::MoveRight(EButtonInput* e)
{
    relative_position_velocity.side = e->pressed * sideways_throttle;
}

void CCamera::MoveLeft(EButtonInput* e)
{
    relative_position_velocity.side = e->pressed * -sideways_throttle;
}

void CCamera::MoveForwards(EButtonInput* e)
{
    relative_position_velocity.direct = e->pressed * forward_throttle;
}

void CCamera::MoveBackwards(EButtonInput* e)
{
    relative_position_velocity.direct = e->pressed * -forward_throttle;
}

void CCamera::Pitch(EAnalogInput* e)
{
    rotation_velocity.pitch = e->value * pitch_throttle;
}

void CCamera::PitchUp(EButtonInput* e)
{
    rotation_velocity.pitch = e->pressed * pitch_throttle;
}

void CCamera::PitchDown(EButtonInput* e)
{
    rotation_velocity.pitch = e->pressed * -pitch_throttle;
}

void CCamera::Yaw(EAnalogInput* e)
{
    rotation_velocity.yaw = -e->value * yaw_throttle;
}

void CCamera::YawRight(EButtonInput* e)
{
    rotation_velocity.yaw = e->pressed * -yaw_throttle;
}

void CCamera::YawLeft(EButtonInput* e)
{
    rotation_velocity.yaw = e->pressed * yaw_throttle;;
}

void CCamera::Roll(EAnalogInput* e)
{
    rotation_velocity.roll = e->value * yaw_throttle;
}

void CCamera::RollRight(EButtonInput* e)
{
    rotation_velocity.roll = e->pressed * yaw_throttle;
}

void CCamera::RollLeft(EButtonInput* e)
{
    rotation_velocity.roll = e->pressed * -yaw_throttle;
}

void CCamera::Zoom(EAnalogInput* e)
{
    zoom_velocity = e->value * zoom_throttle;
}

void CCamera::ZoomIn(EButtonInput* e)
{
    zoom_velocity = e->pressed * zoom_throttle;
}

void CCamera::ZoomOut(EButtonInput* e)
{
    zoom_velocity = e->pressed * -zoom_throttle;
}

void CCamera::View(EAnalogInput* e)
{
    view_velocity = e->value * view_throttle;
}

void CCamera::AttachRod(Shared<Actor> actor, float length, Vector3 rotation, bool lock_on_actor)
{
    attached_actor = actor;
    rod_length = length;
    rod_rotation = rotation;
    looking_at = attached_actor->position;
    rod_lock = lock_on_actor;
    free_cam = false;
}

void CCamera::RodPitch(EAnalogInput* e)
{
    rod_rotation_velocity.pitch = e->value * rod_pitch_throttle;
}

void CCamera::RodPitchUp(EButtonInput* e)
{
    rod_rotation_velocity.pitch = e->pressed * rod_pitch_throttle;
}

void CCamera::RodPitchDown(EButtonInput* e)
{
    rod_rotation_velocity.pitch = e->pressed * -rod_pitch_throttle;
}

void CCamera::RodYaw(EAnalogInput* e)
{
    rod_rotation_velocity.yaw = e->value * rod_yaw_throttle;
}

void CCamera::RodYawRight(EButtonInput* e)
{
    rod_rotation_velocity.yaw = e->pressed * rod_yaw_throttle;
}

void CCamera::RodYawLeft(EButtonInput* e)
{
    rod_rotation_velocity.yaw = e->pressed * -rod_yaw_throttle;
}

void CCamera::RodRoll(EAnalogInput* e)
{
    rod_rotation_velocity.roll = e->value * rod_roll_throttle;
}

void CCamera::RodRollRight(EButtonInput* e)
{
    rod_rotation_velocity.roll = e->pressed * rod_roll_throttle;
}

void CCamera::RodRollLeft(EButtonInput* e)
{
    rod_rotation_velocity.roll = e->pressed * -rod_roll_throttle;
}

void CCamera::RodDistance(EAnalogInput* e)
{
    rod_length_velocity = e->value * rod_length_throttle;
}

void CCamera::RodDistanceIn(EButtonInput* e)
{
    rod_length_velocity = e->pressed * rod_length_throttle;
}

void CCamera::RodDistanceOut(EButtonInput* e)
{
    rod_length_velocity = e->pressed * -rod_length_throttle;
}

void CCamera::ToggleFreeCam()
{
    free_cam = !free_cam;
}

void CCamera::AttachToLevel(Level& lvl)
{
    lvl.camera_components.push_back(shared_from_this());
}
