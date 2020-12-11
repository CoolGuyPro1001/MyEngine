#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

out vec4 fragment_color;
uniform mat4 mvps[32];

void main()
{
   gl_Position = mvps[gl_InstanceID] * vec4(position, 1.0);
   fragment_color = color;
}

#shader fragment
#version 330 core
in vec4 fragment_color;
out vec4 color;

void main()
{
   color = fragment_color;
}