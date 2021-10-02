#ifndef UNIFORM_BUFFER_H
#define UNIFORM_BUFFER_H

#include "Graphics.h"

namespace Graphics
{
    struct UniformBuffer : public Buffer
    {
        UniformBuffer& operator=(UniformBuffer&& other);

        void Init() override;
        void Fill(std::vector<glm::mat4> mvps);
        void Clear() override;
    };

    extern UniformBuffer mvp_buffer;
    void InitUniformBuffers();
    void ClearUniformBuffers();
}
#endif