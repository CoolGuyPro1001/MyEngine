#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <GL/glew.h>

#include "../File.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/projection.hpp>

#include "Camera.h"

namespace Graphics
{
    extern glm::mat4 mvp;
    extern uint transfrom_uniform_id;
    extern uint shader_program;
    extern bool initialized;
    extern Camera camera;
    extern std::vector<glm::mat4> model_matrices;

    //Rendering Information
    extern uint buffer_id;
    extern uint vao_id;
    extern std::vector<uint> render_counts;
    extern std::vector<uint> object_sizes;
    extern std::vector<glm::mat4> model_matrices;

    uint* BufferId();
    uint* VaoId();
    std::vector<uint>& RenderCounts();
    std::vector<uint>& ObjectSizes();

    bool Initialize();
    void Draw();
    //unsigned int CompileShader(unsigned int type, const std::string& source);
    //unsigned int CreateShader(const std::string& vertex_shader, const std::string& fragment_shader);
    Shader ParseShader(const std::string& file_path);
    void UseShader(const std::string shader_file_path);

    void AddModelMatrix(Vector3* position, Vector3* rotation, Vector3* scale);
    void InitTransformUniform();
}

#endif