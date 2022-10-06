#include "Text.h"
#include "Common/Color.h"
#include "Core/Graphics.h"
#include "Core/Graphics/GLDebug.h"
#include "Common/Error.h"
#include "Common/Shapes.h"

std::vector<Vertex> RenderText(std::string& text, Font* font, TextStyle s, Vector2 position, 
    float scale, float z_depth, Color color)
{
    std::vector<TextChar>& characters = font->characters_regular;
    switch(s)
    {
        case TextStyle::BOLD:
            characters = font->characters_bold;
            break;
        case TextStyle::ITALIC:
            characters = font->characters_italic;
            break;
        case TextStyle::BOTH:
            characters = font->characters_both;
            break;
    }

    std::vector<Vertex> vertices;

    for (auto c = text.begin(); c != text.end(); c++)
    {
        TextChar ch = characters[*c];

        float xpos = position.x + (2 * ch.bearing.x * scale) / Graphics::g_window_width;
        float ypos = position.y - (2 * (ch.size.y - ch.bearing.y) * scale) / Graphics::g_window_height;

        float w = (ch.size.x * scale) / Graphics::g_window_width;
        float h = (ch.size.y * scale) / Graphics::g_window_height;

        std::array<TextureCoords, 6> coords;
        coords[0] = {0, 1};
        coords[1] = {1, 1};
        coords[2] = {1, 0};
        coords[3] = {0, 1};
        coords[4] = {0, 0};
        coords[5] = {1, 0};

        //Create Quad
        std::array<Vertex, 6> text_rectangle = Rectangle(Vector2(xpos, ypos), w, h, z_depth, color, coords, ch.tex);
        vertices.insert(vertices.end(), text_rectangle.begin(), text_rectangle.end());
        
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        position.x += ((ch.advance >> 6) * scale) / Graphics::g_window_width; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
    
    return vertices;
}

void AddFont(const std::string ttf_file, const std::string ttf_bold_file, const std::string ttf_italic_file,
    const std::string ttf_both_file, uint width, uint height)
{
    ttf_files.push_back(ttf_file);
    ttf_bold_files.push_back(ttf_bold_file);
    ttf_italic_files.push_back(ttf_italic_file);
    ttf_both_files.push_back(ttf_both_file);
    font_widths.push_back(width);
    font_heights.push_back(height);
}

bool LoadFonts()
{
    if(!ft)
       FatalError(FREETYPE_ERROR, "Library Not Loaded");

    GLCall(glPixelStorei(GL_UNPACK_ALIGNMENT, 1)); //Disable byte-alignment restriction
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));  

    auto add_characters = [&](const std::string file, size_t font_index, std::vector<TextChar>& characters)
    {
        FT_Face face;

        if (FT_New_Face(ft, file.c_str(), 0, &face))
        {
            FatalErrorArgs(FREETYPE_ERROR, "Failed To Load Font, %s", file.c_str())
            return false;
        }

        FT_Set_Pixel_Sizes(face, font_widths[font_index], font_heights[font_index]);

        ulong c = 0;
        while(c < 128)
        {
            //Load character glyph 
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                CriticalErrorArgs(FREETYPE_ERROR, "Failed to load Glyph %c Of Font %s", c, file.c_str())
                c++;
                continue;
            }

            uint tex;
            GLCall(glGenTextures(1, &tex));
            GLCall(glBindTexture(GL_TEXTURE_2D, tex));
            GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
            GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

            GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
            GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

            GLCall(glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            ));

            Texture::texture_object_count++;
            TextChar character = 
            {
                tex,
                Vector2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                Vector2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                face->glyph->advance.x
            };

            characters.push_back(character);
            c++;
        }
        return true;
    };

    bool success = true;
    Font f;
    int i = 0;
    while(i < ttf_files.size())
    {
        if(!add_characters(ttf_files[i], i, f.characters_regular)) success = false;
        if(!add_characters(ttf_bold_files[i], i, f.characters_bold)) success = false;
        if(!add_characters(ttf_italic_files[i], i, f.characters_italic)) success = false;
        if(!add_characters(ttf_both_files[i], i, f.characters_both)) success = false;

        uint slash = ttf_files[i].find_last_of('/') + 1;
        uint dot = ttf_files[i].find_last_of('.');
        std::string name = ttf_files[i].substr(slash, dot -slash);
        bool ret = fonts.insert(std::make_pair(name, f)).second;
        if(!ret)
            fonts[name] = f;
        i++;
    }

    return success;
}

Font* GetFont(std::string name)
{
    return &fonts[name];
}
