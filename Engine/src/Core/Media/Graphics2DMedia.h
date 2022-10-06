#ifndef GRAPHICS2D_H
#define GRAPHICS2D_H

class Renderer2D
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
