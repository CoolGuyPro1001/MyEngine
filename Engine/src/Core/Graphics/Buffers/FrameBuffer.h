#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "Core/Graphics/Buffer.h"

namespace Graphics
{
    struct FrameBuffer : public Buffer
    {
        FrameBuffer();
        ~FrameBuffer();

        size_t GetSize();

        void Init() override;
        void Clear();
        void Bind() override;
        void AddData(u8* data, uint data_amount, uint data_bytesize) override;

    private:
        uint texture;
    };
}
#endif
