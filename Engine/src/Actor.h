#ifndef ACTOR_H
#define ACTOR_H

#include "Common/Units.h"
#include "Events.h"
#include "Graphics/Texture.h"
#include "Collision.h"

struct Level;
class Component;

struct Model
{
    Model(std::vector<Vertex> vertices);
    Model(std::vector<Vertex> vertices, Shared<Graphics::Texture> texture);
    Model(std::string file_path, Shared<Graphics::Texture> texture);
    
    uint offset;
    std::vector<Vertex> vertices;
    Shared<Graphics::Texture> texture;
};

struct Object
{
    Object();
    Object(Vector3 position, Vector3 rotation, Vector3 scale);
    Object(Shared<Model> model);
    Object(Shared<Model> model, Vector3 position, Vector3 rotation, Vector3 scale);

    Shared<Model> model;
    bool visible;

    Vector3 position;
    Vector3 rotation;
    Vector3 scale;

    Vector3 position_velocity;
    Vector3 rotation_velocity;
    Vector3 scale_velocity;
};

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

class Component : public Object
{
public:
    
    //r_position, r_rotation, r_scale are relative values of actor

    Component(Shared<Actor> actor);
    Component(Shared<Actor> actor, Vector3 r_position, Vector3 r_rotation, Vector3 r_scale);
    Component(Shared<Actor> actor, Shared<Model> model);
    Component(Shared<Actor> actor, Shared<Model> model, Vector3 r_position, Vector3 r_rotation, Vector3 r_scale);
    ~Component();

    Shared<Actor> actor;

    Vector3 r_position;
    Vector3 r_rotation;
    Vector3 r_scale;
};
#endif