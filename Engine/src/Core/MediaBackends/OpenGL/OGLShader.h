#ifndef OGLSHADER_H
#define OGLSHADER_H

Shared<char> OGLProgramLog(uint program);
uint OGLCompileShader(std::string file, uint type);
bool OGLCreateProgram(uint vs, uint fs, uint& programd_id);

#endif
