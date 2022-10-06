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

void Start(Unique<MWindow> window, Unique<MRenderer> renderer, Unique<MInput> input, Level& lvl)
{
    bool b = InitLog();

    if(!window->Create())
        FatalError(SDL_ERROR, "Could Not Create Window");
    
    renderer->Init();
    renderer->vb_instance->Init();
    renderer->ub_mvp->Init(1024);

    /*if(FT_Init_FreeType(&ft))
        FatalError(FREETYPE_ERROR, "Could Not Init FreeType Library");

    if(!LoadFonts())
        FatalError(FREETYPE_ERROR, "At Least One Font Couldn't Be Loaded. Perhaps There's A Typo In The File Name");
    */

    //Add Shaders
    renderer->AddShader("../../res/GameVertex.vshader", "../../res/GameFrag.fshader");
    //Graphics::AddShader("../../res/TextVertex.vshader", "../../res/TextFrag.fshader");

    renderer->SetMVPBlock();

    //Create Batch Buffer Vector
    //renderer->VBManager->CreateBatchBuffers();

    //Load GUI
    //GUI::Load();

    LoadLevel(*renderer, lvl);
    while(true)
    {
        EventSystem(*window, *input);
        ProcessEvents();
        ActorSystem(lvl.actors);
        CollisionSystem(lvl.collision_components);
        ViewProjectionSystem(*renderer, *window, lvl.camera_components, lvl.model_components);
        RenderSystem(*renderer, lvl.model_components);
        window->UpdateGraphics();
        UpdateTime();
        //Log("FPS: %f\n", FramesPerSecond());
    }
}

void LoadLevel(MRenderer& renderer, Level& lvl)
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
