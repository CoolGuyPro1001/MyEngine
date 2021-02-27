#include "Texture.h"
#include "Core/Log.h"

namespace Graphics
{
    Texture::Texture(std::string image_path, uint slot)
    {
        FILE* file;
        file = fopen(image_path.c_str(), "r");
        if(file == NULL)
        {
            Engine::Log("Can't open file");
            exit(EXIT_FAILURE);
        }

        u16 dict_length;

        fread(&width, sizeof(u16), 1, file);
        fread(&height, sizeof(u16), 1, file);
        fread(&dict_length, sizeof(u32), 1, file);

        //U16 format
        //[Color ID][Red and Green][Blue and Alpha]
        Color dictionary[dict_length];
        fread(&dictionary, sizeof(Color), dict_length, file);

        u32 data[width * height];
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

    Texture::Texture(std::vector<Color> data, u16 width, u16 height, uint slot)
    {
        texture_data = data;
        this->width = width;
        this->height = height;
        this->slot = slot;
    }

    Shared<Texture> Texture::BMPToTexture(std::string bmp_path, uint slot)
    {
        FILE* file;
        file = fopen(bmp_path.c_str(), "r");
        
        if(file == NULL)
        {
            Engine::Log("Can't open file");
            exit(EXIT_FAILURE);
        }

        u16 file_type;
        fread(&file_type, sizeof(u16), 1, file);
        if(file_type != 0x4D42)
        {
            Engine::Log("Not A BMP");
            exit(EXIT_FAILURE);
        }

        u32 file_size;
        u32 pixel_offset;
        u32 width;
        u32 height;
        u16 bpp;

        fread(&file_size, sizeof(u32), 1, file);
        fseek(file, 4, SEEK_CUR);
        fread(&pixel_offset, sizeof(u32), 1, file);
        fseek(file, 4, SEEK_CUR);
        fread(&width, sizeof(u32), 1, file);
        fread(&height, sizeof(u32), 1, file);
        fseek(file, 2, SEEK_CUR);
        fread(&bpp, sizeof(u16), 1, file);
        fseek(file, pixel_offset, SEEK_SET);

        int area = width * height;
        std::vector<Color> color_data  = std::vector<Color>(area);
        u8* raw_data = new u8[area * 4];
        fread(raw_data, sizeof(u8), area * 4, file);


        //Need ocumentation on this
        int bmp_change = width * (height - 1);
        int bmp_row_change = -2 * width;

        int b = 0;
        for(int p = 0; p < area; p++)
        {
            Color selected_pixel = Color(raw_data[b + 2], raw_data[b + 1], raw_data[b], 0xff);

            if(bpp == 32) 
                selected_pixel.a = raw_data[b + 3];

            if(p % width == 0 && p != 0)
                bmp_change += bmp_row_change;
            
            color_data[p + bmp_change] = selected_pixel;

            b += bpp / 8;
        }

        delete[] raw_data;
        fclose(file);
        return CreateShared<Texture>(color_data, width, height, slot);
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