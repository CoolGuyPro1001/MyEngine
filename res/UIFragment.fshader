#version 330 core
precision highp int;
precision highp float;

in vec4 fragment_color;
in vec3 uvw;

uniform sampler2DArray game_textures;
uniform sampler2D text_textures[32];
uniform bool render_game_textures;

out vec4 color;

void main()
{
   if(uvw.z != float(-1))
   {
      vec4 texel;
      if(render_game_textures)
      {
         texel = texture(game_textures, uvw);
      }
      else
      {
         texel = texture(text_textures[int(mod((uvw.z - float(2)), float(32)))], uvw.xy);
      }

      if(texel.a < 0.5)
         discard;
         
      color = texel;
   }
   else 
   {
      color = fragment_color;
   }
}