#include "Common/Shapes.h"
#include "Common/Vector2.h"
#include "Common/Vertex.h"

std::array<Vertex, 6> Square(Vector2 origin, float size, float z_depth, Color color)
{
    std::array<Vertex, 6> vertices;
    vertices[0] = Vertex(Vector3(origin, z_depth), color);
    vertices[1] = Vertex(Vector3(origin + Vector2(size, 0), z_depth), color);
    vertices[2] = Vertex(Vector3(origin + Vector2(size, size), z_depth), color);
    vertices[3] = Vertex(Vector3(origin, z_depth), color);
    vertices[4] = Vertex(Vector3(origin + Vector2(0, size), z_depth), color);
    vertices[5] = Vertex(Vector3(origin + Vector2(size, size), z_depth), color);

    return vertices;
}

std::array<Vertex, 6> Square(Vector2 origin, float size, float z_depth, TextureCoord uv, uint tex_id)
{
    std::array<Vertex, 6> vertices;
    vertices[0] = Vertex(Vector3(origin, z_depth), uv, tex_id);
    vertices[1] = Vertex(Vector3(origin + Vector2(size, 0), z_depth), uv, tex_id);
    vertices[2] = Vertex(Vector3(origin + Vector2(size, size), z_depth), uv, tex_id);
    vertices[3] = Vertex(Vector3(origin, z_depth), uv, tex_id);
    vertices[4] = Vertex(Vector3(origin + Vector2(0, size), z_depth), uv, tex_id);
    vertices[5] = Vertex(Vector3(origin + Vector2(size, size), z_depth), uv, tex_id);

    return vertices;
}

std::array<Vertex, 6> Square(Vector2 origin, float size, float z_depth, std::array<Color, 6> colors)
{
    std::array<Vertex, 6> vertices;
    vertices[0] = Vertex(Vector3(origin, z_depth), colors[0]);
    vertices[1] = Vertex(Vector3(origin + Vector2(size, 0), z_depth), colors[1]);
    vertices[2] = Vertex(Vector3(origin + Vector2(size, size), z_depth), colors[2]);
    vertices[3] = Vertex(Vector3(origin, z_depth), colors[3]);
    vertices[4] = Vertex(Vector3(origin + Vector2(0, size), z_depth), colors[4]);
    vertices[5] = Vertex(Vector3(origin + Vector2(size, size), z_depth), colors[5]);

    return vertices;
}

std::array<Vertex, 6> Square(Vector2 origin, float size, float z_depth,
    std::array<TextureCoord, 6> uv, uint tex_id)
{
    std::array<Vertex, 6> vertices;
    vertices[0] = Vertex(Vector3(origin, z_depth), uv[0], tex_id);
    vertices[1] = Vertex(Vector3(origin + Vector2(size, 0), z_depth), uv[1], tex_id);
    vertices[2] = Vertex(Vector3(origin + Vector2(size, size), z_depth), uv[2], tex_id);
    vertices[3] = Vertex(Vector3(origin, z_depth), uv[3], tex_id);
    vertices[4] = Vertex(Vector3(origin + Vector2(0, size), z_depth), uv[4], tex_id);
    vertices[5] = Vertex(Vector3(origin + Vector2(size, size), z_depth), uv[5], tex_id);

    return vertices;
}

std::array<Vertex, 6> Square(Vector2 origin, float size, float z_depth, Color color,
    std::array<TextureCoord, 6> uv, u16 tex_id)
{
    std::array<Vertex, 6> vertices;
    vertices[0] = Vertex(Vector3(origin, z_depth), color, uv[0], tex_id);
    vertices[1] = Vertex(Vector3(origin + Vector2(size, 0), z_depth), color, uv[1], tex_id);
    vertices[2] = Vertex(Vector3(origin + Vector2(size, size), z_depth), color, uv[2], tex_id);
    vertices[3] = Vertex(Vector3(origin, z_depth), color, uv[3], tex_id);
    vertices[4] = Vertex(Vector3(origin + Vector2(0, size), z_depth), color, uv[4], tex_id);
    vertices[5] = Vertex(Vector3(origin + Vector2(size, size), z_depth), color, uv[5], tex_id);

    return vertices;
}

