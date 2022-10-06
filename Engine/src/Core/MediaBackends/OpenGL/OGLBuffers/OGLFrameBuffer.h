#ifndef OGLFRAMEBUFFER_H
#define OGLFBMANAGER_H
#define OGLFBMANAGER_H

#include "../OGLBuffer.h"
#include "Core/Media/WindowMedia.h"

struct OGLFrameBuffer : public OGLBuffer
{
    OGLFrameBuffer();
    ~OGLFrameBuffer();

    size_t GetSize();

    void Init();
    void Clear();
    uint Bind();
    void AddData(u8* data, uint data_amount, uint data_bytesize);
    void SetTexture(Unique<MWindow> window);

private:
    uint m_texture;
};
#endif
