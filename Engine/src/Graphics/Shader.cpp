#include "Shader.h"
#include "GLDebug.h"
#include "Core/Log.h"

#include "File.h"

namespace Graphics
{
    Shader::Shader() :
        vertex_source(""),
        fragment_source("")
    {}

    Shader::Shader(std::string v_source, std::string f_source) :
        vertex_source(v_source),
        fragment_source(f_source)
    {}

    ///@brief Compiles The Shader Source
    ///@param type The Type Of Shader To Compile To. GL_VERTEX_SHADER Or GL_FRAGMENT_SHADER
    ///@return The ID Of Vertex/Fragment Shader Program
    unsigned int Shader::Compile(unsigned int type)
    {
        std::string source = (type == GL_VERTEX_SHADER) ? vertex_source : fragment_source;

        unsigned int id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if(result == GL_FALSE)
        {
            int length = 0;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            std::unique_ptr<char[]> message = std::make_unique<char[]>(length);
            glGetShaderInfoLog(id, length, &length, message.get());

            std::string s = (type == GL_VERTEX_SHADER ? "vertex" : "fragment");
            Engine::Log("%d", 1);
            Engine::Log("Failed to compile %s\n", s);
            Engine::Log("%s\n", std::string(message.get()));

            glDeleteShader(id);
            return 0;
        }
        return id;
    }

    ///@brief Creates The Shader Program. Includes Both Vertex And Fragment
    ///@return ID Of Shader Program
    unsigned int Shader::CreateProgram()
    {
        unsigned int program = glCreateProgram();
        unsigned int vs = Compile(GL_VERTEX_SHADER);
        unsigned int fs = Compile(GL_FRAGMENT_SHADER);

        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glValidateProgram(program);

        int valid;
        glGetProgramiv(program, GL_VALIDATE_STATUS, &valid);
        if(valid == false)
        {
            exit(EXIT_FAILURE);
        }

        glDeleteShader(vs);
        glDeleteShader(fs);
        return program;
    }
}