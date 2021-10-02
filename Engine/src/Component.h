#ifndef COMPONENT_H
#define COMPONENT_H

#include "Actor.h"

class Actor;
class Component : public Object
{
public:  
    //r_position, r_rotation, r_scale are relative values of actor

    Component(Shared<Actor> actor);
    Component(Shared<Actor> actor, Vector3 relative_position, Vector3 relative_rotation, Vector3 r_scale);
    Component(Shared<Actor> actor, Shared<Model> model);
    Component(Shared<Actor> actor, Shared<Model> model, Vector3 relative_position, 
        Vector3 relative_rotation, Vector3 relative_scale);
    ~Component();

    Vector3 GetRelativePosition();
    Vector3 GetRelativeRotation();
    Vector3 GetRelativeScale();

    void SetRelativePosition(Vector3 position);
    void SetRelativeRotation(Vector3 rotation);
    void SetRelativeScale(Vector3 scale);

    void SetRelativePosition(float x, float y, float z);
    void SetRelativeRotation(float pitch, float yaw, float roll);
    void SetRelativeScale(float x, float y, float z);

    void ChangeRelativePosition(Vector3 position);
    void ChangeRelativeRotation(Vector3 rotation);
    void ChangeRelativeScale(Vector3 scale);

    void ChangeRelativePosition(float x, float y, float z);
    void ChangeRelativeRotation(float pitch, float yaw, float roll);
    void ChangeRelativeScale(float x, float y, float z);

    Shared<Actor> actor;

private:
    Vector3 relative_position;
    Vector3 relative_rotation;
    Vector3 relative_scale;
};
#endif