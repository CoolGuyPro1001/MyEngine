#include "Strevo.h"
#include <Common/Log.h>
#include <Core/Time.h>
#include <Common/Mathematics.h>

Strevo::Strevo() : Actor()
{
    relative_velocity = Vector3(0, 0, 0);
}

Strevo::Strevo(Vector3 position) : Actor(position)
{
    relative_velocity = Vector3(0, 0, 0);
}

void Strevo::Tick()
{
    float direct = relative_velocity.direct;
    float side = relative_velocity.side;


    Shared<CCamera> camera = GetComponent<CCamera>();

    if(camera)
    {
        float yaw = DegreesToRadians(camera->rotation.yaw);
        float sin_yaw = sin(yaw);
        float cos_yaw = cos(yaw);

        position_velocity.x = sin_yaw * direct + -cos_yaw * side;
        position_velocity.z = cos_yaw * direct + sin_yaw * side;

        rotation_velocity.yaw = camera->rod_rotation_velocity.yaw * Delay();
    }
    
    Actor::Tick();
}

/*void Strevo::OnJump(ButtonEvent e)
{
    if(e.pressed
    relative_velocity.y = 0;
}*/

/*void Strevo::JumpBegin(EButtonInput* e)
{
    //Vector3 position_velocity = GetPositionVelocity();
    //position_velocity.y = 0.1f * Delay();
    //SetPositionVelocity(position_velocity);
    Log("Jump Ended\n");
}

void Strevo::JumpEnd(EButtonInput* e)
{
    Log("Jump Ended\n");
}*/

void Strevo::OnForwards(EAnalogInput* e)
{
    relative_velocity.direct = 10 * e->value * Delay();
}

void Strevo::OnRight(EAnalogInput* e)
{
    relative_velocity.side = 10 * e->value * Delay();
}

void Strevo::OnKeyForward(EButtonInput* e)
{
    relative_velocity.direct = 10 * e->pressed * Delay();
}

void Strevo::OnKeyBack(EButtonInput* e)
{
    relative_velocity.direct = -10 * e->pressed * Delay();
}

void Strevo::OnKeyLeft(EButtonInput* e)
{
    relative_velocity.side = -10 * e->pressed * Delay();
}

void Strevo::OnKeyRight(EButtonInput* e)
{
    relative_velocity.side = 10 * e->pressed * Delay();
}
