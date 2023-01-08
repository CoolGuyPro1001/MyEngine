#include "ModelComponent.h"

#include "Level.h"

#include "Common/Error.h"
#include "Common/Vertex.h"

#include "Core/Media/Graphics/Texture.h"

CModel::CModel()
{
}

CModel::CModel(Shared<CModel> other)
{
    vertices = other->vertices;
    indices = other->indices;
    textures = other->textures;
}

CModel::CModel(std::vector<Vertex> vertices, std::vector<ushort> indices, std::vector<size_t> face_offsets) : vertices(vertices), indices(indices), face_offsets(face_offsets)
{
    textures = std::vector<Shared<ModelTexture>>();
}

CModel::CModel(std::vector<Vertex> vertices, std::vector<ushort> indices, std::vector<size_t> face_offsets, std::vector<Shared<ModelTexture>> textures) :
    vertices(vertices), indices(indices), face_offsets(face_offsets), textures(textures)
{
    for(Vertex& v : this->vertices)
    {
        v.texture_coord.w = textures[v.texture_coord.w]->id;
    }
}

CModel::CModel(std::string file_path, std::vector<Shared<ModelTexture>> textures) : textures(textures)
{
    FILE* file;
    file = fopen(file_path.c_str(), "r");
    if(file == NULL)
    {
        CriticalErrorArgs(ENGINE_ERROR, "Can't Open CModel File %s\n", file_path.c_str())
        return;
    }

    auto vertex_comp = [=](Vertex lv, Vertex rv)
    {
        if(lv.vector == rv.vector)
        {
            if(lv.normal == rv.normal)
            {
                if(lv.texture_coord == rv.texture_coord)
                {
                    return false;
                }
                return lv.texture_coord < rv.texture_coord;
            }
            return lv.normal < rv.normal;
        }
        return lv.vector < rv.vector;
    };

    std::set<Vertex, decltype(vertex_comp)> vertices_set(vertex_comp);

    std::vector<Vector3> geometric_vertices;
    std::vector<Vector3> normals;
    std::vector<TextureCoord> texture_coords;

    char line[100];
    char* ptr = line;
    while(fgets(line, 100, file) != NULL)
    {
        char* element;
        int num_chars_read;

        sscanf(ptr, "%s%n", element, num_chars_read);
        ptr += num_chars_read + 1; //+1 For Space

        if(element == "f")
        {
            char* token;
            const char delims[3] = " \t";

            token = strtok(ptr, delims);
            while(token != NULL)
            {
                int v, vn, vt;
                sscanf(token, "%d/%d/%d", &v, &vn, &vt);

                auto result = vertices_set.insert(Vertex
                (
                    geometric_vertices[v],
                    normals[vn],
                    texture_coords[vt]
                ));

                indices.emplace_back(std::distance(vertices_set.begin(), result.first));

                token = strtok(NULL, delims);
            }

            indices.emplace_back(PRIMITIVE_RESTART);
        }

        //Reading Colors
        /*if(element == "vc")
        {
            u8 r, g, b, a;
            scanf("%x %x %x %x", &r, &g, &b, &a);
            colors.emplace_back(r, g, b, a);
        }*/

        float a, b, c;
        scanf("%f %f %f", &a, &b, &c);

        if(element == "v")
        {
            geometric_vertices.emplace_back(a, b, c);
            continue;
        }

        if(element == "vn")
        {
            normals.emplace_back(a, b, c);
            continue;
        }

        if(element == "vt")
        {
            c = textures[c]->id;
            texture_coords.emplace_back(a, b, c);
            continue;
        }
    }

    vertices = std::vector<Vertex>(vertices_set.begin(), vertices_set.end());
}

CModel::CModel(const CModel& m)
{
    vertices = m.vertices;
    indices = m.indices;
    textures = m.textures;
    face_offsets = m.face_offsets;
}

void CModel::AttachToLevel(Level& lvl)
{
    lvl.model_components.push_back(shared_from_this());
}

Color CModel::GetFaceColor(uint face_index)
{
    size_t first_vertex = indices[face_offsets[face_index]];
    return vertices[first_vertex].color;
}

std::vector<TextureCoord> CModel::GetFaceTextureCoordinates(uint face_index)
{
    std::vector<TextureCoord> tex_coords;

    for(auto it = indices.begin() + face_offsets[face_index]; *it != PRIMITIVE_RESTART && it != indices.end(); it++)
    {
        tex_coords.push_back(vertices[*it].texture_coord);
    }

    return tex_coords;
}

void CModel::SetFaceColor(uint face_index, Color color)
{
    for(auto it = indices.begin() + face_offsets[face_index]; *it != PRIMITIVE_RESTART && it != indices.end(); it++)
    {
        vertices[*it].color = color;
    }
}

void CModel::SetMultipleFaceColor(std::vector<uint> face_indices, Color color)
{
    for(uint face_index : face_indices)
    {
        SetFaceColor(face_index, color);
    }
}

void CModel::SetMultipleFaceColors(std::vector<uint> face_indices, std::vector<Color> colors)
{
    if(face_indices.size() != colors.size())
    {
        CriticalError(ENGINE_ERROR, "Number Of Face Indices Does Not Equal Number Of Colors\n");
        return;
    }

    for(int i = 0; i < face_indices.size(); i++)
    {
        SetFaceColor(face_indices[i], colors[i]);
    }
}

void CModel::SetFaceTextureCoords(uint face_index, std::vector<TextureCoord> tex_coords)
{
    int i = 0;
    for(auto it = indices.begin() + face_offsets[face_index]; *it != PRIMITIVE_RESTART && it != indices.end(); it++)
    {
        if(i >= tex_coords.size())
        {
            CriticalError(ENGINE_ERROR, "Not Enough Texture Coordinates Provided\n");
        }

        vertices[*it].texture_coord = tex_coords[i];
        i++;
    }
}

void CModel::SetMultipleFaceTextureCoords(std::vector<uint> face_indices, std::vector<std::vector<TextureCoord>> tex_coords_collection)
{
    if(face_indices.size() != tex_coords_collection.size())
    {
        CriticalError(ENGINE_ERROR, "Number Of Faces Does Not Equal Number Of Texture Coord Groups\n");
        return;
    }

    for(int i = 0; i < face_indices.size(); i++)
    {
        SetFaceTextureCoords(face_indices[i], tex_coords_collection[i]);
    }
}
