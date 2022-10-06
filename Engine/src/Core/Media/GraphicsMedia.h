#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Graphics/GraphicsBuffer.h"
#include "Graphics/Texture.h"

#include "Common/Vector3.h"
#include "Common/Matrix.h"

struct EWindowResized;

class GraphicsMath
{
public:
    virtual Mat4 GenerateModelMatrix(Vector3 position, Vector3 rotation, Vector3 scale) = 0;
    virtual Mat4 GenerateViewMatrix(Vector3 position, Vector3 looking_at, Vector3 up) = 0;
    virtual Mat4 GeneratePerspectiveMatrix(float fov, uint window_width, uint window_height) = 0;
    virtual Mat4 GenerateMVP(Mat4 model, Mat4 view, Mat4 projection) = 0;

    virtual Mat4 IdentityMatrix() = 0;
    virtual void MVPToSkyBoxMVP(Mat4& mvp) = 0;
    //virtual Matrix<float, 4, 4> TransformationMatrix(Vector3 position, Vector3 rotation, Vector3 scale) = 0;

};

class MRenderer
{
public:
    #undef DrawText

    virtual void Init() = 0;

    virtual void ClearDrawBuffers() = 0;
    virtual bool PrepareDraw() = 0;
    virtual void Draw(uint model_buffer_size, uint model_instance_amount, uint buffer_offset, uint mvp_index) = 0;
    virtual void DrawSkyBox(uint skybox_offset, uint skybox_mvp_index) = 0;
    virtual void SwapBuffers() = 0;

    virtual void AddShader(const std::string vertex_path, const std::string fragment_path) = 0;
    virtual void SetMVPBlock() = 0;
    virtual void UpdateViewPort(EWindowResized* e) = 0;

    //Public Variables Because FREEEEEEEEEEEEEEEEEEEEEDOM!!!!!!!!!!!!!!!!!
    Shared<GraphicsMath> Math;
    Shared<GraphicsTextureManager> TextureManager;

    Shared<GraphicsBuffer> vb_instance;
    Shared<GraphicsBuffer> ub_mvp;

protected:
    bool m_initialized;
};

#endif
