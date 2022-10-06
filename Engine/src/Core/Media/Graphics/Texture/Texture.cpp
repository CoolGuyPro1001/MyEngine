#include "Bitmap.h"

#include "../Texture.h"

#include "Common/TextureCoord.h"
#include "Common/Error.h"
#include "Common/Color.h"

std::vector<Shared<ModelTexture>> LoadTextureFile(std::string image_path, uint slice_size)
{
    uint width, height;
    std::vector<Color> model_colors;
    ReadBitmapFile(image_path, model_colors, width, height);

    float ratio = (float) std::max(width, height) / (float) std::min(width, height);

    if(ratio - floor(ratio) != 0)
        CriticalError(ENGINE_ERROR, "Texture Width And Height Ratio Isn't 1 / Width Or 1 / Height\n");

    if(slice_size > width || slice_size > height)
        CriticalError(ENGINE_ERROR, "Slice Size Is Greater Than Either Texture Width Or Height\n");

    float slices_across_width = (float) width / (float) slice_size;
    float slices_across_height = (float) height / (float) slice_size;

    if(slices_across_width - floor(slices_across_width) != 0)
        CriticalError(ENGINE_ERROR, "Non Whole Number Of Slices Per Width (Width / Slice Size != Whole Number)\n");

    if(slices_across_height - floor(slices_across_height) != 0)
        CriticalError(ENGINE_ERROR, "Non Whole Number Of Slices Per Height (Height / Slice Size != Whole Number)\n");

    uint slice_count = slices_across_width * slices_across_height;
    std::vector<Shared<ModelTexture>> model_textures = std::vector<Shared<ModelTexture>>(slice_count);

    std::vector<Color> slice_color_data = std::vector<Color>(slice_size * slice_size);
    for(int s = 0; s < slice_count; s++)
    {
        for(int i = 0; i < slice_color_data.size(); i++)
        {
            //Coordinates For Bottom Left Spot Of Texture Slice
            uint slice_y = slice_size * width * (s / (int) slices_across_width);
            uint slice_x = slice_size * (s % (int) slices_across_width);

            //Coordinates Within The Texture Slice
            uint in_slice_x = width * (i / slice_size);
            uint in_slice_y = i % slice_size;

            slice_color_data[i] = model_colors[slice_y + slice_x + in_slice_x + in_slice_y];
        }
        model_textures[s] = CreateShared<ModelTexture>(s, slice_size, slice_color_data);
    }

    return model_textures;
}
