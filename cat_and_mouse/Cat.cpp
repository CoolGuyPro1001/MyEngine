#include "Cat.h"
#include <Core/Runtime.h>
#include <Core/Log.h>

Cat::Cat(Shared<Model> model) : Actor(model)
{
}

void Cat::Tick()
{
    Actor::Tick();
    Engine::Log("X:%f Y:%f Z:%f\n", position.x, position.y, position.z);
}

void Cat::OnUpPressed()
{
    position_velocity.y = 0.005f * Engine::Delay();
}

void Cat::OnReleased()
{
    position_velocity.y = 0;
}

void Cat::OnDownPressed()
{
    position_velocity.y = -0.005f * Engine::Delay();
}

void Cat::OnForwards(StickYEvent e)
{
    if(e.value == 0)
    {
        position_velocity.x = 0;
    }
    else
    {
        position_velocity.x = (e.value / SHRT_MAX) * 0.005f * Engine::Delay();
    }
}

void Cat::OnRight(StickXEvent e)
{
    if(e.value == 0)
    {
        position_velocity.z = 0;
    }
    else
    {
        position_velocity.z = (e.value / SHRT_MAX) * 0.005f * Engine::Delay();
    }
}