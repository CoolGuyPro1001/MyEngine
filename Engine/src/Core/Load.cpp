#include "Load.h"

#include "Graphics/VertexBuffer.h"
#include "Graphics/Graphics.h"
#include "Actor.h"
#include "Controller.h"
#include "Graphics/Camera.h"

#include <SDL2/SDL.h>


namespace Engine
{
    static Level current_level = Level();

    void Start(int window_width, int window_height, const char* window_name)
    {
        if(!Graphics::InitWindow(window_width, window_height, window_name) || !Graphics::Initialize())
        {
            exit(EXIT_FAILURE);
        }

        if(SDL_Init(SDL_INIT_GAMECONTROLLER | SDL_INIT_AUDIO) != 0)
        {
            SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
            exit(EXIT_FAILURE);
        }
        //atexit(SDL_Quit);*/

        Graphics::UseShader("../../res/BaseShader.shader");
    }

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

        current_level = level;
    }

    void Run()
    {
        TIME last_time;
        bool running = true;

        std::vector<int> sizes = std::vector<int>();

        for(Shared<Model> model : current_level.models)
        {
            sizes.push_back(model->vertices.size() * sizeof(Vertex));
        }

        while(running)
        {
            TIME current_time = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> delay = current_time - last_time;
            last_time = current_time;

            //Model      Actors in Model
            std::vector<std::vector<Actor>> total_actors = std::vector<std::vector<Actor>>(current_level.models.size());
            Graphics::Camera world_camera;
            
            PollEvents(level.controllers);

            for(Actor actor : current_level.actors)
            {
                actor.Tick();

                for(int i = 0; i < current_level.models.size(); i++)
                {
                    if(actor.model == current_level.models[i])
                    {
                        total_actors[i].push_back(actor);
                    }
                }
            }

            for(Graphics::Camera camera : current_level.cameras)
            {
                camera.Tick();
                world_camera = camera;
            }

            Draw(sizes, total_actors, world_camera);
        }

        Graphics::EndWindow();
    }
}