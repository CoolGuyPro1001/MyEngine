#include "Model.h"

Model::Model(std::vector<std::shared_ptr<Graphics::VertexBuffer>> vertex_buffers, std::shared_ptr<Graphics::IndexBuffer> indices) :
    vertex_buffers(vertex_buffers),
    indices(indices)
{
    position = Graphics::Vector3(0, 0, 0);
    scale = Graphics::Vector3(1, 1, 1);
    rotation = Graphics::Vector3(0, 0, 0);
}

void Model::Render()
{
    //Apply For Graphics Rendering
    //Graphics::AddBuffers(vertex_buffers, indices);
}