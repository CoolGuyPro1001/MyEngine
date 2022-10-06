#ifndef OGLBUFFER_H
#define OGLBUFFER_H

#include "Core/Media/Graphics/GraphicsBuffer.h"

struct OGLBuffer : public GraphicsBuffer
{
    OGLBuffer(uint*& id_ptr, bool mirror_data);
    ~OGLBuffer();

    //Copy = Bad
    OGLBuffer(const OGLBuffer&) = delete;
    OGLBuffer &operator=(const OGLBuffer&) = delete;

    //Move = Good
    OGLBuffer(OGLBuffer&& other);
    OGLBuffer& operator=(OGLBuffer&& other);

    virtual void Init(size_t size = 0);
    virtual void Destroy();
    virtual void Fill(u8* data, size_t size);
    virtual void Insert(u8* data, size_t size);

protected:
    uint m_id;
    uint m_target;
    uint m_usage;
    uint AddBufferData(u8* data, size_t size, uint target, uint usage); //Used For Insert()
};
#endif
