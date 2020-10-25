#ifndef ACTOR_H
#define ACTOR_H

#include "../Common/Units.h"
#include "Events.h"


struct Model
{
    Model(std::vector<Vertex> vertices);
    std::vector<Vertex> vertices;
    uint off_set;
};

class Actor
{
public:
    Actor();
    Actor(Shared<Model> model);
    
    virtual Tick()

    //AddSoundEffect(SoundEffect sound);
    //RemoveSoundEffect(SoundEffect sound);
    //GetSoundEffects();

    Shared<Model> model;

    Vector3 position;
    Vector3 rotation;
    Vector3 scale;

    Vector3 position_velocity;
    Vector3 rotation_velocity;
    Vector3 scale_velocity;
private:
    
    //std::vector<SoundEffect> sound_effects;
};
#endif