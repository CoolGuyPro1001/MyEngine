#include "Entry.h"

#include "Time.h"

#include "Media/GraphicsMedia.h"
#include "Media/Graphics/GraphicsBuffer.h"
#include "Media/Graphics/Texture.h"

#include "Common/Error.h"
#include "Common/Log.h"

#include "Level.h"
#include "Systems.h"
#include "Events.h"

static Level& CurrentLevel()
{
    static Level default_level = Level();
    return default_level;
}

void Start(Level& lvl, Unique<MWindow> window, Unique<MRenderer> renderer, Unique<MInput> input)
{
    bool b = InitLog();

    if(window && !window->Create())
        FatalError(SDL_ERROR, "Could Not Create Window");
    
    if(renderer)
    {
        renderer->Init();

        //Add Shaders
        renderer->AddShader("../../res/GameVertex.vshader", "../../res/GameFrag.fshader");
        //Graphics::AddShader("../../res/TextVertex.vshader", "../../res/TextFrag.fshader");

        renderer->SetUniforms();
    }

    /*if(FT_Init_FreeType(&ft))
        FatalError(FREETYPE_ERROR, "Could Not Init FreeType Library");

    if(!LoadFonts())
        FatalError(FREETYPE_ERROR, "At Least One Font Couldn't Be Loaded. Perhaps There's A Typo In The File Name");
    */

    //Create Batch Buffer Vector
    //renderer->VBManager->CreateBatchBuffers();

    //Load GUI
    //GUI::Load();

    LoadLevel(lvl, renderer.get());
    while(true)
    {
        EventSystem(window.get(), input.get());
        ProcessEvents();
        ActorSystem(lvl.actors);
        CollisionSystem(lvl.collision_components);
        ModelSystem(renderer.get(), lvl.model_components);
        LightingSystem(renderer.get(), lvl.camera_components[0], lvl.ambient_factor, lvl.specular_factor, lvl.light_source_position, lvl.light_color);
        ViewProjectionSystem(renderer.get(), window.get(), lvl.camera_components);
        RenderSystem(renderer.get(), lvl.model_components);
        if (window) window->UpdateGraphics();
        UpdateTime();
        //Log("FPS: %f\n", FramesPerSecond());
    }
}

void LoadLevel(Level& lvl, MRenderer* renderer)
{
    CurrentLevel() = lvl;
    lvl.Init();

    VertexSystem(renderer, lvl.model_components, lvl.model_textures);
}

void Close(MWindow& window)
{
    window.Close();
    CloseLog();
    CloseConsole();
}
