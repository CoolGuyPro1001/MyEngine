#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Graphics/Shader.h"
#include "Graphics/VertexBuffer.h"
#include "Common/Units.h"
#include "Camera.h"
#include "Actor.h"

namespace Graphics
{
    extern uint transfrom_uniform_id;
    extern uint shader_program;
    extern bool initialized;

    //Rendering Information
    extern uint buffer_id;
    extern uint vao_id;

    extern SDL_Window* window;
    extern int window_width;
    extern int window_height;

    uint* BufferId();
    uint* VaoId();

    bool Initialize();
    bool InitWindow(int width, int height, const char* name);

    bool WindowClosed();
    void CloseWindow();
    
    void Draw(std::vector<std::vector<Shared<Actor>>>& total_actors, Shared<Camera> camera, Shared<Model> sky_block, Shared<Model> terrain);

    Shader ParseShader(const std::string& file_path);
    void UseShader(const std::string shader_file_path);
    
    glm::vec3 Vector3GLM(const Vector3 v);
    glm::mat4 TransformationMatrix(Vector3 position, Vector3 rotation, Vector3 scale);
}

#endif