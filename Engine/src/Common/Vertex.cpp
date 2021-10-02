#include "Vertex.h"

Vertex::Vertex()
{
    texture_id = 0;
}

Vertex::Vertex(const Vertex& v)
{
    vector = v.vector;
    color = v.color;
    texture_coords = v.texture_coords;
    texture_id = v.texture_id;
}

Vertex::Vertex(Vector3 vector, Color color) : color(color), vector(vector)
{
    texture_coords = TextureCoords(0.0f, 0.0f);
    texture_id = -1;
}

Vertex::Vertex(Vector2 vector, Color color) : color(color)
{
    this->vector = Vector3(vector, 0);
    texture_coords = TextureCoords(0.0f, 0.0f);
    texture_id = 0;
}

Vertex::Vertex(Vector3 vector, TextureCoords texture_coords, float texture_id) : 
    vector(vector), texture_coords(texture_coords), texture_id(texture_id)
{
    color = Color(0.0f, 0.0f, 0.0f, 1.0f);
}

Vertex::Vertex(Vector2 vector, TextureCoords texture_coords, float texture_id) : 
    texture_coords(texture_coords), texture_id(texture_id)
{
    this->vector = Vector3(vector, 0);
    color = Color(0.0f, 0.0f, 0.0f, 1.0f);
}

Vertex::Vertex(Vector3 vector, Color color, TextureCoords texture_coords, float texture_id) : 
    color(color), vector(vector), texture_coords(texture_coords), texture_id(texture_id)
{
}

Vertex::Vertex(Vector2 vector, Color color, TextureCoords texture_coords, float texture_id) : 
    color(color), texture_coords(texture_coords), texture_id(texture_id)
{
    this->vector = Vector3(vector, 0);
}

bool Vertex::operator==(const Vertex& v) const
{
    return v.vector == vector && v.color == color && v.texture_coords == texture_coords && v.texture_id == texture_id;
}

bool Vertex::operator!=(const Vertex& v) const
{
    return v.vector != vector || v.color != color || v.texture_coords != texture_coords || v.texture_id != texture_id;
}

void Vertex::operator=(const Vertex& v)
{
    vector = v.vector;
    color = v.color;
    texture_coords = v.texture_coords;
    texture_id = v.texture_id;
}