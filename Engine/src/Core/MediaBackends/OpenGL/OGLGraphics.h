#ifndef OGLGRAPHICS_H
#define OGLGRAPHICS_H

#include "OGLShader.h"
#include "OGLTextureManager.h"

#include "Core/Media/GraphicsMedia.h"
#include "Common/Delegate.h"

struct MWindow;
struct EWindowResized;

template<typename T, std::size_t R, std::size_t C>
struct Matrix;

class OGLRenderer : public MRenderer
{
public:
    #undef DrawText

    OGLRenderer(MWindow& window);

    void Init();

    void ClearDrawBuffers();
    bool PrepareDraw();
    void DrawText(std::vector<uint> current_text_textures);
    void Draw(uint model_buffer_size, uint model_instance_amount, uint buffer_offset, uint mvp_index);
    void DrawSkyBox(uint skybox_offset, uint skybox_mvp_index);
    void SwapBuffers();

    void AddShader(const std::string vertex_path, const std::string fragment_path);
    void SetMVPBlock();
    void UpdateViewPort(EWindowResized* e);

private:
    Delegate<void> m_swapbuffers_func;
    int m_max_texture_units;
    uint m_texture_id;

    std::vector<uint> m_shader_programs;

    uint* m_instance_id_ptr;
    uint* m_instance_vao_ptr;
    uint* m_mvp_id_ptr;

    uint m_mvp_block_index;
    uint m_mvp_index_uniform;
};
#endif

