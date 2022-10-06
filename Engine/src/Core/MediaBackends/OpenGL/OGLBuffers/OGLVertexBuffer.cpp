#include "OGLVertexBuffer.h"
#include "../OGLDebug.h"
#include "Common/Vertex.h"

#define BUFFER_OFFSET(x) (static_cast<u8*>(0) + (x))

#define POSITION_ATTRIB_INDEX 0
#define COLOR_ATTRIB_INDEX 1
#define TEXCOORD_ATTRIB_INDEX 2


OGLVertexBuffer::OGLVertexBuffer(uint*& id_ptr, uint*& vao_ptr, bool mirror_data) : OGLBuffer(id_ptr, mirror_data)
{
    m_vao = 0;
    vao_ptr = &m_vao;
    m_target = GL_ARRAY_BUFFER;
    m_usage = GL_STATIC_DRAW;
    /*int i = 0;
    while(i < 5)
    {
        buffers[BATCH_BUFFER].emplace_back(VertexBuffer);
        i++;
    }*/
}

OGLVertexBuffer::~OGLVertexBuffer()
{
    //Destroy();
}

OGLVertexBuffer::OGLVertexBuffer(OGLVertexBuffer&& other) : OGLBuffer(std::move(other)), m_vao(other.m_vao)
{
    other.m_vao = 0;
}

OGLVertexBuffer& OGLVertexBuffer::operator=(OGLVertexBuffer&& other)
{
    //ALWAYS check for self-assignment.
    GraphicsBuffer::operator=(std::move(other));
    return *this;
}

/*bool OGLVertexBufferManager::MoveBuffer(uint vb_type, uint vb_destination, uint vb_source)
{
    VertexBuffer& destination = GetBuffer(vb_type, vb_destination)
    VertexBuffer& source = instance_buffers(vb_type, vb_source);

    //ALWAYS check for self-assignment.
    if(source.id != destination.id)
    {
        ReleaseBuffer(vb_type, vb_source);

        std::swap(source.id, destination.id);
        std::swap(source.size, destination.size);
        std::swap(source.vao, destination.vao);

        instance_buffers.erase(vb_source);
        return true;
    }

    return false;
}*/

void OGLVertexBuffer::Init(size_t size)
{
    OGLBuffer::Init(size);
    GLCall(glGenVertexArrays(1, &m_vao));
}

void OGLVertexBuffer::Fill(u8* data, size_t size)
{
    OGLBuffer::Fill(data, size);
    Format();
}

void OGLVertexBuffer::Destroy()
{
    OGLBuffer::Destroy();

    if(m_id != 0)
    {
        GLCall(glDeleteVertexArrays(1, &m_vao));
        m_vao = 0;
    }
}

void OGLVertexBuffer::Format()
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
    GLCall(glBindVertexArray(m_vao));

    GLCall(glEnableVertexAttribArray(POSITION_ATTRIB_INDEX));
    GLCall(glEnableVertexAttribArray(COLOR_ATTRIB_INDEX));
    GLCall(glEnableVertexAttribArray(TEXCOORD_ATTRIB_INDEX));

    int color_offset = 3 * sizeof(float);
    int texcoord_offset = color_offset + 4 * sizeof(u8);

    //Vector3
    GLCall(glVertexAttribPointer(POSITION_ATTRIB_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        BUFFER_OFFSET(0)));

    //Color
    GLCall(glVertexAttribPointer(COLOR_ATTRIB_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex),
        BUFFER_OFFSET(color_offset)));

    //Texture Coordinates (UVW) W Being Slice Index Of Texture Array
    GLCall(glVertexAttribPointer(TEXCOORD_ATTRIB_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        BUFFER_OFFSET(texcoord_offset)));
}
