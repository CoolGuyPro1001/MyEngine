#include "OGLUniformBuffer.h"
#include "../OGLDebug.h"

OGLUniformBuffer::OGLUniformBuffer(uint*& id_ptr, bool mirror_data) : OGLBuffer(id_ptr, mirror_data)
{
    m_target = GL_UNIFORM_BUFFER;
    m_usage = GL_DYNAMIC_COPY;
}

OGLUniformBuffer& OGLUniformBuffer::operator=(OGLUniformBuffer&& other)
{
    GraphicsBuffer::operator=(std::move(other));
    return *this;
}

