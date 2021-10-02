#ifndef GUI_H
#define GUI_H

#include "Widget.h"
#include "Text.h"
#include "Common/Color.h"
#include "Common/Vector2.h"

namespace GUI
{
    uint CreateWidget();
    uint CopyWidget(uint original_handle);
    static Shared<Widget> GetWidget(uint handle);
    void DeleteWidget(uint handle);
    void Load();
    void Render();

    Vector2 GetWidgetPosition(uint handle);
    float GetWidgetWidth(uint handle);
    float GetWidgetHeight(uint handle);
    float GetWidgetZDepth(uint handle);
    Vector2 GetWidgetSize(uint handle);
    Color GetWidgetColor(uint handle);
    TextureCoords GetWidgetUV(uint handle);
    Texture GetWidgetTexture(uint handle);
    std::string GetWidgetText(uint handle);
    TextAlignHorizontal GetWidgetHorizontalAlignment(uint handle);
    TextAlignVertical GetWidgetVerticalAllignment(uint handle);
    Color GetWidgetTextColor(uint handle);
    float GetWidgetTextScale(uint handle, float scale);
    float GetWidgetTextZDepth(uint handle, float z_depth);
    bool GetWidgetWordWrap(uint handle);
    float GetWidgetLineSpacing(uint handle);
    Font GetWidgetFont(uint handle);
    TextStyle GetWidgetTextStyle(uint handle);

    void SetWidgetPosition(uint handle, Vector2 position);
    void SetWidgetPosition(uint handle, float x, float y);
    void SetWidgetWidth(uint handle, float width);
    void SetWidgetHeight(uint handle, float height);
    void SetWidgetZDepth(uint handle, float z_depth);
    void SetWidgetSize(uint handle, Vector2 size);
    void SetWidgetColor(uint handle, Color color);
    void SetWidgetColor(uint handle, u8 red, u8 green, u8 blue, u8 alpha);
    void SetWidgetUV(uint handle, TextureCoords uv);
    void SetWidgetUV(uint handle, float u, float v);
    void SetWidgetTexture(uint handle, Shared<Texture> texture);
    void SetWidgetText(uint handle, std::string text);
    void SetWidgetHorizontalAlignment(uint handle, TextAlignHorizontal alignment);
    void SetWidgetVerticalAllignment(uint handle, TextAlignVertical alignment);
    void SetWidgetTextColor(uint handle, Color color);
    void SetWidgetTextColor(uint handle, u8 red, u8 green, u8 blue, u8 alpha);
    void SetWidgetTextScale(uint handle, float scale);
    void SetWidgetTextZDepth(uint handle, float z_depth);
    void SetWidgetWordWrap(uint handle, bool wrap);
    void SetWidgetLineSpacing(uint handle, float spacing);
    void SetWidgetFont(uint handle, Font* font);
    void SetWidgetTextStyle(uint handle, TextStyle style);
}
    
#endif