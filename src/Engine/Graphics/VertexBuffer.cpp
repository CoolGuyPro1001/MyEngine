#include "VertexBuffer.h"
#include "GLDebug.h"

namespace Graphics
{
    void InitVertexBuffer(unsigned int id)
    {
        GLCall(glCreateBuffers(1, &id));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, id));
    }

    void AddDataToBuffer(std::vector<Vertex>& vertices, unsigned int& buffer_size)
    {
        unsigned int vertices_size = vertices.size() * sizeof(Vertex);
        
        //Backup data from vertex buffer. Changing the buffer data deletes everything!
        float stored_data[buffer_size / sizeof(float)];
        GLCall(glGetBufferSubData(GL_ARRAY_BUFFER, 0, buffer_size * sizeof(Vertex), data));

        //Add the data
        GLCall(glBufferData(GL_ARRAY_BUFFER, vertices_size + buffer_size, 0, GL_DYNAMIC_DRAW));
        GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, buffer_size, stored_data));
        GLCall(glBufferSubData(GL_ARRAY_BUFFER, buffer_size, vertices_size, vertices));

        buffer_size += vertices_size;
    }

    int VertexBufferSize(std::vector<Vertex>& vertices)
    {
        int v_size = vertices.size() * sizeof(Vertex);
        return v_size;
    }

    void RefreshData(std::vector<Vertex>& vertices)
    {
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
    }
}