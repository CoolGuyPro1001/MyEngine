#ifndef TEXTURE_H
#define TEXTURE_H

#include "Common/Units.h"
namespace Graphics
{
    class Texture
    {
    public:
        Texture(std::string image_path, uint slot);
        ~Texture();
        
        void Load();
        void Use(uint shader_program);

        u8 width;
        u8 height;
    private:
        std::vector<Color> texture_data;
        uint texture_id;
        uint slot;
    };
}
#endif