#ifndef GRAPHICS_H
#define GRAPHICS_H

struct Vector3;
namespace Graphics
{
    #undef DrawText

    extern std::vector<uint> g_shader_programs;
    extern bool g_initialized;

    extern SDL_Window* g_window;
    extern int g_window_width;
    extern int g_window_height;
    extern int g_max_texture_units;

    void Initialize();
    bool InitWindow(int width, int height, const char* name);

    bool WindowClosed();
    void CloseWindow();
    
    void ClearDrawBuffers();
    bool PrepareDraw();
    void DrawText(std::vector<uint> current_text_textures);
    void Draw(uint model_buffer_size, uint model_instance_amount, uint buffer_offset, uint mvp_index);
    void DrawSkyBox(uint sky_box_buffer_offset, glm::mat4 mvp);
    void UpdateGraphics();

    void AddShader(const std::string vertex_path, const std::string fragment_path);
    
    glm::vec3 Vector3GLM(const Vector3 v);
    glm::mat4 GeneratePerspectiveMatrix(float fov);
    glm::mat4 GenerateViewMatrix(Vector3 position, Vector3 looking_at, Vector3 up);
    glm::mat4 GetIdentityMatrix();
    glm::mat4 GenerateModelMatrix(Vector3 position, Vector3 rotation, Vector3 scale);

    glm::mat4 TransformationMatrix(Vector3 position, Vector3 rotation, Vector3 scale);
}

#endif
