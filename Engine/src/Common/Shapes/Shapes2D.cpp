#include "Common/Shapes.h"

#include "Common/Vector2.h"
#include "Common/Vertex.h"

std::array<Vertex, 6> Square(float size, float z_depth, Color color)
{
    Vector2 bottom_left_corner = Vector2(-size / 2, -size / 2);
    std::array<Vertex, 6> vertices;

    vertices[0] = Vertex(Vector3(bottom_left_corner, z_depth), color);
    vertices[1] = Vertex(Vector3(bottom_left_corner + Vector2(size, 0), z_depth), color);
    vertices[2] = Vertex(Vector3(bottom_left_corner + Vector2(size, size), z_depth), color);
    vertices[3] = Vertex(Vector3(bottom_left_corner, z_depth), color);
    vertices[4] = Vertex(Vector3(bottom_left_corner + Vector2(0, size), z_depth), color);
    vertices[5] = Vertex(Vector3(bottom_left_corner + Vector2(size, size), z_depth), color);

    return vertices;
}

std::array<Vertex, 6> Square(float size, float z_depth, Vector3 normal, TextureCoord tex_coord)
{
    Vector2 bottom_left_corner = Vector2(-size / 2, -size / 2);
    std::array<Vertex, 6> vertices;

    vertices[0] = Vertex(Vector3(bottom_left_corner, z_depth), normal, tex_coord);
    vertices[1] = Vertex(Vector3(bottom_left_corner + Vector2(size, 0), z_depth), normal, tex_coord);
    vertices[2] = Vertex(Vector3(bottom_left_corner + Vector2(size, size), normal, z_depth), tex_coord);
    vertices[3] = Vertex(Vector3(bottom_left_corner, z_depth), normal, tex_coord);
    vertices[4] = Vertex(Vector3(bottom_left_corner + Vector2(0, size), z_depth), normal, tex_coord);
    vertices[5] = Vertex(Vector3(bottom_left_corner + Vector2(size, size), z_depth), normal, tex_coord);

    return vertices;
}

std::array<Vertex, 6> Square(float size, float z_depth, std::array<Color, 6> colors)
{
    Vector2 bottom_left_corner = Vector2(-size / 2, -size / 2);
    std::array<Vertex, 6> vertices;

    vertices[0] = Vertex(Vector3(bottom_left_corner, z_depth), colors[0]);
    vertices[1] = Vertex(Vector3(bottom_left_corner + Vector2(size, 0), z_depth), colors[1]);
    vertices[2] = Vertex(Vector3(bottom_left_corner + Vector2(size, size), z_depth), colors[2]);
    vertices[3] = Vertex(Vector3(bottom_left_corner, z_depth), colors[3]);
    vertices[4] = Vertex(Vector3(bottom_left_corner + Vector2(0, size), z_depth), colors[4]);
    vertices[5] = Vertex(Vector3(bottom_left_corner + Vector2(size, size), z_depth), colors[5]);

    return vertices;
}

std::array<Vertex, 6> Square(float size, float z_depth, std::array<TextureCoord, 6> tex_coords)
{
    Vector2 bottom_left_corner = Vector2(-size / 2, -size / 2);
    std::array<Vertex, 6> vertices;

    vertices[0] = Vertex(Vector3(bottom_left_corner, z_depth), tex_coords[0]);
    vertices[1] = Vertex(Vector3(bottom_left_corner + Vector2(size, 0), z_depth), tex_coords[1]);
    vertices[2] = Vertex(Vector3(bottom_left_corner + Vector2(size, size), z_depth), tex_coords[2]);
    vertices[3] = Vertex(Vector3(bottom_left_corner, z_depth), tex_coords[3]);
    vertices[4] = Vertex(Vector3(bottom_left_corner + Vector2(0, size), z_depth), tex_coords[4]);
    vertices[5] = Vertex(Vector3(bottom_left_corner + Vector2(size, size), z_depth), tex_coords[5]);

    return vertices;
}

std::array<Vertex, 6> Square(float size, float z_depth, Color color, std::array<TextureCoord, 6> tex_coords)
{
    Vector2 bottom_left_corner = Vector2(-size / 2, -size / 2);
    std::array<Vertex, 6> vertices;

    vertices[0] = Vertex(Vector3(bottom_left_corner, z_depth), color, tex_coords[0]);
    vertices[1] = Vertex(Vector3(bottom_left_corner + Vector2(size, 0), z_depth), color, tex_coords[1]);
    vertices[2] = Vertex(Vector3(bottom_left_corner + Vector2(size, size), z_depth), color, tex_coords[2]);
    vertices[3] = Vertex(Vector3(bottom_left_corner, z_depth), color, tex_coords[3]);
    vertices[4] = Vertex(Vector3(bottom_left_corner + Vector2(0, size), z_depth), color, tex_coords[4]);
    vertices[5] = Vertex(Vector3(bottom_left_corner + Vector2(size, size), z_depth), color, tex_coords[5]);

    return vertices;
}

