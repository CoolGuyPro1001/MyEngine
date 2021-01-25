#include "Actor.h"
#include "Core/Enviroment.h"
#include "Common/Hex.h"

Model::Model(std::vector<Vertex> vertices) : vertices(vertices)
{
    texture = nullptr;
}

Model::Model(std::vector<Vertex> vertices, Shared<Graphics::Texture> texture) : vertices(vertices), texture(texture)
{
}

Model::Model(std::string file_path, Shared<Graphics::Texture> texture) : texture(texture)
{
    Vector3 vec3 = Vector3();
    Color color = Color();
    TextureCoords tex = TextureCoords();

    FILE* file;
    file = fopen(file_path.c_str(), "r");
    if(file == NULL)
    {
        printf("Can't open file\n");
        return;
    }

    while(true)
    {
        char red[4];
        char green[4];
        char blue[4];
        char alpha[4];

        int res = fscanf(file, "%f %f %f %s %s %s %s %f %f\n", 
        &vec3.x, &vec3.y, &vec3.z, &red, &green, &blue, &alpha, &tex.u, &tex.v);
        
        if(res == EOF)
        {
            break;
        }

        color.r = Hex(std::string(red)).ToDecimal();
        color.g = Hex(std::string(green)).ToDecimal();
        color.b = Hex(std::string(blue)).ToDecimal();
        color.a = Hex(std::string(alpha)).ToDecimal();

        vertices.push_back(Vertex(vec3, color, tex));
    }
}

Actor::Actor()
{
}

Actor::Actor(Shared<Model> model) : model(model)
{
}

void Actor::Tick()
{
}
