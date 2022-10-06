#ifndef OGLTEXTUREMANAGER_H
#define OGLTEXTUREMANAGER_H

#include "Core/Media/Graphics/Texture.h"

struct ModelTexture;
class OGLTextureManager : public GraphicsTextureManager
{
public:
    void InitModelTextureArray(std::vector<Shared<ModelTexture>> textures, uint common_size);
    void Use(uint shader_program);

private:
    uint m_texture_id;
};
#endif
