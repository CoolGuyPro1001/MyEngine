#include "Common/Shapes.h"

#include "Common/Color.h"
#include "Common/TextureCoord.h"
#include "Common/Vector3.h"
#include "Common/Vertex.h"

#include "Components/ModelComponent.h"

std::vector<Vertex> Triangle(Vector3 p0, Vector3 p1, Vector3 p2, Color color, std::vector<Vertex>& shape, size_t shape_index)
{
    std::vector<Vertex> vertices = std::vector<Vertex>(3);

    vertices[0] = Vertex(p0, color);
    vertices[1] = Vertex(p1, color);
    vertices[2] = Vertex(p2, color);

    shape[shape_index] = Vertex(p0, color);
    shape[shape_index + 1] = Vertex(p1, color);
    shape[shape_index + 2] = Vertex(p2, color);

    return vertices;
}

std::vector<Vertex> Triangle(Vector3 p0, Vector3 p1, Vector3 p2, TextureCoord uv0, TextureCoord uv1,
    TextureCoord uv2, uint texture_id, std::vector<Vertex>& shape, size_t shape_index)
{
    std::vector<Vertex> vertices = std::vector<Vertex>(3);

    vertices[0] = Vertex(p0, uv0, texture_id);
    vertices[1] = Vertex(p1, uv1, texture_id);
    vertices[2] = Vertex(p2, uv2, texture_id);

    shape[shape_index] = Vertex(p0, uv0, texture_id);
    shape[shape_index + 1] = Vertex(p1, uv1, texture_id);
    shape[shape_index + 2] = Vertex(p2, uv2, texture_id);

    return vertices;
}

//TODO: Give circle an angle by using normals
std::vector<Vertex> Circle(float radius, int triangles, Color color, std::vector<Vertex>& shape, size_t shape_index)
{
    std::vector<Vertex> circle = std::vector<Vertex>(triangles * 3);
    Vector3 center = Vector3(0, 0, 0);
    Vector3 first_point;
    Vector3 second_point;
    float radian = 0;

    int i = 0;
    while(i < triangles)
    {
        first_point.x = cos(radian) * radius;
        first_point.y = sin(radian) * radius;

        radian += (2 * M_PI) / triangles;
        second_point.x = cos(radian) * radius;
        second_point.y = sin(radian) * radius;

        Triangle(center, first_point, second_point, color, circle, i * 3);
        shape[shape_index] = Vertex(center, color);
        shape[shape_index + 1] = Vertex(first_point, color);
        shape[shape_index + 2] = Vertex(second_point, color);

        i++;
    }

    return circle;
};

Shared<CModel> Cube(float size, Color front, Color back, Color left, Color right, Color top, Color bottom,
    Vector3 origin)
{
    std::vector<Vertex> vertices = std::vector<Vertex>(36);

    const Vector3 X = origin + Vector3(size, 0, 0);
    const Vector3 Y = origin + Vector3(0, size, 0);
    const Vector3 Z = origin + Vector3(0, 0, size);
    const Vector3 XY = origin + Vector3(size, size, 0);
    const Vector3 XZ = origin + Vector3(size, 0, size);
    const Vector3 YZ = origin + Vector3(0, size, size);
    const Vector3 XYZ = origin + Vector3(size, size, size);

    Triangle(origin, X, XY, front, vertices, 0);
    Triangle(origin, Y, XY, front, vertices, 3);

    Triangle(Z, XZ, XYZ, back, vertices, 6);
    Triangle(Z, YZ, XYZ, back, vertices, 9);

    Triangle(X, XZ, XYZ, right, vertices, 12);
    Triangle(X, XY, XYZ, right, vertices, 15);

    Triangle(origin, Y, YZ, left, vertices, 18);
    Triangle(origin, Z, YZ, left, vertices ,21);

    Triangle(Y, YZ, XYZ, top, vertices, 24);
    Triangle(Y, XY, XYZ, top, vertices, 27);

    Triangle(origin, Z, XZ, bottom, vertices, 30);
    Triangle(origin, X, XZ, bottom, vertices, 33);

    Shared<CModel> cube = CreateShared<CModel>(vertices);
    return cube;
}

