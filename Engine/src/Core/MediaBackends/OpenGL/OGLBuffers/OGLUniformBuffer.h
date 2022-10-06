#ifndef OGLUNIFORMBUFFER_H
#define OGLUNIFORMBUFFER_H

#include "../OGLBuffer.h"
#include "../OGLShader.h"

struct OGLUniformBuffer : public OGLBuffer
{
    OGLUniformBuffer(uint*& id_ptr, bool mirror_data);
    OGLUniformBuffer& operator=(OGLUniformBuffer&& other);
};
#endif
