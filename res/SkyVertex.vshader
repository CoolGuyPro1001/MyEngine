#version 330 core

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec4 vertex_color;
layout(location = 2) in vec3 vertex_uvw;

uniform mat4 mvp;

out vec4 color;
out vec3 uvw;

void main()
{
    vec4 position = mvp * vec4(vertex_position, 1.0);
    gl_Position = position.xyww;
    color = vertex_color;
    uvw = vertex_uvw;
}