Shared<CModel> Cube(float size,
    Shared<ModelTexture> front, Shared<ModelTexture> back,
    Shared<ModelTexture> left, Shared<ModelTexture> right,
    Shared<ModelTexture> top, Shared<ModelTexture> bottom,
    Vector3 origin)
{
    std::vector<Vertex> vertices = std::vector<Vertex>(36);

    const Vector3 X = origin + Vector3(size, 0, 0);
    const Vector3 Y = origin + Vector3(0, size, 0);
    const Vector3 Z = origin + Vector3(0, 0, size);
    const Vector3 XY = origin + Vector3(size, size, 0);
    const Vector3 XZ = origin + Vector3(size, 0, size);
    const Vector3 YZ = origin + Vector3(0, size, size);
    const Vector3 XYZ = origin + Vector3(size, size, size);

    const TextureCoord bottom_left = TextureCoord(0.0, 0.0);
    const TextureCoord bottom_right = TextureCoord(1.0, 0.0);
    const TextureCoord top_left = TextureCoord(0.0, 1.0);
    const TextureCoord top_right = TextureCoord(1.0, 1.0);

    //Front
    Triangle(origin, X, XY, bottom_left, bottom_right, top_right, 0, vertices, 0);
    Triangle(origin, Y, XY, bottom_left, top_left, top_right, 0, vertices, 3);

    //Back
    Triangle(Z, XZ, XYZ, bottom_right, bottom_left, top_left, 1, vertices, 6);
    Triangle(Z, YZ, XYZ, bottom_right, top_right, top_left, 1, vertices, 9);

    //Right
    Triangle(X, XZ, XYZ, bottom_left, bottom_right, top_right, 2, vertices, 12);
    Triangle(X, XY, XYZ, bottom_left, top_left, top_right, 2, vertices, 15);

    //Left
    Triangle(origin, Y, YZ, bottom_right, top_right, top_left, 3, vertices, 18);
    Triangle(origin, Z, YZ, bottom_right, bottom_left, top_left, 3, vertices ,21);

    //Top
    Triangle(Y, YZ, XYZ, bottom_left, top_left, top_right, 4, vertices, 24);
    Triangle(Y, XY, XYZ, bottom_left, bottom_right, top_right, 4, vertices, 27);

    //Bottom
    Triangle(origin, Z, XZ, top_left, bottom_left, bottom_right, 5, vertices, 30);
    Triangle(origin, X, XZ, top_left, top_right, bottom_right, 5, vertices, 33);

    Shared<CModel> cube = CreateShared<CModel>(vertices, std::vector{front, back, right, left, top, bottom});
    return cube;
}

Shared<CModel> Prism(float x, float y, float z, Color color, Vector3 origin)
{
    std::vector<Vertex> vertices = std::vector<Vertex>(36);

    const Vector3 X = origin + Vector3(x, 0, 0);
    const Vector3 Y = origin + Vector3(0, y, 0);
    const Vector3 Z = origin + Vector3(0, 0, z);
    const Vector3 XY = origin + Vector3(x, y, 0);
    const Vector3 XZ = origin + Vector3(x, 0, z);
    const Vector3 YZ = origin + Vector3(0, y, z);
    const Vector3 XYZ = origin + Vector3(x, y, z);

    //Front Side
    Triangle(origin, X, XY, color, vertices, 0);
    Triangle(origin, Y, XY, color, vertices, 3);

    //Back Side
    Triangle(Z, XZ, XYZ, color, vertices, 6);
    Triangle(Z, YZ, XYZ, color, vertices, 9);

    //Right Side
    Triangle(X, XZ, XYZ, color, vertices, 12);
    Triangle(X, XY, XYZ, color, vertices, 15);

    //Left Side
    Triangle(origin, Y, YZ, color, vertices, 18);
    Triangle(origin, Z, YZ, color, vertices ,21);

    //Top Side
    Triangle(Y, YZ, XYZ, color, vertices, 24);
    Triangle(Y, YZ, XYZ, color, vertices, 27);

    //Bottom Side
    Triangle(origin, Z, XZ, color, vertices, 30);
    Triangle(origin, X, XZ, color, vertices, 33);

    Shared<CModel> prism = CreateShared<CModel>(vertices);
    return prism;
}

