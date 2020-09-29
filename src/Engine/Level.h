#ifndef LEVEL_H
#define LEVEL_H

#include "Actor.h"

struct Level
{
public:
    Level(std::vector<Actor> actors);
    std::vector<Actor> actors;
};
#endif