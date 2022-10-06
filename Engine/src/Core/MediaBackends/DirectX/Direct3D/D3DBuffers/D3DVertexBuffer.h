#ifndef D3DVERTEXBUFFER_H
#define D3DVERTEXBUFFER_H

#include "Core/Media/Graphics/Buffers/VertexBuffer.h"

class D3DVertexBuffer : public VertexBuffer
{
public:
    D3DVertexBuffer();
    ~D3DVertexBuffer();

    void Init();

private:
    struct m_VertexFormat
    {
        XMFLOAT3 position;
        XMUBYTE4 color;
        XMFLOAT3 tex;
    };
};
#endif
