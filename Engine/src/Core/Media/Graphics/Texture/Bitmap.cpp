#include "Bitmap.h"

#include "Common/Color.h"
#include "Common/Error.h"

bool ReadBitmapFile(std::string image_path, std::vector<Color>& colors, uint& width, uint& height)
{
    uint dot = image_path.find_last_of('.');
    std::string extension = image_path.substr(dot, image_path.size() - dot);

    if(extension == ".bmp")
        return BMPToTexture(image_path, colors, width, height);

    FatalError(ENGINE_ERROR, "Image File Format Not Supported\n Currently Supported: BMP");
    return true;
};

bool BMPToTexture(std::string bmp_path, std::vector<Color>& colors, uint& width, uint& height)
{
    FILE* file;
    file = fopen(bmp_path.c_str(), "rb");

    if(file == NULL)
    {
        FatalErrorArgs(ENGINE_ERROR, "Can't Open BMP File %s", bmp_path.c_str())
        return false;
    }

    u16 file_type;
    fread(&file_type, sizeof(u16), 1, file);

    if(file_type != 0x4D42)
    {
        FatalErrorArgs(ENGINE_ERROR, "%s Is Not A BMP File", bmp_path.c_str())
        return false;
    }

    u32 file_size;
    u32 pixel_offset;
    u32 bmp_width;
    u32 bmp_height;
    u16 bpp;

    fread(&file_size, sizeof(u32), 1, file);
    fseek(file, 4, SEEK_CUR);
    fread(&pixel_offset, sizeof(u32), 1, file);
    fseek(file, 4, SEEK_CUR);
    fread(&bmp_width, sizeof(u32), 1, file);
    fread(&bmp_height, sizeof(u32), 1, file);
    fseek(file, 2, SEEK_CUR);
    fread(&bpp, sizeof(u16), 1, file);
    fseek(file, pixel_offset, SEEK_SET);

    int area = bmp_width * bmp_height;
    width = bmp_width;
    height = bmp_height;
    colors = std::vector<Color>(area);
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

        colors[p] = selected_pixel;

        b += bpp / 8;
    }

    delete[] raw_data;
    fclose(file);
    return true;
}
