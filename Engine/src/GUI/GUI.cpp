#include "GUI.h"

#include "Graphics/VertexBuffer.h"
#include "Graphics/Graphics.h"
#include "Common/Error.h"

#include "Graphics/GLDebug.h"

namespace GUI
{  
    static std::vector<Shared<Widget>> widgets;
    static std::vector<uint> textures2d;

    uint CreateWidget()
    {
        auto first_null = std::find(widgets.begin(), widgets.end(), nullptr);
        if(first_null != widgets.end())
        {
            *first_null = CreateShared<Widget>();
        }

        widgets.emplace_back(CreateShared<Widget>());
        return widgets.size() - 1;
    }

    uint CopyWidget(uint original_handle)
    {
        auto first_null = std::find(widgets.begin(), widgets.end(), nullptr);
        if(first_null != widgets.end())
        {
            *first_null = CreateShared<Widget>(*GetWidget(original_handle).get());
        }

        widgets.emplace_back(CreateShared<Widget>(*GetWidget(original_handle).get()));
        return widgets.size() - 1;
    }

    static Shared<Widget> GetWidget(uint handle)
    {
        if(handle >= widgets.size() || widgets[handle] == nullptr)
            FatalError(GUI_ERROR, "Widget ID References Nothing (Widget Might've Been Deleted)\n");

        return widgets[handle];
    }

    void DeleteWidget(uint handle)
    {
        if(handle >= widgets.size())
            FatalError(GUI_ERROR, "ID For DeleteWidget() Exceeds Number Of Widgets");

        widgets[handle] = nullptr;
    }

    void Load()
    {
        std::vector<Vertex> widget_vertices;
        std::vector<Vertex> text_vertices;

        for(Shared<Widget> w : widgets)
        {
            w->Render(widget_vertices, text_vertices, textures2d);
        }

        std::sort(textures2d.begin(), textures2d.end());

        Graphics::buffer2d.AddData(widget_vertices);

        int batch_num = floor((text_vertices[0].texture_id - 2) / 32) + 1;
        auto from = text_vertices.begin();
        std::vector<Vertex> temp;
        
        auto it = text_vertices.begin(); 
        for(; it != text_vertices.end(); it++)
        {
            if(floor((it->texture_id - 2) / 32) + 1 > batch_num)
            {
                temp.insert(temp.end(), from, it);
                Graphics::batch_2d_buffers[batch_num - 1].AddData(temp);
                batch_num++;
                temp.clear();
            }
        }
        temp.insert(temp.end(), from, it);
        Graphics::batch_2d_buffers[batch_num - 1].AddData(temp);
    }

    void Render()
    {
        Graphics::Draw2D(textures2d);
    }

    Vector2 GetWidgetPosition(uint handle)
    {
        return GetWidget(handle)->position;
    }

    float GetWidgetWidth(uint handle)
    {
        return GetWidget(handle)->width;
    }

    float GetWidgetHeight(uint handle)
    {
        return GetWidget(handle)->height;
    }

    float GetWidgetZDepth(uint handle)
    {
        return GetWidget(handle)->z_depth;
    }

    Vector2 GetWidgetSize(uint handle)
    {
        return Vector2(GetWidget(handle)->width, GetWidget(handle)->height);
    }

    Color GetWidgetColor(uint handle)
    {
        return GetWidget(handle)->color;
    }

    TextureCoords GetWidgetUV(uint handle)
    {
        return GetWidget(handle)->uv;
    }

    Texture GetWidgetTexture(uint handle)
    {
        return *(GetWidget(handle)->texture);
    }

    std::string GetWidgetText(uint handle)
    {
        return GetWidget(handle)->text;
    }

    TextAlignHorizontal GetWidgetHorizontalAlignment(uint handle)
    {
        return GetWidget(handle)->horizontal_alignment;
    }

