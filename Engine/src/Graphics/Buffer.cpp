#include "Buffer.h"
#include "GLDebug.h"

namespace Graphics
{
    Buffer::Buffer()
    {
        id = 0;
        size = 0;
    }

    Buffer::~Buffer()
    {
        Release();
    }

    Buffer::Buffer(Buffer&& other) : id(other.id), size(other.size)
    {
        other.id = 0;
        other.size = 0;
    }

    Buffer& Buffer::operator=(Buffer&& other)
    {
        //ALWAYS check for self-assignment.
        if(this != &other)
        {
            Release();
            std::swap(id, other.id);
            std::swap(size, other.size);
        }

        return *this;
    }

    void Buffer::Init()
    {
        if(id == 0)
            GLCall(glCreateBuffers(1, &id));
    }

    void Buffer::Release()
    {
        if(id != 0)
        {
            GLCall(glDeleteBuffers(1, &id));
            id = 0;
        }
    }

    void Buffer::Bind()
    {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, id));
    }

    void Buffer::Clear()
    {
        Bind();
        GLCall(glBufferData(GL_ARRAY_BUFFER, size, 0, GL_STATIC_DRAW));
    }

    uint Buffer::GetID()
    {
        return id;
    }

    size_t Buffer::GetSize()
    {
        return size;
    }
}