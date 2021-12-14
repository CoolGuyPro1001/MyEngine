#include "CameraComponent.h"

#include "Level.h"
#include "Actor.h"
#include "Common/Log.h"
#include "Core/Time.h"
#include "Events.h"

CCamera::CCamera(float focal_distance, bool enable_logging, int log_delay)
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
    zoom_velocity = 0;
    view_velocity = 0;
    rod_length_velocity = 0;
    fov = 70.0f;
    free_cam = true;

    log_on_tick = enable_logging;
    if(log_on_tick) this->log_delay = log_delay;
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

    log_on_tick = c.log_on_tick;
    if(log_on_tick) log_delay = c.log_delay;
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
        float pitch_velocity = rod_rotation_velocity.pitch * Delay();
        float yaw_velocity = rod_rotation_velocity.yaw * Delay();
        float roll_velocity = rod_rotation_velocity.roll * Delay();

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

    if(rod_lock && attached_actor && !free_cam)
    {
        looking_at = attached_actor->position;

        float& pitch = rod_rotation.pitch;
        float& yaw = rod_rotation.yaw;
        float& roll = rod_rotation.roll;

        rotation.pitch = (pitch >= 0 && pitch <= PI) ? pitch - PI : pitch + PI;
        rotation.yaw = (yaw >= 0 && yaw <= PI) ? yaw - PI : yaw + PI;
    }
    else
    {
        //Rotate CCamera
        float pitch_velocity = rotation_velocity.pitch * Delay();
        float yaw_velocity = rotation_velocity.yaw * Delay();
        float roll_velocity = rotation_velocity.roll * Delay();

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

    if(!attached_actor || free_cam)
    {
        //Move CCamera
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


    if(--log_delay == 0 && log_on_tick)
    {
        PrintLocation();
        log_delay = 500;
    }
}

void CCamera::AddToOrientation(float& axis, float deg, bool full_circle)
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

void CCamera::PrintLocation()
{
    Log("At| X: %f Y: %f Z: %f\n", position.x, position.y, position.z);
    Log("Looking At| X: %f Y: %f Z: %f\n", looking_at.x, looking_at.y, looking_at.z);
    Log("Orientation| P: %f Y: %f R: %f\n", rotation.pitch, rotation.yaw, rotation.roll);
    Log("Rod Orientation| P: %f Y: %f R: %f\n", rod_rotation.pitch, rod_rotation.yaw, rod_rotation.roll);
    Log("Up| X: %f Y: %f Z; %f\n\n", up.x, up.y, up.z);
}

void CCamera::MoveSideways(StickXEvent e)
{
    relative_position_velocity.side = e.value * sideways_throttle;
}

void CCamera::MoveDirectly(StickYEvent e)
{
    relative_position_velocity.direct = e.value * forward_throttle;
}

void CCamera::MoveVertical(StickYEvent e)
{
    relative_position_velocity.vertical = e.value * vertical_throttle;
}

void CCamera::MoveUpwards(ButtonEvent e)
{
    relative_position_velocity.vertical = e.value * vertical_throttle;
}

void CCamera::MoveDownwards(ButtonEvent e)
{
    relative_position_velocity.vertical = -e.value * vertical_throttle;
}

void CCamera::MoveRight(ButtonEvent e)
{
    relative_position_velocity.side = e.value * sideways_throttle;
}

void CCamera::MoveLeft(ButtonEvent e)
{
    relative_position_velocity.side = -e.value * sideways_throttle;
}

void CCamera::MoveForwards(ButtonEvent e)
{
    relative_position_velocity.direct = e.value * forward_throttle;
}

void CCamera::MoveBackwards(ButtonEvent e)
{
    relative_position_velocity.direct = -e.value * forward_throttle;
}

void CCamera::Pitch(StickYEvent e)
{
    rotation_velocity.pitch = e.value * pitch_throttle;
}

void CCamera::PitchUp(ButtonEvent e)
{
    rotation_velocity.pitch = e.value * pitch_throttle;
}

void CCamera::PitchDown(ButtonEvent e)
{
    rotation_velocity.pitch = -e.value * pitch_throttle;
}

void CCamera::Yaw(StickXEvent e)
{
    rotation_velocity.yaw = -e.value * yaw_throttle;
}

void CCamera::YawRight(ButtonEvent e)
{
    rotation_velocity.yaw = -e.value * yaw_throttle;
}

void CCamera::YawLeft(ButtonEvent e)
{
    rotation_velocity.yaw = e.value * yaw_throttle;;
}

void CCamera::Roll(StickXEvent e)
{
    rotation_velocity.roll = e.value * yaw_throttle;
}

void CCamera::RollRight(ButtonEvent e)
{
    rotation_velocity.roll = e.value * yaw_throttle;
}

void CCamera::RollLeft(ButtonEvent e)
{
    rotation_velocity.roll = -e.value * yaw_throttle;
}

void CCamera::Zoom(StickYEvent e)
{
    zoom_velocity = e.value * zoom_throttle;
}

void CCamera::ZoomIn(ButtonEvent e)
{
    zoom_velocity = e.value * zoom_throttle;
}

void CCamera::ZoomOut(ButtonEvent e)
{
    zoom_velocity = -e.value * zoom_throttle;
}

void CCamera::View(StickXEvent e)
{
    view_velocity = e.value * view_throttle;
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

void CCamera::RodPitch(StickYEvent e)
{
    rod_rotation_velocity.pitch = e.value * rod_pitch_throttle;
}

void CCamera::RodPitchUp(ButtonEvent e)
{
    rod_rotation_velocity.pitch = e.value * rod_pitch_throttle;
}

void CCamera::RodPitchDown(ButtonEvent e)
{
    rod_rotation_velocity.pitch = -e.value * rod_pitch_throttle;
}

void CCamera::RodYaw(StickXEvent e)
{
    rod_rotation_velocity.yaw = e.value * rod_yaw_throttle;
}

void CCamera::RodYawRight(ButtonEvent e)
{
    rod_rotation_velocity.yaw = e.value * rod_yaw_throttle;
}

void CCamera::RodYawLeft(ButtonEvent e)
{
    rod_rotation_velocity.yaw = -e.value * rod_yaw_throttle;
}

void CCamera::RodRoll(StickXEvent e)
{
    rod_rotation_velocity.roll = e.value * rod_roll_throttle;
}

void CCamera::RodRollRight(ButtonEvent e)
{
    rod_rotation_velocity.roll = e.value * rod_roll_throttle;
}

void CCamera::RodRollLeft(ButtonEvent e)
{
    rod_rotation_velocity.roll = -e.value * rod_roll_throttle;
}

void CCamera::RodDistance(StickYEvent e)
{
    rod_length_velocity = e.value * rod_length_throttle;
}

void CCamera::RodDistanceIn(ButtonEvent e)
{
    rod_length_velocity = e.value * rod_length_throttle;
}

void CCamera::RodDistanceOut(ButtonEvent e)
{
    rod_length_velocity = -e.value * rod_length_throttle;
}

void CCamera::ToggleFreeCam()
{
    free_cam = !free_cam;
}

void CCamera::AttachToLevel(Level& lvl)
{
    lvl.camera_components.push_back(shared_from_this());
}
