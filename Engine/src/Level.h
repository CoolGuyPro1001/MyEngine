#ifndef LEVEL_H
#define LEVEL_H

#include "Graphics/Texture.h"
#include "Graphics/Camera.h"
#include "Controller.h"

class Model;
class Actor;

struct Level
{
public:
    Level();

    void AddTexture(Shared<Graphics::Texture> texture);
    void AddModel(Shared<Model> model);
    void AddActor(Shared<Actor> actor);
    void AddCamera(Shared<Graphics::Camera> camera);
    void AddController(Shared<Controller> controller);
    void ReadCollisionFile(std::string file);
    
    std::vector<Shared<Graphics::Texture>> textures;
    std::vector<Shared<Model>> models;
    std::vector<Shared<Actor>> actors;
    std::vector<Shared<Graphics::Camera>> cameras;
    std::vector<Shared<Controller>> controllers;

    std::function<void()> script;

    Shared<Model> sky_block;
    Shared<Model> terrain;
    std::vector<CollisionTri> flat_collisions;

    float gravity;
};
#endif