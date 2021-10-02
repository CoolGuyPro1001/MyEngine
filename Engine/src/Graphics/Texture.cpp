#include "Texture.h"
#include "Graphics.h"
#include "Common/Error.h"
#include "Graphics/GLDebug.h"

static uint game_texture_counter = 0;

u16 Texture::width = 0;
u16 Texture::height = 0;
uint Texture::texture_array_id = 0;
uint Texture::texture_object_count = 0;

Texture::Texture()
{
    id = game_texture_counter;
    game_texture_counter++;
}

Texture::Texture(std::string image_path)
{
    if(width == 0 || height == 0)
        FatalError(ENGINE_ERROR, "Texture Width Or Height Not Set");

    FILE* file;
    file = fopen(image_path.c_str(), "r");
    if(file == NULL)
        FatalErrorArgs(ENGINE_ERROR, "Can't Open Texture File %s", image_path.c_str())

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

    id = game_texture_counter;
    game_texture_counter++;
}

Texture::Texture(std::vector<Color> data)
{
    if(width == 0 || height == 0)
        FatalError(ENGINE_ERROR, "Texture Width Or Height Not Set")

    if(data.size() != width * height)
        FatalError(ENGINE_ERROR, "Texture Data != Texture Dimensions (width * height)")

    texture_data = data;
    id = game_texture_counter;
    game_texture_counter++;
}

Shared<Texture> Texture::BMPToTexture(std::string bmp_path)
{
    FILE* file;
    file = fopen(bmp_path.c_str(), "r");
    
    if(file == NULL)
        FatalErrorArgs(ENGINE_ERROR, "Can't Open BMP File %s", bmp_path.c_str())

    u16 file_type;
    fread(&file_type, sizeof(u16), 1, file);
    if(file_type != 0x4D42)
        FatalErrorArgs(ENGINE_ERROR, "%s Is Not A BMP File", bmp_path.c_str())

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


    //Need documentation on this
    //int bmp_change = width * (height - 1);
    //int bmp_row_change = -2 * width;

    int b = 0;
    for(int p = 0; p < area; p++)
    {
        Color selected_pixel = Color(raw_data[b + 2], raw_data[b + 1], raw_data[b], 0xff);

        if(bpp == 32) 
            selected_pixel.a = raw_data[b + 3];

        //if(p % width == 0 && p != 0)
            //   bmp_change += bmp_row_change;
        
        color_data[p] = selected_pixel;

        b += bpp / 8;
    }

    delete[] raw_data;
    fclose(file);
    return CreateShared<Texture>(color_data);
}

Texture::~Texture()
{
    game_texture_counter--;
}

void Texture::SetParameter(uint pname, int param)
{
    GLCall(glActiveTexture(GL_TEXTURE0));
    GLCall(glBindTexture(GL_TEXTURE_2D_ARRAY, texture_array_id));
    GLCall(glTexParameteri(GL_TEXTURE_2D_ARRAY, pname, param));
}

void Texture::InitArray(const std::vector<Shared<Texture>>& textures)
{
    GLCall(glGenTextures(1, &texture_array_id));
    GLCall(glBindTexture(GL_TEXTURE_2D_ARRAY, texture_array_id));
    SetParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    SetParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    SetParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    SetParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    std::vector<Color> data;
    for(const Shared<Texture>& tex : textures)
    {
        std::vector<Color> tex_data = tex->GetColorData();
        data.insert(data.end(), tex_data.begin(), tex_data.end());
    }
    GLCall(glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, width, height, textures.size(), 0, GL_RGBA, GL_UNSIGNED_BYTE, &data[0]));
    texture_object_count++;
}

void Texture::DeleteArray()
{
    GLCall(glDeleteTextures(1, &texture_array_id));
}

void Texture::Use(uint shader_program)
{
    GLCall(glActiveTexture(GL_TEXTURE0));
    GLCall(glBindTexture(GL_TEXTURE_2D_ARRAY, texture_array_id));

    int tex_uniform_id = glGetUniformLocation(shader_program, "game_textures");
    GLCall(glUniform1i(tex_uniform_id, 0));
}

uint Texture::GetID()
{
    return id;
}

std::vector<Color> Texture::GetColorData()
{
    return texture_data;
}