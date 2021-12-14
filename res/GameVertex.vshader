#version 330 core

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec4 vertex_color;
layout(location = 2) in vec3 vertex_uvw;

layout(std140) uniform MVPBlock
{
   mat4 mvps[1024];
};

uniform int mvp_index;

out vec4 color;
out vec3 uvw;

void main()
{
   gl_Position = mvps[mvp_index + gl_InstanceID] * vec4(vertex_position, 1.0);

   color = vertex_color;
   uvw = vertex_uvw;
}
