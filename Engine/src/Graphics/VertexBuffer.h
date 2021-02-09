#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "Common/Units.h"

namespace Graphics
{
    void DeleteBuffer();
    void InitVertexBuffer();
    void AddDataToBuffer(std::vector<Vertex>& vertices);
    void FormatData(int starting_offset);
    void ModifyData(std::vector<Vertex>& vertices);
}

#endif