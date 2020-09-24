#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <GL/glew.h>
#include "Units.h"

#include <memory>
#include <vector>

namespace Graphics
{
    class VertexBuffer
    {
    private:
        unsigned int name;
        std::vector<Vertex> vertices;
    public:
        VertexBuffer(std::vector<Vertex> vertices);
        VertexBuffer();

        int ByteSize();
        std::vector<Vertex> GetVertices();
        void RefreshData();
        void Bind();
        void UnBind();

        VertexBuffer operator+=(VertexBuffer x);
    };
}

#endif