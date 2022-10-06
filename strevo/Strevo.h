#ifndef STREVO_H
#define STREVO_H

#include <Actor.h>
#include <Components/CameraComponent.h>
#include <Events/InputEvents.h>

class Strevo : public Actor
{
public:
    Vector3 relative_velocity;

    Strevo();
    Strevo(Vector3 position);

    void Tick();
    void OnForwards(EAnalogInput* e);
    void OnRight(EAnalogInput* e);

    void OnKeyForward(EButtonInput* e);
    void OnKeyBack(EButtonInput* e);
    void OnKeyLeft(EButtonInput* e);
    void OnKeyRight(EButtonInput* e);
    //void OnJumpReleased();
    //void JumpBegin(EButtonInput* e);
    //void JumpEnd(EButtonInput* e);
};

#endif