std::array<Vertex, 6> Rectangle(Vector2 origin, float width, float height, float z_depth, Color color)
{
    std::array<Vertex, 6> vertices;
    vertices[0] = Vertex(Vector3(origin, z_depth), color);
    vertices[1] = Vertex(Vector3(origin + Vector2(width, 0), z_depth), color);
    vertices[2] = Vertex(Vector3(origin + Vector2(width, height), z_depth), color);
    vertices[3] = Vertex(Vector3(origin, z_depth), color);
    vertices[4] = Vertex(Vector3(origin + Vector2(0, height), z_depth), color);
    vertices[5] = Vertex(Vector3(origin + Vector2(width, height), z_depth), color);

    return vertices;
}

std::array<Vertex, 6> Rectangle(Vector2 origin, float width, float height, float z_depth, TextureCoord uv, uint tex_id)
{
    std::array<Vertex, 6> vertices;
    vertices[0] = Vertex(Vector3(origin, z_depth), uv, tex_id);
    vertices[1] = Vertex(Vector3(origin + Vector2(width, 0), z_depth), uv, tex_id);
    vertices[2] = Vertex(Vector3(origin + Vector2(width, height), z_depth), uv, tex_id);
    vertices[3] = Vertex(Vector3(origin, z_depth), uv, tex_id);
    vertices[4] = Vertex(Vector3(origin + Vector2(0, height), z_depth), uv, tex_id);
    vertices[5] = Vertex(Vector3(origin + Vector2(width, height), z_depth), uv, tex_id);

    return vertices;
}

std::array<Vertex, 6> Rectangle(Vector2 origin, float width, float height, float z_depth, std::array<Color, 6> colors)
{
    std::array<Vertex, 6> vertices;
    vertices[0] = Vertex(Vector3(origin, z_depth), colors[0]);
    vertices[1] = Vertex(Vector3(origin + Vector2(width, 0), z_depth), colors[1]);
    vertices[2] = Vertex(Vector3(origin + Vector2(width, height), z_depth), colors[2]);
    vertices[3] = Vertex(Vector3(origin, z_depth), colors[3]);
    vertices[4] = Vertex(Vector3(origin + Vector2(0, height), z_depth), colors[4]);
    vertices[5] = Vertex(Vector3(origin + Vector2(width, height), z_depth), colors[5]);

    return vertices;
}

std::array<Vertex, 6> Rectangle(Vector2 origin, float width, float height, float z_depth,
    std::array<TextureCoord, 6> uv, uint tex_id)
{
    std::array<Vertex, 6> vertices;
    vertices[0] = Vertex(Vector3(origin, z_depth), uv[0], tex_id);
    vertices[1] = Vertex(Vector3(origin + Vector2(width, 0), z_depth), uv[1], tex_id);
    vertices[2] = Vertex(Vector3(origin + Vector2(width, height), z_depth), uv[2], tex_id);
    vertices[3] = Vertex(Vector3(origin, z_depth), uv[3], tex_id);
    vertices[4] = Vertex(Vector3(origin + Vector2(0, height), z_depth), uv[4], tex_id);
    vertices[5] = Vertex(Vector3(origin + Vector2(width, height), z_depth), uv[5], tex_id);

    return vertices;
}

std::array<Vertex, 6> Rectangle(Vector2 origin, float width, float height, float z_depth, Color color,
    std::array<TextureCoord, 6> uv, u16 tex_id)
{
    std::array<Vertex, 6> vertices;
    vertices[0] = Vertex(Vector3(origin, z_depth), color, uv[0], tex_id);
    vertices[1] = Vertex(Vector3(origin + Vector2(width, 0), z_depth), color, uv[1], tex_id);
    vertices[2] = Vertex(Vector3(origin + Vector2(width, height), z_depth), color, uv[2], tex_id);
    vertices[3] = Vertex(Vector3(origin, z_depth), color, uv[3], tex_id);
    vertices[4] = Vertex(Vector3(origin + Vector2(0, height), z_depth), color, uv[4], tex_id);
    vertices[5] = Vertex(Vector3(origin + Vector2(width, height), z_depth), color, uv[5], tex_id);

    return vertices;
}
