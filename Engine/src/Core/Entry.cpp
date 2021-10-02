#include "Entry.h"

#include "Graphics/Graphics.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/UniformBuffer.h"

#include "Common/Error.h"
#include "Common/Console.h"

#include "GUI/Text.h"
#include "GUI/GUI.h"

#include <SDL2/SDL.h>


//For Testing Only
#include "Graphics/GLDebug.h"
#include "Graphics/Shader.h"

void Start(int window_width, int window_height, const char* window_name)
{
    bool b = InitLog();
    
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_AUDIO) != 0)
    {
        FatalErrorArgs(SDL_ERROR, "Unable to initialize SDL: %s", SDL_GetError())
    }

    //SDL_ShowCursor(SDL_DISABLE);
    //SDL_SetRelativeMouseMode(SDL_TRUE);

    SDL_GameControllerEventState(SDL_ENABLE);

    if(!Graphics::InitWindow(window_width, window_height, window_name))
        FatalError(SDL_ERROR, "Could Not Create Window");
    
    Graphics::Initialize();

    if(FT_Init_FreeType(&ft))
        FatalError(FREETYPE_ERROR, "Could Not Init FreeType Library");

    if(!LoadFonts())
        FatalError(FREETYPE_ERROR, "At Least One Font Couldn't Be Loaded. Perhaps There's A Typo In The File Name");

    //Add Shaders
    Graphics::AddShader("../../res/UI.vshader", "../../res/UIFragment.fshader");
    Graphics::AddShader("../../res/BasicVertex.vshader", "../../res/BasicFragment.fshader");

    //Create Batch Buffer Vector
    Graphics::CreateBatchBuffers();
    
    //Init OpenGL Buffers
    Graphics::InitVertexBuffers();
    Graphics::InitUniformBuffers();

    //Load GUI
    GUI::Load();
}

void Close()
{
    Graphics::CloseWindow();
    CloseLog();
    CloseConsole();
}

/*void Test()
{
    //Classes
    struct Vertex
    {
        float x, y;
        u8 r, g, b, a;
        float u, v;
        int tex;
    };

    //Globals:
    SDL_Window* window;
    int window_width = 800;
    int window_height = 600;
    bool initialized = false;
    uint vbo;
    uint vao;

    std::vector<Vertex> buffer = 
    {
        {0, 0, 255, 0, 0, 255, 0, 0, -1},
        {0.1, 0, 255, 0, 0, 255, 0, 0, -1},
        {0.1, 0.1, 255, 0, 0, 255, 0, 0, -1},
        {0, 0, 255, 0, 0, 255, 0, 0, -1},
        {0, 0.1, 255, 0, 0, 255, 0, 0, -1},
        {0.1, 0.1, 255, 0, 0, 255, 0, 0, -1}
    };

    {
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_AUDIO) != 0)

        g_window = SDL_CreateWindow
        (
            "Strevo", 
            SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, 
            window_width, 
            window_height,
            SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
        );

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_CreateContext(window);

        SDL_GL_SetSwapInterval(1);
    }

    {   
        GLenum error = glewInit();
        const char* c;
        if(GLEW_OK != error)
            c = (const char*) glewGetErrorString(error);
        
        initialized = true;

        GLCall(glEnable(GL_DEPTH_TEST));
        GLCall(glDepthFunc(GL_LESS));
    }

    {
        //Graphics::AddShader("../../res/UI.vshader", "../../res/UIFragment.fshader");
        //Shader shader = ParseShader(vertex_path, fragment_path);
        //g_shader_programs.push_back(shader.CreateProgram());
    }

        GLCall(glCreateBuffers(1, &vbo));
        GLCall(glGenVertexArrays(1, &vao));

        //GLCall(glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex), &buffer[0], GL_STATIC_DRAW);
    }

    {
        Graphics::ClearVertexBuffers();
        Graphics::FormatVertexBuffers();

        while(running)
        {
            Graphics::ClearDrawBuffers();
            GUI::Render();
            Graphics::UpdateGraphics();
        }
    }
}*/