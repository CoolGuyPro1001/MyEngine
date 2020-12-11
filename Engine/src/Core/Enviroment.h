#ifndef ENVIROMENT_H
#define ENVIROMENT_H

#include "../pch.h"
#include "Controller.h"

namespace Engine
{
    float Normalize(int num, int low, int high);
    void PollEvents(std::vector<Controller>& controllers);
}
#endif