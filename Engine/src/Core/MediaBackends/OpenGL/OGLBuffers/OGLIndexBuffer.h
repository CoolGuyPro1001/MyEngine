#ifndef OGLINDEXBUFFER_H
#define OGLINDEXBUFFER_H

#include "../OGLBuffer.h"

struct OGLIndexBuffer : public OGLBuffer
{
    OGLIndexBuffer(uint*& id_ptr, bool mirror_data);
    OGLIndexBuffer& operator=(OGLIndexBuffer&& other);
};
#endif
