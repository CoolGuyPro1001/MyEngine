#ifndef OGLGRAPHICS2D_H
#define OGLGRAPHICS2D_H

#include "OGLShader.h"
#include "OGLTextureManager.h"

#include "Core/Media/Graphics2DMedia.h"
#include "Common/Delegate.h"

struct Window;
struct EWindowResized;

template<typename T, std::size_t R, std::size_t C>
struct Matrix;

class OGLRenderer2D : MRenderer2D
{
public:
    virtual void Init() = 0;

    virtual void ClearDrawBuffers() = 0;
    virtual bool PrepareDraw() = 0;
    virtual void Draw() = 0;
    virtual void SwapBuffers() = 0;

    virtual void AddShader(const std::string vertex_path, const std::string fragment_path) = 0;
    virtual void SetMVPBlock() = 0;
    virtual void UpdateViewPort(EWindowResized* e) = 0;

    //Public Variables Because FREEEEEEEEEEEEEEEEEEEEEDOM!!!!!!!!!!!!!!!!!
    Shared<GraphicsMath> Math;
    //Shared<GraphicsTextureManager> TextureManager;

    Shared<GraphicsBuffer> widget_buffer;

protected:
    bool m_initialized;
};
#endif
