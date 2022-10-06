#ifndef OGLVERTEXBUFFER_H
#define OGLVERTEXBUFFER_H

#include "../OGLBuffer.h"

struct OGLVertexBuffer : public OGLBuffer
{
public:
    OGLVertexBuffer(uint*& id_tpr, uint*& vao_ptr, bool mirror_data);
    ~OGLVertexBuffer();

    //Copy = Bad
    OGLVertexBuffer(const OGLVertexBuffer&) = delete;
    OGLVertexBuffer &operator=(const OGLVertexBuffer&) = delete;

    //Move = Good
    OGLVertexBuffer(OGLVertexBuffer&& other);
    OGLVertexBuffer& operator=(OGLVertexBuffer&& other);

    void Init(size_t size = 0);
    void Fill(u8* data, size_t size);
    void Destroy();
private:
    void Format();
    uint m_vao;
};

#endif
