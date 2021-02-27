#ifndef TEXTURE_H
#define TEXTURE_H

#include "Common/Units.h"
namespace Graphics
{
    class Texture
    {
    public:
        Texture(std::string image_path, uint slot);
        Texture(std::vector<Color> data, u16 width, u16 height, uint slot);
        ~Texture();

        static Shared<Texture> BMPToTexture(std::string bmp_path, uint slot);
        
        void Load();
        void Use(uint shader_program);

        u16 width;
        u16 height;
    private:
        std::vector<Color> texture_data;
        uint texture_id;
        uint slot;
    };
}
#endif