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

    uint transfrom_uniform_id = NULL_ID;
    uint shader_program = NULL_ID;
    bool initialized = false;
    Camera camera = Camera();

    uint buffer_id = NULL_ID;
    uint vao_id = NULL_ID;
    std::vector<uint> render_counts = std::vector<uint>();
    std::vector<uint> object_sizes = std::vector<uint>();
    std::vector<glm::mat4> model_matrices = std::vector<glm::mat4>();
    
    uint* BufferId()
    {
        return &buffer_id;
    }

    uint* VaoId()
    {
        return &vao_id;
    }

    std::vector<uint>& RenderCounts()
    {
        return render_counts;
    }

    std::vector<uint>& ObjectSizes()
    {
        return object_sizes;
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

        GLuint VertexArrayID;
        GLCall(glGenVertexArrays(1, &VertexArrayID));
        GLCall(glBindVertexArray(VertexArrayID));
        initialized = true;

        GLCall(glEnable(GL_DEPTH_TEST));
        GLCall(glDepthFunc(GL_LESS));

        return true;
    }

    void InitTransformUniform()
    {
        if(shader_program == NULL_ID)
        {
            std::cout << "Shader not set\n";
        }
        GLCallAssign(glGetUniformLocation(shader_program, "mvp"), transfrom_uniform_id);
    }

    ///@brief Uses the shader program from .shader file
    ///@param shader_file_path The full path to the shader file
    void UseShader(const std::string shader_file_path)
    {
        Shader shader = ParseShader(shader_file_path);
        shader_program = shader.CreateProgram();
        GLCall(glUseProgram(shader_program));
    }

    void AddModelMatrix(Vector3* position, Vector3* rotation, Vector3* scale)
    {
        glm::mat4 rotation_matrix =    glm::rotate(rotation->x, glm::vec3(1.0f, 0.0f, 0.0f)) * 
                                glm::rotate(rotation->y, glm::vec3(0.0f, 1.0f, 0.0f)) * 
                                glm::rotate(rotation->z, glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 translate_matrix = glm::translate(glm::vec3(position->x, position->y, position->z));
        glm::mat4 scale_matrix = glm::scale(glm::vec3(scale->x, scale->y, scale->z));
        
        model_matrices.push_back(translate_matrix * scale_matrix * rotation_matrix);
    }

    ///@brief Draws To Screen
    void Draw(Camera camera)
    
    {
        if(!initialized || shader_program == NULL_ID || transfrom_uniform_id == NULL_ID)
        {
            return;
        }

        

        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        //SetMVP(0);


        GLCall(glBindVertexArray(vao_id))
        uint draw_pointer = 0;
        size_t matrix_index = 0;
        for(int i = 0; i < render_counts.size(); i++)
        {
            int i1 = 0;
            while(i1 < render_counts[i])
            {
                glm::vec3 look = glm::vec3(camera.looking_at.x, camera.looking_at.y, camera.looking_at.z);
                glm::mat4 projection = glm::perspective(glm::radians(90.0f), 8.0f / 5.0f, 0.1f, 100.0f);
                glm::mat4 view = glm::lookAt(camera.position, look, glm::vec3(0, 1, 0));

                glm::mat4 mvp = projection * view * model_matrices[matrix_index];
                GLCall(glUniformMatrix4fv(transfrom_uniform_id, 1, GL_FALSE, &(mvp[0][0])));
                GLCall(glDrawArrays(GL_TRIANGLES, draw_pointer, object_sizes[i]));
                i1++;
                matrix_index++;
            }
            draw_pointer += object_sizes[i];
        }
    }
}