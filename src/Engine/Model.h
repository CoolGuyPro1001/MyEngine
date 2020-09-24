#ifndef MODEL_H
#define MODEL_H

#include "Graphics/Graphics.h"
#include "Graphics/Units.h"

#include <memory>
#include <vector>

#include "../Defines.h"

class Model
{
public:
    std::vector<Shared<Graphics::VertexBuffer>> vertex_buffers;
    //std::shared_ptr<Graphics::IndexBuffer> indices;

    unsigned int vertex_name;
    //unsigned int index_name;
     
    Graphics::Vector3 position;
    Graphics::Vector3 scale;
    Graphics::Vector3 rotation;
    
    Model(std::vector<Shared<Graphics::VertexBuffer>> vertex_buffers, Shared<Graphics::IndexBuffer> indices);
    void Render();
};

#endif