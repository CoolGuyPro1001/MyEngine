#include "../Texture.h"
#include "Common/Color.h"

ModelTexture::ModelTexture(float id, uint size, std::vector<Color> color_data) : id(id), size(size), color_data(color_data)
{
}

ModelTexture::~ModelTexture()
{
}
