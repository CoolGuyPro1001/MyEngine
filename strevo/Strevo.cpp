#include "Strevo.h"
#include <Core/Runtime.h>
#include <Core/Log.h>

Strevo::Strevo(Shared<Model> model) : Actor(model)
{
}

void Strevo::Tick()
{
    Actor::Tick();
    Engine::Log("X:%f Y:%f Z:%f\n", position.x, position.y, position.z);
}

void Strevo::OnJumpReleased()
{
    position_velocity.y = 0;
}

void Strevo::OnJumpPressed()
{
    position_velocity.y = 0.1f * Engine::Delay();
}

void Strevo::OnForwards(StickYEvent e)
{
    if(e.value == 0)
    {
        position_velocity.x = 0;
    }
    else
    {
        position_velocity.x = (e.value / SHRT_MAX) * 0.02f * Engine::Delay();
    }
}

void Strevo::OnRight(StickXEvent e)
{
    if(e.value == 0)
    {
        position_velocity.z = 0;
    }
    else
    {
        position_velocity.z = (e.value / SHRT_MAX) * 0.02f * Engine::Delay();
    }
}