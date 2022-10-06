#ifndef ACTOR_H
#define ACTOR_H

#include "Common/Vector3.h"

struct Level;
struct Component;

/*
 * Actor Is A Container For Components That Give It Properties
 * The Only Properties All Actors Have Are
 * Position, Rotation, Scale (These Might Be Combined Into One Model Matrix In The Future)
 * Their Velocities; And Their Accelerations
 * And Also [model_matrix], Which Is Used For 3D Rendering
*/

/*
 * There Can Only Be One Component Of Each Type
 * Use AddComponent<Type>() To Add A Component Of [Type]
 * Use GetComponent<Type>() To Retrieve A Component Of [Type]
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

    Level* current_level;
    ComponentMap components;

    Vector3 position;
    Vector3 rotation;
    Vector3 scale;

    Vector3 position_velocity;
    Vector3 rotation_velocity;
    Vector3 scale_velocity;

    //Not Implemented Yet
    Vector3 position_acceleration;
    Vector3 rotation_acceleration;
    Vector3 scale_acceleration;

    bool enable_tick;
    bool can_fall;
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
