#ifndef LEVEL_H
#define LEVEL_H

#include "Actor.h"
#include "Graphics/Camera.h"
struct Level
{
public:
    Level(std::vector<Actor> actors);
    Level(std::vector<Graphics::Camera> actors, std::vector<Graphics::Camera> cameras);

    void AddCamera(Graphics::Camera camera);
    
    std::vector<Actor> actors;
    std::vector<Graphics::Camera> cameras;
};
#endif