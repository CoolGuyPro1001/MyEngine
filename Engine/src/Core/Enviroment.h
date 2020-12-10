#ifndef ENVIROMENT_H
#define ENVIROMENT_H

#include "../pch.h"
#include "Controller.h"

namespace Engine
{
    void PollEvents(std::vector<Controller>& controllers);
}
#endif