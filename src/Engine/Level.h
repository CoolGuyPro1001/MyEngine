#ifndef LEVEL_H
#define LEVEL_H

#include "Actor.h"
#include "Graphics/Camera.h"
struct Level
{
public:
    Level(std::vector<Actor> actors);
    Level(std::vector<Actor> actors, std::vector<Graphics::Camera> cameras);
    Level(std::vector<Actor> actors, std::function<void()> script);
    Level(std::vector<Actor> actors, std::vector<Graphics::Camera> cameras, std::function<void()> script);
    
    std::vector<Actor> actors;
    std::vector<Graphics::Camera> cameras;
    std::function<void()> script;
};
#endif