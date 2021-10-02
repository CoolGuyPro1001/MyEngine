#ifndef SHADER_H
#define SHADER_H

namespace Graphics
{
    struct Shader
    {
        std::string vertex_file;
        std::string fragment_file;

        std::string vertex_source;
        std::string fragment_source;
        
        Shader();
        Shader(std::string v_file, std::string f_file);
        Shader(const Shader& s);
        
        Shared<char> ProgramLog(uint program);
        uint Compile(uint type);
        uint CreateProgram();
        void Use();
    };
}
#endif