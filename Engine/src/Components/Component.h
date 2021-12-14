#ifndef COMPONENT_H
#define COMPONENT_H

struct Level;
struct Actor;

struct Component
{
    virtual void AttachToLevel(Level& lvl) = 0;
    std::vector<Shared<Actor>> actors;
};

#endif
