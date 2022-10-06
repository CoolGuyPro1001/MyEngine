#ifndef WINDOWMEDIA_H
#define WINDOWMEDIA_H

struct EWindowResized;

//More polymorphism
class MWindow
{
public:
    MWindow(uint width, uint height, std::string title);

    virtual bool Create() = 0;
    virtual void Close() = 0;
    virtual void ProcessEvents() = 0;
    virtual void UpdateGraphics() = 0;

    uint Width();
    uint Height();

    EWindowResized* resize_event;

protected:
    uint m_width;
    uint m_height;
    std::string m_title;
};

#endif
