#include "OGLFrameBuffer.h"

#include "../OGLDebug.h"

void OGLFrameBuffer::Init()
{
    if(m_id != 0)
        return;

    GLCall(glGenFramebuffers(1, &m_id));

    GLCall(glGenTextures(1, &m_texture));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_texture));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
}

void OGLFrameBuffer::Clear()
{
    //TODO Clear Framebuffer contents
}

uint OGLFrameBuffer::Bind()
{
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_id));
    return GL_FRAMEBUFFER;
}

void OGLFrameBuffer::AddData(u8* data, uint data_amount, uint data_bytesize)
{
    //TODO Something Here That Fills FrameBuffer
}

void OGLFrameBuffer::SetTexture(Unique<MWindow> window)
{
    GLCall(glBindTexture(GL_TEXTURE_2D, m_texture));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, window->Width(), window->Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL));
}
