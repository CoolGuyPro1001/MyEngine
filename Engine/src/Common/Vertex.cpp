#include "Vertex.h"
#include "Vector2.h"

Vertex::Vertex()
{
    texture_coord.w = 0.0f;
}

Vertex::Vertex(const Vertex& v)
{
    vector = v.vector;
    normal = v.normal;
    color = v.color;
    texture_coord = v.texture_coord;
}

Vertex::Vertex(Vector3 vector, Vector3 normal, Color color) : vector(vector), normal(normal), color(color)
{
    texture_coord = TextureCoord(0.0f, 0.0f, 0.0f);
}

Vertex::Vertex(Vector2 vector, Vector3 normal, Color color) : normal(normal), color(color)
{
    this->vector = Vector3(vector, 0);
    texture_coord = TextureCoord(0.0f, 0.0f, 0.0f);
}

Vertex::Vertex(Vector3 vector, Vector3 normal, TextureCoord texture_coord) :
    vector(vector), normal(normal), texture_coord(texture_coord)
{
    color = Color(0xff, 0xff, 0xff, 0xff);
}

Vertex::Vertex(Vector2 vector, Vector3 normal, TextureCoord texture_coord) :
    normal(normal), texture_coord(texture_coord)
{
    this->vector = Vector3(vector, 0);
    color = Color(0xff, 0xff, 0xff, 0xff);
}

Vertex::Vertex(Vector3 vector, Vector3 normal, Color color, TextureCoord texture_coord) :
    vector(vector), normal(normal), color(color), texture_coord(texture_coord)
{
}

Vertex::Vertex(Vector2 vector, Vector3 normal, Color color, TextureCoord texture_coord) :
     normal(normal), color(color), texture_coord(texture_coord)
{
    this->vector = Vector3(vector, 0);
}

bool Vertex::operator==(const Vertex& v) const
{
    return v.vector == vector && v.normal == normal && v.color == color && v.texture_coord == texture_coord;
}

bool Vertex::operator!=(const Vertex& v) const
{
    return v.vector != vector || v.normal != normal || v.color != color || v.texture_coord != texture_coord;
}

void Vertex::operator=(const Vertex& v)
{
    vector = v.vector;
    normal = v.normal;
    color = v.color;
    texture_coord = v.texture_coord;
}
