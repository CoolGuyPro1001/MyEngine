#include "Widget.h"
//#include "Common/Shapes.h"
#include "Actor.h"
#include "Core/Graphics/Graphics.h"

Widget::Widget()
{
    position = Vector2();
    width = 1;
    height = 1;
    z_depth = 0;
    color = Color();
    uv = TextureCoords();
    texture = nullptr;
    text = "";
    horizontal_alignment = TextAlignHorizontal::MIDDLE;
    vertical_alignment = TextAlignVertical::MIDDLE;
}

Widget::Widget(const Widget& other)
{
    position = other.position;
    width = other.width;
    height = other.height;
    z_depth = other.z_depth;
    color = other.color;
    uv = other.uv;
    texture = other.texture;
    text = other.text;
    horizontal_alignment = other.horizontal_alignment;
    vertical_alignment = other.vertical_alignment;
}

void Widget::Render(std::vector<Vertex>& all_widget_vertices,
        std::vector<Vertex>& all_text_vertices, std::vector<uint>& textures_now)
//In GUI::Load(), the vertices from this function are inserted based on the z_depth
//After all text_vertices have been inserted, they are split into batches based on texture id

{
    std::array<TextureCoords, 6> coords;
    coords[0] = {0.0f, 0.0f};
    coords[1] = {1.0f, 0.0f};
    coords[2] = {1.0f, 1.0f};
    coords[3] = {0.0f, 0.0f};
    coords[4] = {0.0f, 1.0f};
    coords[5] = {1.0f, 1.0f};

    std::array<Vertex, 6> vertices;
    if(texture && color == Color(0, 0, 0, 0))
        vertices = Rectangle(position, width, height, z_depth, coords, texture->GetID());
    else if(!texture && color != Color(0, 0, 0, 0))
        vertices = Rectangle(position, width, height, z_depth, color);
    else if(texture && color != Color(0, 0, 0, 0))
        vertices = Rectangle(position, width, height, z_depth, color, coords, texture->GetID());

    //Text Rendering
    Vector2 text_pos;

    switch(horizontal_alignment)
    {
        case TextAlignHorizontal::RIGHT:
            //text_pos.x = position.x + width - text_width;
            break;
         case TextAlignHorizontal::MIDDLE:
            //text_pos.x = position.x + (width / 2) - (text_width / 2);
            break;
        case TextAlignHorizontal::LEFT:
            text_pos.x = position.x;
            break;   
    }
    
    switch(vertical_alignment)
    {
        case TextAlignVertical::UPPER:
            //text_pos.y = position.y + height - text_height;
            break;
         case TextAlignVertical::MIDDLE:
            //text_pos.y = position.y + (height / 2) - (text_height / 2);
            break;
        case TextAlignVertical::BOTTOM:
            text_pos.y = position.y;
            break;   
    }

    //Add Wiget Rectangle
    auto widget_insert_from = all_widget_vertices.end();
    auto text_insert_from = all_text_vertices.end();

    for(auto it = all_widget_vertices.begin(); it != all_widget_vertices.end(); it++)
    {
        if(it->vector.z > z_depth)
        {
            widget_insert_from = it;
            break;
        }
    }
    
    using Quad = std::array<Vertex, 6>;

    all_widget_vertices.insert(widget_insert_from, vertices.begin(), vertices.end());


    //Text Widget Insertion

    std::vector<Vertex> text_vertices = RenderText(text, font, text_style, text_pos,
        text_scale, text_z_depth, text_color);

    int batch_number;

    auto is_equal = [&](Vertex v)
    {
        return batch_number == floor((v.texture_id - 2) / Graphics::g_max_texture_units);
    };

    auto is_higher = [&](Vertex v)
    {
        return batch_number < floor((v.texture_id - 2) / Graphics::g_max_texture_units);
    };

    for(Vertex v : text_vertices)
    {
        batch_number = floor((v.texture_id - 2) / Graphics::g_max_texture_units); //Math Pog

        auto batch_begin = std::find_if(all_text_vertices.begin(), all_text_vertices.end(), is_equal);
        auto batch_end = std::find_if(batch_begin, all_text_vertices.end(), is_higher);

        auto insert = batch_end;
        for(auto it = batch_begin; it != batch_end; it++)
        {
            if(it->vector.z > text_z_depth)
            {
                insert = it;
                break;
            }
        }

        all_text_vertices.insert(insert, v);

        //Add Unique Textures
        int texture = v.texture_id;
        if(std::find(textures_now.begin(), textures_now.end(), texture) == textures_now.end())
            textures_now.push_back(texture);
    }
}
