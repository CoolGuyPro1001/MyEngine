#include "OGLIndexBuffer.h"

OGLIndexBuffer::OGLIndexBuffer(uint*& id_ptr, bool mirror_data) : OGLBuffer(id_ptr, mirror_data)
{
    m_target = GL_ELEMENT_ARRAY_BUFFER;
    m_usage = GL_STATIC_DRAW;
}

OGLIndexBuffer& OGLIndexBuffer::operator=(OGLIndexBuffer&& other)
{
    GraphicsBuffer::operator=(std::move(other));
    return *this;
}
