#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../File.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/projection.hpp>

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

    extern GLFWwindow* window;

    uint* BufferId();
    uint* VaoId();

    bool Initialize();
    bool InitWindow(int width, int height, std::string name);
    
    void Draw(std::vector<int> sizes, std::vector<std::vector<Actor>>& total_actors, Camera& camera);

    //unsigned int CompileShader(unsigned int type, const std::string& source);
    //unsigned int CreateShader(const std::string& vertex_shader, const std::string& fragment_shader);
    Shader ParseShader(const std::string& file_path);
    void UseShader(const std::string shader_file_path);

    glm::mat4 TransformationMatrix(Vector3 position, Vector3 rotation, Vector3 scale);
    void InitTransformUniform();
}

#endif