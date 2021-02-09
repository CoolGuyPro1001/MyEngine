#include "Level.h"

Level::Level()
{
}

Level::Level(std::vector<Shared<Actor>> actors) : 
    actors(actors)
{
}

Level::Level(std::vector<Shared<Actor>> actors, std::vector<Shared<Graphics::Camera>> cameras) : 
    actors(actors), 
    cameras(cameras)
{
}

Level::Level(std::vector<Shared<Actor>> actors, std::function<void()> script) : 
    actors(actors), 
    script(script)
{
}

Level::Level(std::vector<Shared<Actor>> actors, std::vector<Shared<Graphics::Camera>> cameras, std::function<void()> script) : 
    actors(actors),
    cameras(cameras),
    script(script)
{
}