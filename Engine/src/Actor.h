#ifndef ACTOR_H
#define ACTOR_H

#include "Common/Vector3.h"

struct Level;
struct Component;

/*
Model: The Geometry In Model Space
Object: Geometry In World Space With Transformations And Velocities
Actor: A Child Of Object. Has The Power Of TICK
Component: Also A Child Of Object. Can Be Attached To Actor
*/

typedef std::unordered_map<std::type_index, Shared<Component>> ComponentMap;

class Actor : public std::enable_shared_from_this<Actor>
{
public:
    Actor();
    Actor(Vector3 position);
    Actor(Vector3 position, Vector3 rotation, Vector3 scale);
    Actor(const Actor& a);
    ~Actor();
    
    virtual void Tick();
    template<class T> void AddComponent(Shared<T> component);
    template<class C> Shared<C> GetComponent();

    //void AddModel(Shared<Model> model);
    //void AddModel(Shared<Model> model, Vector3 relative_position, Vector3 relative_rotation, Vector3 relative_scale);


    Level* current_level;
    ComponentMap components;

    glm::mat4 model_matrix;

    Vector3 position;
    Vector3 rotation;
    Vector3 scale;

    Vector3 position_velocity;
    Vector3 rotation_velocity;
    Vector3 scale_velocity;

    Vector3 position_acceleration;
    Vector3 rotation_acceleration;
    Vector3 scale_acceleration;

};

template<class C> void Actor::AddComponent(Shared<C> component)
{
    components[typeid(C)] = component;
    component->actors.push_back(shared_from_this());
}

template<class C> Shared<C> Actor::GetComponent()
{
    return std::static_pointer_cast<C>(components[typeid(C)]);
}

#endif
