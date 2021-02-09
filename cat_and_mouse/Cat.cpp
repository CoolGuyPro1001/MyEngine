#include "Cat.h"
#include <Core/Enviroment.h>
#include <Core/Log.h>

Cat::Cat(Shared<Model> model) : Actor(model)
{
}

void Cat::Tick()
{
    MoveForward();
    MoveRight();
    MoveUp();
    Engine::Log("X:%f Y:%f Z:%f\n", position.x, position.y, position.z);
}

void Cat::MoveForward()
{
    position.z += position_velocity.z;
}

void Cat::MoveRight()
{
    position.x += position_velocity.x;
}

void Cat::MoveUp()
{
    position.y += position_velocity.y;
}

void Cat::OnUpPressed()
{
    position_velocity.y += 0.001;
}

void Cat::OnReleased()
{
    position_velocity.y = 0;
}

void Cat::OnDownPressed()
{
    position_velocity.y -= 0.001;
}

void Cat::OnForwards(StickYEvent e)
{
    if(e.value == 0)
    {
        position_velocity.z = 0;
    }
    else
    {
        position_velocity.z += (e.value / SHRT_MAX) * 0.001;
    }
}

void Cat::OnRight(StickXEvent e)
{
    if(e.value == 0)
    {
        position_velocity.x = 0;
    }
    else
    {
        position_velocity.x += (e.value / SHRT_MAX) * 0.001;
    }
}