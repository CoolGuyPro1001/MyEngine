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
        std::string comment;

        /*fscanf(file, "%s", comment.c_str());
        if(comment.size() > 1 && comment.substr(0, 2)  == "//")
        {
            file
            continue;
        }*/

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

Object::Object()
{
    position = Vector3(0, 0, 0);
    rotation = Vector3(0, 0, 0);
    scale = Vector3(1.0f, 1.0f, 1.0f);
    position_velocity = Vector3(0, 0, 0);
    rotation_velocity = Vector3(0, 0, 0);
    scale_velocity = Vector3(0, 0, 0);
    model = nullptr;
    visible = true;
}

Object::Object(Vector3 position, Vector3 rotation, Vector3 scale) : position(position), rotation(rotation), scale(scale)
{
    model = nullptr;
    visible = true;
}

Object::Object(Shared<Model> model) : model(model)
{
    position = Vector3(0, 0, 0);
    rotation = Vector3(0, 0, 0);
    scale = Vector3(1.0f, 1.0f, 1.0f);
    position_velocity = Vector3(0, 0, 0);
    rotation_velocity = Vector3(0, 0, 0);
    scale_velocity = Vector3(0, 0, 0);
    visible = true;
}

Object::Object(Shared<Model> model, Vector3 position, Vector3 rotation, Vector3 scale) : 
    model(model), position(position), rotation(rotation), scale(scale)
{
    visible = true;
}

Actor::Actor() : Object()
{
    can_fall = true;
    current_level = nullptr;
    collision = nullptr;
}

Actor::Actor(Vector3 position, Vector3 rotation, Vector3 scale) : Object(position, rotation, scale)
{
    can_fall = true;
    current_level = nullptr;
    collision = nullptr;
}

Actor::Actor(Shared<Model> model) : Object(model)
{
    can_fall = true;
    current_level = nullptr;
    collision = nullptr;
}

Actor::Actor(Shared<Model> model, Vector3 position, Vector3 rotation, Vector3 scale) : 
    Object(model, position, rotation, scale)
{
    can_fall = true;
    current_level = nullptr;
    collision = nullptr;
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
    }

    position += position_velocity;
    rotation += rotation_velocity;
    scale += scale_velocity;

    for(Shared<Component> component : components)
    {
        component->position = position + component->r_position;
        component->rotation = rotation + component->r_rotation;
        component->scale = scale + component->r_scale;;
    }
}  

void Actor::CreateHitBox(float depth, float height, float width)
{
    collision = new CollisionBox(position, depth, height, width);
}

void Actor::AddComponent(Shared<Component> component)
{
    components.push_back(component);
}

Component::Component(Shared<Actor> actor) : actor(actor)
{
    r_position = Vector3(0, 0, 0);
    r_rotation = Vector3(0, 0, 0);
    r_scale = Vector3(0, 0, 0);
}

Component::Component(Shared<Actor> actor, Vector3 r_position, Vector3 r_rotation, Vector3 r_scale) :
    actor(actor), r_position(r_position), r_rotation(r_rotation), r_scale(r_scale)
{
    Vector3 p = actor->position + r_position;
    Vector3 r = actor->rotation + r_rotation;
    Vector3 s = actor->scale + r_scale;
    Object(p, r, s);
}

Component::Component(Shared<Actor> actor, Shared<Model> model) : actor(actor), Object(model)
{
    r_position = Vector3(0, 0, 0);
    r_rotation = Vector3(0, 0, 0);
    r_scale = Vector3(0, 0, 0);
}

Component::Component(Shared<Actor> actor, Shared<Model> model, Vector3 r_position, Vector3 r_rotation, Vector3 r_scale) :
    actor(actor), r_position(r_position), r_rotation(r_rotation), r_scale(r_scale)
{
    Vector3 p = actor->position + r_position;
    Vector3 r = actor->rotation + r_rotation;
    Vector3 s = actor->scale + r_scale;
    Object(model, p, r, s);
}

Component::~Component()
{
}