#ifndef SHAPES_H
#define SHAPES_H

#include "Common/Units.h"

//Shape and shape_index are for setting triangles of different vertices

template<class V>
std::vector<Vertex> Triangle(V a, V b, V c, Color color, std::vector<Vertex>& shape, size_t shape_index)
{
    if(!(typeid(V) != typeid(Vector2) || typeid(V) != typeid(Vector3)))
    {
        return std::vector<Vertex>(0);
    }

    std::vector<Vertex> vertices = std::vector<Vertex>(6);

    vertices[0] = Vertex(a, color);
    vertices[1] = Vertex(b, color);
    vertices[2] = Vertex(c, color);

    shape[shape_index] = Vertex(a, color);
    shape[shape_index + 1] = Vertex(b, color);
    shape[shape_index + 2] = Vertex(c, color);

    return vertices;
};

Shared<Model> Square(float size, Color color)
{
    std::vector<Vertex> vertices = std::vector<Vertex>(6);
    vertices[0] = Vertex(Vector2(0, 0), color);
    vertices[1] = Vertex(Vector2(size, 0), color);
    vertices[2] = Vertex(Vector2(size, size), color);
    vertices[3] = Vertex(Vector2(0, 0), color);
    vertices[4] = Vertex(Vector2(0, size), color);
    vertices[5] = Vertex(Vector2(size, size), color);

    Shared<Model> square = CreateShared<Model>(vertices);
    return square;
}

std::vector<Vertex> Circle(float radius, int triangles, Color color, std::vector<Vertex>& shape, size_t shape_index)
{
    std::vector<Vertex> circle = std::vector<Vertex>(triangles * 3);
    Vector2 center = Vector2(0, 0);
    Vector2 first_point;
    Vector2 second_point;
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
}

//===============================================================================================================
Shared<Model> Cube(float size, Color color)
{
    std::vector<Vertex> vertices = std::vector<Vertex>(36);
    
    const Vector3 ORIGIN = Vector3(0, 0, 0);
    const Vector3 X = Vector3(size, 0, 0);
    const Vector3 Y = Vector3(0, size, 0);
    const Vector3 Z = Vector3(0, 0, size);
    const Vector3 XY = Vector3(size, size, 0);
    const Vector3 XZ = Vector3(size, 0, size);
    const Vector3 YZ = Vector3(0, size, size);
    const Vector3 XYZ = Vector3(size, size, size);
    
    //Front Side
    Triangle(ORIGIN, X, XY, color, vertices, 0);
    Triangle(ORIGIN, Y, XY, color, vertices, 3);
    
    //Back Side
    Triangle(Z, XZ, XYZ, color, vertices, 6);
    Triangle(Z, YZ, XYZ, color, vertices, 9);
    
    //Right Side
    Triangle(X, XZ, XYZ, color, vertices, 12);
    Triangle(X, XY, XYZ, color, vertices, 15);
    
    //Left Side
    Triangle(ORIGIN, Y, YZ, color, vertices, 18);
    Triangle(ORIGIN, Z, YZ, color, vertices ,21);

    //Top Side
    Triangle(Y, YZ, XYZ, color, vertices, 24);
    Triangle(Y, YZ, XYZ, color, vertices, 27);

    //Bottom Side
    Triangle(ORIGIN, Z, XZ, color, vertices, 30);
    Triangle(ORIGIN, X, XZ, color, vertices, 33);

    Shared<Model> square = CreateShared<Model>(vertices);
    return square;
}

Shared<Model> Prism(float x, float y, float z, Color color)
{
    std::vector<Vertex> vertices = std::vector<Vertex>(36);
    
    const Vector3 ORIGIN = Vector3(0, 0, 0);
    const Vector3 X = Vector3(x, 0, 0);
    const Vector3 Y = Vector3(0, y, 0);
    const Vector3 Z = Vector3(0, 0, z);
    const Vector3 XY = Vector3(x, y, 0);
    const Vector3 XZ = Vector3(x, 0, z);
    const Vector3 YZ = Vector3(0, y, z);
    const Vector3 XYZ = Vector3(x, y, z);
    
    //Front Side
    Triangle(ORIGIN, X, XY, color, vertices, 0);
    Triangle(ORIGIN, Y, XY, color, vertices, 3);
    
    //Back Side
    Triangle(Z, XZ, XYZ, color, vertices, 6);
    Triangle(Z, YZ, XYZ, color, vertices, 9);
    
    //Right Side
    Triangle(X, XZ, XYZ, color, vertices, 12);
    Triangle(X, XY, XYZ, color, vertices, 15);
    
    //Left Side
    Triangle(ORIGIN, Y, YZ, color, vertices, 18);
    Triangle(ORIGIN, Z, YZ, color, vertices ,21);

    //Top Side
    Triangle(Y, YZ, XYZ, color, vertices, 24);
    Triangle(Y, YZ, XYZ, color, vertices, 27);

    //Bottom Side
    Triangle(ORIGIN, Z, XZ, color, vertices, 30);
    Triangle(ORIGIN, X, XZ, color, vertices, 33);

    Shared<Model> prism = CreateShared<Model>(vertices);
    return prism;
}

Shared<Model> Pyramid4(Vector3 a, Vector3 b, Vector3 c, Vector3 d, Color color)
{
    std::vector<Vertex> vertices = std::vector<Vertex>(0);

    Triangle(a, b, c, color, vertices, 0);
    Triangle(a, b, d, color, vertices, 3);
    Triangle(a, c, d, color, vertices, 6);
    Triangle(b, c, d, color, vertices, 9);

    Shared<Model> pyramid = CreateShared<Model>(vertices);
    return pyramid;
}

Shared<Model> Cylinder(float radius, float height, int triangles, Color color)
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

    Shared<Model> cylinder = CreateShared<Model>(vertices);
    return cylinder;
}
#endif