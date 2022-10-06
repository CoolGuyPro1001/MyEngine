#include "SDLWindow.h"
#include "SDLEvents.h"

#include "Common/Error.h"
#include "Common/Vector2.h"

#include "Events/WindowEvents.h"

SDLWindow::SDLWindow(ushort width, ushort height, std::string title, bool vsync) :
    MWindow(width, height, title), m_vsync(vsync)
{
    if(SDL_InitSubSystem(SDL_INIT_EVENTS | SDL_INIT_VIDEO) != 0)
        FatalErrorArgs(SDL_ERROR, "Unable To Initialize SDL Window: %s", SDL_GetError());

    SDL_ShowCursor(SDL_ENABLE);
    SDL_SetRelativeMouseMode(SDL_TRUE);
}

bool SDLWindow::Create()
{
    m_window = SDL_CreateWindow
    (
        m_title.c_str(),
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        m_width,
        m_height,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
    );

    if(!m_window)
    {
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_CreateContext(m_window);
    SDL_GL_SetSwapInterval(m_vsync);

    return true;
}

void SDLWindow::Close()
{
    if(m_window)
    {
        SDL_DestroyWindow(m_window);
    }
}

void SDLWindow::ProcessEvents()
{
    //Window Updates Are Called Before Input Updates
    UpdateSDLEventList();
    std::vector<SDL_Event> events;

    events = RetrieveSDLEvents(SDL_QUIT, SDL_QUIT);

    if(events.size() > 0)
        exit(EXIT_SUCCESS);

    events = RetrieveSDLEvents(SDL_WINDOWEVENT, SDL_WINDOWEVENT);

    for(SDL_Event& event : events)
    {
        switch(event.window.event)
        {
            case SDL_WINDOWEVENT_CLOSE:
                break;
            case SDL_WINDOWEVENT_ENTER:
                break;
            case SDL_WINDOWEVENT_LEAVE:
                break;
            case SDL_WINDOWEVENT_RESIZED:
            {
                resize_event->new_size = Vector2(event.window.data1, event.window.data2);
                resize_event->Announce();
                m_width = event.window.data1;
                m_height = event.window.data2;
                break;
            }
        }
    }
}

void SDLWindow::UpdateGraphics()
{

    if(m_window)
    {
        SDL_GL_SwapWindow(m_window);
    }
}
