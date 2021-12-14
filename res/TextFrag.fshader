#version 330 core
precision highp int;
precision highp float;

in vec4 text_color;
in vec3 uvw;

uniform sampler2D text_textures[32];

out vec4 color;

void main()
{
   vec4 texel = texture(text_textures[int(mod(uvw.z - float(2), float(32)))], uvw.xy);
   vec4 sample = vec4(1.0, 1.0, 1.0, texel.r);

   color = text_color * sample;
}