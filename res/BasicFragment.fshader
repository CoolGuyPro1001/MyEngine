#version 330 core
in vec4 fragment_color;
in vec3 uvw;

uniform sampler2DArray game_textures;

out vec4 color;

void main()
{
   //A texture_id of 0 means no texture, but texture_samplers have texture in depth 0

   if(uvw.z == float(-1))
   {
      color = fragment_color;
   }
   else
   {
      color = texture(game_textures, uvw).rgba;
   }
}