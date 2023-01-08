#version 330 core

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec4 vertex_color;
layout(location = 3) in vec3 vertex_uvw;

layout(std140) uniform MVPBlock
{
   mat4 mvps[1024];
};

//For Diffuse Lighting
layout(std140) uniform ModelBlock
{
   mat4 models[1024];
};

uniform int mvp_index;

out vec3 normal;
out vec4 color;
out vec3 uvw;
out vec3 fragment_position;

void main()
{
   gl_Position = mvps[mvp_index + gl_InstanceID] * vec4(vertex_position, 1.0);
   fragment_position = vec3(models[mvp_index + gl_InstanceID] * vec4(vertex_position, 1.0));

   normal = vertex_normal;
   color = vertex_color;
   uvw = vertex_uvw;
}
