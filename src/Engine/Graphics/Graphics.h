#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <GL/glew.h>
#include <vector>
#include <iostream>
#include <memory>

#include "../File.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"

namespace Graphics
{
    extern std::vector<VertexBuffer*> vbos;
    extern unsigned int vertex_array_id;
    extern glm::mat4 mvp;
    extern unsigned int matrix_id;
    extern unsigned int shader_program;
    extern bool initialized;
    extern Camera camera;
    extern std::vector<glm::mat4> model_matrices;

    bool Initialize();
    void Draw();
    //unsigned int CompileShader(unsigned int type, const std::string& source);
    //unsigned int CreateShader(const std::string& vertex_shader, const std::string& fragment_shader);
    Shader ParseShader(const std::string& file_path);
    void UseShader(const std::string shader_file_path);

    void AddBuffers(std::vector<VertexBuffer*>);
    void AddBuffer(VertexBuffer*);

    void MoveCameraX(float dis);
    void MoveCameraY(float dis);
    void MoveCameraZ(float dis);
    void PrintCameraLocation();
    void SetMVP(int model_matrix_index);
    void InitMVP();
}

#endif