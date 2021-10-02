#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "Graphics.h"
#include "Buffer.h"

#include "Common/Vertex.h"

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
        void AddData(std::vector<Vertex>& vertices);
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