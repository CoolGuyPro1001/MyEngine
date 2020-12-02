#ifndef LOAD_H
#define LOAD_H

#include "Level.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/Graphics.h"

#include "Actor.h"
#include "Controller.h"
#include "Graphics/Camera.h"

namespace Engine
{
    void LoadLevel(Level& level);
    void RunLevel(Level& level, bool create_window);
}
#endif