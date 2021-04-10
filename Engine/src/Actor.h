#ifndef ACTOR_H
#define ACTOR_H

#include "Common/Units.h"
#include "Events.h"
#include "Graphics/Texture.h"
#include "Collision.h"

struct Level;

struct Model
{
    Model(std::vector<Vertex> vertices);
    Model(std::vector<Vertex> vertices, Shared<Graphics::Texture> texture);
    Model(std::string file_path, Shared<Graphics::Texture> texture);
    
    std::vector<Vertex> vertices;
    Shared<Graphics::Texture> texture;
};

class Actor
{
public:
    Actor();
    Actor(Shared<Model> model);
    ~Actor();

    void CreateHitBox(float depth, float height, float width);
    
    virtual void Tick();

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

    Collision* collision;

    Level* current_level;
    bool can_fall;
private:
    
    //std::vector<SoundEffect> sound_effects;
};
#endif