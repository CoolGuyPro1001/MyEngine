#include "ModelComponent.h"

#include "Level.h"
#include "Common/Vertex.h"
#include "Common/Error.h"
#include "Core/Graphics/Texture.h"

CModel::CModel(std::vector<Vertex> vertices) : vertices(vertices)
{
    textures = std::vector<Shared<ModelTexture>>();
}

CModel::CModel(std::vector<Vertex> vertices, std::vector<Shared<ModelTexture>> textures) :
    vertices(vertices), textures(textures)
{
    for(Vertex& v : this->vertices)
    {
        v.texture_id = textures[v.texture_id]->id;
    }
}

CModel::CModel(std::string file_path, std::vector<Shared<ModelTexture>> textures) : textures(textures)
{
    Vector3 vec3 = Vector3();
    Color color = Color();
    TextureCoord uv = TextureCoord();
    uint tex_index = 0;

    FILE* file;
    file = fopen(file_path.c_str(), "r");
    if(file == NULL)
    {
        CriticalErrorArgs(ENGINE_ERROR, "Can't Open CModel File %s\n", file_path.c_str())
        return;
    }

    while(true)
    {
        uint red, green, blue, alpha;
        std::string comment;

        /*fscanf(file, "%s", comment.c_str());
        if(comment.size() > 1 && comment.substr(0, 2)  == "//")
        {
            file
            continue;
        }*/

        int res = fscanf(file, "%f %f %f %x %x %x %x %f %f %d\n",
            &vec3.x, &vec3.y, &vec3.z, &red, &green, &blue, &alpha, &uv.u, &uv.v, &tex_index);

        if(res == EOF)
        {
            break;
        }

        color.r = red;
        color.g = green;
        color.b = blue;
        color.a = alpha;

        float texid = textures[tex_index]->id;
        vertices.emplace_back(vec3, color, uv, texid);
    }
}

CModel::CModel(const CModel& m)
{
    vertices = m.vertices;
    textures = m.textures;
    buffer_size = m.buffer_size;
}

void CModel::AttachToLevel(Level& lvl)
{
    lvl.model_components.push_back(shared_from_this());
}
