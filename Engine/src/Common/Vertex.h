#ifndef VERTEX_H
#define VERTEX_H

#include "Color.h"
#include "TextureCoord.h"
#include "Vector3.h"

struct Vector2;

struct Vertex
{
    Vector3 vector;
    Vector3 normal;
    Color color;
    TextureCoord texture_coord;

    Vertex();
    Vertex(Vector3 vector, Vector3 normal, Color color);
    Vertex(Vector2 vector, Vector3 normal, Color color);
    Vertex(Vector3 vector, Vector3 normal, TextureCoord texture_coord);
    Vertex(Vector2 vector, Vector3 normal, TextureCoord texture_coord);
    Vertex(Vector3 vector, Vector3 normal, Color color, TextureCoord texture_coord);
    Vertex(Vector2 vector, Vector3 normal, Color color, TextureCoord texture_coord);
    Vertex(const Vertex& v);
    
    bool operator==(const Vertex& v) const;
    bool operator!=(const Vertex& v) const;
    void operator=(const Vertex& v);
};
#endif
