#ifndef TEXTURE_H
#define TEXTURE_H

#include "Common/Units.h"

class Texture
{
public:
    Texture(std::string image_path);
private:
    std::vector<Color> texture_data;
    float u, v;
};
#endif