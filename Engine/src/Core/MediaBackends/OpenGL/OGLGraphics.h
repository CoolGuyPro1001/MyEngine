#ifndef OGLGRAPHICS_H
#define OGLGRAPHICS_H

#include "OGLShader.h"
#include "OGLTextureManager.h"

#include "Core/Media/GraphicsMedia.h"
#include "Common/Delegate.h"

struct MWindow;
struct EWindowResized;

class OGLRenderer : public MRenderer
{
public:
    #undef DrawText

    OGLRenderer(MWindow& window);

    void Init();

    void ClearDrawBuffers();
    bool PrepareDraw();
    void DrawText(std::vector<uint> current_text_textures);
    void Draw(uint indices_count, uint model_instance_amount, uint index_offset, uint mvp_index);
    void DrawSkyBox(uint skybox_offset, uint skybox_mvp_index);
    void SwapBuffers();

    void AddShader(const std::string vertex_path, const std::string fragment_path);
    void SetUniforms();
    void UpdateViewPort(EWindowResized* e);

    void SetAmbientFactor(float factor);
    void SetLightSourcePosition(Vector3 position);
    void SetLightColor(Color color);
    void SetCameraPosition(Vector3 position);
    void SetSpecularFactor(float factor);

private:
    Delegate<void> m_swapbuffers_func;
    int m_max_texture_units;
    uint m_texture_id;

    std::vector<uint> m_shader_programs;

    uint* m_instance_id_ptr;
    uint* m_index_id_ptr;
    uint* m_instance_vao_ptr;
    uint* m_model_id_ptr;
    uint* m_mvp_id_ptr;

    uint m_model_block_index;
    uint m_mvp_block_index;
    uint m_mvp_index_uniform;
};
#endif

