#include "Actor.h"

Model::Model(std::vector<Vertex> vertices) : vertices(vertices)
{
}

Actor::Actor(Model* model) : model(model)
{
}
