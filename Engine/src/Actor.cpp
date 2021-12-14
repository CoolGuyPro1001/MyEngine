#include "Actor.h"
#include "Components/Component.h"
#include "Core/Time.h"
#include "Core/Graphics/Graphics.h"
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
}

Actor::Actor(Vector3 position)
{
    Actor();
    this->position = position;
}

Actor::Actor(Vector3 position, Vector3 rotation, Vector3 scale) : position(position), rotation(rotation), scale(scale)
{
    Actor();

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
    //delete collision; Delete All Linked Components
    delete current_level;
}

void Actor::Tick()
{
    position += position_velocity;
    rotation += rotation_velocity;
    scale += scale_velocity;

    model_matrix = Graphics::GenerateModelMatrix(position, rotation, scale);

    //if(can_fall && current_level)
    //    ChangePositionVelocity(0, (Delay() > 1) ? current_level->gravity : current_level->gravity * Delay(), 0);
}
