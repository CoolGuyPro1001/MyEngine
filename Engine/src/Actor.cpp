#include "Actor.h"
#include "Core/Runtime.h"
#include "Common/Hex.h"
#include "Core/Log.h"
#include "Level.h"

Model::Model(std::vector<Vertex> vertices) : vertices(vertices)
{
    texture = nullptr;
}

Model::Model(std::vector<Vertex> vertices, Shared<Graphics::Texture> texture) : 
    vertices(vertices), texture(texture)
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
        uint red, green, blue, alpha;
        int res = fscanf(file, "%f %f %f %x %x %x %x %f %f\n", 
            &vec3.x, &vec3.y, &vec3.z, &red, &green, &blue, &alpha, &tex.u, &tex.v);
        
        if(res == EOF)
        {
            break;
        }

        color.r = red;
        color.g = green;
        color.b = blue;
        color.a = alpha;

        vertices.push_back(Vertex(vec3, color, tex));
    }
}

Actor::Actor()
{
    can_fall = true;
}

Actor::Actor(Shared<Model> model) : model(model)
{
    can_fall = true;
}

Actor::~Actor()
{
    delete collision;
    delete current_level;
}

void Actor::Tick()
{
    if(can_fall && current_level)
    {
        position_velocity.y += (Engine::Delay() > 1) ? current_level->gravity : current_level->gravity * Engine::Delay();
        position.y += position_velocity.y;
    }
}

void Actor::CreateHitBox(float depth, float height, float width)
{
    collision = new CollisionBox(position, depth, height, width);
}