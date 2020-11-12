#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <GL/glew.h>
#include "../Common/Units.h"

namespace Graphics
{
    void DeleteBuffer(uint& id);
    void InitVertexBuffer(uint& id);
    void AddDataToBuffer(std::vector<Vertex>& vertices, uint& vao_id);
    void FormatData(uint& vao_id, int starting_offset);
    void ModifyData(uint& vao_id, std::vector<Vertex>& vertices);
}

#endif