#ifndef STREVO_H
#define STREVO_H

#include <Actor.h>
#include <Events.h>
#include <Graphics/Camera.h>

class Strevo : public Actor
{
public:
    Vector3 relative_velocity;
    Shared<Graphics::Camera> camera;

    Strevo(Shared<Model> model, Shared<Graphics::Camera> camera);

    void Tick() override;
    void OnForwards(StickYEvent e);
    void OnRight(StickXEvent e);
    void OnJumpReleased();
    void OnJumpPressed();
};

#endif