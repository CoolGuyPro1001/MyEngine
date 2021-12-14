#ifndef STREVO_H
#define STREVO_H

#include <Actor.h>
#include <Components/CameraComponent.h>
#include <Events.h>

class Strevo : public Actor
{
public:
    Vector3 relative_velocity;

    Strevo();

    void Tick() override;
    void OnForwards(StickYEvent e);
    void OnRight(StickXEvent e);
    void OnJumpReleased();
    void OnJumpPressed();
};

#endif
