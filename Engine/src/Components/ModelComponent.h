#ifndef MODELCOMPONENT_H
#define MODELCOMPONENT_H

#include "Component.h"

#include "Common/Vertex.h"

struct Level;
struct ModelTexture;

struct CModel : public Component, public std::enable_shared_from_this<CModel>
{
    CModel();
    CModel(Shared<CModel> other);

    CModel(std::vector<Vertex> vertices);
    CModel(std::vector<Vertex> vertices, std::vector<Shared<ModelTexture>> textures);
    CModel(std::string file_path, std::vector<Shared<ModelTexture>> textures);
    CModel(const CModel& m);

    void AttachToLevel(Level& lvl);
    //void Globalize();

    std::vector<Vertex> vertices;
    std::vector<Shared<ModelTexture>> textures;
    uint buffer_size; //Byte Size Of Model Vertex Data
};
#endif
