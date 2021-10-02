#ifndef TEXTURE_H
#define TEXTURE_H

#include "Common/Color.h"

class Texture
{
public:
    Texture();
    Texture(std::string image_path);
    Texture(std::vector<Color> data);
    ~Texture();
    
    uint GetID();
    std::vector<Color> GetColorData();

    static Shared<Texture> BMPToTexture(std::string bmp_path);
    static void SetParameter(uint pname, int param);
    static void Use(uint shader_program);
    static void InitArray(const std::vector<Shared<Texture>>& textures);
    static void DeleteArray();

    static u16 width;
    static u16 height;
    static uint texture_array_id;
    static uint texture_object_count;

private:
    std::vector<Color> texture_data;
    uint id;
};
#endif