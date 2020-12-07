#ifndef LOAD_H
#define LOAD_H

#include "Level.h"

namespace Engine
{
    void Start(int window_width, int window_height, const char* window_name);
    void LoadLevel(Level& level);
    void Run();
}
#endif