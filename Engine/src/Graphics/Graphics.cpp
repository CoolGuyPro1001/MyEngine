#include "Graphics.h"

#include "GLDebug.h"
#include "File.h"
#include "Texture.h"
#include "Common/Error.h"

#include <glm/gtx/transform.hpp>
#include <glm/gtx/projection.hpp>

namespace Graphics
{
    //static std::vector<VertexBuffer*> vertex_buffers = std::vector<VertexBuffer*>();
    //static std::vector<IndexBuffer*> index_buffers = std::vector<IndexBuffer*>();


    ///@brief Parses a .shader file into a Shader object
    ///@param file_path The full file path to the shader file
    ///@return Shader Object

    std::vector<uint> g_shader_programs = std::vector<uint>();
    bool g_initialized = false;

    SDL_Window* g_window;
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

        //SDL_GL_SetSwapInterval(1);
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

    glm::mat4 Generate3DMatrix(float fov, Vector3 position, Vector3 looking_at, Vector3 up)
    {
        glm::mat4 projection = glm::perspective(glm::radians(fov), (float) g_window_width / (float) g_window_height, 0.1f, 1000.0f);
        glm::mat4 view = glm::lookAt(Vector3GLM(position), Vector3GLM(looking_at), Vector3GLM(up));
        return projection * view;
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
    
    void Draw2D(std::vector<uint> textures_now)
    {
        if(!g_initialized || g_shader_programs[0] == 0)
            return;
        
        GLCall(glUseProgram(g_shader_programs[0]));

        int game_uniform_id = glGetUniformLocation(g_shader_programs[0], "render_game_textures");
        GLCall(glUniform1i(game_uniform_id, true));

        //Draw Widgets
        Texture::Use(g_shader_programs[0]);

        buffer2d.Bind();
        GLCall(glDrawArrays(GL_TRIANGLES, 0, buffer2d.GetSize() / sizeof(Vertex)));

        GLCall(glUniform1i(game_uniform_id, false));

        int tex_index = 0;
        int batch = 1;
        for(VertexBuffer& batch_buffer : batch_2d_buffers)
        {
            if(batch_buffer.GetSize() == 0)
            {
                batch++;
                continue;
            }

            std::array<int, 32> texture_batch;
            for(int i = 0; i < texture_batch.size(); i++)
                texture_batch[i] = i;

            uint* tex_id = &(textures_now[tex_index]);
            while(*tex_id < 32 * batch + 2 && tex_index < textures_now.size())
            {
                int slot = (*tex_id - 2) % 32;
                GLCall(glActiveTexture(GL_TEXTURE0 + slot));
                GLCall(glBindTexture(GL_TEXTURE_2D, *tex_id));
                tex_index++;
                tex_id++;
            }
            
            int text_uniform = glGetUniformLocation(g_shader_programs[0], "text_textures");
            GLCall(glUniform1iv(text_uniform, texture_batch.size(), &texture_batch[0]));

            batch_buffer.Bind();
            GLCall(glDrawArrays(GL_TRIANGLES, 0, batch_buffer.GetSize() / sizeof(Vertex)));

            batch++;
        }
    }

    void Draw3D(std::vector<size_t> sizes, std::vector<size_t> instance_counts)
    {
        if(!g_initialized || g_shader_programs[1] == 0)
            return;

        if(sizes.size() != instance_counts.size())
            return;

        buffer3d.Bind();
        GLCall(glUseProgram(g_shader_programs[1]));

        Texture::Use(g_shader_programs[1]);

        int object_count = 0;
        int object_num_uniform = glGetUniformLocation(g_shader_programs[1], "object_num");

        //Draw Objects
        int offset = 0;
        for(int i = 0; i < sizes.size(); i++)
        {
            GLCall(glUniform1i(object_num_uniform, object_count));
            GLCall(glDrawArraysInstanced(GL_TRIANGLES, offset, sizes[i], instance_counts[i]));
            object_count += instance_counts[i];
            offset += sizes[i];
        }
    }

    void UpdateGraphics()
    {
        if(g_window)
        {
            SDL_GL_SwapWindow(g_window);
        }
    }
}