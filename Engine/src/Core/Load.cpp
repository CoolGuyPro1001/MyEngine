#include "Load.h"

namespace Engine
{
    void LoadLevel(Level& level)
    {
        //Delete Graphics Buffer
        Graphics::DeleteBuffer(*Graphics::BufferId());
        
        //Init A New Buffer
        Graphics::InitVertexBuffer(*Graphics::BufferId());

        //A vector of pointers to models (pointer to a vector of Vertices objects)
        
        int offset = 0;
        for(Shared<Model> model : level.models)
        {
            Graphics::AddDataToBuffer(model->vertices, *Graphics::VaoId());
            Graphics::FormatData(*Graphics::VaoId(), offset);

            offset += model->vertices.size() * sizeof(Vertex);
        }
    }

    void RunLevel(Level& level)
    {
        TIME last_time;
        bool running = true;

        std::vector<int> sizes = std::vector<int>();

        for(Shared<Model> model : level.models)
        {
            sizes.push_back(model->vertices.size() * sizeof(Vertex));
        }

        while(running)
        {
            TIME current_time = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> delay = current_time - last_time;
            last_time = current_time;

            //Model      Actors in Model
            std::vector<std::vector<Actor>> total_actors = std::vector<std::vector<Actor>>(level.models.size());
            Graphics::Camera world_camera;
            
            for(Controller controller : level.controllers)
            {
                controller.PollEvents();
            }

            for(Actor actor : level.actors)
            {
                actor.Tick();

                for(int i = 0; i < level.models.size(); i++)
                {
                    if(actor.model == level.models[i])
                    {
                        total_actors[i].push_back(actor);
                    }
                }
            }

            for(Graphics::Camera camera : level.cameras)
            {
                camera.Tick();
                world_camera = camera;
            }

            Draw(sizes, total_actors, world_camera);
        }
    }
}