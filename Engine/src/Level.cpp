#include "Level.h"
#include "Actor.h"
#include "Components/ModelComponent.h"
#include "Common/Shapes.h"
#include "Core/Graphics/Texture.h"

//static std::vector<Shared<Object>> objects;
//static std::vector<size_t> sizes;
//static std::vector<size_t> instances;

Level::Level(Shared<ModelTexture> sky)
{
    //gravity = 30;
}

void Level::AddActor(Shared<Actor> actor)
{
    actor->current_level = this;
    actors.push_back(actor);
}

void Level::Init()
{
    Shared<ModelTexture> sky = model_textures[0];
    Shared<CModel> sky_box = Cube(2, sky, sky, sky, sky, sky, sky, Vector3(-1.0, -1.0, -1.0));
    sky_box->actors.push_back(CreateShared<Actor>());
    model_components.push_back(sky_box);
}

/*void AddWidget(Widget widget)
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
        }


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

    Texture::FillArray(level.textures);

    SetFlatCollisionNormals(level.flat_collisions);

    while(running)
    {

        DoCollision(level.actors, level.flat_collisions);


        Graphics::ClearDrawBuffers();
        Graphics::Draw(sizes, instances);
        //GUI::TextRender();
        Graphics::UpdateGraphics();
    }
}*/
