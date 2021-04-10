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
    void AddController(Controller controller);
    
    std::vector<Shared<Graphics::Texture>> textures;
    std::vector<Shared<Model>> models;
    std::vector<Shared<Actor>> actors;
    std::vector<Shared<Graphics::Camera>> cameras;
    std::vector<Controller> controllers;

    std::function<void()> script;

    Shared<Model> sky_block;
    Shared<Model> terrain;

    float gravity;
};
#endif