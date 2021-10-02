#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "Buffer.h"

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

    private:
        uint texture;
    };
}
#endif