#include "WindowMedia.h"
#include "Events/WindowEvents.h"

MWindow::MWindow(uint width, uint height, std::string title) :
    m_width(width), m_height(height), m_title(title)
{
    resize_event = new EWindowResized;
}

uint MWindow::Width()
{
    return m_width;
}

uint MWindow::Height()
{
    return m_height;
}
