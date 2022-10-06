#ifndef SDLWINDOW_H
#define SDLWINDOW_H

#include "Core/Media/WindowMedia.h"

class SDLWindow : public MWindow
{
public:
    SDLWindow(ushort width, ushort height, std::string title, bool vsync);

    bool Create();
    void Close();
    void ProcessEvents();
    void UpdateGraphics();

private:
    SDL_Window* m_window;
    bool m_vsync;
};

#endif
