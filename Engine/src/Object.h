#ifndef OBJECT_H
#define OBJECT_H

#include "Common/Vector3.h"
#include "Model.h"

#include <glm/glm.hpp>

struct Object
{
    Object();
    Object(Vector3 position, Vector3 rotation, Vector3 scale);
    Object(Shared<Model> model);
    Object(Shared<Model> model, Vector3 position, Vector3 rotation, Vector3 scale);

    Vector3 GetPosition();
    Vector3 GetRotation();
    Vector3 GetScale();
    Vector3 GetPositionVelocity();
    Vector3 GetRotationVelocity();
    Vector3 GetScaleVelocity();

    void SetPosition(Vector3 position);
    void SetRotation(Vector3 rotation);
    void SetScale(Vector3 scale);
    void SetPositionVelocity(Vector3 position_velocity);
    void SetRotationVelocity(Vector3 rotation_velocity);
    void SetScaleVelocity(Vector3 scale_velocity);

    void SetPosition(float x, float y, float z);
    void SetRotation(float pitch, float yaw, float roll);
    void SetScale(float x, float y, float z);
    void SetPositionVelocity(float x, float y, float z);
    void SetRotationVelocity(float pitch, float yaw, float roll);
    void SetScaleVelocity(float x, float y, float z);

    void ChangePosition(Vector3 position);
    void ChangeRotation(Vector3 rotation);
    void ChangeScale(Vector3 scale);
    void ChangePositionVelocity(Vector3 position_velocity);
    void ChangeRotationVelocity(Vector3 rotation_velocity);
    void ChangeScaleVelocity(Vector3 scale_velocity);

    void ChangePosition(float x, float y, float z);
    void ChangeRotation(float pitch, float yaw, float roll);
    void ChangeScale(float x, float y, float z);
    void ChangePositionVelocity(float x, float y, float z);
    void ChangeRotationVelocity(float pitch, float yaw, float roll);
    void ChangeScaleVelocity(float x, float y, float z);

    glm::mat4 GetMVP();
    void UpdateMVP();

    Shared<Model> model;
    bool visible;
    bool locked;

private:
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;

    Vector3 position_velocity;
    Vector3 rotation_velocity;
    Vector3 scale_velocity;

    glm::mat4 matrix;
};
#endif