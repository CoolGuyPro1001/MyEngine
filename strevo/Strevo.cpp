#include "Strevo.h"
#include <Common/Log.h>
#include <Core/Time.h>

Strevo::Strevo() : Actor()
{
    relative_velocity = Vector3(0, 0, 0);
}

void Strevo::Tick()
{
    float direct = relative_velocity.direct;
    float side = relative_velocity.side;

    Shared<CCamera> camera = GetComponent<CCamera>();
    
    position_velocity.x = sin(camera->rotation.yaw) * direct +
        sin(camera->rotation.yaw - PI / 2.0f) * side;

    position_velocity.z = cos(camera->rotation.yaw) * direct +
        cos(camera->rotation.yaw - PI / 2.0f) * side;
    
    Actor::Tick();
}

void Strevo::OnJumpReleased()
{
    relative_velocity.y = 0;
}

void Strevo::OnJumpPressed()
{
    //Vector3 position_velocity = GetPositionVelocity();
    //position_velocity.y = 0.1f * Delay();
    //SetPositionVelocity(position_velocity);
}

void Strevo::OnForwards(StickYEvent e)
{
    if(e.value == 0)
    {
        relative_velocity.direct = 0;
    }
    else
    {
        relative_velocity.direct = 0.1 * ((float)e.value / (float)SHRT_MAX) * Delay();
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
        relative_velocity.side = 0.1 * ((float)e.value / (float)SHRT_MAX) * Delay();
    }
}
