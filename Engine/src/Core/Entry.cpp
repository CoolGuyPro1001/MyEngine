#include "Entry.h"

#include "Time.h"

#include "Graphics/Graphics.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Buffers/UniformBuffer.h"
#include "Graphics/Texture.h"

#include "Common/Error.h"
#include "Common/Console.h"

#include "Level.h"
#include "Systems.h"

#include <SDL2/SDL.h>

void Start(int window_width, int window_height, const char* window_name)
{
    bool b = InitLog();

    //SDL_ShowCursor(SDL_DISABLE);
    //SDL_SetRelativeMouseMode(SDL_TRUE);

    SDL_GameControllerEventState(SDL_ENABLE);

    if(!Graphics::InitWindow(window_width, window_height, window_name))
        FatalError(SDL_ERROR, "Could Not Create Window");
    
    Graphics::Initialize();

    /*if(FT_Init_FreeType(&ft))
        FatalError(FREETYPE_ERROR, "Could Not Init FreeType Library");

    if(!LoadFonts())
        FatalError(FREETYPE_ERROR, "At Least One Font Couldn't Be Loaded. Perhaps There's A Typo In The File Name");
    */

    //Add Shaders
    Graphics::AddShader("../../res/GameVertex.vshader", "../../res/GameFrag.fshader");
    Graphics::AddShader("../../res/SkyVertex.vshader", "../../res/GameFrag.fshader");
    //Graphics::AddShader("../../res/TextVertex.vshader", "../../res/TextFrag.fshader");

    //Create Batch Buffer Vector
    Graphics::CreateBatchBuffers();
    
    //Init OpenGL Buffers
    Graphics::InitVertexBuffers();
    Graphics::InitUniformBuffers();

    //Load GUI
    //GUI::Load();
}

void Run(Level& lvl)
{
    lvl.Init();
    VertexSystem(lvl.model_components, lvl.model_textures);
    while(true)
    {
        InputSystem(lvl.controllers);
        ActorSystem(lvl.actors);
        CollisionSystem(lvl.collision_components);
        ViewProjectionSystem(lvl.camera_components, lvl.model_components);
        RenderSystem(lvl.model_components);
        UpdateTime();
    }
}

void Close()
{
    Graphics::CloseWindow();
    CloseLog();
    CloseConsole();
}
