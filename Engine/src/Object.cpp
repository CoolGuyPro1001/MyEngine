#include "Object.h"
#include "Graphics/Graphics.h"

Object::Object()
{
    position = Vector3(0, 0, 0);
    rotation = Vector3(0, 0, 0);
    scale = Vector3(1.0f, 1.0f, 1.0f);
    position_velocity = Vector3(0, 0, 0);
    rotation_velocity = Vector3(0, 0, 0);
    scale_velocity = Vector3(0, 0, 0);
    model = nullptr;
    visible = true;
    locked = false;
    matrix = Graphics::GenerateModelMatrix(position, rotation, scale);
}

Object::Object(Vector3 position, Vector3 rotation, Vector3 scale) : position(position), rotation(rotation), scale(scale)
{
    model = nullptr;
    visible = true;
    locked = false;
    matrix = Graphics::GenerateModelMatrix(position, rotation, scale);
}

Object::Object(Shared<Model> model) : model(model)
{
    position = Vector3(0, 0, 0);
    rotation = Vector3(0, 0, 0);
    scale = Vector3(1.0f, 1.0f, 1.0f);
    position_velocity = Vector3(0, 0, 0);
    rotation_velocity = Vector3(0, 0, 0);
    scale_velocity = Vector3(0, 0, 0);
    visible = true;
    locked = false;
    matrix = Graphics::GenerateModelMatrix(position, rotation, scale);
}

Object::Object(Shared<Model> model, Vector3 position, Vector3 rotation, Vector3 scale) : 
    model(model), position(position), rotation(rotation), scale(scale)
{
    visible = true;
    locked = false;
    matrix = Graphics::GenerateModelMatrix(position, rotation, scale);
}

Vector3 Object::GetPosition()
{
    return position;
}

Vector3 Object::GetRotation()
{
    return rotation;
}

Vector3 Object::GetScale()
{
    return scale;
}

Vector3 Object::GetPositionVelocity()
{
    return position_velocity;
}

Vector3 Object::GetRotationVelocity()
{
    return rotation_velocity;
}

Vector3 Object::GetScaleVelocity()
{
    return scale_velocity;
}

void Object::SetPosition(Vector3 position)
{
    if(!locked)
        this->position = position;
}

void Object::SetRotation(Vector3 rotation)
{
    if(!locked)
        this->rotation = rotation;
}

void Object::SetScale(Vector3 scale)
{
    if(!locked)
        this->scale = scale;
}

void Object::SetPositionVelocity(Vector3 position_velocity)
{
    if(!locked)
        this->position_velocity = position_velocity;
}

void Object::SetRotationVelocity(Vector3 rotation_velocity)
{
    if(!locked)
        this->rotation_velocity = rotation_velocity;
}

void Object::SetScaleVelocity(Vector3 scale_velocity)
{
    if(!locked)
        scale_velocity = scale_velocity;
}

void Object::SetPosition(float x, float y, float z)
{
    if(!locked)
        position = Vector3(x, y, z);
}

void Object::SetRotation(float pitch, float yaw, float roll)
{
    if(!locked)
        rotation = Vector3(pitch, yaw, roll);
}

void Object::SetScale(float x, float y, float z)
{
    if(!locked)
        scale = Vector3(x, y, z);
}

void Object::SetPositionVelocity(float x, float y, float z)
{
    if(!locked)
        position = Vector3(x, y, z);
}

void Object::SetRotationVelocity(float pitch, float yaw, float roll)
{
    if(!locked)
        rotation = Vector3(pitch, yaw, roll);
}

void Object::SetScaleVelocity(float x, float y, float z)
{
    if(!locked)
        scale = Vector3(x, y, z);
}

void Object::ChangePosition(Vector3 position)
{
    if(!locked)
        this->position += position;
}

void Object::ChangeRotation(Vector3 rotation)
{
    if(!locked)
        this->rotation += rotation;
}

void Object::ChangeScale(Vector3 scale)
{
    if(!locked)
        this->scale += scale;
}

void Object::ChangePositionVelocity(Vector3 position_velocity)
{
    if(!locked)
        this->position_velocity += position_velocity;
}

void Object::ChangeRotationVelocity(Vector3 rotation_velocity)
{
    if(!locked)
        this->rotation_velocity += rotation_velocity;
}

void Object::ChangeScaleVelocity(Vector3 scale_velocity)
{
    if(!locked)
        this->scale_velocity += scale_velocity;
}

void Object::ChangePosition(float x, float y, float z)
{
    if(!locked)
        this->position += Vector3(x, y, z);
}

void Object::ChangeRotation(float pitch, float yaw, float roll)
{
    if(!locked)
        this->rotation += Vector3(pitch, yaw, roll);
}

void Object::ChangeScale(float x, float y, float z)
{
    if(!locked)
        scale += Vector3(x, y, z);
}

void Object::ChangePositionVelocity(float x, float y, float z)
{
    if(!locked)
        position_velocity += Vector3(x, y, z);
}

void Object::ChangeRotationVelocity(float pitch, float yaw, float roll)
{
    if(!locked)
        rotation_velocity += Vector3(pitch, yaw, roll);
}

void Object::ChangeScaleVelocity(float x, float y, float z)
{
    if(!locked)
        scale_velocity += Vector3(x, y, z);
}

glm::mat4 Object::GetMVP()
{
    return matrix;
}

void Object::UpdateMVP()
{
    if(!locked)
    {
        matrix = Graphics::GenerateModelMatrix(position, rotation, scale);
    }
}