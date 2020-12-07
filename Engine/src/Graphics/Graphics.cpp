#include "Graphics.h"

#include "GLDebug.h"
#include "File.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/projection.hpp>

#include <GLFW/glfw3.h>

#define NULL_ID UINT_MAX
namespace Graphics
{
    //static std::vector<VertexBuffer*> vertex_buffers = std::vector<VertexBuffer*>();
    //static std::vector<IndexBuffer*> index_buffers = std::vector<IndexBuffer*>();


    ///@brief Parses a .shader file into a Shader object
    ///@param file_path The full file path to the shader file
    ///@return Shader Object

    uint transfrom_uniform_id = NULL_ID;
    uint shader_program = NULL_ID;
    bool initialized = false;

    uint buffer_id = NULL_ID;
    uint vao_id = NULL_ID;

    SDL_Window* window;

    static void error_callback(int error, const char* description)
    {
        fprintf(stderr, "Error: %s\n", description);
    }
    
    uint* BufferId()
    {
        return &buffer_id;
    }

    uint* VaoId()
    {
        return &vao_id;
    }

    Shader ParseShader(const std::string& file_path)
    {
        enum ShaderType
        {
            NONE= -1, VERTEX = 0, FRAGMENT = 1
        };

        const std::string shader_source = File::ReadFile(file_path);
        Shader shader_source_parsed;
        ShaderType current_type = ShaderType::NONE;

        int begin = 0; //The beginning of substring
        int end = 0; //The end of substring current marker
        while(true)
        {
            //Move end to closest #shader
            end = shader_source.find("#shader", end);
            if(end == std::string::npos)
            {
                end = shader_source.length() - 1;
            }

            //Set ShaderSource based on previous block of code
            switch(current_type)
            {
                case ShaderType::VERTEX:
                    shader_source_parsed.vertex_source = shader_source.substr(begin, (end - begin));
                    break;
                case ShaderType::FRAGMENT:
                    shader_source_parsed.fragment_source = shader_source.substr(begin, (end - begin));
                    break;
                default:
                    break;
            }

            //Break when end reaches the end of shader source code text
            if(end == shader_source.length() - 1)
                break;

            //Find out what current block of code is for
            begin = end;
            if(shader_source.substr((end + 8), 6) == "vertex")
            {
                current_type = ShaderType::VERTEX;
                begin += 15;
            }
            else if(shader_source.substr((end + 8), 8) == "fragment")
            {
                current_type = ShaderType::FRAGMENT;
                begin += 17;
            }

            end++;
        }

        return shader_source_parsed;
    }

    ///@brief Initializes OpenGL functions
    ///@return True if initialization is successful
    bool Initialize()
    {
        GLenum error = glewInit();
        if(GLEW_OK != error)
        {
            std::cout << "ERROR: GLEW failed to intialize\n" << (const char*)glewGetErrorString(error);
            return false;
        }
        
        
        glGenVertexArrays(1, &vao_id);
        glBindVertexArray(vao_id);
        
        initialized = true;

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        return true;
    }

    bool InitWindow(int width, int height, const char* name)
    {
        window = SDL_CreateWindow
        (
            name, 
            SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, 
            width, 
            height,
            SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
        );

        if(!window)
        {
            return false;
        }

        SDL_GL_SetSwapInterval(1);
        SDL_GL_CreateContext(window);
        return true;
    }

    bool WindowClosed()
    {
        if(glfwWindowShouldClose(window))
            return true;
        return false;
    }

    void EndWindow()
    {
        SDL_DestroyWindow(window);
    }

    ///@brief Uses the shader program from .shader file
    ///@param shader_file_path The full path to the shader file
    void UseShader(const std::string shader_file_path)
    {
        Shader shader = ParseShader(shader_file_path);
        shader_program = shader.CreateProgram();
        glUseProgram(shader_program);
    }

    glm::mat4 TransformationMatrix(Vector3 position, Vector3 rotation, Vector3 scale)
    {
        glm::mat4 rotation_matrix =    glm::rotate(rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)) * 
                                glm::rotate(rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) * 
                                glm::rotate(rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 translate_matrix = glm::translate(glm::vec3(position.x, position.y, position.z));
        glm::mat4 scale_matrix = glm::scale(glm::vec3(scale.x, scale.y, scale.z));
        
        return translate_matrix * scale_matrix * rotation_matrix;
    }

    ///@brief Draws To Screen
    void Draw(std::vector<int> sizes, std::vector<std::vector<Actor>>& total_actors, Camera& camera)
    {
        if(!initialized) //|| shader_program == NULL_ID)
        {
            return;
        }

        //Setup
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(vao_id);

        //Create Matrix For 3D View
        glm::vec3 look = glm::vec3(camera.looking_at.x, camera.looking_at.y, camera.looking_at.z);
        glm::mat4 projection = glm::perspective(glm::radians(90.0f), 8.0f / 5.0f, 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(camera.position, look, glm::vec3(0, 1, 0));
        glm::mat4 to_3d = projection * view;
        
        //Assign Shader 3D Matrix Uniform
        uint world_uniform_id = glGetUniformLocation(shader_program, "to_3d");
        glUniformMatrix4fv(world_uniform_id, 1, GL_FALSE, &(to_3d[0][0]));

        int buffer_size = 0;
        glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &buffer_size);

        //Backup data from vertex buffer. Changing the buffer data deletes everything!
        float stored_data[buffer_size / sizeof(float)];
        glGetBufferSubData(GL_ARRAY_BUFFER, 0, buffer_size, stored_data);

        //Draw Actors
        int offset = 0;
        for(int model = 0; model < total_actors.size(); model++)
        {
            //std::vector<glm::mat4> transforms = std::vector<glm::mat4>();
            //for(Actor actor : total_actors[model])
            //{
           //     transforms.push_back(TransformationMatrix(actor.position, actor.rotation, actor.scale));
            //}

            Actor actor = total_actors[model][0];
            glm::mat4 transforms = TransformationMatrix(actor.position, actor.rotation, actor.scale);

            uint transform_uniform_id= glGetUniformLocation(shader_program, "transformations");
            glUniformMatrix4fv(transform_uniform_id, 1, GL_FALSE, &(transforms[0][0]));
            
            glDrawArraysInstanced(GL_TRIANGLES, offset, (offset + sizes[model]) / sizeof(Vertex), total_actors[model].size());

            offset += sizes[model];
        }

        SDL_GL_SwapWindow(window);
    }
}