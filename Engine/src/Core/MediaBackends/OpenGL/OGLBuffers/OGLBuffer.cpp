#include "../OGLBuffer.h"
#include "../OGLDebug.h"

OGLBuffer::OGLBuffer(uint*& id_ptr, bool mirror_data) : GraphicsBuffer(mirror_data)
{
    m_id = 0;
    id_ptr = &m_id;
}

OGLBuffer::~OGLBuffer()
{
    Destroy();
}

OGLBuffer::OGLBuffer(OGLBuffer&& other) : GraphicsBuffer(other.m_mirror_data), m_id(other.m_id), m_target(other.m_target), m_usage(other.m_usage)
{
    other.m_id = 0;
    other.m_target = 0;
    other.m_usage = 0;
}

OGLBuffer& OGLBuffer::operator=(OGLBuffer&& other)
{
    //ALWAYS check for self-assignment.
    if(this != &other)
    {
        Destroy();
        std::swap(m_id, other.m_id);
        std::swap(m_size, other.m_size);
        std::swap(m_target, other.m_target);
        std::swap(m_usage, other.m_usage);
        std::swap(m_data, other.m_data);
    }

    return *this;
}

void OGLBuffer::Init(size_t size)
{
    GLCall(glCreateBuffers(1, &m_id));

    if(size > 0)
    {
        GLCall(glBindBuffer(m_target, m_id));
        GLCall(glBufferData(m_target, size, 0, m_usage));

        m_size = size;
    }
}

void OGLBuffer::Fill(u8* data, size_t size)
{
    GLCall(glBindBuffer(m_target, m_id));
    GLCall(glBufferData(m_target, size, data, m_usage));

    if(m_mirror_data && data != (u8*) &m_data[0])
    {
        m_data.resize(size);
        memcpy(&m_data[0], data, size);
    }

    m_size = size;
}

void OGLBuffer::Insert(u8* data, size_t size)
{
    GLCall(glBindBuffer(m_target, m_id));

    auto is_less = [](MemorySection ms, size_t size)
    {
        return ms.size < size;
    };

    //Look For First Memory Block With Enough Room Or One That Is At The End Of The Buffer
    auto ms = std::lower_bound(m_free_memory.begin(), m_free_memory.end(), size, is_less);
    if(ms != m_free_memory.end())
    {
        GLCall(glBufferSubData(m_target, ms->offset, size, data));

        if(m_mirror_data && data != (u8*) &m_data[0])
            memcpy(&m_data[ms->offset], data, size);

        ms->size -= size;
        if(ms->size == 0)
            m_free_memory.erase(ms);

        ms->offset += size;
        return;
    }

    uint buffer_data_size = m_size;
    auto last_memory = ms - 1;

    //Any Memory Block At The End Of The Buffer Will Take A Chunk Of Data From The New Data
    if(last_memory->offset + last_memory->size == m_size)
    {
        buffer_data_size += size - last_memory->size;
        m_free_memory.erase(last_memory);
    }
    else
    {
        buffer_data_size += size;
    }

    u8* buffer_data = new u8[buffer_data_size]; //Have Room For Both Buffer Data and New Data
    GLCall(glGetBufferSubData(m_target, 0, m_size, buffer_data)); //Add Data From Buffer
    memcpy(buffer_data + (buffer_data_size - size), data, size); //Then Copy The New Data

    GLCall(glBufferData(m_target, buffer_data_size, buffer_data, m_usage));

    if(m_mirror_data && data != (u8*) &m_data[0])
    {
        m_data.resize(buffer_data_size);
        memcpy(&m_data[0], buffer_data, buffer_data_size);
    }

    delete[] buffer_data;
    m_size = buffer_data_size;
}

void OGLBuffer::Destroy()
{
    if(m_id != 0)
    {
        GLCall(glDeleteBuffers(1, &m_id));
        m_id = 0;
    }
}