    TextAlignVertical GetWidgetVerticalAllignment(uint handle)
    {
        return GetWidget(handle)->vertical_alignment;
    }

    Color GetWidgetTextColor(uint handle)
    {
        return GetWidget(handle)->text_color;
    }

    float GetWidgetTextScale(uint handle)
    {
        return GetWidget(handle)->text_scale;
    }

    float GetWidgetTextZDepth(uint handle)
    {
        return GetWidget(handle)->text_z_depth;
    }

    bool GetWidgetWordWrap(uint handle)
    {
        return GetWidget(handle)->word_wrap;
    }

    float GetWidgetLineSpacing(uint handle)
    {
        return GetWidget(handle)->line_spacing;
    }

    Font GetWidgetFont(uint handle)
    {
        return *(GetWidget(handle)->font);
    }

    TextStyle GetWidgetTextStyle(uint handle)
    {
        return GetWidget(handle)->text_style;
    }

    void SetWidgetPosition(uint handle, Vector2 position)
    {
        GetWidget(handle)->position = position;
    }

    void SetWidgetPosition(uint handle, float x, float y)
    {
        GetWidget(handle)->position = Vector2(x, y);
    }

    void SetWidgetWidth(uint handle, float width)
    {
        GetWidget(handle)->width = width;
    }

    void SetWidgetHeight(uint handle, float height)
    {
        GetWidget(handle)->height = height;
    }

    void SetWidgetZDepth(uint handle, float z_depth)
    {
        GetWidget(handle)->z_depth = z_depth;
    }

    void SetWidgetSize(uint handle, Vector2 size)
    {
        GetWidget(handle)->width = size.x;
        GetWidget(handle)->height = size.y;
    }

    void SetWidgetColor(uint handle, Color color)
    {
        GetWidget(handle)->color = color;
    }

    void SetWidgetColor(uint handle, u8 red, u8 green, u8 blue, u8 alpha)
    {
        GetWidget(handle)->color = Color(red, green, blue, alpha);
    }

    void SetWidgetUV(uint handle, TextureCoords uv)
    {
        GetWidget(handle)->uv = uv;
    }

    void SetWidgetUV(uint handle, float u, float v)
    {
        GetWidget(handle)->uv = TextureCoords(u, v);
    }

    void SetWidgetTexture(uint handle, Shared<Texture> texture)
    {
        GetWidget(handle)->texture = texture;
    }

    void SetWidgetText(uint handle, std::string text)
    {
        GetWidget(handle)->text = text;
    }

    void SetWidgetHorizontalAlignment(uint handle, TextAlignHorizontal alignment)
    {
        GetWidget(handle)->horizontal_alignment = alignment;
    }

    void SetWidgetVerticalAllignment(uint handle, TextAlignVertical alignment)
    {
        GetWidget(handle)->vertical_alignment = alignment;
    }

    void SetWidgetTextColor(uint handle, Color color)
    {
        GetWidget(handle)->text_color = color;
    }

    void SetWidgetTextColor(uint handle, u8 red, u8 green, u8 blue, u8 alpha)
    {
        GetWidget(handle)->text_color = Color(red, green, blue, alpha);
    }

    void SetWidgetTextScale(uint handle, float scale)
    {
        GetWidget(handle)->text_scale = scale;
    }

    void SetWidgetTextZDepth(uint handle, float z_depth)
    {
        GetWidget(handle)->text_z_depth = z_depth;
    }

    void SetWidgetWordWrap(uint handle, bool wrap)
    {
        GetWidget(handle)->word_wrap = wrap;
    }

    void SetWidgetLineSpacing(uint handle, float spacing)
    {
        GetWidget(handle)->line_spacing = spacing;
    }

    void SetWidgetFont(uint handle, Font* font)
    {
        GetWidget(handle)->font = font;
    }

    void SetWidgetTextStyle(uint handle, TextStyle style)
    {
        GetWidget(handle)->text_style = style;
    }
}