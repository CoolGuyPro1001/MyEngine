#include "Graphics.h"

#include "GLDebug.h"
#include "Buffers/VertexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Common/Error.h"
#include "Common/Vertex.h"

#include <glm/gtx/transform.hpp>
#include <glm/gtx/projection.hpp>

namespace Graphics
{
    std::vector<uint> g_shader_programs = std::vector<uint>();
    bool g_initialized = false;

    SDL_Window* g_window;
    int g_max_texture_units;
    int g_window_width = 4;
    int g_window_height = 3;

    ///@brief Initializes OpenGL functions
    ///@return True if initialization is successful
    void Initialize()
    {
        GLenum error = glewInit();
        const char* c;
        if(GLEW_OK != error)
            //FatalError(OPENGL_ERROR, "GLEW Failed To Initialize\n%s", 
            c = (const char*) glewGetErrorString(error);
        
        g_initialized = true;
        GLCall(glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &g_max_texture_units));

        GLCall(glEnable(GL_DEPTH_TEST));
        GLCall(glDepthFunc(GL_LESS));
    }

    bool InitWindow(int width, int height, const char* name)
    {
        g_window = SDL_CreateWindow
        (
            name, 
            SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, 
            width, 
            height,
            SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
        );

        if(!g_window)
        {
            return false;
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_CreateContext(g_window);

        SDL_GL_SetSwapInterval(0);
        g_window_width = width;
        g_window_height = height;

        return true;
    }

    void CloseWindow()
    {
        if(g_window)
        {
            SDL_DestroyWindow(g_window);
        }
    }

    ///@brief Adds a shader program from .vshader and .fshader file
    ///@param shader_file_path The full path to the shader file
    void AddShader(const std::string vertex_path, const std::string fragment_path)
    {
        Shader shader = Shader(vertex_path, fragment_path);
        g_shader_programs.push_back(shader.CreateProgram());
    }

    glm::vec3 Vector3GLM(const Vector3 v)
    {
        return glm::vec3(v.x, v.y, v.z);
    }

    glm::mat4 GeneratePerspectiveMatrix(float fov)
    {
        return glm::perspective(glm::radians(fov), (float) g_window_width / (float) g_window_height, 0.1f, 1000.0f);
    }

    glm::mat4 GenerateViewMatrix(Vector3 position, Vector3 looking_at, Vector3 up)
    {
        return glm::lookAt(Vector3GLM(position), Vector3GLM(looking_at), Vector3GLM(up));
    }

    glm::mat4 GetIdentityMatrix()
    {
        return glm::identity<glm::mat4>();
    }

    glm::mat4 GenerateModelMatrix(Vector3 position, Vector3 rotation, Vector3 scale)
    {
        glm::mat4 rotation_matrix =    glm::rotate(rotation.pitch, glm::vec3(1.0f, 0.0f, 0.0f)) * 
                                glm::rotate(rotation.yaw, glm::vec3(0.0f, 1.0f, 0.0f)) * 
                                glm::rotate(rotation.roll, glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 translate_matrix = glm::translate(glm::vec3(position.x, position.y, position.z));
        glm::mat4 scale_matrix = glm::scale(glm::vec3(scale.x, scale.y, scale.z));
        
        glm::mat4 model = translate_matrix * scale_matrix * rotation_matrix;
        return model;
    }

    ///@brief Draws To Screen

    void ClearDrawBuffers()
    {        
        if(!g_initialized) //|| shader_program == NULL_ID)
            return;

        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
    }
    
    void DrawText(std::vector<uint> current_text_textures)
    {
        if(!g_initialized || g_shader_programs[1] == 0)
            return;

        GLCall(glUseProgram(g_shader_programs[1]));

        int texture_index = 0;
        int batch = 1;
        for(VertexBuffer& batch_buffer : batch_2d_buffers)
        {
            if(batch_buffer.GetSize() == 0)
            {
                batch++;
                continue;
            }

            std::vector<int> texture_batch(g_max_texture_units);
            for(int i = 0; i < texture_batch.size(); i++)
                texture_batch[i] = i;

            uint* texture_id = &(current_text_textures[texture_index]);
            int batch_ending = g_max_texture_units * batch + 2;

            while((*texture_id - 2) < batch_ending && texture_index < current_text_textures.size())
            {
                int slot = (*texture_id - 2) % g_max_texture_units;
                GLCall(glActiveTexture(GL_TEXTURE0 + slot));
                GLCall(glBindTexture(GL_TEXTURE_2D, *texture_id));
                texture_index++;
                texture_id++;
            }
            
            int text_uniform = glGetUniformLocation(g_shader_programs[1], "text_textures");
            GLCall(glUniform1iv(text_uniform, texture_batch.size(), &texture_batch[0]));

            batch_buffer.Bind();
            GLCall(glDrawArrays(GL_TRIANGLES, 0, batch_buffer.GetSize() / sizeof(Vertex)));

            batch++;
        }
    }

    bool PrepareDraw()
    {
        if(!g_initialized || g_shader_programs[0] == 0)
            return false;

        buffer3d.Bind();
        GLCall(glUseProgram(g_shader_programs[0]));

        Texture::Use(g_shader_programs[0]);

        return true;
    }

    void Draw(uint model_buffer_size, uint model_instance_amount, uint buffer_offset, uint mvp_index)
    {
        int mvp_index_uniform = glGetUniformLocation(g_shader_programs[0], "mvp_index");

        //Draw Objects
        GLCall(glUniform1i(mvp_index_uniform, mvp_index));
        GLCall(glDrawArraysInstanced(GL_TRIANGLES, buffer_offset / sizeof(Vertex), model_buffer_size / sizeof(Vertex), model_instance_amount));

        //Draw Widgets
        //buffer2d.Bind();
        //GLCall(glUniform1i(object_num_uniform, object_count));
        //GLCall(glDrawArrays(GL_TRIANGLES, 0, buffer2d.GetSize() / sizeof(Vertex)));
    }

    void DrawSkyBox(uint sky_box_buffer_offset, glm::mat4 mvp)
    {
        GLCall(glUseProgram(g_shader_programs[1]));
        Texture::Use(g_shader_programs[1]);

        GLCall(glDepthFunc(GL_LEQUAL));

        int mvp_uniform = glGetUniformLocation(g_shader_programs[1], "mvp");
        GLCall(glUniformMatrix4fv(mvp_uniform, 1, false, &mvp[0][0]));
        GLCall(glDrawArrays(GL_TRIANGLES, sky_box_buffer_offset / sizeof(Vertex), 36));

        GLCall(glDepthFunc(GL_LESS));
    }

    void UpdateGraphics()
    {
        if(g_window)
        {
            SDL_GL_SwapWindow(g_window);
        }
    }
}
