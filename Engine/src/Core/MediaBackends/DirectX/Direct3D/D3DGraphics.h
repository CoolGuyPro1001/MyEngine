#ifndef D3DGRAPHICS_H
#define D3DGRAPHICS_H

#include "D3DShader.h"

#include "Core/Media/GraphicsMedia.h"

struct Window;

template<typename T, std::size_t R, std::size_t C>
struct Matrix;

class D3DRenderer : public MRenderer
{
public:
    D3DRenderer();

    void Init();

    void ClearDrawBuffers();
    bool PrepareDraw();
    void DrawText(std::vector<uint> current_text_textures);
    void Draw(uint model_buffer_size, uint model_instance_amount, uint buffer_offset, uint mvp_index);
    void DrawSkyBox(uint skybox_offset, uint skybox_mvp_index);
    void SwapBuffers();

    void AddShader(const std::string vertex_path, const std::string fragment_path);
    void SetMVPBlock();

    //Public Variables Because FREEEEEEEEEEEEEEEEEEEEEDOM!!!!!!!!!!!!!!!!!
    std::vector<Shader> shaders;

private:
    ComPtr<ID3D11Device> m_device;
    ComPtr<IDXGISwapChain> m_swap_chain;
    ComPtr<ID3D11DeviceContext> m_device_context;
    ComPtr<ID3D11Texture2D> m_back_buffer;
    ComPtr<ID3D11RenderTargetView> m_render_target;
}
#endif
