#include "OGLTextureManager.h"

#include "OGLDebug.h"

#include "Common/Color.h"
#include "Common/Error.h"

void OGLTextureManager::InitModelTextureArray(std::vector<Shared<ModelTexture>> textures, uint common_size)
{
    GLCall(glGenTextures(1, &m_texture_id));
    GLCall(glBindTexture(GL_TEXTURE_2D_ARRAY, m_texture_id));

    std::vector<Color> all_colors = std::vector<Color>(textures.size() * common_size * common_size);
    auto all_colors_it = all_colors.begin();

    for(Shared<ModelTexture> mt : textures)
    {
        if(mt->size != common_size)
        {
            CriticalErrorArgs(ENGINE_ERROR, "Texture With ID %f Doesn't Have Matching Common Slice Size\n" \
            "Make Sure Each Texture Slice In Textures Array Has The Same Side Length\n", mt->id);
        }

        for(Color c : mt->color_data)
        {
            *all_colors_it = c;
            all_colors_it++;
        }
    }


    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, common_size, common_size, textures.size(), 0, GL_RGBA, GL_UNSIGNED_BYTE, &all_colors[0]);

    GLCall(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
}

void OGLTextureManager::Use(uint shader_program)
{
    GLCall(glActiveTexture(GL_TEXTURE0));
    GLCall(glBindTexture(GL_TEXTURE_2D_ARRAY, m_texture_id));

    int tex_uniform_id = glGetUniformLocation(shader_program, "model_textures");
    GLCall(glUniform1i(tex_uniform_id, 0));
}
