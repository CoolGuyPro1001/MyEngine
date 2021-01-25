#shader vertex
#version 330 core

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec4 vertex_color;
layout(location = 2) in vec2 vertex_uv;

out vec4 fragment_color;
out vec2 uv;
uniform mat4 mvps[32];

void main()
{
   gl_Position = mvps[gl_InstanceID] * vec4(vertex_position, 1.0);
   fragment_color = vertex_color;
   uv = vertex_uv;
}

#shader fragment
#version 330 core
in vec4 fragment_color;
in vec2 uv;

uniform sampler2D texture_sampler;

out vec4 color;

void main()
{
   if(uv.x == 0 && uv.y == 0)
   {
      color = fragment_color;
      return;
   }
   color = texture(texture_sampler, uv).rgba;
}