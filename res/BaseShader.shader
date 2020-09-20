#shader vertex
#version 330 core

layout(location = 0) in vec3 position_model_space;
layout(location = 1) in vec4 color_model_space;

out vec4 fragment_color;
uniform mat4 MVP;

void main()
{
   gl_Position = MVP * vec4(position_model_space, 1);
   fragment_color = color_model_space;
}

#shader fragment
#version 330 core
in vec4 fragment_color;
out vec4 color;

void main()
{
   color = fragment_color;
}