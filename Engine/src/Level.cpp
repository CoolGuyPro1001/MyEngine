#include "Level.h"
#include "Actor.h"

Level::Level()
{
    gravity = 30;
}

void Level::AddTexture(Shared<Graphics::Texture> texture)
{
    textures.push_back(texture);
}

void Level::AddModel(Shared<Model> model)
{
    models.push_back(model);
}

void Level::AddActor(Shared<Actor> actor)
{
    actor->current_level = this;
    actors.push_back(actor);
}

void Level::AddCamera(Shared<Graphics::Camera> camera)
{
    cameras.push_back(camera);
}

void Level::AddController(Controller controller)
{
    controllers.push_back(controller);
}

void Level::ReadCollisionFile(std::string file_path)
{
    FILE* file;
    file = fopen(file_path.c_str(), "r");
    if(file == NULL)
    {
        printf("Can't open file\n");
        return;
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
}