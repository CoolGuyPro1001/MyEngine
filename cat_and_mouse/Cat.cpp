#include "Cat.h"

Cat::Cat(Shared<Model> model) : Actor(model)
{
}

void Cat::Tick()
{
    Actor::Tick();
    MoveForward();
    MoveRight();
}

void Cat::MoveForward()
{
    position.z += position_velocity.z;
}

void Cat::MoveRight()
{
    position.x += position_velocity.x;
}

void Cat::OnUp(StickYEvent e)
{
    position_velocity.z += e.value;
}

void Cat::OnRight(StickXEvent e)
{
    position_velocity.x += e.value;
}