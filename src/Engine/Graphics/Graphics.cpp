#include "Graphics.h"
#include "GLDebug.h"

#define NULL_ID -1
namespace Graphics
{
    //static std::vector<VertexBuffer*> vertex_buffers = std::vector<VertexBuffer*>();
    //static std::vector<IndexBuffer*> index_buffers = std::vector<IndexBuffer*>();


    ///@brief Parses a .shader file into a Shader object
    ///@param file_path The full file path to the shader file
    ///@return Shader Object

    std::vector<glm::mat4> model_matrices = std::vector<glm::mat4>();
    unsigned int vertex_array_id;
    glm::mat4 mvp;
    unsigned int matrix_id;
    unsigned int shader_program = NULL_ID;
    bool initialized = false;
    Camera camera = Camera();
    
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

        GLuint VertexArrayID;
        GLCall(glGenVertexArrays(1, &VertexArrayID));
        GLCall(glBindVertexArray(VertexArrayID));
        initialized = true;

        GLCall(glEnable(GL_DEPTH_TEST));
        GLCall(glDepthFunc(GL_LESS));

        return true;
    }

    void InitMVP()
    {
        if(shader_program == NULL_ID)
        {
            std::cout << "Shader not set\n";
        }
        matrix_id = glGetUniformLocation(shader_program, "MVP");
    }

    ///@brief Uses the shader program from .shader file
    ///@param shader_file_path The full path to the shader file
    void UseShader(const std::string shader_file_path)
    {
        Shader shader = ParseShader(shader_file_path);
        shader_program = shader.CreateProgram();
        GLCall(glUseProgram(shader_program));
    }

    void SetMVP(int model_index)
    {
        glm::vec3 look = glm::vec3(camera.looking_at.x, camera.looking_at.y, camera.looking_at.z);
        glm::mat4 projection = glm::perspective(glm::radians(90.0f), 8.0f / 5.0f, 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(camera.position, look, glm::vec3(0, 1, 0));
        glm::mat4 model = model_matrices[model_index];
        mvp = projection * view * model;  
    }

    ///@brief Draws To Screen
    void Draw(uint& buffer_id)
    {
        if(!initialized || shader_program == NULL_ID)
        {
            return;
        }

        
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        SetMVP(0);
        GLCall(glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &mvp[0][0]));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer_id));

        int size;
        GLCall(glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size));
        GLCall(glDrawArrays(GL_TRIANGLES, 0, size));
    }
}