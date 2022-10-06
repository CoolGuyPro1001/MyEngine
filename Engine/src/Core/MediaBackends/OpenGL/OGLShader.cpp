#include "OGLShader.h"

#include "OGLDebug.h"
#include "Common/Error.h"

Shared<char> OGLProgramLog(uint program)
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
uint OGLCompileShader(std::string shader_path, uint type)
{
    FILE* file;
    file = fopen(shader_path.c_str(), "r");

    if(!file)
    {
        FatalErrorArgs(ENGINE_ERROR, "Can't Open OpenGL Shader File %s", shader_path.c_str())
        return 0;
    }

    std::string shader_code;

    char line[128];
    while(fgets(line, 128, file))
        shader_code += line;

    const char* src = shader_code.c_str();

    uint id = glCreateShader(type);
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if(result == GL_FALSE)
    {
        int length = 200;
        char message[length];

        GLCall(glGetShaderInfoLog(id, length, &length, message));

        std::string error_string;
        std::string type_name = (type == GL_VERTEX_SHADER) ? "vertex" : "fragment";

        error_string = type_name + " shader " + shader_path + "\n" + std::string(message) + "\n";
        CriticalErrorArgs(GLSL_ERROR, "Failed to compile %s\n", error_string.c_str())
        return 0;
    }
    return id;
}

bool OGLCreateProgram(uint vs, uint fs, uint& program_id)
{
    program_id = glCreateProgram();

    GLCall(glAttachShader(program_id, vs));
    GLCall(glAttachShader(program_id, fs));

    GLCall(glLinkProgram(program_id));
    int linked;
    GLCall(glGetProgramiv(program_id, GL_LINK_STATUS, &linked));

    if(linked == false)
    {
        Shared<char> msg = OGLProgramLog(program_id);
        FatalErrorArgs(GLSL_ERROR, "Failed to link program %d\n%s\n", program_id, msg.get())
        return false;
    }

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));
    return true;
}
