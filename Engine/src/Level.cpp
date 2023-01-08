#include "Level.h"
#include "Actor.h"

#include "Components/ModelComponent.h"
#include "Common/Shapes.h"
#include "Core/Media/Graphics/Texture.h"

Level::Level()
{
}

Level::Level(Shared<ModelTexture> sky)
{
    model_textures.push_back(sky);
    gravity = 30;
}

void Level::AddActor(Shared<Actor> actor)
{
    actor->current_level = this;
    actors.push_back(actor);
}

void Level::Init()
{
    Shared<ModelTexture> sky = model_textures[0];
    Shared<CModel> sky_box = CubeTextured(1, sky, sky, sky, sky, sky, sky);
    model_components.push_back(sky_box);
    ambient_factor = 0.1f;
    specular_factor = 0.5f;
    light_source_position = Vector3(0, 10, 0);
    light_color = Color(0xff, 0xff, 0xff, 0xff);
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
}*/

//SetFlatCollisionNormals(level.flat_collisions);
