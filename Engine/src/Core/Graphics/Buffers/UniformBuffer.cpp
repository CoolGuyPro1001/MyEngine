#include "UniformBuffer.h"
#include "Core/Graphics/GLDebug.h"
#include "Core/Graphics/Graphics.h"

namespace Graphics
{
    UniformBuffer mvp_buffer = UniformBuffer();

    UniformBuffer& UniformBuffer::operator=(UniformBuffer&& other)
    {
        Buffer::operator=(std::move(other));
        return *this;
    }

    void UniformBuffer::Init()
    {
        GLCall(glCreateBuffers(1, &id));

        GLCall(glBindBuffer(GL_UNIFORM_BUFFER, id));
        GLCall(glBufferData(GL_UNIFORM_BUFFER, 512, NULL, GL_STREAM_DRAW));

        uint uniform_block_index = glGetUniformBlockIndex(g_shader_programs[0], "MVPBlock");  
        GLCall(glUniformBlockBinding(g_shader_programs[0], uniform_block_index, 0));
        size = 512;
    }

    void UniformBuffer::AddData(u8* data, uint data_amount, uint data_bytesize)
    {
        GLCall(glBindBuffer(GL_UNIFORM_BUFFER, id));
        GLCall(glBufferSubData(GL_UNIFORM_BUFFER, 0, data_amount * data_bytesize, data));
        GLCall(glBindBufferBase(GL_UNIFORM_BUFFER, 0, id));
    }

    void UniformBuffer::Clear()
    {
        Bind();
        GLCall(glBufferData(GL_ARRAY_BUFFER, size, 0, GL_STREAM_DRAW));
    }

    void InitUniformBuffers()
    {
        mvp_buffer.Init();
    }
    
    void ClearUniformBuffers()
    {
        mvp_buffer.Clear();
    }
}
