#ifndef FONTMEDIA_H
#define FONTMEDIA_H

#include <ft2build.h>
#include FT_FREETYPE_H

class MFont
{
    FT_Library ft;
    std::map<std::string, Font> fonts;

    std::vector<std::string> ttf_files;
    std::vector<std::string> ttf_bold_files;
    std::vector<std::string> ttf_italic_files;
    std::vector<std::string> ttf_both_files;

    std::vector<uint> font_widths;
    std::vector<uint> font_heights;
};

#endif
