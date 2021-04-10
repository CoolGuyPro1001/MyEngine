#include "Level.h"
#include "Actor.h"

Level::Level()
{
    gravity = 30;
}

void Level::AddTexture(Shared<Graphics::Texture> texture)
{
    textures.push_back(texture);
}

void Level::AddModel(Shared<Model> model)
{
    models.push_back(model);
}

void Level::AddActor(Shared<Actor> actor)
{
    actor->current_level = this;
    actors.push_back(actor);
}

void Level::AddCamera(Shared<Graphics::Camera> camera)
{
    cameras.push_back(camera);
}

void Level::AddController(Controller controller)
{
    controllers.push_back(controller);
}