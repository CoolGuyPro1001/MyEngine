#include "D3DShader.h"

D3DShader::D3DShader() :
    vertex_source(""),
    fragment_source("")
{}

D3DShader::D3DShader(std::string v_file, std::string f_file) :
    vertex_file(v_file),
    fragment_file(f_file)
{

}

bool D3DShader::CreateProgram()
{

}

bool D3DShader::Use()
{
};
