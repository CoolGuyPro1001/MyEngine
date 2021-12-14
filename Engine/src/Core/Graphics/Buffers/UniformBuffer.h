#ifndef UNIFORM_BUFFER_H
#define UNIFORM_BUFFER_H

#include "Core/Graphics/Buffer.h"

namespace Graphics
{
    struct UniformBuffer : public Buffer
    {
        UniformBuffer& operator=(UniformBuffer&& other);

        void Init() override;
        void AddData(u8* data, uint data_amount, uint data_bytesize) override;
        void Clear() override;
    };

    extern UniformBuffer mvp_buffer;
    void InitUniformBuffers();
    void ClearUniformBuffers();
}
#endif
