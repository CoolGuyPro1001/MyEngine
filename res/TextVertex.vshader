#version 330 core
precision highp int;
precision highp float;

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec4 vertex_color;
layout(location = 2) in vec3 vertex_uvw;

out vec4 text_color;
out vec3 uvw;

void main()
{
   gl_Position = vec4(vertex_position, 1.0);
   text_color = vertex_color;
   uvw = vertex_uvw;
}