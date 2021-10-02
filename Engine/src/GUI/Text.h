#ifndef TEXT_H
#define TEXT_H

#include "Graphics/Texture.h"
#include "Common/Vector2.h"
#include "Common/Vertex.h"
#include "Common/Color.h"

#include <ft2build.h>
#include FT_FREETYPE_H

extern FT_Library ft;

enum class TextStyle {REGULAR, BOLD, ITALIC, BOTH};

struct TextChar
{
    uint tex;
    Vector2 size;
    Vector2 bearing;
    int advance;
};

struct Font
{
    std::vector<TextChar> characters_regular;
    std::vector<TextChar> characters_bold;
    std::vector<TextChar> characters_italic;
    std::vector<TextChar> characters_both;
};

std::vector<Vertex> RenderText(std::string& text, Font* font, TextStyle s, Vector2 position, 
    float scale, float z_depth, Color color);
void AddFont(const std::string ttf_file, const std::string ttf_bold_file, const std::string ttf_italic_file,
    const std::string ttf_both_file, uint width, uint height);
bool LoadFonts();
Font* GetFont(std::string name);

#endif