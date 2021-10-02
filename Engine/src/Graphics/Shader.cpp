#include "Shader.h"
#include "GLDebug.h"
#include "Common/Error.h"

#include "File.h"

namespace Graphics
{
    Shader::Shader() :
        vertex_source(""),
        fragment_source("")
    {}

    Shader::Shader(std::string v_file, std::string f_file) :
        vertex_file(v_file),
        fragment_file(f_file)
    {
        vertex_source = File::ReadFile(vertex_file);
        fragment_source = File::ReadFile(fragment_file);
    }

    Shared<char> Shader::ProgramLog(uint program)
    {
        int length = 0;
        GLCall(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length));
        Shared<char> message = CreateShared<char>();
        GLCall(glGetProgramInfoLog(program, length, &length, message.get()));
        return message;
    }

    ///@brief Compiles The Shader Source
    ///@param type The Type Of Shader To Compile To. GL_VERTEX_SHADER Or GL_FRAGMENT_SHADER
    ///@return The ID Of Vertex/Fragment Shader Program
    uint Shader::Compile(uint type)
    {
        std::string source = (type == GL_VERTEX_SHADER) ? vertex_source : fragment_source;

        uint id = glCreateShader(type);
        const char* src = source.c_str();
        GLCall(glShaderSource(id, 1, &src, nullptr));
        GLCall(glCompileShader(id));

        int result;
        GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
        if(result == GL_FALSE)
        {
            int length = 0;
            GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
            Local<char[]> message = CreateLocal<char[]>(length);
            GLCall(glGetShaderInfoLog(id, length, &length, message.get()));

            std::string s;

            if(type == GL_VERTEX_SHADER)
                s = std::string("vertex ") + vertex_file + "\n" + std::string(message.get()) + "\n";
            else
                s = std::string("fragment ") + fragment_file + "\n" + std::string(message.get()) + "\n";

            CriticalErrorArgs(GLSL_ERROR, "Failed to compile %s\n", s.c_str())
            return 0;
        }
        return id;
    }

    ///@brief Creates The Shader Program. Includes Both Vertex And Fragment
    ///@return ID Of Shader Program
    uint Shader::CreateProgram()
    {
        uint program = glCreateProgram();
        uint vs = Compile(GL_VERTEX_SHADER);
        uint fs = Compile(GL_FRAGMENT_SHADER);

        GLCall(glAttachShader(program, vs));
        GLCall(glAttachShader(program, fs));

        GLCall(glLinkProgram(program));
        int linked;
        GLCall(glGetProgramiv(program, GL_LINK_STATUS, &linked));
        if(linked == false)
        {
            Shared<char> msg = ProgramLog(program);
            FatalErrorArgs(GLSL_ERROR, "Failed to link program %d\n%s\n", program, msg.get())
        }

        GLCall(glDeleteShader(vs));
        GLCall(glDeleteShader(fs));
        return program;
    }
}