#include "Texture.h"

namespace Graphics
{
    Texture::Texture(std::string image_path, uint slot)
    {
        FILE* file;
        file = fopen(image_path.c_str(), "r");
        if(file == NULL)
        {
            printf("Can't open file");
            exit(EXIT_FAILURE);
        }

        u16 dict_length;

        fread(&width, sizeof(u16), 1, file);
        fread(&height, sizeof(u16), 1, file);
        fread(&dict_length, sizeof(u16), 1, file);

        //U16 format
        //[Color ID][Red and Green][Blue and Alpha]
        Color dictionary[dict_length];
        fread(&dictionary, sizeof(Color), dict_length, file);

        u16 data[width * height];
        fread(&data, sizeof(u16), width * height, file);
        texture_data = std::vector<Color>(width * height);

        for(int i = 0; i < width * height; i++)
        {
            u16 color_id = data[i];
            if(color_id > dict_length - 1 )
            {
                continue;
            }

            texture_data[i] = dictionary[color_id];
        }

        this->slot = slot;
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &texture_id);
    }

    void Texture::Load()
    {
        glGenTextures(1, &texture_id);

        glBindTexture(GL_TEXTURE_2D, texture_id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &texture_data[0]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    }

    void Texture::Use(uint shader_program)
    {
        if(slot > 32)
        {
            return;
        }

        glActiveTexture(slot + 0x84C0);
        glBindTexture(GL_TEXTURE_2D, texture_id);
        int uniform_id = glGetUniformLocation(shader_program, "texture_sampler");
        glUniform1i(uniform_id, slot);
    }
}