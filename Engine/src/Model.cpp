#include "Model.h"
#include "Common/Error.h"

Model::Model(std::vector<Vertex> vertices) : vertices(vertices)
{
    textures = std::vector<Shared<Texture>>();
}

Model::Model(std::vector<Vertex> vertices, std::vector<Shared<Texture>> textures) : 
    vertices(vertices), textures(textures)
{
    for(Vertex& v : vertices)
    {
        if(v.texture_id != -1)
            v.texture_id = textures[v.texture_id - 1]->GetID() + 1;
    }
}

Model::Model(std::string file_path, std::vector<Shared<Texture>> textures) : textures(textures)
{
    Vector3 vec3 = Vector3();
    Color color = Color();
    TextureCoords tex = TextureCoords();
    float texid = 0;

    FILE* file;
    file = fopen(file_path.c_str(), "r");
    if(file == NULL)
    {
        CriticalErrorArgs(ENGINE_ERROR, "Can't Open Model File %s\n", file_path.c_str())
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

        int res = fscanf(file, "%f %f %f %x %x %x %x %f %f %f\n", 
            &vec3.x, &vec3.y, &vec3.z, &red, &green, &blue, &alpha, &tex.u, &tex.v, &texid);
        
        if(res == EOF)
        {
            break;
        }

        color.r = red;
        color.g = green;
        color.b = blue;
        color.a = alpha;

        vertices.emplace_back(vec3, color, tex, texid);
    }

    for(Vertex& v : vertices)
    {
        if(v.texture_id != -1)
            v.texture_id = textures[v.texture_id]->GetID();
    }
}

Model::Model(const Model& m)
{
    vertices = m.vertices;
    textures = m.textures;
}

std::vector<Shared<Texture>> Model::GetTextures()
{
    return textures;
}

void Model::SetTextures(std::vector<Shared<Texture>> textures)
{
    this->textures = textures;
    for(Vertex& v : vertices)
    {
        if(v.texture_id != -1)
            v.texture_id = textures[v.texture_id - 1]->GetID() + 1;
    }
}