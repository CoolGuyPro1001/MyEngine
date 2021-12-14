#version 330 core

in vec4 color;
in vec3 uvw;

uniform sampler2DArray model_textures;

out vec4 fragment_color;

void main()
{
    fragment_color = texture(model_textures, uvw) * color;
}

