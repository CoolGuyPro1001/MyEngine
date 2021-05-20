#include "Strevo.h"
#include <Core/Runtime.h>
#include <Core/Log.h>

Strevo::Strevo(Shared<Model> model, Shared<Graphics::Camera> camera) : Actor(model), camera(camera)
{
    relative_velocity = Vector3(0, 0, 0);
}

void Strevo::Tick()
{
    float direct = relative_velocity.direct;
    float side = relative_velocity.side;
    
    position_velocity.x = sin(camera->rotation.yaw) * direct + 
        sin(camera->rotation.yaw - PI / 2.0f) * side;

    position_velocity.z = cos(camera->rotation.yaw) * direct + 
        cos(camera->rotation.yaw - PI / 2.0f) * side;
    
    Actor::Tick();
    //Engine::Log("X:%f Y:%f Z:%f\n", position.x, position.y, position.z);  
}

void Strevo::OnJumpReleased()
{
    relative_velocity.y = 0;
}

void Strevo::OnJumpPressed()
{
    position_velocity.y = 0.1f * Engine::Delay();
}

void Strevo::OnForwards(StickYEvent e)
{
    if(e.value == 0)
    {
        relative_velocity.direct = 0;
    }
    else
    {
        relative_velocity.direct = 0.1 * ((float)e.value / (float)SHRT_MAX) * Engine::Delay();
    }
}

void Strevo::OnRight(StickXEvent e)
{
    if(e.value == 0)
    {
        relative_velocity.side = 0;
    }
    else
    {
        relative_velocity.side = 0.1 * ((float)e.value / (float)SHRT_MAX) * Engine::Delay();
    }
}