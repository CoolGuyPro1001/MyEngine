#ifndef D3DUNIFORMBUFFER_H
#define D3DUNIFORMBUFFER_H

#include "Core/Media/Graphics/Buffers/UniformBuffer.h"

class D3DUniformBuffer : public UniformBuffer
{
public:
    void InitBuffer(uint ub_id);
    void ClearBuffer(uint ub_id);
    void AddDataToBuffer(uint ub_id, u8* data, uint data_amount, uint data_bytesize);

    void InitUniformBuffers();
    void ClearUniformBuffers();
};
#endif
