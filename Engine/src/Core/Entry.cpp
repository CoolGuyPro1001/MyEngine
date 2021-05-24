#include "Entry.h"

#include "Graphics/VertexBuffer.h"
#include "Graphics/Graphics.h"
#include "Actor.h"
#include "Controller.h"
#include "Graphics/Camera.h"
#include "Core/Runtime.h"
#include "Core/Log.h"
#include "Collision.h"

#include <SDL2/SDL.h>

namespace Engine
{
    static Level current_level = Level();
    static std::map<Shared<Model>, std::vector<Shared<Object>>> instances;

    void Start(int window_width, int window_height, const char* window_name)
    {
        bool b = InitLog();
        
        if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_AUDIO) != 0)
        {
            SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
            exit(EXIT_FAILURE);
        }

        //SDL_ShowCursor(SDL_DISABLE);
        //SDL_SetRelativeMouseMode(SDL_TRUE);

        SDL_GameControllerEventState(SDL_ENABLE);

        if(!Graphics::InitWindow(window_width, window_height, window_name) || !Graphics::Initialize())
        {
            exit(EXIT_FAILURE);
        }

        //atexit(SDL_Quit);*/

        Graphics::UseShader("../../res/BaseShader.shader");
    }

    void LoadLevel(Level& level)
    {
        //Delete Graphics Buffer
        Graphics::DeleteBuffer();
        
        //Init A New Buffer
        Graphics::InitVertexBuffer();

        for(Shared<Graphics::Texture> texture : level.textures)
        {
            texture->Load();
        }

        int offset = 0;

        //Sky Block
        Shared<Model> sky_block = level.sky_block;
        Graphics::AddDataToBuffer(sky_block->vertices);
        offset += sky_block->vertices.size() * sizeof(Vertex);

        //Terrain
        Shared<Model> terrain = level.terrain;
        Graphics::AddDataToBuffer(terrain->vertices);
        offset += terrain->vertices.size() * sizeof(Vertex);

        //A vector of pointers to models (pointer to a vector of Vertices objects)
        for(Shared<Model> model : level.models)
        {
            Graphics::AddDataToBuffer(model->vertices);
            model->offset = offset;
            offset += model->vertices.size() * sizeof(Vertex);
        }
        Graphics::FormatData(offset);

        for(Shared<Actor> actor : level.actors)
        {
            if(!instances.contains(actor->model))
                instances.insert(std::pair<Shared<Model>, 
                    std::vector<Shared<Object>>>(actor->model, std::vector<Shared<Object>>()));

            instances[actor->model].push_back(actor);

            for(Shared<Component> component : actor->components)
            {
                if(!instances.contains(component->model))
                    instances.insert(std::pair<Shared<Model>, 
                        std::vector<Shared<Object>>>(component->model, std::vector<Shared<Object>>()));

                instances[component->model].push_back(component);
            }
        }

        SetFlatCollisionNormals(level.flat_collisions);

        current_level = level;
    }

    void Run(bool log_delay)
    {
        TIME last_time;
        bool running = true;

        while(running)
        {
            TIME current_time = std::chrono::high_resolution_clock::now();
            delay = current_time - last_time;
            last_time = current_time;

            //Model Actors in Model
            Shared<Graphics::Camera> world_camera;
            
            PollEvents(current_level.controllers);

            for(Shared<Actor> actor : current_level.actors)
            {
                actor->Tick();
            }

            DoCollision(current_level.actors, current_level.flat_collisions);

            for(Shared<Graphics::Camera> camera : current_level.cameras)
            {
                camera->Tick();
                world_camera = camera;
            }

            Draw(instances, world_camera, current_level.sky_block, current_level.terrain);

            if(log_delay)
            {
                Log("Delay: %f\n", delay.count());
                Log("FPS: %f\n\n", (1000.0 / delay.count()));
            }
        }
    }

    void Close()
    {
        Graphics::CloseWindow();
        CloseLog();
    }
}