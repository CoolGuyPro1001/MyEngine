#include "Level.h"

Level::Level(std::vector<Actor> actors) : actors(actors)
{
    
}

Level::Level(std::vector<Actor> actors, std::vector<Graphics::Camera> cameras) : actors(actors), cameras(cameras)
{

}

Level::AddCamera(Graphics::Camera camera)
{
    cameras.push_back(camera);
}