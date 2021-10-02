#ifndef VERTEX_H
#define VERTEX_H

#include "Vector2.h"
#include "Vector3.h"
#include "Color.h"
#include "TextureCoords.h"

struct Vertex
{
    Vector3 vector;
    Color color;
    TextureCoords texture_coords;
    float texture_id;

    Vertex();
    Vertex(Vector3 vector, Color color);
    Vertex(Vector2 vector, Color color);
    Vertex(Vector3 vector, TextureCoords texture_coords, float texture_id = -1);
    Vertex(Vector2 vector, TextureCoords texture_coords, float texture_id = -1);
    Vertex(Vector3 vector, Color color, TextureCoords texture_coords, float texture_id = -1);
    Vertex(Vector2 vector, Color color, TextureCoords texture_coords, float texture_id = -1);
    Vertex(const Vertex& v);
    
    bool operator==(const Vertex& v) const;
    bool operator!=(const Vertex& v) const;
    void operator=(const Vertex& v);
};
#endif