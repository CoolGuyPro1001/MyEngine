#ifndef SHADER_H
#define SHADER_H

namespace Graphics
{
    struct Shader
    {
        std::string vertex_source;
        std::string fragment_source;
        
        Shader();
        Shader(std::string v_source, std::string f_source);
        unsigned int Compile(unsigned int type);
        unsigned int CreateProgram();
        void Use();
    };
}
#endif