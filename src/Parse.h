#ifndef PARSE_H
#define PARSE_H

#include "Graphics/VertexBuffer.h"
#include "Graphics/Units.h"
#include "File.h"
#include "Common/Hex.h"
#include <memory>

namespace Parse
{
    std::shared_ptr<Graphics::VertexBuffer> FileToVbo(std::string file_path);

    template<typename T>
    size_t FindNumber(std::string x, size_t pos);
    float Normalize(int num, int low, int high);
}

#endif