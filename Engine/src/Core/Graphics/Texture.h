#ifndef TEXTURE_H
#define TEXTURE_H

//Sky Textures
//Model Textures
//Font Textures

//Image To Color Functions
//TODO png, gif, jpeg

//All Model Textures Are Stored In Same File, And Loaded Into Same Texture Object

struct TextureCoord;
struct Color;

struct ModelTexture
{
    ModelTexture(float id, uint size, std::vector<Color> colors);
    ~ModelTexture();

    float id;
    uint size;
    std::vector<Color> color_data;
};

namespace Texture
{
    using ::ModelTexture;

    std::vector<Shared<ModelTexture>> LoadTextureFile(std::string image_path, uint slice_size);
    void InitModelTextureArray(std::vector<Shared<ModelTexture>> textures, uint common_size);

    void Use(uint shader_program);
}

/*class FontTexture : public Texture
{
public:
    Texture();
    Texture(std::string image_path);
    Texture(std::vector<Color> data);
    ~Texture();

    static void SetParameter(uint pname, int param);
    static void Use(uint shader_program);

private:
    std::vector<Color> texture_data;
    uint id;
};*/
#endif
