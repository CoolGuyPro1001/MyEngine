#ifndef CAT_H
#define CAT_H

#include <Actor.h>
#include <Events.h>

class Cat : public Actor
{
public:
    Cat(Shared<Model> model);
    void MoveForward(float val);
    void MoveRight(float val);

    void OnUp(StickYEvent e);
    void OnRight(StickXEvent e);

private:
    Vector3 velocity;
};

#endif