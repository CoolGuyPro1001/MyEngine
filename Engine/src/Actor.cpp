#include "Actor.h"

Model::Model(std::vector<Vertex> vertices) : vertices(vertices)
{
}

Actor::Actor()
{
}

Actor::Actor(Shared<Model> model) : model(model)
{
}

void Actor::Tick()
{
}
