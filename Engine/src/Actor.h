#ifndef ACTOR_H
#define ACTOR_H

#include "Object.h"
#include "Collision.h"
#include "Component.h"

struct Level;
class Component;
struct Collision;

/*
Model: The Geometry In Model Space
Object: Geometry In World Space With Transformations And Velocities
Actor: A Child Of Object. Has The Power Of TICK
Component: Also A Child Of Object. Can Be Attached To Actor
*/

class Actor : public Object
{
public:
    Actor();
    Actor(Vector3 position, Vector3 rotation, Vector3 scale);
    Actor(Shared<Model> model);
    Actor(Shared<Model> model, Vector3 position, Vector3 rotation, Vector3 scale);
    ~Actor();

    void CreateHitBox(float depth, float height, float width);
    void AddComponent(Shared<Component> component);
    
    virtual void Tick();

    //AddSoundEffect(SoundEffect sound);
    //RemoveSoundEffect(SoundEffect sound);
    //GetSoundEffects();

    std::vector<Shared<Component>> components;

    Collision* collision;


    Level* current_level;
    bool can_fall;
};
#endif