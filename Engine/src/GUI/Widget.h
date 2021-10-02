#ifndef WIDGET_H
#define WIDGET_H

#include "Common/Vertex.h"
#include "Common/Color.h"
#include "Common/Vector2.h"
#include "Common/TextureCoords.h"

#include "Graphics/Texture.h"

#include "Text.h"

enum class TextAlignHorizontal{LEFT, MIDDLE, RIGHT};
enum class TextAlignVertical{UPPER, MIDDLE, BOTTOM};

class Widget
{
public:
    Widget();
    Widget(const Widget& other);

    void Render(std::vector<Vertex>& all_widget_vertices,
        std::vector<Vertex>& all_text_vertices, std::vector<uint>& textures_now);

    Vector2 position;
    float width;
    float height;
    float z_depth;

    Color color;
    TextureCoords uv;
    Shared<Texture> texture;

    std::string text;
    TextAlignHorizontal horizontal_alignment;
    TextAlignVertical vertical_alignment;
    Color text_color;
    float text_scale;
    float text_z_depth;
    bool word_wrap;
    float line_spacing;
    Font* font;
    TextStyle text_style;
};
#endif