#include "VertexBuffer.h"
#include "Graphics.h"
#include "GLDebug.h"

#define BUFFER_OFFSET(x) (static_cast<u8*>(0) + (x))

namespace Graphics
{
    VertexBuffer buffer2d = VertexBuffer();
    VertexBuffer buffer3d = VertexBuffer();
    std::vector<VertexBuffer> batch_2d_buffers = std::vector<VertexBuffer>();

    #define POSITION_ATTRIB_INDEX 0
    #define COLOR_ATTRIB_INDEX 1
    #define TEXCOORD_ATTRIB_INDEX 2

    VertexBuffer::VertexBuffer() : Buffer()
    {
        vao = 0;
    }

    VertexBuffer::~VertexBuffer()
    {
        Release();
    }

    VertexBuffer::VertexBuffer(VertexBuffer&& other) : Buffer(std::move(other)), vao(other.vao)
    {
        other.vao = 0;
    }

    VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other)
    {
        //ALWAYS check for self-assignment.
        if(this != &other)
        {
            Release();
            std::swap(id, other.id);
            std::swap(size, other.size);
            std::swap(vao, other.vao);
        }

        return *this;
    }

    uint VertexBuffer::GetVAO()
    {
        return vao;
    }

    void VertexBuffer::Init()
    {
        Buffer::Init();
        GLCall(glGenVertexArrays(1, &vao));
    }

    void VertexBuffer::Bind()
    {
        Buffer::Bind();
        GLCall(glBindVertexArray(vao));
    }

    void VertexBuffer::Release()
    {
        Buffer::Release();
        GLCall(glDeleteVertexArrays(1, &vao));
    }

    void VertexBuffer::AddData(std::vector<Vertex>& vertices)
    {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, id));
        uint vertices_size = vertices.size() * sizeof(Vertex);

        int buffer_size = 0;
        GLCall(glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &buffer_size));

        //Backup data from vertex buffer. Changing the buffer data deletes everything!
        u8 stored_data[buffer_size / sizeof(u8)];
        GLCall(glGetBufferSubData(GL_ARRAY_BUFFER, 0, buffer_size, stored_data));

        //Add the data
        GLCall(glBufferData(GL_ARRAY_BUFFER, vertices_size + buffer_size, 0, GL_STATIC_DRAW));
        GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, buffer_size, stored_data));
        GLCall(glBufferSubData(GL_ARRAY_BUFFER, buffer_size, vertices_size, &(vertices[0])));
        
        size += vertices_size;
    }


    void VertexBuffer::Format()
    {
        //Vertex
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, id));
        GLCall(glBindVertexArray(vao));

        GLCall(glEnableVertexAttribArray(POSITION_ATTRIB_INDEX));
        GLCall(glEnableVertexAttribArray(COLOR_ATTRIB_INDEX));
        GLCall(glEnableVertexAttribArray(TEXCOORD_ATTRIB_INDEX));
        
        int color_offset = 3 * sizeof(float);
        int texcoord_offset = color_offset + 4 * sizeof(u8);

        //Vector3
        GLCall(glVertexAttribPointer(POSITION_ATTRIB_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 
            BUFFER_OFFSET(0)));
            
        //Color
        GLCall(glVertexAttribPointer(COLOR_ATTRIB_INDEX, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(Vertex), 
            BUFFER_OFFSET(color_offset)));

        //Texture Coordinates
        GLCall(glVertexAttribPointer(TEXCOORD_ATTRIB_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 
            BUFFER_OFFSET(texcoord_offset)));
    }

    void CreateBatchBuffers()
    {
        int i = 0;
        while(i < 5)
        {
            batch_2d_buffers.emplace_back(VertexBuffer());
            i++;
        }
    }

    void InitVertexBuffers()
    {
        buffer2d.Init();
        buffer3d.Init();
        for(VertexBuffer& buffer : batch_2d_buffers)
            buffer.Init();
    }

    void ClearVertexBuffers()
    {
        buffer2d.Clear();
        buffer3d.Clear();
        for(VertexBuffer& buffer : batch_2d_buffers)
            buffer.Clear();
    }

    void FormatVertexBuffers()
    {
        buffer2d.Format();
        buffer3d.Format();
        for(VertexBuffer& buffer : batch_2d_buffers)
            buffer.Format();
    }
}