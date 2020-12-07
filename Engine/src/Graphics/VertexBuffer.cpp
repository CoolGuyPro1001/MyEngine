#include "VertexBuffer.h"
#include "GLDebug.h"

namespace Graphics
{
    void InitVertexBuffer(uint& id)
    {
        glCreateBuffers(1, &id);
        glBindBuffer(GL_ARRAY_BUFFER, id);
    }

    void DeleteBuffer(uint& id)
    {
        glDeleteBuffers(1, &id);
    }

    void AddDataToBuffer(std::vector<Vertex>& vertices, uint& vao_id)
    {
        uint vertices_size = vertices.size() * sizeof(Vertex);
        int buffer_size = 0;
        glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &buffer_size);

        //Backup data from vertex buffer. Changing the buffer data deletes everything!
        float stored_data[buffer_size / sizeof(float)];
        glGetBufferSubData(GL_ARRAY_BUFFER, 0, buffer_size, stored_data);

        //Add the data
        glBufferData(GL_ARRAY_BUFFER, vertices_size + buffer_size, 0, GL_DYNAMIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, buffer_size, stored_data);
        glBufferSubData(GL_ARRAY_BUFFER, buffer_size, vertices_size, &(vertices[0]));

        //Setup VAO
        glGenVertexArrays(1, &vao_id);
    }

    void FormatData(uint& vao_id, int starting_offset)
    {
        int position_attrib_index = 0;
        int color_attrib_index = 1;

        glBindVertexArray(vao_id);

        glEnableVertexAttribArray(position_attrib_index);
        glEnableVertexAttribArray(color_attrib_index);
        
        int vertex_color_offset = 3 * sizeof(float);
        
        glVertexAttribPointer(position_attrib_index, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(starting_offset)); //Vector3
        glVertexAttribPointer(color_attrib_index, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(starting_offset + vertex_color_offset)); //Color
    }

    /*void ModifyData(uint& vao_id, std::vector<Vertex>& vertices)
    {
        glBindVertexArray(vao_id));
        glEnableVertexAttribArray(position_attrib_index));
        glEnableVertexAttribArray(color_attrib_index));
        
        int vertex_color_offset = 3 * sizeof(float);
        
        glVertexAttribPointer(position_attrib_index, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0)); //Vector3
        glVertexAttribPointer(color_attrib_index, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*) vertex_color_offset)); //Color
    }*/
}