#ifndef WIDGET_H
#define WIDGET_H

#include "Common/Vertex.h"
#include "Common/Color.h"
#include "Common/Vector2.h"
#include "Common/TextureCoord.h"

#include "Core/Graphics/Texture.h"

#include "Text.h"

enum class TextAlignHorizontal{LEFT, MIDDLE, RIGHT};
enum class TextAlignVertical{UPPER, MIDDLE, BOTTOM};

typedef std::unordered_map<std::type_index, Shared<GUIComponent>> GUIComponentMap;

class Widget
{
public:
    Widget();
    Widget(const Widget& other);

    void Render(std::vector<Vertex>& all_widget_vertices,
        std::vector<Vertex>& all_text_vertices, std::vector<uint>& textures_now);

    template<class G> void AddGUIComponent(Shared<G> component);
    template<class G> Shared<G> GetGUIComponent();

    GUIComponentMap components;

    Vector2 position;
    float width;
    float height;
    float z_depth;
    Color color;
    TextureCoord uv;
    Shared<Texture> texture;


};

template<class G> void Widget::AddComponent(Shared<G> component)
{
    components[typeid(G)] = component;
    component->widget = shared_from_this();
}

template<class G> Shared<G> Widget::GetComponent()
{
    return std::static_pointer_cast<G>(components[typeid(G)]);
}
#endif
