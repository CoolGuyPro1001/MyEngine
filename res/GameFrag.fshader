#version 330 core

in vec3 normal;
in vec4 color;
in vec3 uvw;
in vec3 fragment_position;

uniform sampler2DArray model_textures;
uniform vec3 light_source_position;
uniform float ambient_factor;
uniform vec3 camera_position;
uniform float specular_factor;
uniform vec3 light_color;

out vec4 fragment_color;

void main()
{
    vec3 ambient = ambient_factor * light_color;

    vec3 light_direction = normalize(light_source_position - fragment_position);
    vec3 diffuse = max(dot(normal, light_direction), 0.0) * light_color;

    vec3 view_direction = normalize(camera_position - fragment_position);
    vec3 reflect_direction = reflect(-light_direction, normal);
    vec3 specular = specular_factor * pow(max(dot(view_direction, reflect_direction), 0.0), 256) * light_color;

    fragment_color = vec4((ambient + diffuse + specular), 1.0) * texture(model_textures, uvw) * color;
    //fragment_color = texture(model_textures, uvw) * color;
}
