#include "Actor.h"
#include "Component.h"
#include "Core/Time.h"
#include "Level.h"

Actor::Actor()
{
    current_level = nullptr;
    components = ComponentMap();

    position = Vector3();
    rotation = Vector3();
    scale = Vector3(1, 1, 1);

    position_velocity = Vector3();
    rotation_velocity = Vector3();
    scale_velocity = Vector3();

    position_acceleration = Vector3();
    rotation_acceleration = Vector3();
    scale_acceleration = Vector3();

    enable_tick = true;
    can_fall = false;
}

Actor::Actor(Vector3 position) : Actor()
{
    this->position = position;
}

Actor::Actor(Vector3 position, Vector3 rotation, Vector3 scale) : Actor()
{
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
}

Actor::Actor(const Actor& a)
{
    current_level = a.current_level;
    components = a.components;

    position = a.position;
    rotation = a.rotation;
    scale = a.scale;

    position_velocity = a.position_velocity;
    rotation_velocity = a.rotation_velocity;
    scale_velocity = a.scale_velocity;

    position_acceleration = a.position_acceleration;
    rotation_acceleration = a.rotation_acceleration;
    scale_acceleration = a.scale_acceleration;
}

Actor::~Actor()
{
    delete current_level;
}

void Actor::Tick()
{
    position += position_velocity;
    rotation += rotation_velocity;
    scale += scale_velocity;

    auto restrict_angle = [&](float angle)
    {
        float num_revolutions = floor((angle - 180) / 360) + 1;
        angle = angle - 360 * num_revolutions;
    };

    //Restrict Rotation To The Interval [-180, 180]
    if(rotation.pitch < -180 || rotation.pitch > 180) restrict_angle(rotation.pitch);
    if(rotation.yaw < -180 || rotation.yaw > 180) restrict_angle(rotation.yaw);
    if(rotation.roll < -180 || rotation.roll > 180) restrict_angle(rotation.roll);

    if(can_fall && current_level)
        position_velocity.y = current_level->gravity * Delay();
}
