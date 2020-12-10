#ifndef CAT_H
#define CAT_H

#include <Actor.h>
#include <Events.h>

class Cat : public Actor
{
public:
    Cat(Shared<Model> model);

    void Tick() override;
    
    void MoveForward();
    void MoveRight();
    void OnUp(StickYEvent e);
    void OnRight(StickXEvent e);
};

#endif