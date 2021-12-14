#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "Core/Graphics/Buffer.h"

namespace Graphics
{
    struct VertexBuffer : public Buffer
    {
        VertexBuffer();
        ~VertexBuffer();

        VertexBuffer(VertexBuffer&& other);
        VertexBuffer& operator=(VertexBuffer&& other);

        virtual void Format();
        uint GetVAO();
        void AddData(u8* vertices, uint vertex_amount, uint vertex_size) override;
        void Init() override;
        void Bind() override;
        void Release() override;

    protected:
        uint vao;
    };

    extern VertexBuffer buffer2d;
    extern VertexBuffer buffer3d;
    extern std::vector<VertexBuffer> batch_2d_buffers;

    void CreateBatchBuffers();
    void InitVertexBuffers();
    void ClearVertexBuffers();
    void FormatVertexBuffers();
}

#endif
