#include "Texture.h"

Texture::Texture(std::string image_path)
{
    FILE* file;
    file = fopen(image_path.c_str(), "r");
    if(file == NULL)
    {
        printf("Can't open file");
        exit(EXIT_FAILURE);
    }

    u16 width;
    u16 height;
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
}