#include "Level.h"

Level::Level(std::vector<Actor> actors) : 
    actors(actors)
{
}

Level::Level(std::vector<Actor> actors, std::vector<Graphics::Camera> cameras) : 
    actors(actors), 
    cameras(cameras)
{
}

Level(std::vector<Actor> actors, std::funtion<void()> script) : 
    actors(actors), 
    script(script)
{
}

Level(std::vector<Actor> actors, std::vector<Graphics::Camera> cameras, std::function<void()> script) : 
    actors(actors),
    cameras(cameras),
    script(scripts)
{
}