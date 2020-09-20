#include "VertexBuffer.h"
#include "GLDebug.h"

namespace Graphics
{
    VertexBuffer::VertexBuffer(std::vector<Vertex> vertices) :
        vertices(vertices)
    {
        GLCall(glCreateBuffers(1, &name));
        RefreshData();
    }

    VertexBuffer::VertexBuffer()
    {
        GLCall(glCreateBuffers(1, &name));
        RefreshData();
    }

    void VertexBuffer::Bind()
    {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, name));
    }

    void VertexBuffer::UnBind()
    {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    int VertexBuffer::ByteSize()
    {
        int v_size = vertices.size() * sizeof(Vertex);
        return v_size;
    }

    std::vector<Vertex> VertexBuffer::GetVertices()
    {
        return vertices;
    }

    void VertexBuffer::RefreshData()
    {
        Bind();
        int vertex_buffer_size = vertices.size();
        int position_attrib_index = 0;
        int color_attrib_index = 1;

        int size = sizeof(Vertex);
        GLCall(glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size * sizeof(Vertex), &(vertices[0]), GL_DYNAMIC_DRAW));
        
        float data[vertex_buffer_size * 7];
        GLCall(glGetBufferSubData(GL_ARRAY_BUFFER, 0, vertex_buffer_size * sizeof(Vertex), data));

        GLCall(glEnableVertexAttribArray(position_attrib_index));
        GLCall(glEnableVertexAttribArray(color_attrib_index));
        
        int vertex_color_offset = 3 * sizeof(float);
        
        GLCall(glVertexAttribPointer(position_attrib_index, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0)); //Vector3
        GLCall(glVertexAttribPointer(color_attrib_index, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*) vertex_color_offset)); //Color

        UnBind();
    }
}