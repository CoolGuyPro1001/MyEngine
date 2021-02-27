#ifndef LEVEL_H
#define LEVEL_H

#include "Actor.h"
#include "Graphics/Camera.h"
#include "Controller.h"

struct Level
{
public:
    Level();
    
    std::vector<Shared<Graphics::Texture>> textures;
    std::vector<Shared<Model>> models;
    std::vector<Shared<Actor>> actors;
    std::vector<Shared<Graphics::Camera>> cameras;
    std::vector<Controller> controllers;

    std::function<void()> script;

    Shared<Model> sky_block;
    Shared<Model> terrain;
};
#endif