std::array<Vertex, 6> Rectangle(float width, float height, float z_depth, Color color)
{
    Vector2 bottom_left_corner = Vector2(-width / 2, -height / 2);
    std::array<Vertex, 6> vertices;

    vertices[0] = Vertex(Vector3(bottom_left_corner, z_depth), color);
    vertices[1] = Vertex(Vector3(bottom_left_corner + Vector2(width, 0), z_depth), color);
    vertices[2] = Vertex(Vector3(bottom_left_corner + Vector2(width, height), z_depth), color);
    vertices[3] = Vertex(Vector3(bottom_left_corner, z_depth), color);
    vertices[4] = Vertex(Vector3(bottom_left_corner + Vector2(0, height), z_depth), color);
    vertices[5] = Vertex(Vector3(bottom_left_corner + Vector2(width, height), z_depth), color);

    return vertices;
}

std::array<Vertex, 6> Rectangle(float width, float height, float z_depth, TextureCoord tex_coord)
{
    Vector2 bottom_left_corner = Vector2(-width / 2, -height / 2);
    std::array<Vertex, 6> vertices;

    vertices[0] = Vertex(Vector3(bottom_left_corner, z_depth), tex_coord);
    vertices[1] = Vertex(Vector3(bottom_left_corner + Vector2(width, 0), z_depth), tex_coord);
    vertices[2] = Vertex(Vector3(bottom_left_corner + Vector2(width, height), z_depth), tex_coord);
    vertices[3] = Vertex(Vector3(bottom_left_corner, z_depth), tex_coord);
    vertices[4] = Vertex(Vector3(bottom_left_corner + Vector2(0, height), z_depth), tex_coord);
    vertices[5] = Vertex(Vector3(bottom_left_corner + Vector2(width, height), z_depth), tex_coord);

    return vertices;
}

std::array<Vertex, 6> Rectangle(float width, float height, float z_depth, std::array<Color, 6> colors)
{
    Vector2 bottom_left_corner = Vector2(-width / 2, -height / 2);
    std::array<Vertex, 6> vertices;

    vertices[0] = Vertex(Vector3(bottom_left_corner, z_depth), colors[0]);
    vertices[1] = Vertex(Vector3(bottom_left_corner + Vector2(width, 0), z_depth), colors[1]);
    vertices[2] = Vertex(Vector3(bottom_left_corner + Vector2(width, height), z_depth), colors[2]);
    vertices[3] = Vertex(Vector3(bottom_left_corner, z_depth), colors[3]);
    vertices[4] = Vertex(Vector3(bottom_left_corner + Vector2(0, height), z_depth), colors[4]);
    vertices[5] = Vertex(Vector3(bottom_left_corner + Vector2(width, height), z_depth), colors[5]);

    return vertices;
}

std::array<Vertex, 6> Rectangle(float width, float height, float z_depth, std::array<TextureCoord, 6> tex_coords)
{
    Vector2 bottom_left_corner = Vector2(-width / 2, -height / 2);
    std::array<Vertex, 6> vertices;

    vertices[0] = Vertex(Vector3(bottom_left_corner, z_depth), tex_coords[0]);
    vertices[1] = Vertex(Vector3(bottom_left_corner + Vector2(width, 0), z_depth), tex_coords[1]);
    vertices[2] = Vertex(Vector3(bottom_left_corner + Vector2(width, height), z_depth), tex_coords[2]);
    vertices[3] = Vertex(Vector3(bottom_left_corner, z_depth), tex_coords[3]);
    vertices[4] = Vertex(Vector3(bottom_left_corner + Vector2(0, height), z_depth), tex_coords[4]);
    vertices[5] = Vertex(Vector3(bottom_left_corner + Vector2(width, height), z_depth), tex_coords[5]);

    return vertices;
}

std::array<Vertex, 6> Rectangle(float width, float height, float z_depth, Color color, std::array<TextureCoord, 6> tex_coords)
{
    Vector2 bottom_left_corner = Vector2(-width / 2, -height / 2);
    std::array<Vertex, 6> vertices;

    vertices[0] = Vertex(Vector3(bottom_left_corner, z_depth), color, tex_coords[0]);
    vertices[1] = Vertex(Vector3(bottom_left_corner + Vector2(width, 0), z_depth), color, tex_coords[1]);
    vertices[2] = Vertex(Vector3(bottom_left_corner + Vector2(width, height), z_depth), color, tex_coords[2]);
    vertices[3] = Vertex(Vector3(bottom_left_corner, z_depth), color, tex_coords[3]);
    vertices[4] = Vertex(Vector3(bottom_left_corner + Vector2(0, height), z_depth), color, tex_coords[4]);
    vertices[5] = Vertex(Vector3(bottom_left_corner + Vector2(width, height), z_depth), color, tex_coords[5]);

    return vertices;
}
