#include "Component.h"

Component::Component(Shared<Actor> actor) : actor(actor)
{
    relative_position = Vector3(0, 0, 0);
    relative_rotation = Vector3(0, 0, 0);
    relative_scale = Vector3(0, 0, 0);
}

Component::Component(Shared<Actor> actor, Vector3 relative_position, Vector3 relative_rotation, Vector3 relative_scale) :
    actor(actor), relative_position(relative_position), relative_rotation(relative_rotation), relative_scale(relative_scale)
{
    Vector3 position = actor->GetPosition()+ relative_position;
    Vector3 rotation = actor->GetRotation() + relative_rotation;
    Vector3 scale = actor-> GetScale()+ relative_scale;
    Object(position, rotation, scale);
}

Component::Component(Shared<Actor> actor, Shared<Model> model) : actor(actor), Object(model)
{
    relative_position = Vector3(0, 0, 0);
    relative_rotation = Vector3(0, 0, 0);
    relative_scale = Vector3(0, 0, 0);
}

Component::Component(Shared<Actor> actor, Shared<Model> model, Vector3 relative_position, Vector3 relative_rotation, Vector3 relative_scale) :
    actor(actor), relative_position(relative_position), relative_rotation(relative_rotation), relative_scale(relative_scale)
{
    Vector3 position = actor->GetPosition() + relative_position;
    Vector3 rotation = actor->GetRotation() + relative_rotation;
    Vector3 scale = actor->GetScale() + relative_scale;
    Object(model, position, rotation, scale);
}

Component::~Component()
{
    int bob = 5;
}

Vector3 Component::GetRelativePosition()
{
    return relative_position;
}

Vector3 Component::GetRelativeRotation()
{
    return relative_rotation;
}

Vector3 Component::GetRelativeScale()
{
    return relative_scale;
}

void Component::SetRelativePosition(Vector3 position)
{
    if(!locked)
        relative_position = position;
}

void Component::SetRelativeRotation(Vector3 rotation)
{
    if(!locked)
        relative_rotation = rotation;
}

void Component::SetRelativeScale(Vector3 scale)
{
    if(!locked)
        relative_scale = scale;
}

void Component::SetRelativePosition(float x, float y, float z)
{
    if(!locked)
        relative_position = Vector3(x, y, z);
}

void Component::SetRelativeRotation(float pitch, float yaw, float roll)
{
    if(!locked)
        relative_rotation = Vector3(pitch, yaw, roll);
}

void Component::SetRelativeScale(float x, float y, float z)
{
    if(!locked)
        relative_scale = Vector3(x, y, z);
}


void Component::ChangeRelativePosition(Vector3 position)
{
    if(!locked)
        relative_position += position;
}

void Component::ChangeRelativeRotation(Vector3 rotation)
{
    if(!locked)
        relative_rotation += rotation;
}

void Component::ChangeRelativeScale(Vector3 scale)
{
    if(!locked)
        relative_scale += scale;
}

void Component::ChangeRelativePosition(float x, float y, float z)
{
    if(!locked)
        relative_position += Vector3(x, y, z);
}

void Component::ChangeRelativeRotation(float pitch, float yaw, float roll)
{
    if(!locked)
        relative_rotation += Vector3(pitch, yaw, roll);
}

void Component::ChangeRelativeScale(float x, float y, float z)
{
    if(!locked)
        relative_scale += Vector3(x, y, z);
}