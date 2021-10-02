#include "UniformBuffer.h"
#include "GLDebug.h"

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

        uint uniform_block_index = glGetUniformBlockIndex(g_shader_programs[1], "MVPBlock");  
        GLCall(glUniformBlockBinding(g_shader_programs[1], uniform_block_index, 0));
        size = 512;
    }

    void UniformBuffer::Fill(std::vector<glm::mat4> mvps)
    {
        GLCall(glBindBuffer(GL_UNIFORM_BUFFER, id));
        GLCall(glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_STREAM_DRAW));
        GLCall(glBufferSubData(GL_UNIFORM_BUFFER, 0, mvps.size() * sizeof(glm::mat4), &mvps[0]));
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