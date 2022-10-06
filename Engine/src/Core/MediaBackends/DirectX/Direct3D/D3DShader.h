#ifndef D3DSHADER_H
#define D3DSHADER_H

struct D3DShader
{
    std::string vertex_file;
    std::string fragment_file;

    std::string vertex_source;
    std::string fragment_source;

    uint program_id;

    D3DShader();
    D3DShader(std::string v_file, std::string f_file);
    D3DShader(const D3DShader& s);

    bool CreateProgram();
    bool Use();
};
#endif
