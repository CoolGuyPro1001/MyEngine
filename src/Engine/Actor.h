#ifndef ACTOR_H
#define ACTOR_H

#include "../Common/Units.h"


struct Model
{
    Model(std::vector<Vertex> vertices);
    std::vector<Vertex> vertices;
    uint id;
};

class Actor
{
public:
    Actor();
    Actor(Model* model);
    //Tick()

    //AddSoundEffect(SoundEffect sound);
    //RemoveSoundEffect(SoundEffect sound);
    //GetSoundEffects();

    Destroy();

    Model* model;
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
private:
    
    //std::vector<SoundEffect> sound_effects;
};
#endif