Shared<CModel> Prism(float x, float y, float z,
    Shared<ModelTexture> front, Shared<ModelTexture> back,
    Shared<ModelTexture> left, Shared<ModelTexture> right,
    Shared<ModelTexture> top, Shared<ModelTexture> bottom,
    Vector3 origin)
{
    std::vector<Vertex> vertices = std::vector<Vertex>(36);

    const Vector3 X = origin + Vector3(x, 0, 0);
    const Vector3 Y = origin + Vector3(0, y, 0);
    const Vector3 Z = origin + Vector3(0, 0, z);
    const Vector3 XY = origin + Vector3(x, y, 0);
    const Vector3 XZ = origin + Vector3(x, 0, z);
    const Vector3 YZ = origin + Vector3(0, y, z);
    const Vector3 XYZ = origin + Vector3(x, y, z);

    const TextureCoord bottom_left = TextureCoord(0.0, 0.0);
    const TextureCoord bottom_right = TextureCoord(1.0, 0.0);
    const TextureCoord top_left = TextureCoord(0.0, 1.0);
    const TextureCoord top_right = TextureCoord(1.0, 1.0);

    //Front
    Triangle(origin, X, XY, bottom_left, bottom_right, top_right, 0, vertices, 0);
    Triangle(origin, Y, XY, bottom_left, top_left, top_right, 0, vertices, 3);

    //Back
    Triangle(Z, XZ, XYZ, bottom_right, bottom_left, top_left, 1, vertices, 6);
    Triangle(Z, YZ, XYZ, bottom_right, top_right, top_left, 1, vertices, 9);

    //Right
    Triangle(X, XZ, XYZ, bottom_left, bottom_right, top_right, 2, vertices, 12);
    Triangle(X, XY, XYZ, bottom_left, top_left, top_right, 2, vertices, 15);

    //Left
    Triangle(origin, Y, YZ, bottom_right, top_right, top_left, 3, vertices, 18);
    Triangle(origin, Z, YZ, bottom_right, bottom_left, top_left, 3, vertices ,21);

    //Top
    Triangle(Y, YZ, XYZ, bottom_left, top_left, top_right, 4, vertices, 24);
    Triangle(Y, XY, XYZ, bottom_left, bottom_right, top_right, 4, vertices, 27);

    //Bottom
    Triangle(origin, Z, XZ, top_left, bottom_left, bottom_right, 5, vertices, 30);
    Triangle(origin, X, XZ, top_left, top_right, bottom_right, 5, vertices, 33);

    Shared<CModel> prism = CreateShared<CModel>(vertices, std::vector{front, back, right, left, top, bottom});
    return prism;
}

Shared<CModel> Pyramid4(Vector3 a, Vector3 b, Vector3 c, Vector3 d, Color color)
{
    std::vector<Vertex> vertices = std::vector<Vertex>(0);

    Triangle(a, b, c, color, vertices, 0);
    Triangle(a, b, d, color, vertices, 3);
    Triangle(a, c, d, color, vertices, 6);
    Triangle(b, c, d, color, vertices, 9);

    Shared<CModel> pyramid = CreateShared<CModel>(vertices);
    return pyramid;
}

Shared<CModel> Cylinder(float radius, float height, int triangles, Color color)
{
    std::vector<Vertex> vertices = std::vector<Vertex>(triangles * 24);
    Circle(radius, triangles, color, vertices, 0);
    Circle(radius, triangles, color, vertices, 24);

    int i = 0;
    while(i < triangles)
    {
        Triangle(vertices[i + 1].vector, vertices[i + 2].vector, vertices[i + 25].vector, color, vertices, i + 48);
        Triangle(vertices[i + 1].vector, vertices[i + 2].vector, vertices[i + 26].vector, color, vertices, i + 49);
        i++;
    }

    Shared<CModel> cylinder = CreateShared<CModel>(vertices);
    return cylinder;
}
