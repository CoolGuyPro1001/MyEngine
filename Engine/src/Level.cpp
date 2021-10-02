#include "Level.h"
#include "Actor.h"
#include "Events.h"

#include "Core/Clock.h"

#include "Graphics/VertexBuffer.h"
#include "Graphics/UniformBuffer.h"
#include "Graphics/Graphics.h"
#include "Common/Error.h"
#include "GUI/GUI.h"
#include "Graphics/GLDebug.h"

static Level* current_level = nullptr;
static std::vector<Shared<Object>> objects;
static std::vector<size_t> sizes;
static std::vector<size_t> instances;

Level::Level()
{
    gravity = 30;
}

void AddTextureToCurrentLevel(Shared<Texture> texture)
{
    current_level->textures.push_back(texture);
}

void AddModelToCurrentLevel(Shared<Model> model)
{
    current_level->models.push_back(model);
}

void AddActorToCurrentLevel(Shared<Actor> actor)
{
    if(typeid(actor) == typeid(Shared<Component>) || typeid(actor) == typeid(Component))
        return;

    actor->current_level = current_level;
    current_level->actors.push_back(actor);

    for(Shared<Component> component : actor->components)
    {
        std::vector<Shared<Component>>& components = current_level->components;
        if(std::find(components.begin(), components.end(), component) != components.end())
            components.push_back(component);
    }
}

void AddCameraToCurrentLevel(Shared<Camera> camera)
{
    current_level->cameras.push_back(camera);
}

void AddControllerToCurrentLevel(Shared<Controller> controller)
{
    current_level->controllers.push_back(controller);
}

void AddWidget(Widget widget)
{
    current_level->widgets.push_back(widget);
}

std::vector<CollisionTri> ReadCollisionFile(std::string file_path)
{
    std::vector<CollisionTri> flat_collisions;

    FILE* file;
    file = fopen(file_path.c_str(), "r");
    if(file == NULL)
    {
        CriticalErrorArgs(ENGINE_ERROR, "Can't Open File %s\n", file_path.c_str());
        return flat_collisions;
    }
    
    CollisionTri col = CollisionTri();

    while(true)
    {
        std::string comment;

        /*fscanf(file, "%s", comment.c_str());
        if(comment.size() > 1 && comment.substr(0, 2)  == "//")
        {
            file
            continue;
        }*/


        int res = fscanf(file, "%f %f %f %f %f %f %f %f %f", &col.p0.x, &col.p0.y, &col.p0.z, 
            &col.p1.x, &col.p1.y, &col.p1.z, &col.p2.x, &col.p2.y, &col.p2.z);
        
        if(res == EOF)
        {
            break;
        }

        flat_collisions.push_back(col);
    }

    return flat_collisions;
}

void StartLevel(Level& level)
{
    current_level = &level;
    std::vector<uint> batch_texture_ids;

    Graphics::ClearUniformBuffers();

    Texture::InitArray(level.textures);

    //Sky Block
    const Shared<Object>& sky_block = level.sky_block;
    Graphics::buffer3d.AddData(sky_block->model->vertices);
    objects.push_back(sky_block);
    sizes.push_back(sky_block->model->vertices.size());

    //Terrain
    const Shared<Object>& terrain = level.terrain;
    Graphics::buffer3d.AddData(terrain->model->vertices);
    objects.push_back(terrain);
    sizes.push_back(terrain->model->vertices.size());

    //A vector of pointers to models (pointer to a vector of Vertices objects)
    for(const Shared<Model>& model : level.models)
    {
        Graphics::buffer3d.AddData(model->vertices);
        sizes.push_back(model->vertices.size());
    }

    Graphics::FormatVertexBuffers();
    instances = std::vector<size_t>(sizes.size());
    instances[0] = 1;
    instances[1] = 1;

    for(const Shared<Actor>& actor : level.actors)
    {
        objects.push_back(actor);
        for(int i = 0; i < level.models.size(); i++)
        {
            if(actor->model == level.models[i])
                instances[i + 2]++;
        }
        actor->current_level = &level;
    }

    for(const Shared<Component>& component : level.components)
    {
        objects.push_back(component);
        for(int i = 0; i < level.models.size(); i++)
        {
            if(component->model == level.models[i])
                instances[i + 2]++;
        }
    }

    SetFlatCollisionNormals(level.flat_collisions);

    TIME last_time;
    bool running = true;
    bool mvp_a_fill = true;
    std::vector<glm::mat4> object_mvps(objects.size()); 

    while(running)
    {
        TIME current_time = TIME_NOW;
        delay = current_time - last_time;
        last_time = current_time;

        //Model Actors in Model
        Camera* world_camera;
        
        PollEvents(level.controllers);

        for(const Shared<Actor>& actor : level.actors)
        {
            actor->Tick();
        }

        DoCollision(level.actors, level.flat_collisions);

        for(const Shared<Camera>& camera : level.cameras)
        {
            camera->Tick();
            world_camera = camera.get();
        }

        glm::mat4 vp = Graphics::Generate3DMatrix(world_camera->fov, world_camera->position, 
            world_camera->looking_at, world_camera->up);

        for(int i = 0; i < objects.size(); i++)
        {
            objects[i]->UpdateMVP();
            object_mvps[i] = vp * objects[i]->GetMVP();
        }

        Graphics::mvp_buffer.Fill(object_mvps);

        mvp_a_fill = !mvp_a_fill;

        Graphics::ClearDrawBuffers();
        Graphics::Draw3D(sizes, instances);
        GUI::Render();
        Graphics::UpdateGraphics();
    }
}