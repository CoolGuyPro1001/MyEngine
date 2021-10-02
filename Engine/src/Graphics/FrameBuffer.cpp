#include "FrameBuffer.h"

#include "GLDebug.h"
#include "Graphics.h"

namespace Graphics
{
    void FrameBuffer::Init()
    {
        if(id != 0)
            return;

        GLCall(glGenFramebuffers(1, &id));
        
        GLCall(glGenTextures(1, &texture));
        GLCall(glBindTexture(GL_TEXTURE_2D, texture));

        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, g_window_width, g_window_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));  
    }

    void FrameBuffer::Bind()
    {
        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, id));
    }
}