#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Graphics/Shader.h"
#include "Graphics/VertexBuffer.h"
#include "Common/Vector3.h"
#include "Camera.h"
#include "Actor.h"
#include "GUI/Widget.h"

#include <glm/glm.hpp>

namespace Graphics
{
    extern std::vector<uint> g_shader_programs;
    extern bool g_initialized;

    extern SDL_Window* g_window;
    extern int g_window_width;
    extern int g_window_height;

    void Initialize();
    bool InitWindow(int width, int height, const char* name);

    bool WindowClosed();
    void CloseWindow();
    
    void ClearDrawBuffers();
    void Draw2D(std::vector<uint> textures_now);
    void Draw3D(std::vector<size_t> sizes, std::vector<size_t> instance_counts);
    void UpdateGraphics();

    void AddShader(const std::string vertex_path, const std::string fragment_path);
    
    glm::vec3 Vector3GLM(const Vector3 v);
    glm::mat4 Generate3DMatrix(float fov, Vector3 position, Vector3 looking_at, Vector3 up);
    glm::mat4 GenerateModelMatrix(Vector3 position, Vector3 rotation, Vector3 scale);

    glm::mat4 TransformationMatrix(Vector3 position, Vector3 rotation, Vector3 scale);
}

#endif