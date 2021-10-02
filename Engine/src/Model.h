#ifndef MODEL_H
#define MODEL_H

#include "Common/Vertex.h"
#include "Graphics/Texture.h"

struct Model
{
    Model(std::vector<Vertex> vertices);
    Model(std::vector<Vertex> vertices, std::vector<Shared<Texture>> textures);
    Model(std::string file_path, std::vector<Shared<Texture>> textures);
    Model(const Model& m);
    
    std::vector<Shared<Texture>> GetTextures();
    void SetTextures(std::vector<Shared<Texture>> textures);

    std::vector<Vertex> vertices;
    std::vector<Shared<Texture>> textures;
};
#endif