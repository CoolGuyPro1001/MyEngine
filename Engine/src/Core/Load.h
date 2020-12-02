#ifndef LOAD_H
#define LOAD_H

#include "Level.h"

namespace Engine
{
    void LoadLevel(Level& level);
    void RunLevel(Level& level, bool create_window);
}
#endif