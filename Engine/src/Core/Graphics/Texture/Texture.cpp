#include "Bitmap.h"

#include "Core/Graphics/Texture.h"
#include "Core/Graphics/Graphics.h"
#include "Core/Graphics/GLDebug.h"

#include "Common/TextureCoord.h"
#include "Common/Error.h"
#include "Common/Color.h"

namespace Texture
{
    static uint texture_id;

    void InitModelTextureArray(std::vector<Shared<ModelTexture>> textures, uint common_size)
    {
        GLCall(glGenTextures(1, &texture_id));
        GLCall(glBindTexture(GL_TEXTURE_2D_ARRAY, texture_id));

        std::vector<Color> all_colors = std::vector<Color>(textures.size() * common_size * common_size);
        auto all_colors_it = all_colors.begin();

        for(Shared<ModelTexture> mt : textures)
        {
            if(mt->size != common_size)
            {
                CriticalErrorArgs(ENGINE_ERROR, "Texture With ID %f Doesn't Have Matching Common Slice Size\nMake Sure Each Texture Slice In Textures Array Has The Same Side Length\n", mt->id);
            }

            for(Color c : mt->color_data)
            {
                *all_colors_it = c;
                all_colors_it++;
            }
        }

        GLCall(glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, common_size, common_size, textures.size(), 0, GL_RGBA, GL_UNSIGNED_BYTE, &all_colors[0]));

        GLCall(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GLCall(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
        GLCall(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    }

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

    void Use(uint shader_program)
    {
        GLCall(glActiveTexture(GL_TEXTURE0));
        GLCall(glBindTexture(GL_TEXTURE_2D_ARRAY, texture_id));

        int tex_uniform_id = glGetUniformLocation(shader_program, "model_textures");
        GLCall(glUniform1i(tex_uniform_id, 0));
    }
}
