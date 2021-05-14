#ifndef STREVO_H
#define STREVO_H

#include <Actor.h>
#include <Events.h>

class Strevo : public Actor
{
public:
    Strevo(Shared<Model> model);

    void Tick() override;
    
    void OnForwards(StickYEvent e);
    void OnRight(StickXEvent e);
    void OnJumpReleased();
    void OnJumpPressed();
};

#endif