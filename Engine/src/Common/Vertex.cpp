#include "Vertex.h"
#include "Vector2.h"

Vertex::Vertex()
{
    texture_id = false;
}

Vertex::Vertex(const Vertex& v)
{
    vector = v.vector;
    color = v.color;
    texture_coord = v.texture_coord;
    texture_id = v.texture_id;
}

Vertex::Vertex(Vector3 vector, Color color) : color(color), vector(vector)
{
    texture_coord = TextureCoord(0.0f, 0.0f);
    texture_id = false;
}

Vertex::Vertex(Vector2 vector, Color color) : color(color)
{
    this->vector = Vector3(vector, 0);
    texture_coord = TextureCoord(0.0f, 0.0f);
    texture_id = false;
}

Vertex::Vertex(Vector3 vector, TextureCoord texture_coord, float texture_id) :
    vector(vector), texture_coord(texture_coord), texture_id(texture_id)
{
    color = Color(255, 255, 255, 255);
}

Vertex::Vertex(Vector2 vector, TextureCoord texture_coord, float texture_id) :
    texture_coord(texture_coord), texture_id(texture_id)
{
    this->vector = Vector3(vector, 0);
    color = Color(255, 255, 255, 255);
}

Vertex::Vertex(Vector3 vector, Color color, TextureCoord texture_coord, float texture_id) :
    color(color), vector(vector), texture_coord(texture_coord), texture_id(texture_id)
{
}

Vertex::Vertex(Vector2 vector, Color color, TextureCoord texture_coord, float texture_id) :
    color(color), texture_coord(texture_coord), texture_id(texture_id)
{
    this->vector = Vector3(vector, 0);
}

bool Vertex::operator==(const Vertex& v) const
{
    return v.vector == vector && v.color == color && v.texture_coord == texture_coord && v.texture_id == texture_id;
}

bool Vertex::operator!=(const Vertex& v) const
{
    return v.vector != vector || v.color != color || v.texture_coord != texture_coord || v.texture_id != texture_id;
}

void Vertex::operator=(const Vertex& v)
{
    vector = v.vector;
    color = v.color;
    texture_coord = v.texture_coord;
    texture_id = v.texture_id;
}
