#ifndef VERTEX_H
#define VERTEX_H

#include "Vector3.h"
#include "Color.h"
#include "TextureCoord.h"

struct Vector2;

struct Vertex
{
    Vector3 vector;
    Color color;
    TextureCoord texture_coord;
    float texture_id;

    Vertex();
    Vertex(Vector3 vector, Color color);
    Vertex(Vector2 vector, Color color);
    Vertex(Vector3 vector, TextureCoord texture_coord, float texture_id = 0);
    Vertex(Vector2 vector, TextureCoord texture_coord, float texture_id = 0);
    Vertex(Vector3 vector, Color color, TextureCoord texture_coord, float texture_id = 0);
    Vertex(Vector2 vector, Color color, TextureCoord texture_coord, float texture_id = 0);
    Vertex(const Vertex& v);
    
    bool operator==(const Vertex& v) const;
    bool operator!=(const Vertex& v) const;
    void operator=(const Vertex& v);
};
#endif
